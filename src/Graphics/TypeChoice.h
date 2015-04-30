#ifndef _TYPECHOICE_H__
#define _TYPECHOICE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class TypeChoice
{
    public:
        TypeChoice(SDL_Surface *screen, int x, int y);
        virtual~ TypeChoice();
        void SetX(int x);
        void SetY(int y);
        void Show();
        bool Clicked(int mouseX, int mouseY);
        bool Selected(int mouseX, int mouseY);
        int GetType(); // 0 - for 1-8-1; 1 - for 8-1-8;

    private:
        SDL_Surface *screen;
        bool clicked = false;
        std::vector<SDL_Surface*> choiceImages;
        std::vector<SDL_Surface*> imagesTypes;
        int width = 198, height = 28, x, y, currentImage = 0;
        int widthImageType = 62, heightImageType = 24;
};

#endif

