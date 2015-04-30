#include "TypeChoice.h"

TypeChoice::TypeChoice(SDL_Surface *screen, int x, int y)
{
    this->x = x;
    this->y = y;
    this->screen = screen;
    choiceImages.push_back(IMG_Load("images/1-8-1.png"));
    choiceImages.push_back(IMG_Load("images/8-1-8.png"));
    imagesTypes.push_back(IMG_Load("images/1-8-1c.png"));
    imagesTypes.push_back(IMG_Load("images/8-1-8c.png"));
}

TypeChoice::~TypeChoice()
{
    for (auto choiceImage : choiceImages)
        SDL_FreeSurface(choiceImage);
    for (auto imageType : imagesTypes)
        SDL_FreeSurface(imageType);
}

void TypeChoice::SetX(int x)
{
    this->x = x;
}

void TypeChoice::SetY(int y)
{
    this->y = y;
}

void TypeChoice::Show()
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_BlitSurface(choiceImages[currentImage], 0, screen, &dest);
    if (clicked)
    {
        dest.x = x + (width - widthImageType);
        dest.y += height + 1 - heightImageType;
        for (auto imageType : imagesTypes)
        {
            dest.y += (1 + heightImageType);
            SDL_BlitSurface(imageType, 0, screen, &dest);
        }
    }
}

bool TypeChoice::Clicked(int mouseX, int mouseY)
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
        if (mouseX >= x + width - widthImageType && mouseX <= x + width)
        {
            int p = y + height + 1;
            for (auto i = 0u; i < imagesTypes.size(); i++)
            {
                if (mouseY >= p && mouseY <= p + heightImageType)
                {
                    currentImage = i;
                    clicked = false;
                    return true;
                }
                p += heightImageType + 1;
            }
        }
    }

    clicked = false;
    return false;
}

bool TypeChoice::Selected(int mouseX, int mouseY)
{
    if (mouseX >= x + 165 && mouseX <= x + width + 165 &&
        mouseY >= y && mouseY <= y + height)
        return true;

    if (clicked)
    {
        if (mouseX >= x + width - widthImageType && mouseX <= x + width)
        {
            int p = y + height + 1;
            for (auto i = 0u; i < imagesTypes.size(); i++)
            {
                if (mouseY >= p && mouseY <= p + heightImageType)
                    return true;
                p += heightImageType + 1;
            }
        }
    }

    return false;
}

int TypeChoice::GetType()
{
    if (currentImage == 0)
        return 1;

    return 8;
}

