#include <round.h>
#include <errors.h>
#include <constants.h>

#include <cutter.h>
#include <stdlib.h>

void test_round_createRound()
{
    cut_assert_equal_pointer(NULL, round_createRound(MIN_CARDS - 1));
    cut_assert_equal_pointer(NULL, round_createRound(MAX_CARDS + 1));
    
    struct Round *round = round_createRound(MIN_CARDS);
    int check = 0;
    if (round == NULL)
        check++;
    cut_assert_equal_int(0, check);

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        cut_assert_equal_pointer(NULL, round->players[i]);
        cut_assert_equal_int(0, round->bids[i]);
        cut_assert_equal_int(0, round->pointsNumber[i]);
    }

    cut_assert_equal_int(MIN_CARDS, round->roundType);
    cut_assert_equal_pointer(NULL, round->hand);
    cut_assert_equal_pointer(NULL, round->trump);

    round_deleteRound(&round);
}

void test_round_deleteRound()
{
    struct Round *round = round_createRound(MIN_CARDS);
    cut_assert_equal_int(POINTER_NULL, round_deleteRound(NULL));
    cut_assert_equal_int(NO_ERROR, round_deleteRound(&round));
    cut_assert_equal_int(ROUND_NULL, round_deleteRound(&round));
    cut_assert_equal_pointer(NULL, round);
}

void test_round_addPlayer()
{
    struct Round *round = round_createRound(MIN_CARDS);
    struct Player *players[MAX_GAME_PLAYERS + 1];

    players[MAX_GAME_PLAYERS] = player_createPlayer("A", 1);
    cut_assert_equal_int(PLAYER_NULL, round_addPlayer(round, NULL));
    cut_assert_equal_int(ROUND_NULL,
                         round_addPlayer(NULL, players[MAX_GAME_PLAYERS]));
    cut_assert_operator_int(0, >, round_addPlayer(NULL, NULL));

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        players[i] = player_createPlayer("A", i);
        cut_assert_equal_int(NO_ERROR, round_addPlayer(round, players[i]));
        cut_assert_equal_int(DUPLICATE, round_addPlayer(round, players[i]));
        int check = 0;
        for (int j = 0; j < MAX_GAME_PLAYERS; j++)
            if (round->players[j] == players[i])
                check++;
        cut_assert_equal_int(1, check);
    }

    cut_assert_equal_int(FULL, round_addPlayer(round, 
                                               players[MAX_GAME_PLAYERS]));

    round_deleteRound(&round);
    for (int i = 0; i <= MAX_GAME_PLAYERS; i++)
        player_deletePlayer(&players[i]);
}

void test_round_addHand()
{
    struct Round *round = round_createRound(MIN_CARDS);
    struct Hand  *hand  = hand_createHand();

    cut_assert_equal_int(ROUND_NULL, round_addHand(NULL, &hand));
    cut_assert_equal_int(POINTER_NULL, round_addHand(round, NULL));
    cut_assert_operator_int(0, >, round_addHand(NULL, NULL));
    cut_assert_equal_int(NO_ERROR, round_addHand(round, &hand));
    cut_assert_equal_int(HAND_NULL, round_addHand(round, &hand));
    cut_assert_equal_pointer(NULL, hand);
    int check = 0;
    if (round->hand == NULL)
        check++;
    cut_assert_equal_int(0, check);

    round_deleteRound(&round);
}

void test_round_addTrump()
{
    struct Round *round = round_createRound(MIN_CARDS);
    struct Card  *trump = deck_createCard(DIAMONDS, VALUES[0]);

    cut_assert_equal_int(ROUND_NULL, round_addTrump(NULL, &trump));
    cut_assert_equal_int(POINTER_NULL, round_addTrump(round, NULL));
    cut_assert_operator_int(0, >, round_addTrump(NULL, NULL));
    cut_assert_equal_int(NO_ERROR, round_addTrump(round, &trump));
    cut_assert_equal_int(CARD_NULL, round_addTrump(round, &trump));
    cut_assert_equal_pointer(NULL, trump);
    int check = 0;
    if (round->trump == NULL)
        check++;
    cut_assert_equal_int(0, check);

    round_deleteRound(&round);
}

void test_round_addPlayersInHand()
{
    struct Round *round = round_createRound(MIN_CARDS);
    cut_assert_equal_int(ROUND_NULL, round_addPlayersInHand(NULL, 0));
    cut_assert_equal_int(ILLEGAL_VALUE, round_addPlayersInHand(round, -1));
    cut_assert_equal_int(ILLEGAL_VALUE,
                         round_addPlayersInHand(round, MAX_GAME_PLAYERS + 1));
    cut_assert_equal_int(HAND_NULL, round_addPlayersInHand(round, 0));
    round->hand = hand_createHand();
    cut_assert_equal_int(INSUFFICIENT_PLAYERS,
                         round_addPlayersInHand(round, 0));

    struct Player *players[MAX_GAME_PLAYERS];
    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        players[i] = player_createPlayer("A", i);
        round_addPlayer(round, players[i]);
    }

    for (int i = 0 ; i < MAX_GAME_PLAYERS; i++) {
        cut_assert_equal_int(NO_ERROR, round_addPlayersInHand(round, i));
        int position = 0;
        for (int j = i; j < MAX_GAME_PLAYERS; j++) {
            cut_assert_equal_pointer(round->players[j],
                                     round->hand->players[position]);
            position++;
        }
        for (int j = 0; j < i; j++) {
            cut_assert_equal_pointer(round->players[j],
                                     round->hand->players[position]);
            position++;
        }
        hand_deleteHand(&round->hand);
        round->hand = hand_createHand(); 
    }

    round_deleteRound(&round);
    for(int i = 0; i < MAX_GAME_PLAYERS; i++)
        player_deletePlayer(&players[i]);
}

void test_round_disitrbuteCard()
{
    struct Round *round = round_createRound(MAX_CARDS);
    struct Deck  *deck  = deck_createDeck(MAX_GAME_PLAYERS);
    struct Player *players[MAX_GAME_PLAYERS];
    
    cut_assert_equal_int(ROUND_NULL, round_distributeCard(NULL, deck));
    cut_assert_equal_int(DECK_NULL, round_distributeCard(round, NULL));
    cut_assert_equal_int(INSUFFICIENT_PLAYERS,
                         round_distributeCard(round, deck));

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        players[i] = player_createPlayer("A", i);
        round_addPlayer(round, players[i]);
    }

    for (int i = 0; i < MAX_CARDS; i++) {
        cut_assert_equal_int(NO_ERROR, round_distributeCard(round, deck));
        cut_assert_equal_int(DECK_SIZE - (i + 1) * MAX_GAME_PLAYERS,
                             deck_getDeckSize(deck));
        for (int j = 0; j < MAX_GAME_PLAYERS; j++) {
            int cardsNumber = 0;
            for (int k = 0; k < MAX_CARDS; k++)
                if (round->players[j]->hand[k] != NULL)
                    cardsNumber++;
            cut_assert_equal_int(i + 1, cardsNumber);
        }
    }

    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        player_deletePlayer(&players[i]);
    round_deleteRound(&round);
    deck_deleteDeck(&deck);
}

void test_round_distributeDeck()
{
    struct Round *round = round_createRound(MAX_CARDS);
    struct Deck  *deck  = deck_createDeck(MAX_GAME_PLAYERS);
    struct Player *players[MAX_GAME_PLAYERS];

    cut_assert_equal_int(ROUND_NULL, round_distributeDeck(NULL, deck));
    cut_assert_equal_int(DECK_NULL, round_distributeDeck(round, NULL));

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        players[i] = player_createPlayer("A", i);
        round_addPlayer(round, players[i]);
    }

    cut_assert_equal_int(NO_ERROR, round_distributeDeck(round, deck));
    cut_assert_equal_pointer(NULL, round->trump);
    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        int nullCards = 0;
        int duplicate = 0;
        for (int j = 0; j < MAX_CARDS; j++)
            if (round->players[i]->hand[j] == NULL)
                nullCards++;
        for (int j = 0; j < MAX_CARDS - 1; j++)
            for (int k = j + 1; k < MAX_CARDS; k++)
                if (round->players[i]->hand[j] == round->players[i]->hand[k])
                    duplicate++;
        cut_assert_equal_int(0, nullCards);
        cut_assert_equal_int(0, duplicate);
    }

    round_deleteRound(&round);
    deck_deleteDeck(&deck);
    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        player_deletePlayer(&players[i]);
}

void test_round_getPlayerId()
{
    struct Round *round = round_createRound(1);
    struct Player *players[MAX_GAME_PLAYERS + 1];

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        players[i] = player_createPlayer("A", i);
        round_addPlayer(round, players[i]);
        cut_assert_equal_int(i, round_getPlayerId(round, players[i]));
    }

    players[MAX_GAME_PLAYERS] = player_createPlayer("A", 1);
    cut_assert_equal_int(NOT_FOUND, 
                         round_getPlayerId(round, players[MAX_GAME_PLAYERS]));
    cut_assert_equal_int(ROUND_NULL, round_getPlayerId(NULL, players[0]));
    cut_assert_equal_int(PLAYER_NULL, round_getPlayerId(round, NULL));

    round_deleteRound(&round);
    for (int i = 0; i <= MAX_GAME_PLAYERS; i++)
        player_deletePlayer(&players[i]);
}

void test_round_getBidsSum()
{
    struct Round *round = round_createRound(1);
    struct Player *players[MAX_GAME_PLAYERS];

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        players[i] = player_createPlayer("A", i);
        round_addPlayer(round, players[i]);
        round->bids[i] = 1;
        cut_assert_equal_int(i + 1, round_getBidsSum(round));
    }

    round_deleteRound(&round);
    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        player_deletePlayer(&players[i]);
}

void test_round_checkBid()
{
    struct Round *round = round_createRound(8);
    struct Player *players[MAX_GAME_PLAYERS];
    struct Player *player = player_createPlayer("A", 1);

    cut_assert_equal_int(NOT_FOUND, round_checkBid(round, player, 1));

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        players[i] = player_createPlayer("A", i);
        round_addPlayer(round, players[i]);
    }

    cut_assert_equal_int(ROUND_NULL, round_checkBid(NULL, players[0], 1));
    cut_assert_equal_int(PLAYER_NULL, round_checkBid(round, NULL, 1));
    cut_assert_equal_int(ILLEGAL_VALUE,
                         round_checkBid(round, players[0], MIN_CARDS - 2));
    cut_assert_equal_int(ILLEGAL_VALUE,
                         round_checkBid(round, players[0], MAX_CARDS + 1));

    for (int i = 0; i < MAX_GAME_PLAYERS - 1; i++) {
        cut_assert_equal_int(NO_ERROR, round_checkBid(round, players[i], 1));
        round->bids[i] = 1;
    }

    int i = MAX_GAME_PLAYERS - 1;
    cut_assert_equal_int(NO_ERROR, round_checkBid(round, players[i], 1));
    cut_assert_equal_int(ILLEGAL_VALUE, round_checkBid(round, players[i],
                                                       MAX_CARDS - i));

    round_deleteRound(&round);
    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        player_deletePlayer(&players[i]);
}

void test_round_placeBid()
{
    struct Round *round = round_createRound(8);
    struct Player *players[MAX_GAME_PLAYERS];
    struct Player *player = player_createPlayer("A", 1);

    cut_assert_equal_int(NOT_FOUND, round_placeBid(round, player, 1));

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        players[i] = player_createPlayer("A", i);
        round_addPlayer(round, players[i]);
    }

    cut_assert_equal_int(ROUND_NULL, round_placeBid(NULL, players[0], 1));
    cut_assert_equal_int(PLAYER_NULL, round_placeBid(round, NULL, 1));
    cut_assert_equal_int(ILLEGAL_VALUE,
                         round_placeBid(round, players[0], MIN_CARDS - 2));
    cut_assert_equal_int(ILLEGAL_VALUE,
                         round_placeBid(round, players[0], MAX_CARDS + 1));

    for (int i = 0; i < MAX_GAME_PLAYERS - 1; i++) {
        cut_assert_equal_int(NO_ERROR, round_placeBid(round, players[i], i));
        cut_assert_equal_int(i, round->bids[i]);
    }

    round_deleteRound(&round);
    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        player_deletePlayer(&players[i]);
}

