#ifndef _DATABASE_H__
#define _DATABASE_H__

#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <string>
#include <vector>
#include <ctime>
#include <random>

namespace WhistGame {

class Database
{
    public:
        Database(std::string&, std::string&, std::string&, std::string&);
        virtual~ Database();
        std::string Register(std::string&, std::string&, std::string&);
        std::string Login(std::string&, std::string&);
        std::string ChangePassword(std::string&, std::string&, std::string&);
        void GameOver(std::string&, int points, uint64_t exp, bool winner);

        std::string GetId(std::string&);
        std::string GetGames(std::string&);
        std::string GetWonGames(std::string&);
        std::string GetPoints(std::string&);
        std::string GetRegisterDate(std::string&);
        std::string GetLoginDate(std::string&);
        std::string GetFriendsName(std::string&);
        std::string GetAvatarName(std::string&);
        std::string GetRank(std::string&);
        std::string GetUserLevel(std::string&);
        std::string GetUserExp(std::string&);
        std::string GetNameWithRank(std::string&);
        std::string GetBlockedPrivMessages(std::string&);

        std::string ActivateAccount(std::string&, std::string&);
        std::string IsActivated(std::string&);
        std::string SendFriendRequest(std::string&, std::string&);
        std::string AcceptFriendRequest(std::string&, std::string&);
        std::string RefuseFriendRequest(std::string&, std::string&);
        std::string DeleteFriend(std::string&, std::string&);
        std::string DeleteAvatar(std::string&);
        std::string ChangeAvatar(std::string&, std::string&);
        std::string BlockPrivMessages(std::string&);
        std::string DeblockPrivMessages(std::string&);
        std::string BanPlayer(std::string&, std::string&);
        std::string ChangeRank(std::string&, std::string&);
        std::string LostPassword(std::string&, std::string&);
    private:
        sql::Driver *driver = NULL;
        sql::Connection *connection = NULL;
        sql::Statement *statement = NULL;

        bool checkRank(std::string& rank);
        bool checkString(std::string& str);
        uint64_t GetDifferenceInDays(std::string& lastLogin);
        std::tm make_tm(int year, int month, int day);
        std::string GeneratePassword();
        std::string GetRankName(std::string& rank);
        std::string GetName(uint64_t);
        void SendNotification(std::string&, std::string&);
        void PrintData();
        void AddExp(uint64_t*, uint64_t*, uint64_t);
        void AddBonus(std::string& name, std::string& lastLogin,
                      int32_t day, int64_t points);
};

}; //end namespace WhistGame

#endif

