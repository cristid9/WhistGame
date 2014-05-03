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
 * @brief Round structure. Structure used to keep informations about a round. 
 *
 * @var Round::roundType
 *      Variable used to indicate the round type (1, 2, 3, 4, 5, 6, 7, 8).
 * @var Round::trump
 *      Pointer to the card which is the trump of the round, if this exists.
 * @var Round::bids
 *      The bids of the players.
 * @var Round::pointsNumber
 *      The score of the players.
 * @var Round::players
 *      Pointer to the players of the round.
 * @var Round::hands
 *      Pointer to the hand of the round.
 */
struct Round {
    int roundType;
    struct Card *trump;
    int bids[MAX_GAME_PLAYERS];
    int pointsNumber[MAX_GAME_PLAYERS];
    struct Players *players[MAX_GAME_PLAYERS];
    struct Hand *hand;
};

#endif

