/**
 * @file player.c
 * @brief In this file are defined functions used for Player-related operations,
 *        these functions are declared in the header file player.h.
 */

#include "player.h"
#include "errors.h"

#include <string.h>
#include <stdlib.h>

struct Player *player_createPlayer(char *name, int isHuman)
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

