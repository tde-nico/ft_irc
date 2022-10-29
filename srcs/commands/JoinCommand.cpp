#include "Command.hpp"

JoinCommand::JoinCommand(Server *server, int auth) : Command(server, auth) {}

JoinCommand::~JoinCommand() {}

void	JoinCommand::execute(Client *client, std::vector<std::string> args)
{
	if ((int)args.size() != 1)
	{
		client->reply("Wrong number of arguments\n");
		return ;
	}
	std::string	name = args.at(0);
	Channel	*channel = client->getChannel();
	if (channel != nullp)
	{
		client->reply("You are already in a channel\n");
		return ;
	}
	channel = this->server->getChannel(name);
	if (channel == nullp)
		channel = this->server->createChannel(name, client);
	client->join(channel);
}
