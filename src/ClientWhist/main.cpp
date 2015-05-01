#include <cstdlib>
#include <thread>
#include <boost/asio.hpp>
#include "CustomAllocHandler.hpp"
#include <iostream>

using namespace std;
using namespace boost;
using namespace asio;
using namespace ip;
using boost::asio::ip::tcp;

class Client : public std::enable_shared_from_this<Client>
{
    public:
        Client(boost::asio::io_service& service,
               tcp::resolver::iterator endpoint_iterator) :
            service_(service), socketServer(service)
        {
            readBuffer = (char*) malloc(1024 * sizeof(char));
            async_connect(socketServer, endpoint_iterator,
                [this](boost::system::error_code ec, tcp::resolver::iterator)
                {
                    if (!ec)
                    {
                        cout << "conectat\n";
                        Read();
                    }
                    else
                        cout << "eroare la conectare\n";
                }
            );
        }

void Read()
{
            socketServer.async_read_some(
                boost::asio::buffer(readBuffer, 1024),
                [this](boost::system::error_code ec, std::size_t length)
                {
                    if (!ec)
                    {
                        readBuffer[length] = '\0';
                        cout << "From server: " << readBuffer;
                        Read();
                    } else
                        cout << "Eroare la citire\n";
                }
            );
}

        void Write(const char* line, std::size_t size)
        {
            boost::asio::async_write(socketServer,
                boost::asio::buffer(line, size),
                [this](boost::system::error_code ec, std::size_t)
                {
                    if (ec)
                        std::cout << "Eroare la scriere\n";
                }
            );
        }

    private:
        char* readBuffer;
        io_service& service_;
        tcp::socket socketServer;
        HandlerAllocator allocator;
};

int main()
{
    boost::asio::io_service service;
    tcp::resolver r(service);
    auto endpoint_iterator = r.resolve({"localhost", "12345"});
    Client client(service, endpoint_iterator);
    thread t([&service](){service.run();});

    string line;
    while (true)
    {
        getline(cin, line);
        if (line == "quit")
        {
            service.stop();
            break;
        }

        client.Write(line.c_str(), line.size());
        line = "";
    }

    t.join();

    return 0;
}

