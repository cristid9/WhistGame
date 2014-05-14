/**
 * @file game.c
 * @brief In this file are defined functions used for Game-related operations,
 *        these functions are declared in the header file game.h.
 */

#include "game.h"
#include "errors.h"

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

int game_deleteGame(struct Game **game)
{
    if (game == NULL)
        return POINTER_NULL;
    if (*game == NULL)
        return GAME_NULL;

    if ((*game)->deck != NULL)
        deck_deleteDeck(&((*game)->deck));

    for (int i = 0; i < MAX_GAME_ROUNDS; i++)
        if ((*game)->rounds[i] != NULL)
            round_deleteRound(&((*game)->rounds[i]));

    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if ((*game)->players[i] != NULL)
            player_deletePlayer(&((*game)->players[i]));

    free(*game);
    *game = NULL;

    return NO_ERROR;
}

int game_addDeck(struct Game *game, struct Deck **deck)
{
    if (game == NULL)
        return GAME_NULL;
    if (deck == NULL)
        return POINTER_NULL;
    if (*deck == NULL)
        return DECK_NULL;

    if (game->deck != NULL)
        deck_deleteDeck(&game->deck);

    game->deck = *deck;
    *deck = NULL;

    return NO_ERROR;
}

