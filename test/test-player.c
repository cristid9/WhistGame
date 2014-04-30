#include <player.h>
#include <constants.h>
#include <errors.h>

#include <cutter.h>

void test_player_createPlayer()
{
    struct Player *player;
    cut_assert_equal_pointer(NULL, player_createPlayer(NULL, 1));

    char *name[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J" };
    for (int i = 0; i < 10; i++) {
        player = player_createPlayer(name[i], i);
        int check = 0;
        if (player == NULL)
            check++;
        cut_assert_equal_int(0, check);
        cut_assert_equal_int(i, player->isHuman);
        cut_assert_equal_string(name[i], player->name);
        for (int j = 0; j < MAX_CARDS; j++)
            if (player->hand[j] != NULL)
                check++;
        cut_assert_equal_int(0, check);
    }
}

