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

	str.append("Nickname: ").append(client->getNickname()).append("\n");
	str.append("Username: ").append(client->getUsername()).append("\n");
	str.append("Hostname: ").append(client->getHostname()).append("\n");
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
	Channel	*channel = client->getChannel();
	if (channel == nullp)
		return ;
	Client	*target;
	for (int i = 0; i != (int)args.size(); ++i)
	{
		target = this->server->getClient(args.at(i));
		if (target != nullp)
        {
            client->reply(make_info(client));
			break;
        }
	}
}