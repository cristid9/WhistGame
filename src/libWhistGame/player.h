/**
 * @file player.h
 * @brief Player structure, as well as helper functions.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "deck.h"
#include "constants.h"

/**
 * @struct Player
 *
 * @brief Player structure. Structure to keep informations about a player.
 *
 * @var Player::isHuman
 *      Variable used to indicate if the player is human or robot, 0 for AI and
 *      non-zero for human.
 * @var Player::name
 *      Pointer to the name of the player.
 * @var Player::hand
 *      Pointer to the cards of the player.
 */
struct Player {
    int isHuman;
    char *name;
    struct Card *hand[MAX_CARDS];
};


#endif

