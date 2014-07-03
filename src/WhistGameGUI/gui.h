/**
 * @file gui.h
 * @brief In this file are declared the functions used at GUI.
 */

#ifndef GUI_H
#define GUI_H

#include <libWhistGameAI.h>
#include <libWhistGame.h>

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stdlib.h>

struct PlayersGUI {
    GtkWidget *image[MAX_GAME_PLAYERS];
    GtkWidget *nameLabel[MAX_GAME_PLAYERS];
    GtkWidget *bidsLabel[MAX_GAME_PLAYERS];
    GtkWidget *tookLabel[MAX_GAME_PLAYERS];
};

struct SelectedCard {
    GtkWidget *imageSelectedCard;
    GtkWidget *fixed;
    struct Game *game;
    struct Player *player;
    int roundId;
};

struct PlayerCards {
    GtkWidget *images[MAX_CARDS];
};

/**
 * @struct Input
 *
 * @brief The structure is used to keep informations about a game,
 *
 * @var Input::name
 *      Pointer to the GtkEntry. Is used to keep the user name.
 * @var Input::robotsNumber
 *      Pointer to the spin button. Is used to keep the bots number.
 * @var Input::gameType
 *      Pointer to the radio button. Is used to keep the game type.
 */
struct Input {
    GtkWidget *name;
    GtkWidget *robotsNumber;
    GtkWidget *gameType;
    GtkWidget *mainWindow;
    int noOfGames;
};

/**
 * @brief Function initializes the window in which start the game.
 *
 * @param window Pointer to pointer to GtkWidget. Function will initializes
 *               this pointer with GtkWindow.
 * @param fixed Pointer to pointer to GtkWidget. Function will initializes
 *              this pointer with GtkFixed.
 * @param title Pointer to the string which will be set as the name of the
 *              window.
 * @param width The width of the window.
 * @param height The height of the window.
 *
 *return NO_ERROR or 0 on success, other value on failure.
 */
int gui_init(GtkWidget **window, GtkWidget **fixed, char *title,
             int width, int height);

/**
 * @brief Function adds a label and a spin button to be able the player to
 *        enter the bots number.           
 *
 * @param window Pointer to the GtkWindow in which to be added the label and
 *               the spin button.
 * @param fixed Pointer to the GtkFixed which is added in window.
 * @param label Pointer to pointer to GtkWidget. Function will creates a label
 *              to that address.
 * @param spinNumber Pointer to pointer to GtkWidget. Function will creates a
 *                   spin button to that address.
 * @param number Pointer to pointer to GtkAdjustment. Function will creates a 
 *               GtkAdjustment to that address. Function has need this
 *               parameter to create a spin button.
 *
 * @return NO_ERROR or 0 on success, other value on failure.
 */
int gui_noOfBots(GtkWidget *window, GtkWidget *fixed, GtkWidget **label,
                 GtkWidget **spinNumber, GtkAdjustment **number);

/**
 * @brief Function adds a label and a entry to be able the player to enter his
 *        name.
 *
 * @param window Pointer to the GtkWindow in which to be added the label and
 *               the entry.
 * @param fixed Pointer to the GtkFixed which is added in window.
 * @param label Pointer to pointer to GtkWidget. Function will creates a label
 *              to that address.
 * @param name Pointer to pointer to GtkEntry. Function will creates a entry
 *             to that address.
 *
 * @return NO_ERROR or 0 on success, other value on failure.
 */
int gui_playerName(GtkWidget *window, GtkWidget *fixed,
                   GtkWidget **label, GtkWidget **name);

/**
 * @brief Function adds a label, a vbox and two radio buttons to be able the
 *        player to enter the game type.
 *
 * @param window Pointer to the GtkWindow in which to be added the label, the
 *               vbox and the radio buttons.
 * @param fixed Pointer to the GtkFixed which is added in window.
 * @param label Pointer to pointer to GtkWidget. Function will creates a label
 *              to that address.
 * @param radio1 Pointer to pointer to GtkWidget. Function will creates a radio
 *               button to that address.
 * @param radio8 Pointer to pointer to GtkWidget. Function will creates a radio
 *               button to that address.
 *
 * @return NO_ERROR or 0 on success, other value on failure.
 */
int gui_gameType(GtkWidget *window, GtkWidget *fixed, GtkWidget **label,
                 GtkWidget **radio1, GtkWidget **radio8);
/**
 * @brief Function set background for a GtkFixed.
 *
 * @param fixed Pointer to the GtkFixed for which is set the background.
 * @param pathPicture The path to the image which to be set such as background.
 *
 * @return NO_ERROR or 0 on success, other value on failure.
 */
int gui_setBackground(GtkWidget *fixed, char *pathPicture);

/**
 *
 *
 */
int gui_showScore(GtkWidget *button, struct Game *game);

/**
 * @brief Function create the button which will show the score.
 *
 * @param fixed Pointer to the GtkFixed in which is added the button.
 * @param showButton The address to which is created the button.
 * 
 * 
 */ 
int gui_createButtonShowScore(GtkWidget *fixed, GtkWidget **showButton,
                              struct Game *game);

int gui_getPictureName(struct Card *card, char *name);

int gui_destroyTrump(GtkWidget **image);

int gui_initTrump(GtkWidget *fixed, GtkWidget **image);

int gui_showTrump(struct Card *trump, GtkWidget *image);

int gui_destroyPlayerCards(struct PlayerCards *playerCards);

struct PlayerCards *gui_initializePlayerCards(GtkWidget *fixed);

int gui_hidePlayerCards(struct PlayerCards *playerCards);

int gui_showPlayerCards(struct PlayerCards *playerCards, GtkWidget *fixed,
                        struct Player *player);

int gui_initAndShowDialogIncorrectName(GtkWidget *window);

int gui_initAndShowDialogMaxGames(GtkWidget *window);

int gui_closeWhistGame(GtkWidget *windowTable, struct Input *input);

int gui_getCardId(int x, int y);

int gui_clickMouse(GtkWidget *window, GdkEvent *event);

struct SelectedCard *gui_createSelectedCard(GtkWidget *fixed, struct Game *game,
                                            struct Player *player, int roundId);

int gui_selectedCard(GtkWidget *window, GdkEvent *event,
                     struct SelectedCard *selectedCard);

struct PlayersGUI *gui_createPlayersGUI();

int gui_showPlayers(struct Game *game, GtkWidget *fixed,
                    struct PlayersGUI *playersGUI);

#endif

