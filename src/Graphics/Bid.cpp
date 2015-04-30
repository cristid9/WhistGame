#include "Bid.h"

using namespace std;

#define square(x) ((x) * (x))

Bid::Bid(SDL_Window *window, struct Game *game,
         struct Player *player, int x, int y)
{
    this->game = game;
    this->player = player;
    screen = SDL_GetWindowSurface(window);
    image = NULL;
    select = IMG_Load("images/select_bid.png");
    text = NULL;
    destBid.x = x;
    destBid.y = y;
    dest.y = 20;
    font = TTF_OpenFont("font.ttf", 20);
}

Bid::~Bid()
{
    if (image != NULL)
        SDL_FreeSurface(image);
}

char* bid_DigitToString(int digit)
{
    char *c = (char*)malloc(2);
    c[0] = '0' + digit;
    c[1] = '\0';

    return c;
}

void Bid::ShowBid(int x, int y)
{
    image = IMG_Load("images/bid.png");

    dest.x = 20;
    dest.y = 20;
    for (int i = 0; i <= MAX_CARDS; i++)
    {
        if (round_checkBid(game->rounds[game->currentRound], player, i) == 0)
            color = {0, 0, 0};
        else
            color = {132, 132, 132};

        text = TTF_RenderText_Solid(font, bid_DigitToString(i), color);
        SDL_BlitSurface(text, 0, image, &dest);
        SDL_FreeSurface(text);
        dest.x += 31;
    }

    Select(x, y);

    SDL_BlitSurface(image, 0, screen, &destBid);
}

void Bid::Select(int x, int y)
{
    int value = getBidValue(x, y);

    if (value == -1 ||
        round_checkBid(game->rounds[game->currentRound], player, value) != 0)
        return;

    dest.x = 16.5 + 31 * value;
    dest.y = 22;
    SDL_BlitSurface(select, 0, image, &dest);
}

int Bid::getBidValue(int x, int y)
{
    if (y < 22 + destBid.y && y > 42 + destBid.y)
        return -1;

    int radius = 10;
    int CircleX = 26.5 + destBid.x;
    int CircleY = 32 + destBid.y;

    for (int i = 0; i <= MAX_CARDS; i++)
        if (square(radius) >= square(x - CircleX) + square(y - CircleY))
            return i;
        else
            CircleX += 31;

    return -1;
}

bool Bid::Clicked(int x, int y)
{
    int bid = getBidValue(x, y);
    if (round_placeBid(game->rounds[game->currentRound], player, bid) ==
        FUNCTION_NO_ERROR)
        return true;

    return false;
}

