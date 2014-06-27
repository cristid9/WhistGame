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
                 GtkWidget **radio1, GtkWidget **radio8, GtkWidget **vbox)
{
    if (window == NULL || fixed == NULL || label == NULL || radio1 == NULL ||
        radio8 == NULL || vbox == NULL)
        return POINTER_NULL;

    *label = gtk_label_new("Choose the game type");
    gtk_fixed_put(GTK_FIXED(fixed), *label, 10, 40);
    gtk_widget_show(*label);

    *radio1 = gtk_radio_button_new_with_label(NULL, "11-88-11");
    *radio8 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(*radio1), "88-11-88");
    gtk_widget_show(*radio1);
    gtk_widget_show(*radio8);

    *vbox = gtk_vbox_new(FALSE, 5);
    gtk_box_pack_start_defaults(GTK_BOX(*vbox), *radio1);
    gtk_box_pack_start_defaults(GTK_BOX(*vbox), *radio8);
    gtk_fixed_put(GTK_FIXED(fixed), *vbox, 10, 60);
    gtk_widget_show(*vbox);

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

int gui_showScore(GtkWidget *button, struct Game *game)
{
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

int gui_destroyTrump(GtkWidget **image)
{
    if (image == NULL)
        return POINTER_NULL;

    gtk_widget_destroy(*image);

    return NO_ERROR;
}

int gui_showTrump(GtkWidget *fixed, struct Card *trump, GtkWidget **image)
{
    if (fixed == NULL || image == NULL)
        return POINTER_NULL;

    char pathTrump[30] = "pictures/45x60/";
    if (trump == NULL)
        strcat(pathTrump, "45x60.jpg");
    else {
        char pictureName[7];
        gui_getPictureName(trump, pictureName);
        strcat(pathTrump, pictureName);
    }

    *image = gtk_image_new_from_file(pathTrump);
    gtk_fixed_put(GTK_FIXED(fixed), *image, 45, 15);
    gtk_widget_show(*image);

    return NO_ERROR;
}

int gui_destroyPlayerCards(struct PlayerCards *playerCards)
{
    if (playerCards == NULL)
        return POINTER_NULL;

    for (int i = 0; i < MAX_CARDS; i++) {
        if (playerCards->images[i] != NULL) {
            gtk_widget_destroy(playerCards->images[i]);
            playerCards->images[i] = NULL;
        }
    }

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

struct SelectedCard *gui_createSelectedCard(GtkWidget *fixed)
{
    struct SelectedCard *selectedCard;
    
    selectedCard = malloc(sizeof(struct SelectedCard));
    selectedCard->imageSelectedCard = gtk_image_new_from_file
                                      ("pictures/select_card.png"); 
    selectedCard->fixed = fixed;

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
    if (cardId != -1) {
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
        playersGUI->image[i]     = NULL;
        playersGUI->nameLabel[i] = NULL;
        playersGUI->bidsLabel[i] = NULL;
        playersGUI->tookLabel[i] = NULL;
    }

    return playersGUI;
}

int gui_showPlayers(struct Game *game, GtkWidget *fixed,
                    struct PlayersGUI *playersGUI)
{
    if (game == NULL || fixed == NULL || playersGUI == NULL)
        return POINTER_NULL;

    int coordinates[6][2] = { {25 ,275}, 
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
                          coordinates[i][0] + 57, coordinates[i][1] + 20);
            gtk_widget_show(playersGUI->nameLabel[i]);
        }
    }

    return NO_ERROR;
}

