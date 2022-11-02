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
	for (int i = 0; i != (int)args.size(); ++i)
	{
		target = this->server->getClient(args.at(i));
		if (target != nullp)
        {
			std::vector<Client *>::iterator it;
			for (it = channel->getfdBan()->begin(); it != channel->getfdBan()->end(); it++)
			{
				if ((*it)->getFd() == target->getFd())
				{
					channel->getfdBan()->erase(it);
					client->reply("unbanned \n");
				}
				return;
			}
        }
	}
}