/**
 * @file hand.c
 * @brief In this file are defined functions used for Hand-related operations,
 *        these functions are declared in the header file hand.h.
 */

#include "hand.h"
#include "errors.h"

#include <stdlib.h>

struct Hand *hand_createHand()
{
    struct Hand *hand = malloc(sizeof(struct Hand));

    if (hand == NULL)
        return NULL;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        hand->cards[i]   = NULL;
        hand->players[i] = NULL;
    }

    return hand;
}

int hand_deleteHand(struct Hand **hand)
{
    if (hand == NULL)
        return POINTER_NULL;
    if (*hand == NULL)
        return HAND_NULL;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        if ((*hand)->cards[i] != NULL)
            deck_deleteCard(&((*hand)->cards[i]));
        if ((*hand)->players[i] != NULL)
            (*hand)->players[i] = NULL;
    }

    free(*hand);
    *hand = NULL;

    return NO_ERROR;
}

int hand_addPlayer(struct Hand *hand, struct Player *player)
{
    if (hand == NULL)
        return HAND_NULL;
    if (player == NULL)
        return PLAYER_NULL;

    int position = -1;
    for (int i = MAX_GAME_PLAYERS - 1; i >= 0; i--) {
        if (player == hand->players[i])
            return DUPLICATE;
        if (hand->players[i] == NULL)
            position = i;
    }

    if (position != -1) {
        hand->players[position] = player;
        return NO_ERROR;
    }

    return FULL;
}

int hand_addCard(struct Hand *hand, struct Player *player, struct Card **card)
{
    if (hand == NULL)
        return HAND_NULL;
    if (card == NULL)
        return POINTER_NULL;
    if (*card == NULL)
        return CARD_NULL;
    if (player == NULL)
        return PLAYER_NULL;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (hand->players[i] == player) {
            hand->cards[i] = *card;
            *card = NULL;
            return NO_ERROR;
        }

    return NOT_FOUND;
}

