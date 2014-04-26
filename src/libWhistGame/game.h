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

#endif

