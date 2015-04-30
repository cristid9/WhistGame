#include "Players.h"

using namespace std;

Players::Players(SDL_Window *window, struct Game *game)
{
    this->game = game;
    this->screen = SDL_GetWindowSurface(window);
    select = IMG_Load("images/select.png");

    font = TTF_OpenFont("font.ttf", 20);

    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        players[i] = NULL;

    LoadImages();
}

Players::~Players()
{
    SDL_FreeSurface(select);
    FreePlayers();
}

void Players::FreePlayers()
{
    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (players[i] != NULL)
        {
            SDL_FreeSurface(players[i]);
            players[i] = NULL;
        }
}

void Players::LoadImages()
{
    FreePlayers();
    dest.y = 4;
    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (game->players[i] != NULL)
        {
            players[i] = IMG_Load("images/player.png");
            text = TTF_RenderText_Solid(font, game->players[i]->name, color);
            dest.x = (150 - text->w) / 2;
            SDL_BlitSurface(text, 0, players[i], &dest);
            SDL_FreeSurface(text);
        } else
            players[i] = NULL;
}

void Players::UpdateScore()
{
    LoadImages();
    int roundID = game->currentRound;
    string str;
    dest.y = 22;
    dest.x = 55;
    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (game->players[i] != NULL)
        {
            int id = round_getPlayerId(game->rounds[roundID], game->players[i]);
            str = to_string(game->rounds[roundID]->pointsNumber[id]);
            text = TTF_RenderText_Solid(font, str.c_str(), color);
            SDL_BlitSurface(text, 0, players[i], &dest);
            SDL_FreeSurface(text);
        }


}

int Players::getPlayerID(struct Player *player)
{
    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (player == game->players[i])
            return i;

    return -1;
}

void Players::UpdateBid(struct Player *player)
{
    if (player == NULL)
        return;
    string str;
    int roundID = game->currentRound;
    int id = getPlayerID(player);
    int idRound = round_getPlayerId(game->rounds[roundID], player);
    SDL_FreeSurface(players[id]);
    players[id] = IMG_Load("images/player.png");

    text = TTF_RenderText_Solid(font, player->name, color);
    dest.x = (150 - text->w) / 2;
    dest.y = 4;
    SDL_BlitSurface(text, 0, players[id], &dest);
    SDL_FreeSurface(text);

    dest.x = 55;
    dest.y = 22;
    str = to_string(game->rounds[roundID]->pointsNumber[idRound]);
    text = TTF_RenderText_Solid(font, str.c_str(), color);
    SDL_BlitSurface(text, 0, players[id], &dest);
    SDL_FreeSurface(text);

    str = to_string(game->rounds[roundID]->bids[idRound]);
    dest.y = 46;
    dest.x = 46;
    text = TTF_RenderText_Solid(font, str.c_str(), color);
    SDL_BlitSurface(text, 0, players[id], &dest);
    SDL_FreeSurface(text);
}

void Players::UpdateTook(struct Player *player)
{
    if (player == NULL)
        return;
    UpdateBid(player);
    int roundID = game->currentRound, id = getPlayerID(player);
    int idRound = round_getPlayerId(game->rounds[roundID], player);

    string str = to_string(game->rounds[roundID]->handsNumber[idRound]);
    dest.y = 74;
    dest.x = 50;
    text = TTF_RenderText_Solid(font, str.c_str(), color);
    SDL_BlitSurface(text, 0, players[id], &dest);
    SDL_FreeSurface(text);
}

void Players::Show()
{
    static int coordinates[MAX_GAME_PLAYERS][2] = { {40, 200},
                                                    {325, 25},
                                                    {500, 25},
                                                    {750, 200},
                                                    {500, 380},
                                                    {325, 380} };
    static SDL_Rect destination;
    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (game->players[i] != NULL)
        {
            destination.x = coordinates[i][0];
            destination.y = coordinates[i][1];
            SDL_BlitSurface(players[i], 0, screen, &destination);
        }

    if (idSelectedPlayer != -1)
    {
        destination.x = coordinates[idSelectedPlayer][0];
        destination.y = coordinates[idSelectedPlayer][1];
        SDL_BlitSurface(select, 0, screen, &destination);
    }
}

void Players::SelectPlayer(struct Player *player)
{
    idSelectedPlayer = getPlayerID(player);
}

void Players::DeselectPlayer()
{
    idSelectedPlayer = -1;
}

