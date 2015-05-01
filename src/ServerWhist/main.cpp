#include "server/Server.hpp"
#include <functional>
#include <thread>

using namespace std;
using namespace WhistGame;

void ReadCommandsFromKeyboard(Server& server)
{
    string command;
    while (true)
    {
        cin >> command;
        if (command == "quit")
        {
            server.Stop();
            break;
        }
    }
}

int main(void)
{
/*    
    map<string, Command*> functions;
    string h = host;
    string c = client;
    string p = parola;
    string n = nume;
    Parser parser;
    Database database(h, c, p, n);
    functions.insert(make_pair("login", new LoginCommand(database)));

    string command = "login admin2 admin2";
    vector<string> parameters = parser.ParseCommand(command);
    cout << functions[parameters[0]]->Execute(parameters) << "\n";
*/
    Server server(12345);

    thread t(ReadCommandsFromKeyboard, std::ref(server));

    server.Start();

    t.join();

    return 0;
}

