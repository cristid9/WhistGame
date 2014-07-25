#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "gui.h"

/**
 * @brief The maximum number of games on which a player can play them in
 *        same time.
 */
#define MAX_GAMES 3

void *PlayWhistGame(void * a)
{
    return NULL;
}

int InitWhistGame(const char *name, int gameType, int noOfBots, int *noOfGames)
{
    ++*noOfGames;


    return EXIT_SUCCESS;
}

int StartWhistGame(const char *name, int gameType,
                   int botsNumber, struct Input *input)
{
    if (input == NULL || name == NULL)
        return EXIT_FAILURE;

    input->noOfGames++;
    
    struct Game *game = game_createGame(gameType);
    struct Player *player = player_createPlayer(name, 1);
    GtkWidget *windowTable;
    GtkWidget *fixedTable;
    GtkWidget *showScore;
    GtkWidget *trumpImage;
    GtkWidget *roundTypeLabel;
    GtkWidget *noOfBidsLabel;
    GtkWidget *buttonStart;
    struct Select *select;
    struct PlayerCards *playerCards;
    struct Card *card = deck_createCard(SPADES, 15);
    struct PlayersGUI *playersGUI;
    struct BidGUI *bidGUI;
    struct Click *click;

    click = gui_createClick(game, player);

    game_addPlayer(game, &player);
    for (int i = 1; i <= botsNumber; i++) {
        char no = (char)(((int)'0') + i);
        char name[7] = "robot";
        name[5] = no;
        name[6] = '\0';
        player = player_createPlayer(name, 0);
        game_addPlayer(game, &player);
    }
    game_createAndAddRounds(game);
    game_addPlayersInAllRounds(game);

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < MAX_GAME_PLAYERS; j++)
            if (game->rounds[i]->players[j] != NULL) {
                game->rounds[i]->bids[j] = j;
                game->rounds[i]->handsNumber[j] = j;
            }
        if (i > 0)
            round_copyScore(game->rounds[i - 1], game->rounds[i]);
        round_determinesScore(game->rounds[i]);
        game->currentRound = i;
        game_rewardsPlayersFromGame(game, game->currentRound);
    }

    gui_init(&windowTable, &fixedTable, "Whist", 798, 520);
    gui_setBackground(fixedTable, "pictures/table.png");
    gui_createButtonShowScore(fixedTable, &showScore, game);
    gui_initTrump(fixedTable, &trumpImage);
    gui_showTrump(card, trumpImage);
    playerCards = gui_initializePlayerCards(fixedTable);

    bidGUI = gui_createBidGUI();
    gui_initBidGUI(bidGUI, fixedTable);
    gui_showBidGUI(bidGUI, game->rounds[0], game->players[0]);

    select = gui_createSelect(fixedTable, game->players[0]);
    select->cardPlayerTurn = 1;
    select->bidPlayerTurn = 1;
    select->round = game->rounds[0];

    gtk_widget_add_events(windowTable, GDK_BUTTON_PRESS_MASK);
    gtk_widget_add_events(windowTable, GDK_POINTER_MOTION_MASK);
    g_signal_connect(G_OBJECT(windowTable), "motion-notify-event",
                     G_CALLBACK(gui_moveMouse), select);
    g_signal_connect(G_OBJECT(windowTable), "destroy",
                     G_CALLBACK(gui_closeWhistGame), input);
    g_signal_connect(G_OBJECT(windowTable), "button-press-event",
                     G_CALLBACK(gui_clickMouse), click);

    struct Deck *deck = deck_createDeck(game->playersNumber);
    deck_shuffleDeck(deck);
    round_distributeDeck(game->rounds[1], deck);
    qsort(game->players[0]->hand, game->rounds[1]->roundType,
          sizeof(struct Card*), player_compareCards);

    playersGUI = gui_createPlayersGUI();
    gui_showPlayers(game, fixedTable, playersGUI);

    gui_showPlayerCards(playerCards, game->players[0]);
    game->currentRound = 15;
    gui_showInformationsPlayers(playersGUI, game);

    game->currentRound = 0;
    game->rounds[game->currentRound]->hand = hand_createHand();
    round_addPlayersInHand(game->rounds[game->currentRound], 0);
    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        card = deck_createCard(i % 3, VALUES[i]);
        hand_addCard(game->rounds[game->currentRound]->hand,
                     game->rounds[game->currentRound]->hand->players[i],
                     &card);
    }
    struct CardsFromTable *cardsFromTable;
    cardsFromTable = gui_createCardsFromTable();
    gui_initCardsFromTable(cardsFromTable, fixedTable);
    gui_showCardsOnTable(cardsFromTable, game);

    gui_initRoundTypeLabel(&roundTypeLabel, fixedTable);
    gui_initNoOfBidsLabel(&noOfBidsLabel, fixedTable);

    gui_setRoundType(roundTypeLabel, game->rounds[0]);
    printf("%p\n", noOfBidsLabel);
    gui_setNoOfBids(noOfBidsLabel, game->rounds[0]);

    gui_createButtonStart(&buttonStart, fixedTable);

    gtk_main();

    game->players[0]->hand[0] = NULL;
    game->players[0]->hand[1] = NULL;
    game->players[0]->hand[2] = NULL;
    game->players[0]->hand[3] = NULL;
    gui_hidePlayerCards(playerCards);
    gui_showPlayerCards(playerCards, game->players[0]);
    //free(playerCards);
    //game_deleteGame(&game);
    //deck_deleteCard(&card);

    return EXIT_SUCCESS;
}

int getInput(GtkWidget *button, struct Input *input)
{
    if (input == NULL)
        return POINTER_NULL;

    const char *playerName = gtk_entry_get_text(GTK_ENTRY(input->name));
    if (player_checkPlayerName(playerName) != NO_ERROR) {
        gui_initAndShowDialogIncorrectName(input->mainWindow);
        return EXIT_FAILURE;
    }

    if (input->noOfGames >= MAX_GAMES) {
        gui_initAndShowDialogMaxGames(input->mainWindow);
        return EXIT_FAILURE;
    }


    int botsNumber = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON
                                                     (input->robotsNumber));
    int gameType;
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(input->gameType)))
        gameType = 1;
    else
        gameType = 8;

    StartWhistGame(playerName, gameType, botsNumber, input);

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *fixed;
    GtkWidget *labelName, *labelType, *labelNumber;
    GtkWidget *name;
    GtkWidget *radio1, *radio8;
    GtkWidget *spinNumber;
    GtkAdjustment *number;
    struct Input *input = malloc(sizeof(struct Input));
 
    gtk_init(&argc, &argv);

    gui_init(&window, &fixed, "Whist Game", 230, 200);
    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    gui_playerName(window, fixed, &labelName, &name);
    gui_gameType(window, fixed, &labelType, &radio1, &radio8);
    gui_noOfBots(window, fixed, &labelNumber, &spinNumber, &number);
    
    input->name         = name;
    input->robotsNumber = spinNumber;
    input->gameType     = radio1;
    input->mainWindow   = window;
    input->noOfGames    = 0;

    button = gtk_button_new_with_label("Start");
    gtk_fixed_put(GTK_FIXED(fixed), button, 100, 160);
    g_signal_connect(G_OBJECT(button), "clicked", 
                     G_CALLBACK(getInput), input);
    gtk_widget_show(button);

    gtk_main();

    free(input);

    return EXIT_SUCCESS;
}

