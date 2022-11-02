#include "Command.hpp"

Msg::Msg(Server *server, int auth): Command(server, auth) {};

Msg::~Msg() {};


std::string	only_msg(std::string str)
{
	std::string	new_msg;
	size_t i = 5;
	while (str.at(i) != ' ')
		i++;
	i++;
	int z = 0;
	while (str[i])
	{
		new_msg[z] = str[i];
		z++;i++;
	}
	new_msg[z] = '\0';
	return (new_msg);
}


void Msg::execute(Client *client, std::vector<std::string> args)
{

	if ((int)args.size() < 2)
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
			target->reply(only_msg(client->getMsg()));
			return;
        }
	}
	client->reply("User not found\n");
}


