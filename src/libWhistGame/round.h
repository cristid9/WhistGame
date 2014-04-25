/**
 * @file round.h
 * @brief Round structure, as well as helper functions.
 */

#ifndef ROUND_H
#define ROUND_H

#include "player.h"
#include "hand.h"
#include "constants.h"

/**
 * @struct Round
 *
 * @brief Round structure.
 *
 * @var Round::roundType
 *      Variable used to indicate the round type (1, 2, 3, 4, 5, 6, 7, 8).
 * @var Round::trump
 *      The trump of the round, if this exists.
 * @var Round::bids
 *      The bids of the players.
 * @var Round::pointsNumber
 *      The score of the players.
 * @var Round::players
 *      Pointer to the players of the round.
 * @var Round::hands
 *      Pointer to the hands of the round.
 */
struct Round {
    int roundType;
    enum Suit trump;
    int bids[MAX_GAME_PLAYERS];
    int pointsNumber[MAX_GAME_PLAYERS];
    struct Players *players[MAX_GAME_PLAYERS];
    struct Hand *hands[MAX_GAME_PLAYERS];
};

#endif

