#ifndef _BOTSCHOICE_H__
#define _BOTSCHOICE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class BotsChoice
{
    public:
        BotsChoice(SDL_Surface *screen, int x, int y);
        virtual~ BotsChoice();
        void SetX(int x);
        void SetY(int y);
        void Show();
        bool Clicked(int mouseX, int mouseY);
        bool Selected(int mouseX, int mouseY);
        int GetBots();

    private:
        SDL_Surface *screen;
        bool clicked = false;
        std::vector<SDL_Surface*> choiceImages;
        std::vector<SDL_Surface*> imagesNumbers;
        int width = 198, height = 28, x, y, currentImage = 0;
        int widthImageNumber = 34, heightImageNumber = 24;
};

#endif

