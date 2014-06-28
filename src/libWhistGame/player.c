/**
 * @file player.c
 * @brief In this file are defined functions used for Player-related operations,
 *        these functions are declared in the header file player.h.
 */

#include "player.h"
#include "errors.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct Player *player_createPlayer(const char *name, int isHuman)
{
    if (name == NULL)
        return NULL;

    struct Player *player = malloc(sizeof(struct Player));
    if (player == NULL)
        return NULL;

    player->name = malloc((strlen(name) + 1) * sizeof(char));
    if (player->name != NULL)
        strcpy(player->name, name);
    else
        return NULL;

    player->isHuman = isHuman;

    for (int i = 0; i < MAX_CARDS; i++)
        player->hand[i] = NULL;

    return player;
}

int player_deletePlayer(struct Player **player)
{
    if (player == NULL)
        return POINTER_NULL;
    if (*player == NULL)
        return PLAYER_NULL;

    free((*player)->name);
    (*player)->name = NULL;

    free(*player);
    *player = NULL;

    return NO_ERROR;
}

int player_addCard(struct Player *player, struct Card **card)
{
    if (player == NULL)
        return PLAYER_NULL;
    if (card == NULL)
        return POINTER_NULL;
    if (*card == NULL)
        return CARD_NULL;

    int position = -1;
    for (int i = 0; i < MAX_CARDS; i++) {
        if (player->hand[i] == *card)
            return DUPLICATE;
        if (position == -1 && player->hand[i] == NULL)
            position = i;
    }

    if (position != -1) {
        player->hand[position] = *card;
        *card = NULL;
        return NO_ERROR;
    }

    return FULL;
}

/** 
 * @brief Helper for player_sortPlayerCards().
 *
 * @param cards Pointer to array of Card which must to be sorted.
 * @param length The length of the array of Card.
 *
 * @return NO_ERROR or 0 on success, other value on failure.
 */ 
int sortCards(struct Card **cards, int length)
{
    if (cards == NULL || *cards == NULL)
        return CARD_NULL;

    struct Card *card;
    for (int i = 0; i < length - 1; i++)
        for (int j = i + 1; j < length; j++)
            if (cards[i]->value > cards[j]->value) {
                card     = cards[i];
                cards[i] = cards[j];
                cards[j] = card;
            }

    return NO_ERROR;
}

int player_sortPlayerCards(struct Player *player)
{
    if (player == NULL)
        return PLAYER_NULL;

    struct Card *diamonds[MAX_CARDS] = { NULL };
    struct Card *clubs[MAX_CARDS]    = { NULL };
    struct Card *spades[MAX_CARDS]   = { NULL };
    struct Card *hearts[MAX_CARDS]   = { NULL };

    int noD = 0;
    int noC = 0;
    int noS = 0;
    int noH = 0;

    for (int i = 0; i < MAX_CARDS; i++)
        if (player->hand[i] != NULL) {
            if (player->hand[i]->suit == DIAMONDS)
                diamonds[noD++] = player->hand[i];
            if (player->hand[i]->suit == CLUBS)
                clubs[noC++] = player->hand[i];
            if (player->hand[i]->suit == SPADES)
                spades[noS++] = player->hand[i];
            if (player->hand[i]->suit == HEARTS)
                hearts[noH++] = player->hand[i];
        }

    sortCards(diamonds, noD);
    sortCards(clubs, noC);
    sortCards(spades, noS);
    sortCards(hearts, noH);

    for (int i = 0; i < MAX_CARDS; i++)
        player->hand[i] = NULL;

    for (int i = 0; i < noD; i++)
        player->hand[i] = diamonds[i];

    int sum = noD;
    for (int i = 0; i < noC; i++)
        player->hand[i + sum] = clubs[i];

    sum += noC;
    for (int i = 0; i < noS; i++)
        player->hand[i + sum] = spades[i];

    sum += noS;
    for (int i = 0; i < noH; i++)
        player->hand[i + sum] = hearts[i];

    return NO_ERROR;
}

int player_checkPlayerName(const char *name)
{
    if (name == NULL)
        return POINTER_NULL;

    int firstLetter = (int)tolower(name[0]);
    if (strlen(name) < 5 || firstLetter < 97 || firstLetter > 122)
        return INCORRECT_NAME;

    return NO_ERROR;
}

