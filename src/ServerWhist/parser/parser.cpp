#include "parser.h"
#include <iostream>

using namespace std;

namespace WhistGame {

Parser::Parser()
{

}

Parser::~Parser()
{

}

string Parser::ParseMessage(string& message, char delimiter)
{
    size_t found = message.find(delimiter);
    if (found != string::npos)
    {
        string command = message.substr(0, found);
        message.erase(message.begin(), message.begin() + found + 1);
        return command;
    }
    return "";
}

vector<string> Parser::ParseCommand(string& command, char delimiter)
{
    vector<string> parameters;

    size_t found = command.find(delimiter);
    while (found != string::npos)
    {
        parameters.push_back(command.substr(0, found));
        command.erase(command.begin(), command.begin() + found + 1);
        found = command.find(delimiter);
    }

    if (command.size() > 0)
    {
        parameters.push_back(command);
        command = "";
    }

    return parameters;
}

} //end namespace

