#include "Connection.h"
#include <cstdlib>

using namespace boost::asio::ip;
using namespace std;
using namespace WhistGame;

namespace WhistGame {

Connection::Connection(tcp::socket sock, Players* _players) :
    playerSocket(std::move(sock)),
    player(&playerSocket),
    processingCommand(_players, &player, &writeBuffer)
{
    players = _players;
    readBuffer = (char*) malloc(1024 * sizeof(char));
    memset(readBuffer, 0, 1024);
    players->AddPlayer(&player);
}

Connection::~Connection()
{
    free(readBuffer);
}

void Connection::Start()
{
    Read();
}

void Connection::Read()
{
    int length = strlen(readBuffer);
    auto self(shared_from_this());
    playerSocket.async_read_some(
        boost::asio::buffer((void*)(readBuffer + length), 1024 - length),
        MakeCustomAllocHandler(allocator,
            [this, self](boost::system::error_code ec, std::size_t length)
            {
                if (!ec)
                {
                    readBuffer[length] = '\0';
                    std::cout << "From client: " << readBuffer << "\n";
                    processingCommand.Processing(readBuffer);
                    readBuffer[0] = '\0';
                    // procesare readBuffer
                    Write(length);
                }
                else
                {
                    players->RemovePlayer(&player);
                }
            }
        )
    );
}

void Connection::Write(size_t length)
{
    auto self(shared_from_this());
    boost::asio::async_write(
        playerSocket,
        boost::asio::buffer(writeBuffer.c_str(), writeBuffer.size()),
        MakeCustomAllocHandler(allocator,
            [this, self](boost::system::error_code ec, std::size_t)
            {
                if (!ec)
                {
                    writeBuffer = "";
                    Read();
                }
                else
                {
                    players->RemovePlayer(&player);
                }
            }
        )
    );
}

};

