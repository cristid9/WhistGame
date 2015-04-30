#ifndef _PLAYERCARDS_H__
#define _PLAYERCARDS_H__

#include <libWhistGame.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

class PlayerCards
{
    public:
        PlayerCards(SDL_Surface *screen, struct Player *player,
                    struct Game *game);
        virtual~ PlayerCards();
        void ShowCards();
        bool Clicked(int x, int y);
        void Select(int x, int y);

    private:
        int getCardId(struct Card *card);
        int getCardId(int x, int y);
        SDL_Surface *screen, *select;
        struct Player *player;
        struct Game *game;
};

#endif

