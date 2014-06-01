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
                if (player->hand[i]->value == 11 ||
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
                player->hand[i]->value >= 10) || player->hand[i]->value == 14)
                bids++;
        }
    if (round_checkBid(round, player, bids) == NO_ERROR)
        return bids;
    if (bids - 1 < 0)
        return bids + 1;
    else
        return bids - 1;
}

