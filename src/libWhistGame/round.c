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
        round->handsNumber[i]  = 0;
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

int round_addHand(struct Round *round, struct Hand **hand)
{
    if (round == NULL)
        return ROUND_NULL;
    if (hand == NULL)
        return POINTER_NULL;
    if (*hand == NULL)
        return HAND_NULL;

    if (round->hand != NULL)
        hand_deleteHand(&(round->hand));

    round->hand = *hand;
    *hand = NULL;    

    return NO_ERROR;
}

int round_addTrump(struct Round *round, struct Card **trump)
{
    if (round == NULL)
        return ROUND_NULL;
    if (trump == NULL)
        return POINTER_NULL;
    if (*trump == NULL)
        return CARD_NULL;

    if (round->trump != NULL)
        deck_deleteCard(&(round->trump));

    round->trump = *trump;
    *trump = NULL;

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

    int i,j;
    for (i = 0, j = 0; i < MAX_GAME_PLAYERS && j < DECK_SIZE; i++, j++) {
        while (deck->cards[j] == NULL && j < DECK_SIZE)
            j++;
        while (round->players[i] == NULL && i < MAX_GAME_PLAYERS)
            i++;
        if (i < MAX_GAME_PLAYERS && j < DECK_SIZE) {
            int check = player_addCard(round->players[i], &deck->cards[j]);
            if (check != NO_ERROR)
                return check;
        }
    }

    return NO_ERROR;
}

int round_distributeDeck(struct Round *round, struct Deck *deck)
{
    if (round == NULL)
        return ROUND_NULL;
    if (deck == NULL)
        return DECK_NULL;

    for (int i = MIN_CARDS; i <= round->roundType; i++) {
        int check = round_distributeCard(round, deck);
        if (check != NO_ERROR)
            return check;
    }

    int i = 0;
    while (deck->cards[i] == NULL && i < DECK_SIZE)
        i++;

    if (i < DECK_SIZE)
        round_addTrump(round, &deck->cards[i]);

    return NO_ERROR;
}

int round_getPlayerId(struct Round *round, struct Player *player)
{
    if (round == NULL)
        return ROUND_NULL;
    if (player == NULL)
        return PLAYER_NULL;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (round->players[i] == player)
            return i;

    return NOT_FOUND;
}

int round_getBidsSum(struct Round *round)
{
    if (round == NULL)
        return ROUND_NULL;

    int sum = 0;
    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (round->players[i] != NULL)
            sum += round->bids[i];

    return sum;
}

int round_checkBid(struct Round *round, struct Player *player, int bid)
{
    if (round == NULL)
        return ROUND_NULL;
    if (player == NULL)
        return PLAYER_NULL;
    if (bid < MIN_CARDS - 1 || bid > round->roundType)
        return ILLEGAL_VALUE;

    int position = round_getPlayerId(round, player);
    if (position < 0)
        return position;

    for (int i = position + 1; i < MAX_GAME_PLAYERS; i++)
        if (round->players[i] != NULL)
            return NO_ERROR;

    if (round_getBidsSum(round) + bid == round->roundType)
        return ILLEGAL_VALUE;

    return NO_ERROR;
}

int round_placeBid(struct Round *round, struct Player *player, int bid)
{
    int check = round_checkBid(round, player, bid);
    if (check != 0)
        return check;

    int position = round_getPlayerId(round, player);
    round->bids[position] = bid;

    return NO_ERROR;
}

struct Player *round_getPlayerWhichWonHand(struct Round *round)
{
    if (round == NULL || round->hand == NULL)
        return NULL;

    int playersNumber = 0;
    int cardsNumber = 0;
    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        if (round->hand->players[i] != NULL)
            playersNumber++;
        if (round->hand->cards[i] != NULL)
            cardsNumber++;
    }

    if (playersNumber < MIN_GAME_PLAYERS || playersNumber != cardsNumber)
        return NULL;

    struct Player *winningPlayer = round->hand->players[0];
    struct Card   *winningCard   = round->hand->cards[0];
    enum Suit trump;
    if (round->trump == NULL)
        trump = SuitEnd;
    else
        trump = round->trump->suit;

    for (int i = 1; i < MAX_GAME_PLAYERS; i++)
        if (deck_compareCards(winningCard, round->hand->cards[i], trump) == 2) {
            winningPlayer = round->hand->players[i];
            winningCard   = round->hand->cards[i];
        }

    return winningPlayer;
}

