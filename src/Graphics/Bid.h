#ifndef _BID_H__
#define _BID_H__

#include <libWhistGame.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Bid
{
    public:
        Bid(SDL_Window *window, struct Game *game,
            struct Player *player, int x, int y);
        virtual~ Bid();
        void ShowBid(int x, int y);
        bool Clicked(int x, int y);

    private:
        void Select(int x, int y);
        int getBidValue(int x, int y);
        struct Game *game;
        struct Player *player;
        SDL_Rect dest, destBid;
        SDL_Color color;
        TTF_Font *font;
        SDL_Surface *screen, *image, *text, *select;
};

#endif

