#include "SimpleAnimationWhist.h"

SimpleAnimationWhist::SimpleAnimationWhist(SDL_Surface *screen, int x, int y)
{
    this->screen = screen;
    destImage.x = x;
    destImage.y = y;
    image = IMG_Load("images/whist.png");
}

SimpleAnimationWhist::~SimpleAnimationWhist()
{
    SDL_FreeSurface(image);
}

void SimpleAnimationWhist::SetY(int y)
{
    destImage.y = y;
}

void SimpleAnimationWhist::ShowSimpleAnimation()
{
    SDL_BlitSurface(image, 0, screen, &destImage);
}

