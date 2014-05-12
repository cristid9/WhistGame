/**
 * @file game.h
 * @brief Game structure, as well as helper functions.
 */

#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "player.h"
#include "round.h"
#include "constants.h"

/**
 * @struct Game
 *
 * @brief Game structure. Structure used to keep informations about a game.
 *
 * @var Game::playersNumber
 *      The number of the player that are in game.
 * @var Game::gameType
 *      The game type (1 for 1-8-1 or 8 for 8-1-8).
 * @var Game::deck
 *      Pointer to the deck of cards of the game.
 * @var Game::players
 *      Pointer to the players of the game.
 * @var Game::rounds
 *      Pointer to the rounds of the game.
 */
struct Game {
    int playersNumber;
    int gameType;
    struct Deck *deck;
    struct Player *players[MAX_GAME_PLAYERS];
    struct Round *rounds[MAX_GAME_ROUNDS];
};

/**
 * @brief Function allocates and initializes a game.
 *
 * @param playersNumber The number of the players which plays in this game.
 * @param gameType The type of the game (1 or 8).
 *
 * @return Pointer to the new game on success, NULL on failure.
 */
struct Game *game_createGame(int playersNumber, int gameType);

/**
 * @brief Function releases the memory a game and makes pointer NULL.
 *
 * @param game Pointer to pointer to the game which to be released.
 *
 * @return NO_ERROR or 0 on success, other value on failure.
 */
int game_deleteGame(struct Game **game);

#endif

