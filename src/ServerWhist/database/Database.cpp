#include "Database.h"
#include <iostream>

using namespace std;
using namespace sql;

namespace WhistGame {

#define exc PrintData(); \
            cout << "# ERR: SQLException in " << __FILE__; \
            cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl; \
            PrintData(); \
            cout << "# ERR: " << e.what(); \
            cout << " (MySQL error code: " << e.getErrorCode(); \
            cout << ", SQLState: " << e.getSQLState() << " )" << endl; 

#define sendQuery(x) string query = "SELECT * FROM players WHERE name = '"; \
                    query += name + "';"; \
                    ResultSet *result = NULL; \
                    try \
                    { \
                        result = statement->executeQuery(query); \
                        if (result->next()) \
                        { \
                            string str = result->getString(#x); \
                            delete result; \
                            return str;\
                        } \
                        else \
                        { \
                            delete result; \
                            return ""; \
                        } \
                    } catch(SQLException &e) \
                    { \
                        exc \
                        return ""; \
                    }

Database::Database(string& server, string& user, string& password,
                   string& databaseName)
{
    try
    {
        driver = get_driver_instance();
        connection = driver->connect(server, user, password);
        connection->setSchema(databaseName);
        statement = connection->createStatement();
        PrintData();
        cout << "# INFO: Connected successfully to database.\n";
    } catch(SQLException &e)
    {
        exc
        exit(0);
    }

}

Database::~Database()
{
    if (statement != NULL)
        delete statement;
    if (connection != NULL)
        delete connection;
    PrintData();
    cout << "# INFO: Disconnected successfully to database.\n";
}

string Database::Login(string& name, string& password)
{
    if (!checkString(name) || !checkString(password))
        return "Login:failed\n";

    ResultSet *result = NULL;
    string query = "SELECT * FROM players WHERE name = '" + name;
    query += "' AND password = MD5('" + password + "')";

    try 
    {
        result = statement->executeQuery(query);
    } catch(SQLException &e)
    {
        exc
        return "Login:error\n";
    }

    int rowsNumber = result->rowsCount();

    if (rowsNumber == 1)
    {
        result->next();
        if (result->getString("rank") == "0")
            return "Login:banned\n";
        if (result->getString("activated") == "0")
            return "Login:unconfirmed\n";
        PrintData();
        cout << "# INFO: Login successful. '" << name << "' connected.\n";

        string lastLogin = result->getString("loginDate");
        int32_t day = result->getInt("day");
        int64_t points = result->getInt64("points");
        AddBonus(name, lastLogin, day, points);

        delete result;

        return "Login:successfully\n";
    }

    PrintData();
    cout << "# INFO: Login failed. The name '" << name << "' and the password '";
    cout << password << "' doesn't match.\n";

    delete result;

    return "Login:failed\n";
}

void Database::AddBonus(string& name, string& lastLogin,
                        int32_t day, int64_t points)
{
    if (lastLogin == "0000-00-00 00:00:00")
    {
        string query = "UPDATE players SET points = '" + to_string(points + 50);
        query += "', day = '1', loginDate = CURRENT_TIMESTAMP() WHERE name = '";
        query += name + "';";
        try 
        {
            statement->execute(query);
        } catch(SQLException &e)
        {
            exc
        }
        return;
    }

    uint64_t days = GetDifferenceInDays(lastLogin);
    if (days == 1)
    {
        int newDay = day == 7 ? 1 : day + 1;
        string query = "UPDATE players SET points = '";
        query += to_string(points + day * 50) + "', day = '";
        query += to_string(newDay) + "', loginDate = CURRENT_TIMESTAMP()";
        query += " WHERE name = '" + name + "';";
        try
        {
            statement->execute(query);
        } catch(SQLException &e)
        {
            exc
        }
        return;
    }

    if (days > 1)
    {
        string query = "UPDATE players SET points = '";
        query += to_string(points + 50) + "', day = '1'";
        query += ", loginDate = CURRENT_TIMESTAMP()";
        query += " WHERE name = '" + name + "';";
        try
        {
            statement->execute(query);
        } catch(SQLException &e)
        {
            exc
        }
        return;
    }

    string query = "UPDATE players SET loginDate = CURRENT_TIMESTAMP()";
    query += " WHERE name = '" + name + "';";
    try
    {
        statement->execute(query);
    } catch(SQLException &e)
    {
        exc
    }

}

uint64_t Database::GetDifferenceInDays(string& lastLogin)
{
    string str = "";
    str.insert(0, lastLogin, 0, 4);
    int lastLoginYear = stoi(str);

    str = "";
    str.insert(0, lastLogin, 5, 2);
    int lastLoginMonth = stoi(str);

    str = "";
    str.insert(0, lastLogin, 8, 2);
    int lastLoginDay = stoi(str);

    tm lastLoginTime = make_tm(lastLoginYear, lastLoginMonth, lastLoginDay);
    time_t time1 = mktime(&lastLoginTime);
    time_t time2 = time(nullptr);

    if (time2 - time1 < 0)
        return 0;
    else
        return (time2 - time1) / (60 * 60 * 24);
}

tm Database::make_tm(int year, int month, int day)
{
    tm t = {0};
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;

    return t;
}

string Database::Register(string& name, string& password, string& email)
{
    if (!checkString(name) || !checkString(email) || !checkString(password))
        return "Register:failed\n";

    string query = "SELECT * FROM players WHERE name = '" + name + "';";
    ResultSet *result = NULL;

    try
    {
        result = statement->executeQuery(query);
        if (result->rowsCount() > 0)
        {
            delete result;
            return "Register:name_exist\n";
        }

        delete result;
        query = "SELECT * FROM players WHERE email = '" + email + "';";
        result = statement->executeQuery(query);
        if (result->rowsCount())
        {
            delete result;
            return "Register:mail_exist\n";
        }
        delete result;

        query = "INSERT INTO players (name, password) values('" + name;
        query += "', MD5('" + password + "'));";
        statement->execute(query);

        PrintData();
        cout << "# INFO: '" + name + "' was registered with successful.\n";

        return "Register:successfully\n";
    } catch(SQLException &e)
    {
        exc
        return "Register:error\n";
    }

    return "Register:failed\n";
}

string Database::ChangePassword(string& name, string& password,
                                string& newPassword)
{
    if (!checkString(name) || !checkString(password) ||
        !checkString(newPassword))
        return "ChangePassword:failed\n";

    string query = "SELECT * FROM players WHERE name ='" + name + "' AND ";
    query += "password = MD5('" + password + "');";
    ResultSet *result;

    try
    {
        result = statement->executeQuery(query);
        if (result->rowsCount() == 0)
            return "ChangePassword:failed\n";

        query = "UPDATE players SET password = MD5('" + newPassword + "') ";
        query += "WHERE name = '" + name + "';";
        statement->execute(query);

        PrintData();
        cout << "# INFO: '" + name + "' changed the password.\n";

        return "ChangePassword:successfully\n";
    } catch(SQLException &e)
    {
        exc
        return "ChangePassword:error\n";
    }
}

string Database::ActivateAccount(string& name, string& code)
{
    string query = "SELECT * FROM players WHERE name = '" + name + "';";
    ResultSet *result = NULL;

    try
    {
        result = statement->executeQuery(query);
        if (result->next())
        {
            string id = result->getString("id");
            if (id == code)
            {
                query = "UPDATE players SET activated = '1' WHERE name = '";
                query += name + "';";
                bool resultQuery = statement->execute(query);
                if (resultQuery)
                {
                    PrintData();
                    cout << name << " activated his account.\n";
                }
                return "ActivateAccount:successfully\n";
            }
        }
        return "ActivateAccount:failed\n";
    } catch (SQLException &e)
    {
        exc
        return "ActivateAccount:error\n";
    }

}

string Database::IsActivated(string& name)
{
    string query = "SELECT * FROM players WHERE name = '" + name + "';";
    ResultSet *result;

    try
    {
        result = statement->executeQuery(query);
        if (result->next())
        {
            if (result->getString("activated") == "1")
                return "IsActivated:yes\n";
        }
        return "IsActivated:no\n";
    } catch (SQLException &e)
    {
        exc
        return "IsActivated:error\n";
    }

}

void Database::PrintData()
{
    time_t t = time(nullptr);
    tm *time = localtime(&t);
    static vector<string> months = {"January", "February", "March", "April",
                                    "May", "June", "July", "August",
                                    "September", "October", "November",
                                    "December"};
    cout << "[";

    if (time->tm_mday < 10)
        cout << "0" << time->tm_mday << " ";
    else
        cout << time->tm_mday << " ";

    cout<< months[time->tm_mon] << " " << 1900 + time->tm_year << " ";

    if (time->tm_hour < 10)
        cout << "0" << time->tm_hour << ":";
    else
        cout << time->tm_hour << ":";

    if (time->tm_min < 10)
        cout << "0" << time->tm_min << ":";
    else
        cout << time->tm_min << ":";

    if (time->tm_sec < 10)
        cout << "0" << time->tm_sec << "]: ";
    else
        cout << time->tm_sec << "]: ";
}

bool Database::checkString(string& str)
{
    int length = str.size();
    for (int i = 0; i < length; i++)
        if (str[i] == '\n' || str[i] == '\r' || str[i] == '\"' ||
            str[i] == '\'' || str[i] == ';' || str[i] == '/' ||
            str[i] == '\\' || str[i] == '(' || str[i] == ')')
            return false;

    return true;
}


/****************************************************
 *  loc      puncte                 exp             *
 *                                                  *
 *  1.       +100% din miza         60% din miza    *
 *  2.       + 20% din miza         50% din miza    *
 *  3.       + 10% din miza         40% din miza    *
 *  4.       - 30% din miza         30% din miza    *
 *  5.       - 40% din miza         20% din miza    *
 *  6.       -100% din miza         10% din miza    *
 ****************************************************/
void Database::GameOver(string& name, int points, uint64_t exp, bool winner)
{
    string query = "SELECT * FROM players WHERE name = '" + name + "';";
    ResultSet *result;

    try
    {
        result = statement->executeQuery(query);
        if (result->next())
        {
            uint64_t currentPoints = result->getUInt64("points");
            uint64_t currentGames = result->getUInt64("games") + 1;
            uint64_t currentWonGames = result->getUInt64("wonGames");
            uint64_t currentExp = result->getUInt64("currentExp");
            uint64_t currentLevel = result->getUInt64("userLevel");

            if (winner)
                currentWonGames++;
            if (points < 0 && currentPoints < (uint64_t)-points)
                currentPoints = 0;
            else
                currentPoints += points;

            AddExp(&currentExp, &currentLevel, exp);
            query = "UPDATE players SET points = '" + to_string(currentPoints);
            query += "', games = '" + to_string(currentGames);
            query += "', wonGames = '" + to_string(currentWonGames);
            query += "', currentExp = '" + to_string(currentExp);
            query += "', userLevel = '" + to_string(currentLevel);
            query += "' WHERE name = '" + name + "';";

            statement->execute(query);
        }
    } catch(SQLException &e)
    {
        exc
    }

}

void Database::AddExp(uint64_t *currentExp, uint64_t *currentLevel,
                      uint64_t exp)
{
    if (*currentLevel == 100)
        return;

    string query = "SELECT * FROM levels WHERE levels = '";
    query += to_string(*currentLevel) + "';";
    ResultSet *result = NULL;
    uint64_t requiredExp;

    try
    {
        result = statement->executeQuery(query);
        if (result->next())
            requiredExp = result->getUInt64("exp");
    } catch (SQLException &e)
    {
        exc
        return;
    }

    while ((*currentExp) + exp >= requiredExp)
    {
        exp -= requiredExp + (*currentExp);
        *currentExp = 0;
        *currentLevel += 1;
        if (*currentLevel == 100)
            return;
        requiredExp += requiredExp * (1.0/10.0);
    }
    *currentExp += exp;

}

string Database::GetId(string& name)
{
    sendQuery(id);
}

string Database::GetGames(string& name)
{
    sendQuery(games);
}

string Database::GetWonGames(string& name)
{
    sendQuery(wonGames);
}

string Database::GetPoints(string& name)
{
    sendQuery(points);
}

string Database::GetLoginDate(string& name)
{
    sendQuery(loginDate);
}

string Database::GetRegisterDate(string& name)
{
    sendQuery(registerDate);
}

string Database::GetRank(string& name)
{
    sendQuery(rank);
}

string Database::GetAvatarName(string& name)
{
    sendQuery(avatarName);
}

string Database::GetUserLevel(string& name)
{
    sendQuery(userLevel);
}

string Database::GetUserExp(string& name)
{
    sendQuery(currentExp);
}

string Database::GetBlockedPrivMessages(string& name)
{
    sendQuery(blockedPrivMessages);
}

string Database::GetName(uint64_t id)
{
    string query = "SELECT * FROM players WHERE id = '" + to_string(id) + "';";
    ResultSet *result = NULL;

    try
    {
        result = statement->executeQuery(query);
        if (result->next())
        {
            string name = result->getString("name");
            delete result;
            return name;
        }
        return "";
    } catch(SQLException &e)
    {
        exc
        return "";
    }

}

string Database::GetFriendsName(string& name)
{
    uint64_t id = stoull(GetId(name));
    string friendsName = "FriendsName:";
    string query = "SELECT * FROM friends WHERE userId ='" + to_string(id);
    query += "' OR friendId = '" + to_string(id) + "';";
    ResultSet *result = NULL;
    ResultSet *resultFriends = NULL;
    string rank;

    try
    {
        uint64_t id1, id2, friendId;
        result = statement->executeQuery(query);
        while (result->next())
        {
            id1 = result->getUInt64("userId");
            id2 = result->getUInt64("friendId");
            friendId = id1 == id ? id2 : id1;
            query = "SELECT * FROM players WHERE id = '" + to_string(friendId);
            query += "';";
            resultFriends = statement->executeQuery(query);
            if (resultFriends->next())
            {
                rank = resultFriends->getString("rank");
                friendsName += GetRankName(rank);
                friendsName += resultFriends->getString("name") + ";";
            }
            delete resultFriends;
        }
        delete result;
        return friendsName;
    } catch (SQLException &e)
    {
        exc
        friendsName += "error";
    }

    return friendsName;
}

string Database::SendFriendRequest(string& senderName, string& receiverName)
{
    string query = "INSERT INTO friendRequests (senderId, receiverId) values(";
    query += GetId(senderName) + ", " + GetId(receiverName) + ");";
    string content;

    try
    {
        if (!statement->execute(query))
            return "SendFriendRequest:failed\n";
        string receiverId = GetId(receiverName);
        string senderId = GetId(senderName);
        content = senderName + " sent you friend request.";
        SendNotification(receiverId, content);
        content = "You have sent friend request to " + receiverName +".";
        SendNotification(senderId, content);
        return "SendFriendRequest:successfully\n";
    } catch (SQLException &e)
    {
        exc
        return "SendFriendRequest:error\n";
    }

}

string Database::AcceptFriendRequest(string& senderName, string& receiverName)
{
    string receiverId = GetId(receiverName);
    string senderId = GetId(senderName);
    string queryDelete = "DELETE FROM friendRequests WHERE senderId = '";
    queryDelete += receiverId + "' AND receiverId = '" + senderId + "';";
    string queryInsert = "INSERT INTO friends (userId, friendId) VALUES(";
    queryInsert += receiverId + ", " + senderId + ");";
    string content;

    try
    {
        if (!statement->execute(queryDelete))
            return "AcceptFriendRequest:failed\n";
        statement->execute(queryInsert);
        content = senderName + " accepted your friend request.";
        SendNotification(receiverId, content);
        content = "You became friend with " + receiverName + ".";
        SendNotification(senderId, content);
        return "AcceptFriendRequest:successfully\n";
    } catch (SQLException &e)
    {
        exc
        return "AcceptFriendRequest:error\n";
    }

}

string Database::RefuseFriendRequest(string& senderName, string& receiverName)
{
    string receiverId = GetId(receiverName);
    string senderId = GetId(senderName);
    string queryDelete = "DELETE FROM friendRequests WHERE senderId = '";
    queryDelete += receiverId + "' AND receiverId = '" + senderId + "';";
    string content;

    try
    {
        if (!statement->execute(queryDelete))
            return "RefuseFriendRequest:failed\n";
        content = senderName + " refused your friend request.";
        SendNotification(receiverId, content);
        content = "You have refused the friend request sent of " + receiverName;
        content += ".";
        SendNotification(senderId, content);
        return "RefuseFriendRequest:successfully\n";
    } catch (SQLException &e)
    {
        exc
        return "RefuseFriendRequest:error\n";
    }

}

string Database::DeleteFriend(string& userName, string& friendName)
{
    string userId = GetId(userName);
    string friendId = GetId(friendName);
    string query = "DELETE FROM friends WHERE (userId = '" + userId;
    query += "' AND friendId = '" + friendId + "') OR (userId = '" + friendId;
    query += "' AND friendId = '" + userId + "');";
    string content;

    try
    {
        if (!statement->execute(query))
            return "DeleteFriend:failed\n";
        content = userName + " removed you from friends.";
        SendNotification(friendId, content);
        content = "You have removed from friends on " + friendName + ".";
        SendNotification(userId, content);
        return "DeleteFriend:successfully\n";
    } catch (SQLException &e)
    {
        exc
        return "DeleteFriend:error\n";
    }

}

string Database::DeleteAvatar(string& userName)
{
    try
    {
        string query = "UPDATE players SET avatarName = 'default.png' WHERE";
        query += "name = '" + userName + "';";
        if (statement->execute(query))
            return "DeleteAvatar:successfully\n";
        return "DeleteAvatar:failed\n";
    } catch (SQLException &e)
    {
        exc
        return "DeleteAvatar:error\n";
    }

}

string Database::BlockPrivMessages(string& userName)
{
    string query = "UPDATE players SET blockedPrivMessages = '1' WHERE ";
    query += "name = '" + userName + "';";

    try
    {
        if (statement->execute(query))
            return "BlockPrivMessages:successfully\n";
        return "BlockPrivMessages:failed\n";
    } catch (SQLException &e)
    {
        exc
        return "BlockPrivMessages:error\n";
    }

}

string Database::DeblockPrivMessages(string& userName)
{
    string query = "UPDATE players SET blockedPrivMessages = '0' WHERE ";
    query += "name = '" + userName + "';";

    try
    {
        if (statement->execute(query))
            return "DeblockPrivMessages:successfully\n";
        return "DeblockPrivMessages:failed\n";
    } catch (SQLException &e)
    {
        exc
        return "DeblockPrivMessages:error\n";
    }

}

string Database::ChangeAvatar(string& userName, string& extension)
{
    try
    {
        string userId = GetId(userName);
        if (userId == "")
            return "ChangeAvatar:failed\n";
        string query = "UPDATE players SET avatarName = '" + userId;
        query += "." + extension + "' WHERE name = '" + userName + "';";
        statement->execute(query);
        return "ChangeAvatar:successfully\n";
    } catch (SQLException &e)
    {
        exc
        return "ChangeAvatar:error\n";
    }

}

bool Database::checkRank(string& rank)
{
    if (rank != "[ADMIN]" && rank != "[VIP]" && rank != "[OWNER]" &&
        rank != "[CO-OWNER]")
        return false;

    return true;
}

string Database::ChangeRank(string& userName, string& rank)
{
    string query = "UPDATE players SET rank = '" + rank + "' WHERE ";
    query += "name = '" + userName + "';";
    
    try
    {
        if (statement->execute(query))
            return "ChangeRank:successfully\n";
        else
            return "ChangeRank:wrongName\n";
    } catch (SQLException &e)
    {
        exc
        return "ChangeRank:error\n";
    }

}

string Database::BanPlayer(string& userName, string& days)
{
    string id = GetId(userName);
    string query = "INSERT INTO blacklist(userId, period) values(" + id;
    query += ", " + days + ");";

    try
    {
        if (statement->execute(query))
            return "BanPlayer:successfully\n";
        return "BanPlayer:failed\n";
    } catch (SQLException &e)
    {
        return "BanPlayer:error\n";
    }

}

string Database::GetRankName(string& rank)
{
    if (rank == "2")
        return "[VIP] ";
    if (rank == "3")
        return "[ADMIN] ";
    if (rank == "4")
        return "[CO-OWNER] ";
    if (rank == "5")
        return "[OWNER] ";

    return "";
}

void Database::SendNotification(string& id, string& content)
{
    string query = "INSERT INTO notifications(userId, content) values(";
    query += id + ", '" + content + "');";

    try
    {
        statement->execute(query);
    } catch (SQLException &e)
    {
        exc
    }

}

string Database::GeneratePassword()
{
    static std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static random_device rd;
    static default_random_engine re(rd());
    static uniform_int_distribution<int> generator(0, 61);
    string password;

    for (int i = 0; i < 10; i++)
        password += chars[generator(re)];

    return password;
}

string Database::LostPassword(string& userName, string& mail)
{
    string query = "SELECT * FROM players WHERE name = '" + userName;
    query += "', email = '" + mail + "';";
    ResultSet *result = NULL;
    string resultString = "LostPassword:successfully:";

    try
    {
        result = statement->executeQuery(query);
        if (result->next())
        {
            string password = GeneratePassword();
            query = "UPDATE players SET password = MD5('" + password + "');";
            statement->execute(query);
            return resultString + password + "\n";
        }
        return "LostPassword:failed\n";
    } catch (SQLException &e)
    {
        exc
        return "LostPassword:error\n";
    }

}

}; //end namespace WhistGame

