/**
 * @file deck.c
 * @brief In this file are defined functions used for Deck-related and 
 *        Card-related operations, these functions are declared in the header
 *        file deck.h.
 */

#include "deck.h"

#include <stdlib.h>

/**
 * Constants for game values
 */
const int VALUES[] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, -1};

struct Card *deck_createCard(enum Suit suit, int value)
{
    int check = 0;
    for (int i = 0; VALUES[i] != -1; i++)
        if (VALUES[i] == value)
            check++;
    if (check != 1)
        return NULL;

    for (int i = 0; i < SuitEnd; i++)
        if (suit == i)
            check++;
    if (check != 2)
        return NULL;

    struct Card *card = malloc(sizeof(struct Card));
    if (card == NULL)
        return NULL;

    card->suit  = suit;
    card->value = value;

    return card;
}

