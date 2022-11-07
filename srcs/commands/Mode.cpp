#include "Command.hpp"

Mode::Mode(Server *server, int auth): Command(server, auth){}

Mode::~Mode(){};

void	Mode::execute(Client *client, std::vector<std::string> args)
{
    std::string str;

    if (args.size() < 2)
        return ;
    if (args.at(1).compare("+b") == 0)
    {
        str = "BAN ";
        this->server->getHandler()->handle_command(client, str.append(args[2]));
    }
     if (args.at(1).compare("-b") == 0)
     {
        str = "UNBAN ";
        this->server->getHandler()->handle_command(client, str.append(args[2]));
     }
}