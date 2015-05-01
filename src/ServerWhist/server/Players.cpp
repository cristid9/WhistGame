#include "Players.h"

namespace WhistGame {

Players::Players()
{

}

Players::~Players()
{

}

void Players::AddPlayer(WhistGame::Player* player)
{
    players.push_back(player);
}

WhistGame::Player* Players::GetPlayer(std::string& name)
{
    for (auto i = players.begin(); i != players.end(); i++)
        if ((*i)->GetName() == name)
            return *i;

    return NULL;
}

void Players::RemovePlayer(WhistGame::Player* player)
{
    players.remove(player);
}

}

