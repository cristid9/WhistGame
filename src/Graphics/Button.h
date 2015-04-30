#ifndef _BUTTON_H__
#define _BUTTON_H__

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Button
{
    public:
        Button(const char* normalImagePath, const char* selectedImagePath,
               unsigned int width, unsigned int height,
               unsigned int posX, unsigned int posY);
        virtual~ Button();
        void ShowButton(SDL_Surface* surface);
        void SetX(int x);
        void SetY(int y);
        bool Clicked(int x, int y);
        void Selected(SDL_Surface* surface, int x, int y);
        int GetX();
        int GetY();

    private:
        int mode = 0; // 0 - normal; 1 - pressed; 2 - selected
        std::string imagePath, selectedImagePath;
        SDL_Surface *normalImage, *selectedImage;
        int width = 0, height = 0, posX = 0, posY = 0;
};

#endif

