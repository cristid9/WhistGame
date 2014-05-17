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
 * @param hand Pointer to pointer to the hand which to be added.
 *
 * @return NO_ERROR or 0 on success, other value on failure.
 */
int round_addHand(struct Round *round, struct Hand **hand);

/**
 * @brief Function adds the trump in a round.
 *
 * @param round Pointer to the round in which is added the trump.
 * @param trump Pointer to pointer to the card which to be added as trump.
 *
 * @return NO_ERROR or 0 on succes, other value on failure.
 */
int round_addTrump(struct Round *round, struct Card **trump);

/**
 * @brief Function adds players in hand in a certain order.
 *
 * @param round Pointer to the round from which are added the players.
 * @param firstPlayer The player id from round which is the first added in hand.
 *
 * @return NO_ERROR or 0 on success, other value on failure.
 */
int round_addPlayersInHand(struct Round *round, int firstPlayer);

/**
 * @brief Function distributes one card each player from round.
 *
 * @param round Pointer to the round in which are the players.
 * @param deck Pointer to the deck from which are distributed the cards.
 *
 * @return NO_ERROR or 0 on success, other value on failure.
 */
int round_distributeCard(struct Round *round, struct Deck *deck);

/**
 * @brief Function distributes the cards of the players.
 *
 * @param round Pointer to the round in which are the players.
 * @param deck Pointer to the deck which is distributed.
 *
 * @return NO_ERROR or 0 on success, other value on failure.
 */
int round_distributeDeck(struct Round *round, struct Deck *deck);

/**
 * @brief Function get the id of the player.
 *
 * @param round Pointer to the round in which is the player.
 * @param player Pointer to the player for which it get the id.
 *
 * @return A number between 0 and MAX_GAME_PLAYERS on success, a negative value
 *         on failure.
 */
int round_getPlayerId(struct Round *round, struct Player *player);

/**
 * @brief Function get the sum of the bids from a round.
 *
 * @param round Pointer to the round for which is calculated the sum of the 
 *              bids.
 *
 * @return A positive value on success, a negative value on failure.
 */
int round_getBidsSum(struct Round *round);

/**
 * @brief Function checks if a bid can be bid.
 *
 * @param round Pointer to the round in which is checked the bid.
 * @param player Pointer to the player who bids.
 * @param bid The bid which is bid.
 *
 * @return NO_ERROR or 0 on success, other value on failure.
 */
int round_checkBid(struct Round *round, struct Player *player, int bid);

#endif

