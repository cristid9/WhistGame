#include "FireAnimationWhist.h"
#include <string>

using namespace std;

void createPath(int imageNumber, string& path)
{
    int x = imageNumber;
    int digits = 0;
    do
    {
        digits++;
        x /= 10;
    } while (x > 0);
    for (int i = 0; i < 5 - digits; i++)
        path.push_back('0');
    path += to_string(imageNumber);
    path += ".png";
}

FireAnimationWhist::FireAnimationWhist(int x, int y)
{
    destFireAnimation.x = x;
    destFireAnimation.y = y;
    screen = NULL;
    string path;
    for (int i = 0; i < 151; i++)
    {
        path = "images/whist/0_";
        createPath(i, path);
        images.push_back(IMG_Load(path.c_str()));
    }
}

FireAnimationWhist::~FireAnimationWhist()
{
    for (auto image : images)
        SDL_FreeSurface(image);
}

void FireAnimationWhist::ChangeScreen(SDL_Surface *screen)
{
    this->screen = screen;
}

void FireAnimationWhist::ShowFireAnimation()
{
    SDL_BlitSurface(images[currentImages], 0, screen, &destFireAnimation);
    if (currentImages == 150)
        currentImages = 0;
    else
        currentImages++;
}

