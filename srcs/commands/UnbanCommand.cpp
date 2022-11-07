#include "Command.hpp"

UnBan::UnBan(Server *server, int auth): Command(server, auth) {}

UnBan::~UnBan() {};


void UnBan::execute(Client *client, std::vector<std::string> args)
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
	if (client->getNickname().compare(channel->getAdmin()) == 0)
	{
			target = this->server->getClient(args.at(0));
			if (target != nullp)
			{
				std::vector<Client *>::iterator it;
				for (it = channel->getfdBan()->begin(); it != channel->getfdBan()->end(); it++)
				{
					if ((*it)->getNickname() == target->getNickname())
					{
						channel->broadcast(RPL_MODE((*it)->getPrefix(), channel->getName(), "-b", target->getNickname()));

						channel->getfdBan()->erase(it);
						return;
					}
				}
			}
	}
}