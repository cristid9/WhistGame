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
    if (roundType < MIN_CARDS || roundType > MAX_CARDS)
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

int round_addPlayer(struct Round *round, struct Player *player)
{
    if (round == NULL)
        return ROUND_NULL;
    if (player == NULL)
        return PLAYER_NULL;

    int position = -1;
    for (int i = MAX_GAME_PLAYERS - 1; i >= 0; i--) {
        if (round->players[i] == player)
            return DUPLICATE;
        if (round->players[i] == NULL)
            position = i;
    }

    if (position != -1) {
        round->players[position] = player;
        return NO_ERROR;
    }

    return FULL;
}

int round_addHand(struct Round *round, struct Hand *hand)
{
    if (round == NULL)
        return ROUND_NULL;
    if (hand == NULL)
        return HAND_NULL;

    if (round->hand != NULL)
        hand_deleteHand(&(round->hand));

    round->hand = hand;

    return NO_ERROR;
}

int round_addTrump(struct Round *round, struct Card *trump)
{
    if (round == NULL)
        return ROUND_NULL;
    if (trump == NULL)
        return CARD_NULL;

    if (round->trump != NULL)
        deck_deleteCard(&(round->trump));

    round->trump = trump;

    return NO_ERROR;
}

int round_addPlayersInHand(struct Round *round, int firstPlayer)
{
    if (round == NULL)
        return ROUND_NULL;
    if (firstPlayer < 0 || firstPlayer >= MAX_GAME_PLAYERS)
        return ILLEGAL_VALUE;
    if (round->hand == NULL)
        return HAND_NULL;

    int playersNumber = 0;
    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (round->players[i] != NULL)
            playersNumber++;

    if (playersNumber < MIN_GAME_PLAYERS)
        return INSUFFICIENT_PLAYERS;

    for (int i = firstPlayer; i < MAX_GAME_PLAYERS; i++)
        hand_addPlayer(round->hand, round->players[i]);
    for (int i = 0; i < firstPlayer; i++)
        hand_addPlayer(round->hand, round->players[i]);

    return NO_ERROR;
}

int round_distributeCard(struct Round *round, struct Deck *deck)
{
    if (round == NULL)
        return ROUND_NULL;
    if (deck == NULL)
        return DECK_NULL;

    int playersNumber = 0;
    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        if (round->players[i] != NULL)
            playersNumber++;
    }

    if (playersNumber < MIN_GAME_PLAYERS)
        return INSUFFICIENT_PLAYERS;

    int deckSize = deck_getDeckSize(deck);
    if (deckSize < playersNumber)
        return INSUFFICIENT_CARDS;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (round->players[i] != NULL)
            for (int j = 0; j < DECK_SIZE; j++)
                if (deck->cards[j] != NULL) {
                    player_addCard(round->players[i], deck->cards[j]);
                    break;
                }

    return NO_ERROR;
}

