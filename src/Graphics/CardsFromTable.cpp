#include "CardsFromTable.h"

using namespace std;

CardsFromTable::CardsFromTable(SDL_Surface *screen, struct Game *game)
{
    this->screen = screen;
    this->game = game;
}

CardsFromTable::~CardsFromTable()
{

}

int CardsFromTable::getCardId(struct Card *card)
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

int CardsFromTable::getPlayerId(struct Player *player)
{
    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (game->players[i] == player)
            return i;

    return -1;
}

void CardsFromTable::DrawCards(struct Round *round)
{
    struct Hand *hand = round->hand;

    static int coordinates[MAX_GAME_PLAYERS][2] = { {263, 220},
                                                    {389, 160},
                                                    {574, 160},
                                                    {668, 220},
                                                    {574, 280},
                                                    {389, 280} };
    static int check = 0;
    static SDL_Rect destTrump;
    static vector<SDL_Surface*> cards;
    if (!check)
    {
        check++;
        string str;
        destTrump.x = 463;
        destTrump.y = 217;
        for (int i = 1; i <= 48; i++)
        {
            str = "images/28x40/";
            str += to_string(i);
            str += ".png";
            cards.push_back(IMG_Load(str.c_str()));
        }
    }

    if (round->trump != NULL)
        SDL_BlitSurface(cards[getCardId(round->trump)],
                        0, screen, &destTrump);

    if (hand == NULL)
        return;

    SDL_Rect dest;
    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        if (hand->cards[i] != NULL)
        {
            int id = getPlayerId(hand->players[i]);
            dest.x = coordinates[id][0];
            dest.y = coordinates[id][1];
            SDL_BlitSurface(cards[getCardId(hand->cards[i])],
                            0, screen, &dest);
        }
}

