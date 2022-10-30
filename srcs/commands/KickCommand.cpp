#include "Command.hpp"

KickCommand::KickCommand(Server *server, int auth) : Command(server, auth) {}

KickCommand::~KickCommand() {}

void	KickCommand::execute(Client *client, std::vector<std::string> args)
{
	if ((int)args.size() < 1)
	{
		client->reply("Wrong number of arguments\n");
		return ;
	}
	Channel	*channel = client->getChannel();
	if (channel == nullp)
	{
		client->reply("You are not in a channel\n");
		return ;
	}
	Client	*target;
	for (int i = 0; i != (int)args.size(); ++i)
	{
		target = this->server->getClient(args.at(i));
		if (target != nullp)
		{
			if (target == client)
				client->reply("You cannot kick yourself\n");
			else
				channel->kick(client, target);
		}
	}
}
