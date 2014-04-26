/**
 * @file hand.h
 * @brief Hand structure, as well as helper functions.
 */

#ifndef HAND_H
#define HAND_H

#include "deck.h"
#include "player.h"
#include "constants.h"

/**
 * @struct Hand
 *
 * @brief Hand structure. In Hand, player[i] gives cards[i]. The players should
 *        be added in the order of the bids.
 *
 * @var Hand::cards
 *      Pointer to the cards of the hand.
 * @var Hand::players
 *      Pointer to the players of the hand.
 */
struct Hand {
    struct Card *cards[MAX_GAME_PLAYERS];
    struct Player *players[MAX_GAME_PLAYERS];
};

#endif

