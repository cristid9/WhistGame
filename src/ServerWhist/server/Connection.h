#ifndef _CONNECTION_H__
#define _CONNECTION_H__

#include "CustomAllocHandler.hpp"
#include "ProcessingCommand.h"
#include <iostream>

namespace WhistGame {

class Connection : public std::enable_shared_from_this<Connection>
{
    public:
        Connection(boost::asio::ip::tcp::socket sock,
                   WhistGame::Players* _players);
        virtual~ Connection();
        void Start();
    private:
        void Read();
        void Write(std::size_t length);

        boost::asio::ip::tcp::socket playerSocket;
        HandlerAllocator allocator;
        std::string writeBuffer;
        Players *players;
        Player player;
        ProcessingCommand processingCommand;
        char *readBuffer;
};

};

#endif

