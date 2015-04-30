#include "PlayerCards.h"

using namespace std;

PlayerCards::PlayerCards(SDL_Surface *screen, struct Player *player,
                         struct Game *game)
{
    this->screen = screen;
    this->player = player;
    this->game   = game;
    select = IMG_Load("images/selectCard.png");
}

PlayerCards::~PlayerCards()
{
    SDL_FreeSurface(select);
}

int PlayerCards::getCardId(int x, int y)
{
    int x2 = 10;
    if (y >= 556 && y <= 666)
        for (int i = 0; i < MAX_CARDS; i++)
        {
            if (x >= x2 && x <= x2 + 76)
                return i;
            x2 += 86;
        }

    return -1;
}

void PlayerCards::Select(int x, int y)
{
    int id = getCardId(x, y);
    int cardsNumber = player_getCardsNumber(player);

    if (id == -1 || id >= cardsNumber)
        return;

    SDL_Rect dest;
    dest.x = 10 + id * 86;
    dest.y = 556;

    SDL_BlitSurface(select, 0, screen, &dest);
}

bool PlayerCards::Clicked(int x, int y)
{
    int id = getCardId(x, y);
    if (id > -1)
    {
        int ID = player_getIdNumberthCardWhichIsNotNull(player, id + 1);
        if (ID < 0)
            return false;
        if (hand_checkCard(game->rounds[game->currentRound]->hand, player,
            ID, game->rounds[game->currentRound]->trump))
        {
            hand_addCard(game->rounds[game->currentRound]->hand, player,
                         &(player->hand[ID]));
            return true;
        }
    }
    return false;
}

void PlayerCards::ShowCards()
{
    static int check = 0;
    static vector<SDL_Surface*> cards;
    if (!check)
    {
        check++;
        string str;
        for (int i = 1; i <= 48; i++)
        {
            str = "images/76x110/";
            str += to_string(i);
            str += ".png";
            cards.push_back(IMG_Load(str.c_str()));
        }
    }

    SDL_Rect dest;
    dest.x = 10;
    dest.y = 556;
    for (int i = 0; i < MAX_CARDS; i++)
        if (player->hand[i] != NULL)
        {
            SDL_BlitSurface(cards[getCardId(player->hand[i])],
                            0, screen, &dest);
            dest.x += 86;
        }
}

int PlayerCards::getCardId(struct Card *card)
{
    int no;
    if (card->value > 10)
        no = (card->value - 4) * 4;
    else
        no = (card->value - 3) * 4;

    switch (card->suit)
    {
        case DIAMONDS:
            no += 4;
            break;
        case HEARTS:
            no += 3;
            break;
        case CLUBS:
            no += 2;
            break;
        case SPADES:
            no += 1;
            break;
        case SuitEnd:
            break;
    }

    return no - 1;
}

