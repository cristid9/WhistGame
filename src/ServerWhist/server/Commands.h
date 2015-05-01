#ifndef _COMMANDS_H__
#define _COMMANDS_H__

#include "../database/Database.h"
#include "Player.h"

namespace WhistGame {

#define constructor(x) x(WhistGame::Database& database) : _database(&database) \
                        { \
                        }

#define if_wrong_command(x, message) if (parameters.size() != x) \
                                        return message

class Command
{
    public:
        virtual std::string Execute(std::vector<std::string>& parameters) = 0;
};

class LoginCommand : public Command
{
    public:
        constructor(LoginCommand)

        virtual std::string Execute(std::vector<std::string>& parameters)
        {
            if_wrong_command(3, "Wrong command\n");
            return _database->Login(parameters[1], parameters[2]);
        }

    private:
        WhistGame::Database *_database;
};

class RegisterCommand : public Command
{
    public:
        constructor(RegisterCommand)

        virtual std::string Execute(std::vector<std::string>& parameters)
        {
            if_wrong_command(4, "Wrong command\n");
            return _database->Register(parameters[1], parameters[2],
                                       parameters[3]);
        }
        
    private:
        WhistGame::Database *_database;
};

class SendFriendRequestCommand : public Command
{
    public:
        constructor(SendFriendRequestCommand)

        virtual std::string Execute(std::vector<std::string>& parameters)
        {
            if_wrong_command(3, "Wrong command\n");
            return _database->SendFriendRequest(parameters[1], parameters[2]);
        }

    private:
        WhistGame::Database *_database;
};

class AcceptFriendRequestCommand : public Command
{
    public:
        constructor(AcceptFriendRequestCommand)

        virtual std::string Execute(std::vector<std::string>& parameters)
        {
            if_wrong_command(3, "Wrong command\n");
            return _database->AcceptFriendRequest(parameters[1], parameters[2]);
        }

    private:
        WhistGame::Database *_database;
};

class RefuseFriendRequestCommand : public Command
{
    public:
        constructor(RefuseFriendRequestCommand)

        virtual std::string Execute(std::vector<std::string>& parameters)
        {
            if_wrong_command(3, "Wrong command\n");
            return _database->RefuseFriendRequest(parameters[1], parameters[2]);
        }
        
    private:
        WhistGame::Database *_database;
};

class ChangePasswordCommand : public Command
{
    public:
        constructor(ChangePasswordCommand)

        virtual std::string Execute(std::vector<std::string>& parameters)
        {
            if_wrong_command(4, "Wrong command\n");
            return _database->ChangePassword(parameters[1], parameters[2],
                                             parameters[3]);
        }
        
    private:
        WhistGame::Database *_database;
};

class DeleteFriendCommand : public Command
{
    public:
        constructor(DeleteFriendCommand)

        virtual std::string Execute(std::vector<std::string>& parameters)
        {
            if_wrong_command(3, "Wrong command\n");
            return _database->DeleteFriend(parameters[1], parameters[2]);
        }

    private:
        WhistGame::Database *_database;
};

class DeleteAvatarCommand : public Command
{
    public:
        constructor(DeleteAvatarCommand)

        virtual std::string Execute(std::vector<std::string>& parameters)
        {
            if_wrong_command(2, "Wrong command\n");
            return _database->DeleteAvatar(parameters[1]);
        }

    private:
        WhistGame::Database *_database;
};

class ChangeAvatarCommand : public Command
{
    public:
        constructor(ChangeAvatarCommand)

        virtual std::string Execute(std::vector<std::string>& parameters)
        {
            if_wrong_command(3, "Wrong command\n");
            return _database->ChangeAvatar(parameters[1], parameters[2]);
        }

    private:
        WhistGame::Database *_database;
};

class BlockPrivMessagesCommand : public Command
{
    public:
        constructor(BlockPrivMessagesCommand)

        virtual std::string Execute(std::vector<std::string>& parameters)
        {
            if_wrong_command(2, "Wrong command\n");
            return _database->BlockPrivMessages(parameters[1]);
        }

    private:
        WhistGame::Database *_database;
};

class DeblockPrivMessagesCommand : public Command
{
    public:
        constructor(DeblockPrivMessagesCommand)

        virtual std::string Execute(std::vector<std::string>& parameters)
        {
            if_wrong_command(2, "Wrong command\n");
            return _database->DeblockPrivMessages(parameters[1]);
        }

    private:
        WhistGame::Database *_database;
};

class BanPlayerCommand : public Command
{
    public:
        constructor(BanPlayerCommand)

        virtual std::string Execute(std::vector<std::string>& parameters)
        {
            if_wrong_command(3, "Wrong command\n");
            return _database->BanPlayer(parameters[1], parameters[2]);
        }

    private:
        WhistGame::Database *_database;
};

class ChangeRankCommand : public Command
{
    public:
        constructor(ChangeRankCommand)

        virtual std::string Execute(std::vector<std::string>& parameters)
        {
            if_wrong_command(4, "Wrong command\n");
            return _database->ChangeRank(parameters[2], parameters[3]);
        }

    private:
        WhistGame::Database *_database;
};

class LostPasswordCommand : public Command
{
    public:
        constructor(LostPasswordCommand)

        virtual std::string Execute(std::vector<std::string>& parameters)
        {
            if_wrong_command(3, "Wrong command\n");
            return _database->LostPassword(parameters[1], parameters[2]);
        }

    private:
        WhistGame::Database *_database;
};

class IsActivatedCommand : public Command
{
    public:
        constructor(IsActivatedCommand)

        virtual std::string Execute(std::vector<std::string>& parameters)
        {
            if_wrong_command(2, "Wrong command\n");
            return _database->IsActivated(parameters[1]);
        }

    private:
        WhistGame::Database *_database;
};

}; // end namespace

#endif

