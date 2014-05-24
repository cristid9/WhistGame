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
 * @var Round::handsNumber
 *      The number of the won hands of each players.
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
    int handsNumber[MAX_GAME_PLAYERS];
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

/**
 * @brief Function places a bid of a player.
 *
 * @param round Pointer to the round in which is found the player.
 * @param player Pointer to the player who places the bid.
 * @param bid The value of the bid.
 *
 * @return NO_ERROR or 0 on success, other value on failure.
 */
int round_placeBid(struct Round *round, struct Player *player, int bid);

/**
 * @brief Function determines who won the hand and incremets handsNumber for
 *        the winning player.
 *
 * @param round Pointer to the round in which is the hand for which is 
 *              determinated the winning player.
 *
 * @return Pointer to the winning player on success, NULL on failure.
 */
struct Player *round_getPlayerWhichWonHand(struct Round *round);

/**
 * @brief Function determines score after what the round ended.
 *
 * @param round Pointer to the round for which is determined the score.
 *
 * @return NO_ERROR or 0 on success, other value on failure.
 */
int round_determinesScore(struct Round *round);

/**
 * @brief Function copy the score from round1 in round2.
 *
 * @param round1 Pointer to the round from which is copied the score.
 * @param round2 Pointer to the round in which is added the score from round1.
 *
 * @return NO_ERROR or 0 on success, other value on failure.
 */
int round_copyScore(struct Round *round1, struct Round *round2);

/**
 * @brief Function checks if in round exists at least a player which won the 
 *        correct number of hands.
 *
 * @param round Pointer to the round for which the function checks if will be
 *              replayed or not.
 *
 * @return NO_ERROR or 0 if the function doen't will be replayed.
 *         1 if the function will be replayed.
 *         A negative value on failure.
 */
int round_replayRound(struct Round *round);

#endif

