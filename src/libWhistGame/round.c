/**
 * @file round.c
 * @brief In this file are defined functions used for Round-related operations,
 *        these functions are declared in the header file round.h.
 */

#include "round.h"

struct Round *round_createRound(int roundType)
{
    if (roundType < 1 || roundType > 8)
        return NULL;

    struct Round *round = malloc(sizeof(struct Round));
    if (round == NULL)
        return NULL;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        round->bids[i]         = 0;
        round->pointsNumber[i] = 0;
        round->players[i]      = NULL;
    }

    round->hand      = NULL;
    round->trump     = NULL;
    round->roundType = roundType;

    return round;
}

