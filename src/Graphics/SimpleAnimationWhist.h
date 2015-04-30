#ifndef _SIMPLEANIMATIONWHIST_H__
#define _SIMPLEANIMATIONWHIST_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SimpleAnimationWhist
{
    public:
        SimpleAnimationWhist(SDL_Surface *screen, int x, int y);
        virtual~ SimpleAnimationWhist();
        void ShowSimpleAnimation();
        void SetY(int y);

    private:
        SDL_Rect destImage;
        SDL_Surface *image, *screen;
};

#endif

