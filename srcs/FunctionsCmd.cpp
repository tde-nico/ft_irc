#include "CommandHandler.hpp"
#include "Server.hpp"
#include "Client.hpp"

int			CommandHandler::nickFun(std::vector<std::string> args, Client *client)
{
    char str[100];
    
    if (args.size() == 1)
    {
        sprintf(str, "Your NickName is : %s\n", client->getNickname().c_str());
        if (send(client->getFd(), str, strlen(str), 0) == -1)
            throw std::runtime_error("Error while showing Nickname");
    }
    else
    {
        client->setNickname(args.at(1));
        sprintf(str, "You're now known as : %s\n", client->getNickname().c_str());
         if (send(client->getFd(), str, strlen(str), 0) == -1)
            throw std::runtime_error("Error while showing Nickname");
        sprintf(str, "host %s has changed Nickname : %s\n",client->getHostname().c_str(), client->getNickname().c_str());
        console_log(str);
    }
    return (1);
}