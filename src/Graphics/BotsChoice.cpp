#include "BotsChoice.h"

BotsChoice::BotsChoice(SDL_Surface *screen, int x, int y)
{
    this->x = x;
    this->y = y;
    this->screen = screen;
    choiceImages.push_back(IMG_Load("images/2.png"));
    choiceImages.push_back(IMG_Load("images/3.png"));
    choiceImages.push_back(IMG_Load("images/4.png"));
    choiceImages.push_back(IMG_Load("images/5.png"));
    imagesNumbers.push_back(IMG_Load("images/2c.png"));
    imagesNumbers.push_back(IMG_Load("images/3c.png"));
    imagesNumbers.push_back(IMG_Load("images/4c.png"));
    imagesNumbers.push_back(IMG_Load("images/5c.png"));
}

BotsChoice::~BotsChoice()
{
    for (auto choiceImage : choiceImages)
        SDL_FreeSurface(choiceImage);
    for (auto imageNumber : imagesNumbers)
        SDL_FreeSurface(imageNumber);
}

void BotsChoice::SetX(int x)
{
    this->x = x;
}

void BotsChoice::SetY(int y)
{
    this->y = y;
}

void BotsChoice::Show()
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_BlitSurface(choiceImages[currentImage], 0, screen, &dest);
    if (clicked)
    {
        dest.x = x + (width - widthImageNumber);
        dest.y += height + 1 - heightImageNumber;
        for (auto imageNumber : imagesNumbers)
        {
            dest.y += (1 + heightImageNumber);
            SDL_BlitSurface(imageNumber, 0, screen, &dest);
        }
    }
}

bool BotsChoice::Clicked(int mouseX, int mouseY)
{
    if (mouseX >= x + 165 && mouseX <= x + width &&
        mouseY >= y && mouseY <= y + height)
    {
        if (clicked)
            clicked = false;
        else
            clicked = true;
        return true;
    }

    if (clicked)
    {
        if (mouseX >= x + width - widthImageNumber && mouseX <= x + width)
        {
            int p = y + height + 1;
            for (auto i = 0u; i < imagesNumbers.size(); i++)
            {
                if (mouseY >= p && mouseY <= p + heightImageNumber)
                {
                    currentImage = i;
                    clicked = false;
                    return true;
                }
                p += heightImageNumber + 1;
            }
        }
    }

    clicked = false;
    return false;
}

bool BotsChoice::Selected(int mouseX, int mouseY)
{
    if (mouseX >= x + 165 && mouseX <= x + width + 165 &&
        mouseY >= y && mouseY <= y + height)
        return true;

    if (clicked)
    {
        if (mouseX >= x + width - widthImageNumber && mouseX <= x + width)
        {
            int p = y + height + 1;
            for (auto i = 0u; i < imagesNumbers.size(); i++)
            {
                if (mouseY >= p && mouseY <= p + heightImageNumber)
                    return true;
                p += heightImageNumber + 1;
            }
        }
    }

    return false;
}

int BotsChoice::GetBots()
{
    return currentImage + 2;
}

