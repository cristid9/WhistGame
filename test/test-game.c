#include <game.h>
#include <errors.h>

#include <cutter.h>

void test_game_createGame()
{
    struct Game *game = game_createGame(MIN_GAME_PLAYERS, 1);

    int check = 0;
    if (game != NULL)
        check++;
    cut_assert_equal_int(1, check);

    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        cut_assert_equal_pointer(NULL, game->players[i]);
    for (int i = 0; i < MAX_GAME_ROUNDS; i++)
        cut_assert_equal_pointer(NULL, game->rounds[i]);

    cut_assert_equal_int(MIN_GAME_PLAYERS, game->playersNumber);
    cut_assert_equal_int(1, game->gameType);
    cut_assert_equal_pointer(NULL, game->deck);

    game_deleteGame(&game);

    cut_assert_equal_pointer(NULL, game_createGame(MIN_GAME_PLAYERS - 1, 1));
    cut_assert_equal_pointer(NULL, game_createGame(MAX_GAME_PLAYERS + 1, 1));
    cut_assert_equal_pointer(NULL, game_createGame(MIN_GAME_PLAYERS, 0));
    cut_assert_equal_pointer(NULL, game_createGame(MIN_GAME_PLAYERS, 9));
    cut_assert_equal_pointer(NULL, game_createGame(MIN_GAME_PLAYERS - 1, 5));
    cut_assert_equal_pointer(NULL, game_createGame(MAX_GAME_PLAYERS + 1, 5));
}

void test_game_deleteGame()
{
    struct Game *game = game_createGame(MIN_GAME_PLAYERS, 1);
    cut_assert_equal_int(POINTER_NULL, game_deleteGame(NULL));
    cut_assert_equal_int(NO_ERROR, game_deleteGame(&game));
    cut_assert_equal_int(GAME_NULL, game_deleteGame(&game));
    cut_assert_equal_pointer(NULL, game);
}

void test_game_addDeck()
{
    struct Game *game = game_createGame(MIN_GAME_PLAYERS, 1);
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

