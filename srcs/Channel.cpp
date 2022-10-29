#include "Channel.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "Client.hpp"

Channel::Channel()
{
	users = new std::vector<Client *>  ;
}

