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

    if (channel->getAdmin().compare(client->getNickname()) == 0)
    {
        Client *target = NULL;    
        std::string str;
        for (size_t i = 0; i < channel->getfdBan()->size(); i++)
        {
            target = channel->getfdBan()->at(i);
            if (target->getNickname() == args.at(0))
            {
                client->msgReply("Already banned");
                return ;
            }
        }
        for (size_t i = 0; i < channel->getClients().size(); i++)
        {
            str = channel->getClients().at(i)->getNickname();
            if (str.compare(args.at(0)) == 0 && str != client->getNickname())
            {
                channel->getfdBan()->push_back(channel->getClients().at(i));
                channel->kick(client, channel->getClients().at(i), "BAN");
                break;
            }
        }
    }
}