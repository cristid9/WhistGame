/**
 * @file game.c
 * @brief In this file are defined functions used for Game-related operations,
 *        these functions are declared in the header file game.h.
 */

#include "game.h"

#include <stdlib.h>

struct Game *game_createGame(int playersNumber, int gameType)
{
    if (playersNumber < MIN_GAME_PLAYERS || playersNumber > MAX_GAME_PLAYERS)
        return NULL;
    if (gameType != 1 && gameType != 8)
        return NULL;

    struct Game *game = malloc(sizeof(struct Game));
    if (game == NULL)
        return NULL;

    game->playersNumber = playersNumber;
    game->gameType      = gameType;
    game->deck          = NULL;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        game->players[i] = NULL;
    for (int i = 0; i < MAX_GAME_ROUNDS; i++)
        game->rounds[i] = NULL;

    return game;
}

