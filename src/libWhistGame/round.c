/**
 * @file round.c
 * @brief In this file are defined functions used for Round-related operations,
 *        these functions are declared in the header file round.h.
 */

#include "round.h"
#include "errors.h"

#include <stdlib.h>

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

int round_deleteRound(struct Round **round)
{
    if (round == NULL)
        return POINTER_NULL;
    if (*round == NULL)
        return ROUND_NULL;

    if ((*round)->hand != NULL)
        hand_deleteHand(&((*round)->hand));
    if ((*round)->trump != NULL)
        deck_deleteCard(&((*round)->trump));
    
    free(*round);
    *round = NULL;

    return NO_ERROR;
}


