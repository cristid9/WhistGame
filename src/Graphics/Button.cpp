#include "Button.h"

using namespace std;

Button::Button(const char* normalImagePath, const char* selectedImagePath,
               unsigned int width, unsigned int height,
               unsigned int posX, unsigned int posY)
{
    this->width = width;
    this->height = height;
    this->posX = posX;
    this->posY = posY;
    this->imagePath = normalImagePath;
    this->selectedImagePath = selectedImagePath;

    this->selectedImage = IMG_Load(selectedImagePath);
    this->normalImage = IMG_Load(normalImagePath);
}

Button::~Button()
{
    SDL_FreeSurface(normalImage);
    SDL_FreeSurface(selectedImage);
}

int Button::GetX()
{
    return posX;
}

int Button::GetY()
{
    return posY;
}

bool Button::Clicked(int x, int y)
{
    if (x >= posX && x <= posX + width &&
        y >= posY && y <= posY + height)
        return true;

    return false;
}

void Button::ShowButton(SDL_Surface* surface)
{
    SDL_Rect dest;
    dest.x = posX;
    dest.y = posY;
    if (mode == 0)
        SDL_BlitSurface(normalImage, NULL, surface, &dest);
    if (mode == 2)
        SDL_BlitSurface(selectedImage, NULL, surface, &dest);
}

void Button::SetX(int x) 
{
    posX = x;
}

void Button::SetY(int y)
{
    posY = y;
}

void Button::Selected(SDL_Surface *surface, int x, int y)
{
    if (x >= posX && x <= posX + width &&
        y >= posY && y <= posY + height)
        mode = 2;
    else
        mode = 0;
}

