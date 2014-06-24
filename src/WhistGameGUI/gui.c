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
            char pictureName[10] = {'\0'};
            gui_getPictureName(player->hand[i], pictureName);
            char pathImage[30] = "pictures/80x110/";
            strcat(pathImage, pictureName);
            playerCards->images[i] = gtk_image_new_from_file(pathImage);
            playerCards->event_box[i] = gtk_event_box_new();
            gtk_container_add(GTK_CONTAINER(playerCards->event_box[i]), 
                              playerCards->images[i]);
            gtk_fixed_put(GTK_FIXED(fixed), playerCards->event_box[i],
                          10 + noOfCards * 90, 400);
            gtk_widget_show(playerCards->event_box[i]);
            gtk_widget_show(playerCards->images[i]);
            noOfCards++;
        }

    return NO_ERROR;
}

