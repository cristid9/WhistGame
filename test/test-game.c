#include <game.h>
#include <errors.h>

#include <cutter.h>
#include <stdio.h>

void test_game_createGame()
{
    struct Game *game = game_createGame(1);

    int check = 0;
    if (game != NULL)
        check++;
    cut_assert_equal_int(1, check);

    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        cut_assert_equal_pointer(NULL, game->players[i]);
    for (int i = 0; i < MAX_GAME_ROUNDS; i++)
        cut_assert_equal_pointer(NULL, game->rounds[i]);

    cut_assert_equal_int(0, game->playersNumber);
    cut_assert_equal_int(1, game->gameType);
    cut_assert_equal_pointer(NULL, game->deck);

    game_deleteGame(&game);

    cut_assert_equal_pointer(NULL, game_createGame(0));
    cut_assert_equal_pointer(NULL, game_createGame(9));
}

void test_game_deleteGame()
{
    struct Game *game = game_createGame(1);
    cut_assert_equal_int(POINTER_NULL, game_deleteGame(NULL));
    cut_assert_equal_int(NO_ERROR, game_deleteGame(&game));
    cut_assert_equal_int(GAME_NULL, game_deleteGame(&game));
    cut_assert_equal_pointer(NULL, game);
}

void test_game_addDeck()
{
    struct Game *game = game_createGame(1);
    struct Deck *deck = deck_createDeck(MIN_GAME_PLAYERS);
    struct Deck *deck2 = deck;

    cut_assert_equal_int(GAME_NULL, game_addDeck(NULL, &deck));
    cut_assert_equal_int(POINTER_NULL, game_addDeck(game, NULL));
    cut_assert_equal_int(NO_ERROR, game_addDeck(game, &deck));
    cut_assert_equal_pointer(deck2, game->deck);
    cut_assert_equal_pointer(NULL, deck);
    cut_assert_equal_int(DECK_NULL, game_addDeck(game, &deck));

    deck2 = NULL;
    game_deleteGame(&game);
}

void *getName(int i, char name[4])
{
    i++;
    int j = 0;
    while (i != 0) {
        name[j++] = 48 + i % 10;
        i /= 10;
    }
    name[j] = '\0';
}

void test_game_addPlayer()
{
    struct Game *game = game_createGame(1);
    struct Player *player1;
    struct Player *player2;
    char name[4];

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        getName(i, name);
        player1 = player_createPlayer(name, 1);
        player2 = player1;
        cut_assert_equal_int(NO_ERROR, game_addPlayer(game, &player1));

        int check = 0;
        for (int j = 0; j < MAX_GAME_PLAYERS; j++)
            if (game->players[j] == player2)
                check++;
        cut_assert_equal_int(1, check);
        cut_assert_equal_pointer(NULL, player1);
        cut_assert_equal_int(DUPLICATE, game_addPlayer(game, &player2));
        player1 = player_createPlayer(name, 1);
        cut_assert_equal_int(DUPLICATE_NAME, game_addPlayer(game, &player1));
        cut_assert_equal_int(i + 1, game->playersNumber);
    }

    getName(MAX_GAME_PLAYERS, name);
    player1 = player_createPlayer(name, 1);
    cut_assert_equal_int(FULL, game_addPlayer(game, &player1));

    player_deletePlayer(&player1);
    player2 = NULL;
    game_deleteGame(&game);
}

void test_game_addRound()
{
    struct Game *game = game_createGame(1);
    struct Round *round1;
    struct Round *round2;

    round1 = round_createRound(1);
    cut_assert_equal_int(GAME_NULL, game_addRound(NULL, &round1));
    cut_assert_equal_int(POINTER_NULL, game_addRound(game, NULL));
    round_deleteRound(&round1);
    cut_assert_equal_int(ROUND_NULL, game_addRound(game, &round1));

    for (int i = 0; i < MAX_GAME_ROUNDS; i++) {
        round1 = round_createRound(1);
        round2 = round1;
        cut_assert_equal_int(NO_ERROR, game_addRound(game, &round1));
        cut_assert_equal_int(DUPLICATE, game_addRound(game, &round2));
        cut_assert_equal_pointer(NULL, round1);
        int check = 0;
        for (int j = 0; j < MAX_GAME_ROUNDS; j++)
            if (game->rounds[j] == round2)
                check++;
        cut_assert_equal_int(1, check);
    }

    round1 = round_createRound(1);
    cut_assert_equal_int(FULL, game_addRound(game, &round1));
    
    round_deleteRound(&round1);
    round2 = NULL;
    game_deleteGame(&game);
}

void test_game_addPlayersInRound()
{
    struct Game *game = game_createGame(1);
    struct Round *round = round_createRound(1);
    struct Player *players[MAX_GAME_PLAYERS];

    cut_assert_equal_int(GAME_NULL, game_addPlayersInRound(NULL, round, 0));
    cut_assert_equal_int(ROUND_NULL, game_addPlayersInRound(game, NULL, 0));
    cut_assert_equal_int(ILLEGAL_VALUE,
                         game_addPlayersInRound(game, round, -1));
    cut_assert_equal_int(INSUFFICIENT_PLAYERS,
                         game_addPlayersInRound(game, round, 0));
    round_deleteRound(&round);

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        char name[4];
        getName(i, name);
        players[i] = player_createPlayer(name, i);
        game_addPlayer(game, &players[i]);
    }

    for (int i = 0; i < MAX_GAME_PLAYERS; i++) {
        round = round_createRound(1);
        cut_assert_equal_int(NO_ERROR, game_addPlayersInRound(game, round, i));
        int position = 0;
        for (int j = i; j < MAX_GAME_PLAYERS; j++)
            cut_assert_equal_pointer(game->players[j],
                                     round->players[position++]);
        for (int j = 0; j < i; j++)
            cut_assert_equal_pointer(game->players[j],
                                     round->players[position++]);
        round_deleteRound(&round);
    }

    game_deleteGame(&game);
}

void test_game_createAndAddRounds()
{
    struct Game *game = game_createGame(1);
    game->playersNumber = MIN_GAME_PLAYERS;

    cut_assert_equal_int(GAME_NULL, game_createAndAddRounds(NULL));
    cut_assert_equal_int(NO_ERROR, game_createAndAddRounds(game));
    
    int i;
    for (i = 0; i < MIN_GAME_PLAYERS; i++)
        cut_assert_equal_int(1, game->rounds[i]->roundType);

    int type = 1;
    for (; i < MIN_GAME_PLAYERS + 6; i++) {
        type++;
        cut_assert_equal_int(type, game->rounds[i]->roundType);
    }

    for (; i < 2 * MIN_GAME_PLAYERS + 6; i++)
        cut_assert_equal_int(8, game->rounds[i]->roundType);

    for (; i < 2 * MIN_GAME_PLAYERS + 12; i++) {
        cut_assert_equal_int(type, game->rounds[i]->roundType);
        type--;
    }

    for (; i < 3 * MIN_GAME_PLAYERS + 12; i++)
        cut_assert_equal_int(1, game->rounds[i]->roundType);

    game_deleteGame(&game);
    game = game_createGame(8);
    game->playersNumber = MIN_GAME_PLAYERS;
    cut_assert_equal_int(NO_ERROR, game_createAndAddRounds(game));

    for (i = 0; i < MIN_GAME_PLAYERS; i++)
        cut_assert_equal_int(8, game->rounds[i]->roundType);

    type = 8;
    for (; i < MIN_GAME_PLAYERS + 6; i++) {
        type--;
        cut_assert_equal_int(type, game->rounds[i]->roundType);
    }

    for (; i < 2 * MIN_GAME_PLAYERS + 6; i++)
        cut_assert_equal_int(1, game->rounds[i]->roundType);

    for (; i < 2 * MIN_GAME_PLAYERS + 12; i++) {
        cut_assert_equal_int(type, game->rounds[i]->roundType);
        type++;
    }

    for (; i < 3 * MIN_GAME_PLAYERS + 12; i++)
        cut_assert_equal_int(8, game->rounds[i]->roundType);

    game_deleteGame(&game);
}

