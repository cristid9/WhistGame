/**
 * @file deck.c
 * @brief In this file are defined functions used for Deck-related and 
 *        Card-related operations, these functions are declared in the header
 *        file deck.h.
 */

#include "deck.h"
#include "errors.h"

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

int deck_deleteCard(struct Card *card)
{
    if (card == NULL)
        return CARD_NULL;

    free(card);
    card = NULL;

    return NO_ERROR;
}

struct Deck *deck_createDeck(int playersNumber)
{
    if (playersNumber > MAX_GAME_PLAYERS || playersNumber < MIN_GAME_PLAYERS)
        return NULL;

    struct Deck *deck = malloc(sizeof(struct Deck));
    if (deck == NULL)
        return NULL;

    int k = 0;
    for (int i = 0 + (MAX_GAME_PLAYERS - playersNumber) * 2;
         VALUES[i] != -1; i++)
    for (int j = 0; j != SuitEnd; j++) {
        deck->cards[k++] = deck_createCard(j, VALUES[i]);
    }

    for (int i = k; i < DECK_SIZE; i++)
        deck->cards[i] = NULL;

    return deck;
}

