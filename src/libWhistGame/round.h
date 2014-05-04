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
    struct Player *players[MAX_GAME_PLAYERS];
    struct Hand *hand;
};

/**
 * @brief Function allocates and initializes a round.
 *
 * @param roundType The round type (1, 2, 3, 4, 5, 6, 7, 8).
 *
 * @return Pointer to the new round on success, NULL on failure.
 */
struct Round *round_createRound(int roundType);

/**
 * @brief Function releases the memory of the round.
 *
 * @param round Pointer to pointer to the round which to be released.
 *
 * @return NO_ERROR or 0 on success, other value on failure.
 */
int round_deleteRound(struct Round **round);

/**
 * @brief Function adds a player in a round.
 *
 * @param round Pointer to the round in which is added the player.
 * @param player Pointer to the player which to be added.
 *
 * @return NO_ERROR or 0 on success, other value on failure.
 */
int round_addPlayer(struct Round *round, struct Player *player);

/**
 * @brief Function adds a hand in a round.
 *
 * @param round Pointer to the round in which is added the hand.
 * @param hand Pointer to the hand which to be added.
 *
 * @return NO_ERROR or 0 on success, other value on failure.
 */
int round_addHand(struct Round *round, struct Hand *hand);

/**
 * @brief Function adds the trump in a round.
 *
 * @param round Pointer to the round in which is added the trump.
 * @param trump Pointer to the card which to be added as trump.
 *
 * @return NO_ERROR or 0 on succes, other value on failure.
 */
int round_addTrump(struct Round *round, struct Card *trump);

#endif

