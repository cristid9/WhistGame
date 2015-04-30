#ifndef _PLAYERS_H__
#define _PLAYERS_H__

#include <libWhistGame.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Players
{
    public:
        Players(SDL_Window *window, struct Game *game);
        virtual~ Players();
        void Show();
        void UpdateScore();
        void UpdateBid(struct Player *player);
        void UpdateTook(struct Player *player);
        void SelectPlayer(struct Player *player);
        void DeselectPlayer();

    private:
        void LoadImages();
        void FreePlayers();
        int getPlayerID(struct Player *player);
        struct Game *game;
        TTF_Font *font;
        SDL_Rect dest;
        SDL_Color color = {0, 0, 0};
        SDL_Surface *select, *players[MAX_GAME_PLAYERS], *screen, *text;
        int idSelectedPlayer = -1;
};

#endif

