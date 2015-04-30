#ifndef _SCOREWINDOW_H__
#define _SCOREWINDOW_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <libWhistGame.h>
#include <SDL2/SDL_ttf.h>

class ScoreWindow
{
    public:
        ScoreWindow(struct Game *game);
        virtual~ ScoreWindow();
        void Exit();
        void Show();
        int GetWindowID();
        void Draw();
        void UpdateScore(int roundID);
        void DrawBid(struct Player *player, int roundID, int bid);
        void DeleteBids(int roundID);
        bool IsClosed();

    private:
        void DrawTable();
        SDL_Rect dest, source;
        SDL_Color color;
        TTF_Font *font;
        int windowID;
        SDL_Window *window;
        struct Game *game;
        int width, height;
        SDL_Surface *screen, *image, *icon, *text;
};

#endif

