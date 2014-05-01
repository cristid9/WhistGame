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

int player_deletePlayer(struct Player *player)
{
    if (player == NULL)
        return PLAYER_NULL;

    free(player->name);
    player->name = NULL;

    free(player);
    player = NULL;

    return NO_ERROR;
}

