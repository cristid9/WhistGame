#ifndef _PARSER_H__
#define _PARSER_H__

#include <string>
#include <vector>

namespace WhistGame {

class Parser
{
    public:
        Parser();
        virtual~ Parser();
        std::string ParseMessage(std::string&, char = '\n');
        std::vector<std::string> ParseCommand(std::string&, char = ' ');
};

} // end namespace

#endif

