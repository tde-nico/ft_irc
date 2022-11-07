#include "Command.hpp"
#include <iostream>
#include <string>

/*Displays information of user requested. Includes Full
 Name, Host, Channels User is in, and Oper Status*/

WhoisCommand::WhoisCommand(Server *server, int auth): Command(server, auth) {}

WhoisCommand::~WhoisCommand() {};

std::string	make_info(Client *client)
{
	std::string		str;
	str.append("\n");
	str.append("Nickname: ").append(client->getNickname()).append("\n");
	str.append("Username: ").append(client->getUsername()).append("\n");
	str.append("Hostname: ").append(client->getHostname()).append("\n");
	if (client->getChannel() != nullp)
		str.append("Channel: ").append(client->getChannel()->getName().append("\n"));
	return (str);
}

void WhoisCommand::execute(Client *client, std::vector<std::string> args)
{
	if ((int)args.size() < 1)
	{
		client->reply("Wrong number of arguments\n");
		return ;
	}
	if (this->server->getClient(args.at(0)) == NULL)
		return;
	else
	{
		client->reply(make_info(this->server->getClient(args.at(0))));
	}
}
