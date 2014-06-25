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

int gui_showScore(struct Game *game)
{
    printf("A\n");
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
        if (playerCards->event_box[i] != NULL) {
            gtk_widget_destroy(playerCards->event_box[i]);
            playerCards->event_box[i] = NULL;
        }
    }

    return NO_ERROR;
}

int gui_clickCard0()
{
    gtk_main_quit();
    printf("%d\n", 0);
    return 0;
}

int gui_clickCard1()
{
    printf("%d\n", 1);
    return 0;
}


int gui_clickCard2()
{
    printf("%d\n", 2);
    return 0;
}

int gui_clickCard3()
{
    printf("%d\n", 3);
    return 0;
}

int gui_clickCard4()
{
    printf("%d\n", 4);
    return 0;
}

int gui_clickCard5()
{
    printf("%d\n", 5);
    return 0;
}

int gui_clickCard6()
{
    printf("%d\n", 6);
    return 0;
}

int gui_clickCard7()
{
    printf("%d\n", 7);
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
    if (player->hand[0] != NULL) {
        char pictureName[10] = { '\0' };
        gui_getPictureName(player->hand[0], pictureName);
        char pathImage[30] = "pictures/80x110/";
        strcat(pathImage, pictureName);
        playerCards->images[0] = gtk_image_new_from_file(pathImage);
        playerCards->event_box[0] = gtk_event_box_new();
        gtk_container_add(GTK_CONTAINER(playerCards->event_box[0]), 
                          playerCards->images[0]);
        gtk_fixed_put(GTK_FIXED(fixed), playerCards->event_box[0],
                     10 + noOfCards * 90, 400);
        gtk_widget_show(playerCards->event_box[0]);
        gtk_widget_show(playerCards->images[0]);
        g_signal_connect(G_OBJECT(playerCards->event_box[0]),
                        "button_press_event", G_CALLBACK(gui_clickCard0), NULL);
        noOfCards++;
    }
    if (player->hand[1] != NULL) {
        char pictureName[10] = {'\0'};
        gui_getPictureName(player->hand[1], pictureName);
        char pathImage[30] = "pictures/80x110/";
        strcat(pathImage, pictureName);
        playerCards->images[1] = gtk_image_new_from_file(pathImage);
        playerCards->event_box[1] = gtk_event_box_new();
        gtk_container_add(GTK_CONTAINER(playerCards->event_box[1]), 
                          playerCards->images[1]);
        gtk_fixed_put(GTK_FIXED(fixed), playerCards->event_box[1],
                      10 + noOfCards * 90, 400);
        gtk_widget_show(playerCards->event_box[1]);
        gtk_widget_show(playerCards->images[1]);
        g_signal_connect(G_OBJECT(playerCards->event_box[1]),
                        "button_press_event", G_CALLBACK(gui_clickCard1), NULL);
        noOfCards++;
    }
    if (player->hand[2] != NULL) {
        char pictureName[10] = {'\0'};
        gui_getPictureName(player->hand[2], pictureName);
        char pathImage[30] = "pictures/80x110/";
        strcat(pathImage, pictureName);
        playerCards->images[2] = gtk_image_new_from_file(pathImage);
        playerCards->event_box[2] = gtk_event_box_new();
        gtk_container_add(GTK_CONTAINER(playerCards->event_box[2]), 
                          playerCards->images[2]);
        gtk_fixed_put(GTK_FIXED(fixed), playerCards->event_box[2],
                     10 + noOfCards * 90, 400);
        gtk_widget_show(playerCards->event_box[2]);
        gtk_widget_show(playerCards->images[2]);
        g_signal_connect(G_OBJECT(playerCards->event_box[2]),
                        "button_press_event", G_CALLBACK(gui_clickCard2), NULL);
        noOfCards++;
    }
    if (player->hand[3] != NULL) {
        char pictureName[10] = {'\0'};
        gui_getPictureName(player->hand[3], pictureName);
        char pathImage[30] = "pictures/80x110/";
        strcat(pathImage, pictureName);
        playerCards->images[3] = gtk_image_new_from_file(pathImage);
        playerCards->event_box[3] = gtk_event_box_new();
        gtk_container_add(GTK_CONTAINER(playerCards->event_box[3]), 
                          playerCards->images[3]);
        gtk_fixed_put(GTK_FIXED(fixed), playerCards->event_box[3],
                     10 + noOfCards * 90, 400);
        gtk_widget_show(playerCards->event_box[3]);
        gtk_widget_show(playerCards->images[3]);
        g_signal_connect(G_OBJECT(playerCards->event_box[3]),
                        "button_press_event", G_CALLBACK(gui_clickCard3), NULL);
        noOfCards++;
    }
    if (player->hand[4] != NULL) {
        char pictureName[10] = {'\0'};
        gui_getPictureName(player->hand[4], pictureName);
        char pathImage[30] = "pictures/80x110/";
        strcat(pathImage, pictureName);
        playerCards->images[4] = gtk_image_new_from_file(pathImage);
        playerCards->event_box[4] = gtk_event_box_new();
        gtk_container_add(GTK_CONTAINER(playerCards->event_box[4]), 
                          playerCards->images[4]);
        gtk_fixed_put(GTK_FIXED(fixed), playerCards->event_box[4],
                     10 + noOfCards * 90, 400);
        gtk_widget_show(playerCards->event_box[4]);
        gtk_widget_show(playerCards->images[4]);
        g_signal_connect(G_OBJECT(playerCards->event_box[4]),
                        "button_press_event", G_CALLBACK(gui_clickCard4), NULL);
        noOfCards++;
    }
    if (player->hand[5] != NULL) {
        char pictureName[10] = {'\0'};
        gui_getPictureName(player->hand[5], pictureName);
        char pathImage[30] = "pictures/80x110/";
        strcat(pathImage, pictureName);
        playerCards->images[5] = gtk_image_new_from_file(pathImage);
        playerCards->event_box[5] = gtk_event_box_new();
        gtk_container_add(GTK_CONTAINER(playerCards->event_box[5]), 
                          playerCards->images[5]);
        gtk_fixed_put(GTK_FIXED(fixed), playerCards->event_box[5],
                     10 + noOfCards * 90, 400);
        gtk_widget_show(playerCards->event_box[5]);
        gtk_widget_show(playerCards->images[5]);
        g_signal_connect(G_OBJECT(playerCards->event_box[5]),
                        "button_press_event", G_CALLBACK(gui_clickCard5), NULL);
        noOfCards++;
    }
    if (player->hand[6] != NULL) {
        char pictureName[10] = {'\0'};
        gui_getPictureName(player->hand[6], pictureName);
        char pathImage[30] = "pictures/80x110/";
        strcat(pathImage, pictureName);
        playerCards->images[6] = gtk_image_new_from_file(pathImage);
        playerCards->event_box[6] = gtk_event_box_new();
        gtk_container_add(GTK_CONTAINER(playerCards->event_box[6]), 
                          playerCards->images[6]);
        gtk_fixed_put(GTK_FIXED(fixed), playerCards->event_box[6],
                     10 + noOfCards * 90, 400);
        gtk_widget_show(playerCards->event_box[6]);
        gtk_widget_show(playerCards->images[6]);
        g_signal_connect(G_OBJECT(playerCards->event_box[6]),
                        "button_press_event", G_CALLBACK(gui_clickCard6), NULL);
        noOfCards++;
    }
    if (player->hand[7] != NULL) {
        char pictureName[10] = {'\0'};
        gui_getPictureName(player->hand[7], pictureName);
        char pathImage[30] = "pictures/80x110/";
        strcat(pathImage, pictureName);
        playerCards->images[7] = gtk_image_new_from_file(pathImage);
        playerCards->event_box[7] = gtk_event_box_new();
        gtk_container_add(GTK_CONTAINER(playerCards->event_box[7]), 
                          playerCards->images[7]);
        gtk_fixed_put(GTK_FIXED(fixed), playerCards->event_box[7],
                     10 + noOfCards * 90, 400);
        gtk_widget_show(playerCards->event_box[7]);
        gtk_widget_show(playerCards->images[7]);
        g_signal_connect(G_OBJECT(playerCards->event_box[7]),
                        "button_press_event", G_CALLBACK(gui_clickCard7), NULL);
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
    gtk_widget_hide_on_delete(windowTable);

    return NO_ERROR;
}

