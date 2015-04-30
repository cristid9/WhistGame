#ifndef _SYMBOL_H__
#define _SYMBOL_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Symbol
{
    public:
        Symbol(const char* symbolPath, int width, int height, SDL_Window *win);
        virtual~ Symbol();
        void Move();
        void Show(SDL_Surface* surface);

    private:
        SDL_Surface *image;
        int width, height, x, y, w, h;

        // 1 - left-up
        // 2 - left-down
        // 3 - right-up
        // 4 - right-down
        int direction; 
};

#endif

