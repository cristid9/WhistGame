#include "Symbol.h"
#include <ctime>
#include <cstdlib>


Symbol::Symbol(const char* symbolPath, int width, int height, SDL_Window *win)
{
    this->width = width;
    this->height = height;
    image = IMG_Load(symbolPath);

    static int i = 0;
    if (i == 0)
    {
        srand((unsigned int)time(NULL));
        i++;
    }

    SDL_GetWindowSize(win, &w, &h);
    w -= width;
    h -= height;

    x = rand() % (w - width);
    y = rand() % (h - height);
    direction = rand() % 4 + 1;
}

Symbol::~Symbol()
{
    SDL_FreeSurface(image);
}

void Symbol::Show(SDL_Surface* surface)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_BlitSurface(image, NULL, surface, &dest);
}

void Symbol::Move()
{
    if (x == 1 && y == 1)
    {
            direction = 4;
            x += 5;
            y += 5;
            return;
    }
    if (x == 1 && y == h)
    {
        direction = 3;
        x += 5;
        y -= 5;
        return;
    }
    if (x == w && y == 1)
    {
        direction = 2;
        x -= 5;
        y += 5;
        return;
    }
    if (x == w && y == w)
    {
        direction = 1;
        x -= 5;
        y -= 5;
        return;
    }
    if (x == 1)
    {
        if (direction == 1)
        {
            direction = 3;
            x += 5;
            y -= 5;
            return;
        }
        if (direction == 2)
        {
            direction = 4;
            x += 5;
            y += 5;
            return;
        }
    }
    if (x == w)
    {
        if (direction == 4)
        {
            direction = 2;
            x -= 5;
            y += 5;
            return;
        }
        if (direction == 3)
        {
            direction = 1;
            x -= 5;
            y -= 5;
            return;
        }
    }
    if (y == 1)
    {
        if (direction == 3)
        {
            direction = 4;
            x += 5;
            y += 5;
            return;
        }
        if (direction == 1)
        {
            direction = 2;
            x -= 5;
            y += 5;
            return;
        }
    }
    if (y == h)
    {
        if (direction == 2)
        {
            direction = 1;
            x -= 5;
            y -= 5;
            return;
        }
        if (direction == 4)
        {
            direction = 3;
            x += 5;
            y -= 5;
            return;
        }
    }

    if (direction == 1)
    {
        if (x > 5)
            x -= 5;
        else
            x = 1;
        if (y > 5)
            y -= 5;
        else
            y = 1;
    }
    if (direction == 2)
    {
        if (x > 5)
            x -= 5;
        else
            x = 1;
        if (y < h - 5)
            y += 5;
        else
            y = h; 
    }
    if (direction == 3)
    {
        if (x < w - 5)
            x += 5;
        else
            x = w;
        if (y > 5)
            y -= 5;
        else
            y = 1;
    }
    if (direction == 4)
    {
        if (x < w - 5)
            x += 5;
        else
            x = w;
        if (y < h - 5)
            y += 5;
        else
            y = h; 
    }
}

