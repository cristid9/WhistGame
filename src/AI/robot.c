/**
 * @file robot.c
 * @brief In this file are defined the functions used at the logic of the robot,
          these functions are defined in the header file robot.c.
 */

#include "robot.h"

#include <stdlib.h>

int robot_getBid(struct Player *player, struct Round *round)
{
    if (player == NULL)
        return PLAYER_NULL;
    if (round == NULL)
        return ROUND_NULL;

    if (round->roundType == 1) {
        for (int i = 0; i < MAX_CARDS; i++)
            if (player->hand[i] != NULL &&
                player->hand[i]->suit == round->trump->suit) {
                if (round_checkBid(round, player, 1) == NO_ERROR)
                    return 1;
                else
                    return 0;
            }
        if (round_checkBid(round, player, 0) == NO_ERROR)
            return 0;
        else
            return 1;
    }

    if (round->roundType == 8) {
        int bids = 0;
        for (int i = 0; i < MAX_CARDS; i++)
            if (player->hand[i] != NULL) {
                if (player->hand[i]->value == 15 ||
                    player->hand[i]->value == 14)
                    bids++;
            }
        if (round_checkBid(round, player, bids) == NO_ERROR)
            return bids;
        if (bids - 1 < 0)
            return bids + 1;
        else
            return bids - 1;
    }

    int bids = 0;
    for (int i = 0; i < MAX_CARDS; i++)
        if (player->hand[i] != NULL) {
            if ((player->hand[i]->suit == round->trump->suit &&
                player->hand[i]->value >= 10) || player->hand[i]->value == 15)
                bids++;
        }
    if (round_checkBid(round, player, bids) == NO_ERROR)
        return bids;
    if (bids - 1 < 0)
        return bids + 1;
    else
        return bids - 1;
}

int robot_getCard(struct Player *player, struct Round *round)
{
    if (player == NULL)
        return PLAYER_NULL;
    if (round == NULL)
        return ROUND_NULL;
    if (round->hand == NULL)
        return HAND_NULL;

    int playerId = round_getPlayerId(round, player);
    if (playerId < 0)
        return playerId;

    if (round->hand->players[0] == player) {
        if (round->bids[playerId] > round->handsNumber[playerId]) {
            int max = 0;
            int position = 0;
            for (int i = 0; i < MAX_CARDS; i++)
                if (player->hand[i] != NULL) {
                    if (player->hand[i]->value > max) {
                        max = player->hand[i]->value;
                        position = i;
                    }
                }
            return position;
        } else {
            int min = 15;
            int position  = 0;
            for (int i = 0; i < MAX_CARDS; i++)
                if (player->hand[i] != NULL)
                    if (player->hand[i]->value < min) {
                        min = player->hand[i]->value;
                        position = i;
                    }
            return position;
        }
    }

    int numberOfTrumps       =  0;
    int maxValueTrump        =  0;
    int posMaxValueTrump     = -1;
    int minValueTrump        = 15;
    int posMinValueTrump     = -1;

    int numberOfFirstCard    =  0;
    int maxValueFirstCard    =  0;
    int posMaxValueFirstCard = -1;
    int minValueFirstCard    = 15;
    int posMinValueFirstCard = -1;

    for (int i = 0; i < MAX_CARDS; i++) {
        if (player->hand[i] != NULL) {
            if (round->trump != NULL)
                if (player->hand[i]->suit == round->trump->suit) {
                    numberOfTrumps++;

                    if (maxValueTrump < player->hand[i]->value) {
                        maxValueTrump = player->hand[i]->value;
                        posMaxValueTrump = i;
                    }

                    if (minValueTrump > player->hand[i]->value) {
                        minValueTrump = player->hand[i]->value;
                        posMinValueTrump = i;
                    }
                }

            if (player->hand[i]->suit == round->hand->cards[0]->suit) {
                numberOfFirstCard++;

                if (maxValueFirstCard < player->hand[i]->value) {
                    maxValueFirstCard = player->hand[i]->value;
                    posMaxValueFirstCard = i;
                }

                if (minValueFirstCard > player->hand[i]->value) {
                    minValueFirstCard = player->hand[i]->value;
                    posMinValueFirstCard = i;
                }
            }
        }
    }

    if (round->bids[playerId] > round->handsNumber[playerId]) {
        if (numberOfFirstCard > 0) {
            return posMaxValueFirstCard;
        } else {
            if (numberOfTrumps > 0) {
                return posMaxValueTrump;
            } else {
                int min = 15;
                int pos = 0;
                for (int i = 0; i < MAX_CARDS; i++)
                    if (player->hand[i] != NULL)
                        if (player->hand[i]->value < min) {
                            min = player->hand[i]->value;
                            pos = i;
                        }
                return pos;
            }
        }
    } else {
        if (numberOfFirstCard > 0) {
            return posMinValueFirstCard;
        } else {
            if (numberOfTrumps > 0) {
                return posMinValueTrump;
            } else {
                int max = 0;
                int pos = 0;
                for (int i = 0; i < MAX_CARDS; i++)
                    if (player->hand[i] != NULL)
                        if (player->hand[i]->value > max) {
                            max = player->hand[i]->value;
                            pos = i;
                        }
                return pos;
            }
        }
    }
}

