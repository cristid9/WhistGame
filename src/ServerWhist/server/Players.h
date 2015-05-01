#ifndef _PLAYERS_H_
#define _PLAYERS_H_

#include "Player.h"
#include <list>

namespace WhistGame {

class Players
{
    public:
        Players();
        virtual~ Players();
        void AddPlayer(WhistGame::Player*);
        WhistGame::Player* GetPlayer(std::string&);
        void RemovePlayer(WhistGame::Player*);
    private:
        std::list<WhistGame::Player*> players;
};

};

#endif

