#include "ProcessingCommand.h"
#include "../parser/parser.h"
#include "../database/date.h"
#include "Commands.h"
#include <map>

using namespace std;
using namespace WhistGame;

namespace WhistGame {

ProcessingCommand::ProcessingCommand(WhistGame::Players *_players,
                                     WhistGame::Player *_player,
                                     std::string *_writeBuffer)
{
    players = _players;
    player = _player;
    writeBuffer = _writeBuffer;
}

ProcessingCommand::~ProcessingCommand()
{

}

void ProcessingCommand::Processing(std::string input)
{
    static Parser parser;
    static string h = host;
    static string c = client;
    static string p = parola;
    static string n = nume;
    static Database database(h, c, p, n);
    static map<string, Command*> functions =
        {{"Login", new LoginCommand(database)},
         {"SendFriendRequest", new SendFriendRequestCommand(database)},
         {"AcceptFriendRequest", new AcceptFriendRequestCommand(database)},
         {"RefuseFriendRequest", new RefuseFriendRequestCommand(database)},
         {"ChangePassword", new ChangePasswordCommand(database)},
         {"DeleteFriend", new DeleteFriendCommand(database)},
         {"DeleteAvatar", new DeleteAvatarCommand(database)},
         {"ChangeAvatar", new ChangeAvatarCommand(database)},
         {"BlockPrivMessages", new BlockPrivMessagesCommand(database)},
         {"DeblockPrivMessages", new DeblockPrivMessagesCommand(database)},
         {"BanPlayer", new BanPlayerCommand(database)},
         {"ChangeRank", new ChangeRankCommand(database)},
         {"LostPassword", new LostPasswordCommand(database)},
         {"IsActivated", new IsActivatedCommand(database)},
//         {},
//         {},
//         {},
//         {},
//         {},
         {"Register", new RegisterCommand(database)}};

    vector<string> parameters = parser.ParseCommand(input);
    if (functions.count(parameters[0]) > 0)
        *writeBuffer = functions[parameters[0]]->Execute(parameters);
    else
        *writeBuffer = "The command doesn't exist\n";

    if (*writeBuffer == "Login:successfully\n")
        player->SetName(parameters[1]);

}

}

