#ifndef _CARDSFROMTABLE_H__
#define _CARDSFROMTABLE_H__

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <libWhistGame.h>
#include <vector>

class CardsFromTable
{
    public:
        CardsFromTable(SDL_Surface *screen, struct Game *game);
        virtual~ CardsFromTable();
        void DrawCards(struct Round *round);

    private:
        int getPlayerId(struct Player *player);
        int getCardId(struct Card *card);
        SDL_Surface *screen;
        struct Game *game;
};

#endif

