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

    cut_assert_equal_int(ROUND_NULL, round_addHand(NULL, hand));
    cut_assert_equal_int(HAND_NULL, round_addHand(round, NULL));
    cut_assert_operator_int(0, >, round_addHand(NULL, NULL));
    cut_assert_equal_int(NO_ERROR, round_addHand(round, hand));
    cut_assert_equal_pointer(hand, round->hand);

    round_deleteRound(&round);
}

void test_round_addTrump()
{
    struct Round *round = round_createRound(MIN_CARDS);
    struct Card  *trump = deck_createCard(DIAMONDS, VALUES[0]);

    cut_assert_equal_int(ROUND_NULL, round_addTrump(NULL, trump));
    cut_assert_equal_int(CARD_NULL, round_addTrump(round, NULL));
    cut_assert_operator_int(0, >, round_addTrump(NULL, NULL));
    cut_assert_equal_int(NO_ERROR, round_addTrump(round, trump));
    cut_assert_equal_pointer(trump, round->trump);

    round_deleteRound(&round);
}

