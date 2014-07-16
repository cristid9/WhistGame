/**
 * @file gui.c
 * @brief In this file are defined functions used for GUI.
 */

#include "gui.h"

#include <string.h>

int gui_init(GtkWidget **window, GtkWidget **fixed, char *title, 
             int width, int height)
{
    if (window == NULL || fixed == NULL || title == NULL)
        return POINTER_NULL;

    *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable(GTK_WINDOW(*window), FALSE);
    gtk_widget_set_size_request(*window, width, height);
    gtk_window_set_position(GTK_WINDOW(*window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(*window), title);
    *fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(*window), *fixed);
    gtk_widget_show(*fixed);
    gtk_widget_show(*window);

    return NO_ERROR;
}

int gui_noOfBots(GtkWidget *window, GtkWidget *fixed, GtkWidget **label,
                 GtkWidget **spinNumber, GtkAdjustment **number)
{
    if (window == NULL || fixed == NULL || label == NULL ||
        number == NULL || spinNumber == NULL)
        return POINTER_NULL;

    *label = gtk_label_new("Choose the robots number");
    gtk_fixed_put(GTK_FIXED(fixed), *label, 10, 110);
    gtk_widget_show(*label);

    *number = GTK_ADJUSTMENT(gtk_adjustment_new(2.0, 2.0, 5.0, 1.0, 0.0, 0.0));
    *spinNumber = gtk_spin_button_new(*number, 1.0, 0);
    gtk_fixed_put(GTK_FIXED(fixed), *spinNumber, 10, 130);
    gtk_widget_show(*spinNumber);

    return NO_ERROR;
}

int gui_playerName(GtkWidget *window, GtkWidget *fixed,
                   GtkWidget **label, GtkWidget **name)
{
    if (window == NULL || fixed == NULL || label == NULL || name == NULL)
        return POINTER_NULL;

    *label = gtk_label_new("Name ");
    gtk_fixed_put(GTK_FIXED(fixed), *label, 10, 15);
    gtk_widget_show(*label);

    *name = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(*name), 10);
    gtk_fixed_put(GTK_FIXED(fixed), *name, 50, 10);
    gtk_widget_show(*name);

    return NO_ERROR;
}

int gui_gameType(GtkWidget *window, GtkWidget *fixed, GtkWidget **label,
                 GtkWidget **radio1, GtkWidget **radio8)
{
    if (window == NULL || fixed == NULL || label == NULL
         || radio1 == NULL || radio8 == NULL)
        return POINTER_NULL;

    *label = gtk_label_new("Choose the game type");
    gtk_fixed_put(GTK_FIXED(fixed), *label, 10, 40);
    gtk_widget_show(*label);

    *radio1 = gtk_radio_button_new_with_label(NULL, "11-88-11");
    *radio8 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(*radio1), "88-11-88");
    gtk_fixed_put(GTK_FIXED(fixed), *radio1, 10, 60);
    gtk_fixed_put(GTK_FIXED(fixed), *radio8, 10, 85);
    gtk_widget_show(*radio1);
    gtk_widget_show(*radio8);

    return NO_ERROR;
}

int gui_setBackground(GtkWidget *fixed, char *pathPicture)
{
    if (fixed == NULL || pathPicture == NULL)
        return POINTER_NULL;

    GtkWidget *image = gtk_image_new_from_file(pathPicture);
    gtk_fixed_put(GTK_FIXED(fixed), image, 0, 0);
    gtk_widget_show(image);

    return NO_ERROR;
}

//Helpful function for gui_drawScore().
int intToChar(int number, char *string)
{
    int i, copy, j;
    char ch;

    if ((copy = number) < 0)
        number = -number;

    i = 0;
    do {
        string[i++] = number % 10 + '0';
    } while ((number /= 10) > 0);

    if (copy < 0)
        string[i++] = '-';
    string[i] = '\0';

    for (i = 0, j = strlen(string) - 1; i < j; i++, j--) {
        ch = string[i];
        string[i] = string[j];
        string[j] = ch;
    }

    return NO_ERROR;
}

gboolean gui_drawScore(GtkWidget *button, GdkEventExpose *event,
                       struct Game *game)
{
    GdkGC *gc;
    GdkColor color;
    GdkWindow *window;
    GdkFont *font;

    window = button->window;
    font = gdk_font_load("-*-fixed-bold-r-normal--*-120-*-*-*-*-iso8859-1");
    gc = gdk_gc_new(window);

    int noOfPlayers = 0;
    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (game->players[i] != NULL) {
            gdk_draw_text(window, font, gc, 19 + 80 * noOfPlayers, 14,
                          game->players[i]->name,
                          strlen(game->players[i]->name));
            noOfPlayers++;
        }

    int position;
    for (int i = 0; i < MAX_GAME_ROUNDS; i++)
        if (game->rounds[i] != NULL) {
            gdk_color_parse("black", &color);
            gdk_gc_set_rgb_fg_color(gc, &color);
            char type[2] = { '\0' };
            type[0] = '0' + game->rounds[i]->roundType;
            gdk_draw_text(window, font, gc, 5, 28 + i * 16, type, strlen(type));

            if (i < game->currentRound)
                for (int j = 0; j < MAX_GAME_PLAYERS; j++) {
                    position = game_getPlayerPosition
                               (game, game->rounds[i]->players[j]);

                    if (position < 0 )
                        continue;

                    char score[4] = { '\0' };
                    char bids[2]  = { '\0' };
                    intToChar(game->rounds[i]->pointsNumber[j], score);
                    intToChar(game->rounds[i]->bids[j], bids);

                    if (game->rounds[i]->bids[j] ==
                        game->rounds[i]->handsNumber[j])
                        gdk_color_parse("green", &color);
                    else
                        gdk_color_parse("red", &color);

                    gdk_gc_set_rgb_fg_color(gc, &color);
                    gdk_draw_text(window, font, gc, 3 + 80 * (position + 1),
                                  28 + i * 16, bids, strlen(bids));

                    if (game->rounds[i]->bonus[j] == 1)
                        gdk_color_parse("green", &color);
                    if (game->rounds[i]->bonus[j] == 2)
                        gdk_color_parse("red", &color);
                    if (game->rounds[i]->bonus[j] == 0)
                        gdk_color_parse("black", &color);
                    gdk_gc_set_rgb_fg_color(gc, &color);
                    gdk_draw_text(window, font, gc, 37 + 80 * position,
                                  28 + i * 16, score, strlen(score));
                }

            if (i == game->currentRound)
                for (int j = 0; j < MAX_GAME_PLAYERS; j++) {
                    position = game_getPlayerPosition
                               (game, game->rounds[i]->players[j]);

                    if (position < 0)
                        continue;

                    char bids[2] = { '\0' };
                    intToChar(game->rounds[i]->bids[j], bids);

                    gdk_color_parse("black", &color);
                    gdk_gc_set_rgb_fg_color(gc, &color);
                    gdk_draw_text(window, font, gc, 3 + 80 * (position + 1),
                                  28 + i * 16, bids, strlen(bids));
                }
        }

    return TRUE;
}

int gui_showScore(GtkWidget *button, struct Game *game)
{
    GtkWidget *window, *helpfulButton;
    GtkWidget *fixed;

    gui_init(&window, &fixed, "Score", 496, 500);
    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gui_setBackground(fixed, "pictures/score.png");

    // I used helpfulButton to can draw the score. Other method I didn't
    // found when I written this code.
    helpfulButton = gtk_button_new_with_label("AAAAAAAAAAAA");
    gtk_fixed_put(GTK_FIXED(fixed), helpfulButton, 150, 150);
    gtk_widget_show(helpfulButton);
    g_signal_connect(G_OBJECT(helpfulButton), "expose-event",
                     G_CALLBACK(gui_drawScore), game);

    gtk_main();

    return NO_ERROR;
}

int gui_createButtonShowScore(GtkWidget *fixed, GtkWidget **showScore,
                              struct Game *game)
{
    if (fixed == NULL)
        return POINTER_NULL;

    *showScore = gtk_button_new_with_label("Show score");
    gtk_fixed_put(GTK_FIXED(fixed), *showScore, 620, 50);
    gtk_widget_show(*showScore);
    g_signal_connect(G_OBJECT(*showScore), "clicked",
                     G_CALLBACK(gui_showScore), game);
    
    return NO_ERROR;
}

int gui_getPictureName(struct Card *card, char *name)
{
    if (card == NULL)
        return CARD_NULL;
    if (name == NULL)
        return POINTER_NULL;

    char suit[2] = {'\0'};
    switch(card->suit) {
        case DIAMONDS:
            suit[0] = 'D';
            break;
        case CLUBS:
            suit[0] = 'C';
            break;
        case HEARTS:
            suit[0] = 'B';
            break;
        case SPADES:
            suit[0] = 'A';
            break;
        case SuitEnd:
            break;
        }
    char value[3] = {'\0'};
    if (card->value > 9) {
        value[0] = (char)(((int)'0') + card->value / 10);
        value[1] = (char)(((int)'0') + card->value % 10);
    } else {
        value[0] = (char)(((int)'0') + card->value);
    }
    strcpy(name, value);
    strcat(name, suit);
    strcat(name, ".jpg");
    
    return NO_ERROR;
}

int gui_initTrump(GtkWidget *fixed, GtkWidget **image)
{
    if (fixed == NULL || image == NULL)
        return POINTER_NULL;

    *image = gtk_image_new();
    gtk_fixed_put(GTK_FIXED(fixed), *image, 45, 15);

    return NO_ERROR;
}

int gui_hideTrump(GtkWidget *image)
{
    if (image == NULL)
        return POINTER_NULL;

    gtk_widget_hide(image);

    return 0;
}

int gui_showTrump(struct Card *trump, GtkWidget *image)
{
    if (image == NULL)
        return POINTER_NULL;

    char pathTrump[30] = "pictures/45x60/";
    if (trump == NULL)
        strcat(pathTrump, "45x60.jpg");
    else {
        char pictureName[7];
        gui_getPictureName(trump, pictureName);
        strcat(pathTrump, pictureName);
    }

    gtk_image_set_from_file(GTK_IMAGE(image), pathTrump);
    gtk_widget_show(image);

    return NO_ERROR;
}

int gui_deletePlayerCards(struct PlayerCards **playerCards)
{
    if (playerCards == NULL || *playerCards == NULL)
        return POINTER_NULL;

    free(*playerCards);
    *playerCards = NULL;

    return NO_ERROR;
}

struct PlayerCards *gui_initializePlayerCards(GtkWidget *fixed)
{
    if (fixed == NULL)
        return NULL;

    struct PlayerCards *playerCards = malloc(sizeof(struct PlayerCards));

    for (int i = 0; i < MAX_CARDS; i++) {
        playerCards->images[i] = gtk_image_new();
        gtk_fixed_put(GTK_FIXED(fixed), playerCards->images[i],
                      10 + i * 90, 400);
    }
    
    return playerCards;
}

int gui_hidePlayerCards(struct PlayerCards *playerCards)
{
    if (playerCards == NULL)
        return POINTER_NULL;

    for (int i = 0; i < MAX_CARDS; i++) {
        gtk_widget_hide(playerCards->images[i]);
    }

    return 0;
}

int gui_showPlayerCards(struct PlayerCards *playerCards, GtkWidget *fixed,
                        struct Player *player)
{
    if (playerCards == NULL || fixed == NULL)
        return POINTER_NULL;
    if (player == NULL)
        return PLAYER_NULL;

    int noOfCards = 0;
    for (int i = 0; i < MAX_CARDS; i++)
        if (player->hand[i] != NULL) {
            char pictureName[10] = { '\0' };
            gui_getPictureName(player->hand[i], pictureName);
            char pathImage [30] = "pictures/80x110/";
            strcat(pathImage, pictureName);
            gtk_image_set_from_file(GTK_IMAGE(playerCards->images[noOfCards]),
                                    pathImage);
            gtk_widget_show(playerCards->images[noOfCards]);
            noOfCards++;
        }

    return NO_ERROR;
}

int gui_initAndShowDialogIncorrectName(GtkWidget *window)
{
    if (window == NULL)
        return POINTER_NULL;

    GtkWidget *dialog, *image, *label, *hbox;

    dialog = gtk_dialog_new_with_buttons("Error", GTK_WINDOW(window),
                                         GTK_DIALOG_MODAL, GTK_STOCK_OK,
                                         GTK_RESPONSE_OK, NULL);
    gtk_dialog_set_has_separator(GTK_DIALOG(dialog), FALSE);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);

    label = gtk_label_new("The name must contain at least 5 characters\n and must begin with a letter.");
    image = gtk_image_new_from_stock(GTK_STOCK_DIALOG_ERROR,
                                     GTK_ICON_SIZE_DIALOG);
    hbox = gtk_hbox_new(FALSE, 5);
    gtk_container_set_border_width(GTK_CONTAINER(hbox), 10);
    gtk_box_pack_start_defaults(GTK_BOX(hbox), image);
    gtk_box_pack_start_defaults(GTK_BOX(hbox), label);

    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox);
    gtk_widget_show_all(dialog);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    return NO_ERROR;
}

int gui_initAndShowDialogMaxGames(GtkWidget *window)
{
    if (window == NULL)
        return POINTER_NULL;

    GtkWidget *dialog, *image, *label, *hbox;

    dialog = gtk_dialog_new_with_buttons("Error", GTK_WINDOW(window),
                                         GTK_DIALOG_MODAL, GTK_STOCK_OK,
                                         GTK_RESPONSE_OK, NULL);
    gtk_dialog_set_has_separator(GTK_DIALOG(dialog), FALSE);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);

    label = gtk_label_new("Already exist too much open games.");
    image = gtk_image_new_from_stock(GTK_STOCK_DIALOG_ERROR,
                                     GTK_ICON_SIZE_DIALOG);
    hbox = gtk_hbox_new(FALSE, 5);
    gtk_container_set_border_width(GTK_CONTAINER(hbox), 10);
    gtk_box_pack_start_defaults(GTK_BOX(hbox), image);
    gtk_box_pack_start_defaults(GTK_BOX(hbox), label);

    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox);
    gtk_widget_show_all(dialog);

    gtk_dialog_run(GTK_DIALOG(dialog)); 
    gtk_widget_destroy(dialog);

    return NO_ERROR;
}

int gui_closeWhistGame(GtkWidget *windowTable, struct Input *input)
{
    if (windowTable == NULL)
        return POINTER_NULL;

    input->noOfGames--;
    gtk_widget_destroy(windowTable);
    gtk_main_quit();

    return NO_ERROR;
}

int gui_getCardId(int x, int y)
{
    int cardPosition = -1;
    if (y >= 400 && y <= 510) {
        for (int i = 0; i < MAX_CARDS; i++)
            if (x >= (10 + 90 * i) && x <= (90 + 90 * i))
                cardPosition = i;
    }

    return cardPosition;
}

int gui_clickMouse(GtkWidget *window, GdkEvent *event)
{
    if (window == NULL || event == NULL)
        return POINTER_NULL;

    int x = (int)((GdkEventButton*)event)->x;
    int y = (int)((GdkEventButton*)event)->y;

    int cardPosition = gui_getCardId(x, y);

    return NO_ERROR;
}

struct SelectedCard *gui_createSelectedCard(GtkWidget *fixed, struct Game *game,
                                            struct Player *player, int roundId)
{
    struct SelectedCard *selectedCard;
    
    selectedCard = malloc(sizeof(struct SelectedCard));
    selectedCard->imageSelectedCard = gtk_image_new_from_file
                                      ("pictures/select_card.png"); 
    selectedCard->fixed   = fixed;
    selectedCard->game    = game;
    selectedCard->player  = player;
    selectedCard->roundId = roundId;

    gtk_fixed_put(GTK_FIXED(fixed), selectedCard->imageSelectedCard, 10, 400);

    return selectedCard;
}

int gui_selectedCard(GtkWidget *window, GdkEvent *event,
                     struct SelectedCard *selectedCard)
{
    if (selectedCard == NULL)
        return POINTER_NULL;
    if (selectedCard->fixed == NULL || selectedCard->imageSelectedCard == NULL)
        return POINTER_NULL;

    int x = (int)((GdkEventButton*)event)->x;
    int y = (int)((GdkEventButton*)event)->y;

    int cardId = gui_getCardId(x, y);
    if (cardId != -1 && selectedCard->player->hand[cardId] != NULL) {
        gtk_fixed_move(GTK_FIXED(selectedCard->fixed),
                       selectedCard->imageSelectedCard,
                       10 + 90 * cardId, 400);
        gtk_widget_show(selectedCard->imageSelectedCard);
    } else {
        gtk_widget_hide(selectedCard->imageSelectedCard);
    }

    return NO_ERROR;
}

struct PlayersGUI *gui_createPlayersGUI()
{
    struct PlayersGUI *playersGUI = malloc(sizeof(struct PlayersGUI));

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        playersGUI->image[i]      = NULL;
        playersGUI->nameLabel[i]  = NULL;
        playersGUI->bidsLabel[i]  = NULL;
        playersGUI->tookLabel[i]  = NULL;
        playersGUI->scoreLabel[i] = NULL;
    }

    return playersGUI;
}

int gui_showPlayers(struct Game *game, GtkWidget *fixed,
                    struct PlayersGUI *playersGUI)
{
    if (game == NULL || fixed == NULL || playersGUI == NULL)
        return POINTER_NULL;

    int coordinates[MAX_GAME_PLAYERS][2] = { {25 ,275}, 
                                             {25 ,145}, 
                                             {225 ,15}, 
                                             {425 ,15}, 
                                             {625 ,145}, 
                                             {625 ,275} };

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        if (game->players[i] != NULL) {
            playersGUI->image[i] = gtk_image_new_from_file
                                   ("pictures/player.png");
            gtk_fixed_put(GTK_FIXED(fixed), playersGUI->image[i],
                          coordinates[i][0], coordinates[i][1]);
            gtk_widget_show(playersGUI->image[i]);

            playersGUI->nameLabel[i] = gtk_label_new(game->players[i]->name);
            gtk_fixed_put(GTK_FIXED(fixed), playersGUI->nameLabel[i],
                          coordinates[i][0] + 8, coordinates[i][1] + 5);
            gtk_widget_show(playersGUI->nameLabel[i]);

            playersGUI->bidsLabel[i] = gtk_label_new("0");
            gtk_fixed_put(GTK_FIXED(fixed), playersGUI->bidsLabel[i],
                          coordinates[i][0] + 44, coordinates[i][1] + 53);
            gtk_widget_show(playersGUI->bidsLabel[i]);

            playersGUI->tookLabel[i] = gtk_label_new("0");
            gtk_fixed_put(GTK_FIXED(fixed), playersGUI->tookLabel[i],
                          coordinates[i][0] + 48, coordinates[i][1] + 81);
            gtk_widget_show(playersGUI->tookLabel[i]);
            
            playersGUI->scoreLabel[i] = gtk_label_new("0");
            gtk_fixed_put(GTK_FIXED(fixed), playersGUI->scoreLabel[i],
                          coordinates[i][0] + 53, coordinates[i][1] + 28);
            gtk_widget_show(playersGUI->scoreLabel[i]);
        }
    }

    return NO_ERROR;
}

int gui_showInformationsPlayers(struct PlayersGUI *playersGUI,
                                struct Game *game)
{
    if (game == NULL)
        return GAME_NULL;
    if (game->rounds[game->currentRound] == NULL)
        return ROUND_NULL;
    if (playersGUI == NULL)
        return POINTER_NULL;

    struct Round *round = game->rounds[game->currentRound];
    char text[4] = { '\0' };

    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (game->players[i] != NULL) {
            int position = round_getPlayerId(round, game->players[i]);
            if (position < 0)
                return position;

            intToChar(round->bids[position], text);
            gtk_label_set_text(GTK_LABEL(playersGUI->bidsLabel[i]), text);

            intToChar(round->handsNumber[position], text);
            gtk_label_set_text(GTK_LABEL(playersGUI->tookLabel[i]), text);

            intToChar(round->pointsNumber[position], text);
            gtk_label_set_text(GTK_LABEL(playersGUI->scoreLabel[i]), text);
        }

    return NO_ERROR;
}

struct CardsFromTable *gui_createCardsFromTable()
{
    struct CardsFromTable *cardsFromTable;
    cardsFromTable = malloc(sizeof(struct CardsFromTable));

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        cardsFromTable->images[i] = NULL;
    }

    return cardsFromTable;
}

int gui_deleteCardsFromTable(struct CardsFromTable **cardsFromTable)
{
    if (cardsFromTable == NULL || *cardsFromTable == NULL)
        return POINTER_NULL;

    free(*cardsFromTable);
    *cardsFromTable = NULL;

    return NO_ERROR;
}

int gui_initCardsFromTable(struct CardsFromTable *cardsFromTable,
                           GtkWidget *fixed)
{
    if (cardsFromTable == NULL || fixed == NULL)
        return POINTER_NULL;

    int coordinates[MAX_GAME_PLAYERS][2] = { {210, 295},
                                             {210, 165},
                                             {277, 140},
                                             {477, 140},
                                             {545, 165},
                                             {545, 285} };

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        cardsFromTable->images[i] = gtk_image_new();
        gtk_fixed_put(GTK_FIXED(fixed), cardsFromTable->images[i],
                      coordinates[i][0], coordinates[i][1]);
    }

    return NO_ERROR;
}

int gui_hideCardsFromTable(struct CardsFromTable *cardsFromTable)
{
    if (cardsFromTable == NULL)
        return POINTER_NULL;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        gtk_widget_hide(cardsFromTable->images[i]);
    }

    return NO_ERROR;
}

int gui_showCardsOnTable(struct CardsFromTable *cardsFromTable,
                         struct Game *game)
{
    if (game == NULL)
        return GAME_NULL;
    if (cardsFromTable == NULL)
        return POINTER_NULL;

    struct Hand *hand = game->rounds[game->currentRound]->hand;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (game->players[i] != NULL) {
            int position = hand_getPlayerId(hand, game->players[i]);
            if (position < 0)
                return position;
            if (hand->cards[position] != NULL) {    
                char pictureName[10] = { '\0' };
                gui_getPictureName(hand->cards[position], pictureName);
                char pathImage [30] = "pictures/45x60/";
                strcat(pathImage, pictureName);
                gtk_image_set_from_file(GTK_IMAGE(cardsFromTable->images[i]),
                                        pathImage);
                gtk_widget_show(cardsFromTable->images[i]);
            }
        }

    return NO_ERROR;
}

int gui_deletePlayersGUI(struct PlayersGUI **playersGUI)
{
    if (playersGUI == NULL || *playersGUI == NULL)
        return POINTER_NULL;

    free(*playersGUI);
    *playersGUI = NULL;

    return NO_ERROR;
}

int gui_deleteSelectedCard(struct SelectedCard **selectedCard)
{
    if (selectedCard == NULL || *selectedCard == NULL)
        return POINTER_NULL;

    free(*selectedCard);
    *selectedCard = NULL;

    return NO_ERROR;
}

int gui_deleteInput(struct Input **input)
{
    if (input == NULL || *input == NULL)
        return POINTER_NULL;

    free(*input);
    *input = NULL;

    return NO_ERROR;
}

int gui_initRoundTypeLabel(GtkWidget **roundTypeLabel, GtkWidget *fixed)
{
    if (*roundTypeLabel == NULL || roundTypeLabel == NULL || fixed == NULL)
        return POINTER_NULL;

    GdkColor color;
    gdk_color_parse("black", &color);

    *roundTypeLabel = gtk_label_new("1 ");
    gtk_fixed_put(GTK_FIXED(fixed), *roundTypeLabel, 700, 12);
    gtk_widget_modify_fg(*roundTypeLabel, GTK_STATE_NORMAL, &color);
    gtk_widget_show(*roundTypeLabel);

    return NO_ERROR;
}

int gui_initNoOfBidsLabel(GtkWidget **noOfBidsLabel, GtkWidget *fixed)
{
    if (*noOfBidsLabel == NULL || noOfBidsLabel == NULL || fixed == NULL)
        return POINTER_NULL;

    GdkColor color;
    gdk_color_parse("black", &color);

    *noOfBidsLabel = gtk_label_new("1 ");
    gtk_fixed_put(GTK_FIXED(fixed), *noOfBidsLabel, 655, 29);
    gtk_widget_modify_fg(*noOfBidsLabel, GTK_STATE_NORMAL, &color);
    gtk_widget_show(*noOfBidsLabel);

    return NO_ERROR;
}

