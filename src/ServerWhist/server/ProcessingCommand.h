#ifndef _PROCESSINGCOMMAND_H__
#define _PROCESSINGCOMMAND_H__

#include "Players.h"

namespace WhistGame {

class ProcessingCommand
{
    public:
        ProcessingCommand(WhistGame::Players*, WhistGame::Player*,
                          std::string*);
        virtual~ ProcessingCommand();
        void Processing(std::string);
    private:
        WhistGame::Players *players;
        WhistGame::Player *player;
        std::string *writeBuffer;
};

}

#endif

