#include "ScoreWindow.h"
#include <cstdlib>
#include <string>

using namespace std;

void drawPixel(SDL_Surface *surface, int x, int y, int r, int g, int b, int a)
{
    int bpr = surface->format->BytesPerPixel;
    uint8_t *p = (uint8_t*)surface->pixels + y * surface->pitch + x * bpr;
    *p = r;
    p++;
    *p = g;
    p++;
    *p = b;
    if (bpr == 4)
    {
        p++;
        *p = a;
    }
}

void hDrawLine(SDL_Surface *surface, int x0, int x1, int y, SDL_Color color)
{
    for (int i = x0; i < x1; i++)
        drawPixel(surface, i, y, color.r, color.g, color.b, color.a);
}

void vDrawLine(SDL_Surface *surface, int x, int y0, int y1, SDL_Color color)
{
    for (int i = y0; i < y1; i++)
        drawPixel(surface, x, i, color.r, color.g, color.b, color.a);
}

void DrawRect(SDL_Surface *surface, int x0, int y0, int x1, int y1,
              SDL_Color color)
{
    for (int i = x0; i <= x1; i++)
        for (int j = y0; j <= y1; j++)
            drawPixel(surface, i, j, color.r, color.g, color.b, color.a);
}

SDL_Surface* CreateSurface(int width, int height)
{
    uint32_t rmask, gmask, bmask, amask = 0;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
#endif

    return SDL_CreateRGBSurface(0, width, height, 32, rmask,
                                gmask, bmask, amask);
}

void ScoreWindow::DrawTable()
{
    int noOfRounds;
    noOfRounds = game->playersNumber * 3 + 12;
    width = game->playersNumber * 80 + 20;
    height = noOfRounds * 20 + 24;

    image = CreateSurface(width, height);

    SDL_Color color = {255, 255, 255};
    DrawRect(image, 0, 0, width - 1, height - 1, color);

    color = {112, 146, 190};
    DrawRect(image, 0, 0, width - 1, 24, color);
    for (int i = 0; i < game->playersNumber; i++)
    {
        int x = (i + 1) * 80;
        DrawRect(image, x, 24, x + 20, height - 1, color);
    }

    color = {0, 0, 0};

    int x = 20;
    for (int i = 0; i < game->playersNumber; i++)
    {
        vDrawLine(image, (i + 1) * 80, 24, height - 1, color);
        vDrawLine(image, x, 0, height - 1, color);
        x += 80;
    }

    int y = 24;
    for (int i = 0; i < noOfRounds; i++)
    {
        hDrawLine(image, 0, width, y, color);
        y += 20;
    }

}

char* DigitToString(int digit)
{
    char *c = (char*)malloc(2);
    c[0] = '0' + digit;
    c[1] = '\0';

    return c;
}

ScoreWindow::ScoreWindow(struct Game *game)
{
    this->game = game;
    icon = IMG_Load("images/logo_game.png");
    window = NULL;
    windowID = -1;

    DrawTable();

    font = TTF_OpenFont("font.ttf", 20);

    color = {0, 0, 0};
    int noOfPlayers = 0;
    dest.x = -60;
    dest.y = 0;
    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (game->players[i] != NULL)
        {
            dest.x += 80;
            noOfPlayers++;
            text = TTF_RenderText_Solid(font, game->players[i]->name, color);
            SDL_BlitSurface(text, 0, image, &dest);
            SDL_FreeSurface(text);
        }

    dest.y = 24;
    for (int i = 0; game->rounds[i] != NULL && i < MAX_GAME_ROUNDS; i++)
    {
        text = TTF_RenderText_Solid(font,
                                    DigitToString(game->rounds[i]->roundType),
                                    color);
        dest.x = (20 - text->w) / 2;
        SDL_BlitSurface(text, 0, image, &dest);
        SDL_FreeSurface(text);
        dest.y += 20;
    }

}

ScoreWindow::~ScoreWindow()
{
    SDL_FreeSurface(image);
}

void ScoreWindow::Draw()
{
    if (window != NULL)
        SDL_UpdateWindowSurface(window);
}

void ScoreWindow::Exit()
{
    windowID = -1;
    SDL_DestroyWindow(window);
    window = NULL;
}

void ScoreWindow::Show()
{
    window = SDL_CreateWindow("Score", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width, height,
                              SDL_WINDOW_OPENGL);
    SDL_SetWindowIcon(window, icon);
    screen = SDL_GetWindowSurface(window);
    windowID = SDL_GetWindowID(window);
    SDL_BlitSurface(image, 0, screen, 0);
    SDL_UpdateWindowSurface(window);
}

int ScoreWindow::GetWindowID()
{
    return windowID;
}

void ScoreWindow::UpdateScore(int roundID)
{
    int id, noOfPlayers = 0;
    string str;

    dest.y = 24 + roundID * 20;

    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (game->players[i] != NULL)
        {
            id = round_getPlayerId(game->rounds[roundID], game->players[i]);

            color = {0, 0, 0};
            if (game->rounds[roundID]->bonus[id] == 1)
                color = {0, 255, 0};
            if (game->rounds[roundID]->bonus[id] == 2)
                color = {255, 0, 0};

            str = to_string(game->rounds[roundID]->pointsNumber[id]);
            text = TTF_RenderText_Solid(font, str.c_str(), color);

            dest.x = 20 + noOfPlayers * 80;
            dest.x += ((60 - text->w) / 2);
            SDL_BlitSurface(text, 0, image, &dest);
            SDL_FreeSurface(text);
            noOfPlayers++;

            if (game->rounds[roundID]->bids[id] ==
                game->rounds[roundID]->handsNumber[id])
                color = {0, 255, 0};
            else
                color = {255, 0, 0};

            str = to_string(game->rounds[roundID]->bids[id]);
            text = TTF_RenderText_Solid(font, str.c_str(), color);
            dest.x = noOfPlayers * 80;
            dest.x += ((20 - text->w) / 2);
            SDL_BlitSurface(text, 0, image, &dest);
            SDL_FreeSurface(text);
        }

    if (window != NULL)
    {
        SDL_BlitSurface(image, 0, screen, 0);
        SDL_UpdateWindowSurface(window);
    }
}

void ScoreWindow::DrawBid(struct Player *player, int roundID, int bid)
{
    int id = game_getPlayerPosition(game, player);
    string str = to_string(bid);

    dest.y = 24 + roundID * 20;
    dest.x = (id + 1) * 80;

    color = {0, 0, 0};
    text = TTF_RenderText_Solid(font, str.c_str(), color);

    dest.x += ((20 - text->w) / 2);

    SDL_BlitSurface(text, 0, image, &dest);
    SDL_FreeSurface(text);

    if (window != NULL)
    {
        SDL_BlitSurface(image, 0, screen, 0);
        SDL_UpdateWindowSurface(window);
    }
}

void ScoreWindow::DeleteBids(int roundID)
{
    int y = 25 + roundID * 20;
    color = {112, 146, 190};

    for (int i = 0; i < game->playersNumber; i++)
        DrawRect(image, (i + 1) * 80 + 1, y, (i + 1) * 80 + 19, y + 18, color);

    if (IsClosed())
        return;

    SDL_BlitSurface(image, 0, screen, 0);
    SDL_UpdateWindowSurface(window);
}

bool ScoreWindow::IsClosed()
{
    return (windowID == -1);
}

