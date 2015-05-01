#ifndef SERVER_HPP
#define SERVER_HPP

#include "Connection.h"

namespace WhistGame {

class Server
{
    public:
        Server(unsigned short port) :
            Acceptor(Service,
                     boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
                                                    port)),
            serverSocket(Service)
        {

        }

        void Start()
        {
            Accept();
            Service.run();
        }

        void Stop()
        {
            Acceptor.close();
            serverSocket.close();
            Service.stop();
        }

    private:
        void Accept()
        {
            Acceptor.async_accept(serverSocket,
                [this](boost::system::error_code ec)
                {
                    if (!ec)
                    {
                        std::make_shared<WhistGame::Connection>(
                            std::move(serverSocket), &players)->Start();
                        Accept();
                    }
                }
            );
        }

        boost::asio::io_service Service;
        boost::asio::ip::tcp::acceptor Acceptor;
        boost::asio::ip::tcp::socket serverSocket;
        Players players;
};

};

#endif

