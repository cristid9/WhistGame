/**
 * @file constants.h
 * @brief Contains definitions of various symbolic constants.
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
 * @brief Constants for suit.
 *
 * SuitEnd is a flag used when iterating.
 */
enum Suit {DIAMONDS = 0, CLUBS, SPADES, HEARTS, SuitEnd};

/**
 * @brief Game values for cards.
 *
 * -1 is a flag used when iterating.
 */
const int VALUES[13];

/**
 * @brief The maximum number of cards in a deck.
 */
#define DECK_SIZE 48

/**
 * @brief The maximum number of players in a game.
 */
#define MAX_GAME_PLAYERS 6

/**
 * @brief The maximum number of rounds in a game.
 */
#define MAX_GAME_ROUNDS 30

/**
 * @brief The maximum number of cards in a player's hand.
 */
#define MAX_CARDS 8

/**
 * @brief The maximum number of hands in a round.
 */ 
#define MAX_ROUND_HANDS 8

#endif

