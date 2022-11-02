#include "Command.hpp"

Ban::Ban(Server *server, int auth): Command(server, auth){}

Ban::~Ban(){};

void	Ban::execute(Client *client, std::vector<std::string> args)
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
            size_t z = 0;
            if (target->getFd() != client->getFd())
            {
                while (z < channel->getfdBan()->size())
                {
                        if (channel->getfdBan()->at(z)->getFd() == target->getFd())
                        {
                            client->reply("already banned\n");
                            return;
                        }
                        z++;
                }
                channel->getfdBan()->push_back(target);
                channel->kick(client, target, "ban");
            }
            else
            {
                client->reply("you cannot ban yourself\n");
            }
            break;
        }
	}
}