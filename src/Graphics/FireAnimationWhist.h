#ifndef _FIREANIMATIONWHIST_H__
#define _FIREANIMATIONWHIST_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class FireAnimationWhist
{
    public:
        FireAnimationWhist(int x, int y);
        virtual~ FireAnimationWhist();
        void ShowFireAnimation();
        void ChangeScreen(SDL_Surface *screen);

    private:
        std::vector<SDL_Surface*> images;
        int currentImages = 0;
        SDL_Rect destFireAnimation;
        SDL_Surface *screen;
};

#endif

