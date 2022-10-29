#include "Command.hpp"

ListCommand::ListCommand(Server *server, int auth) : Command(server, auth) {}

ListCommand::~ListCommand() {}

void ListCommand::execute(Client *client, std::vector<std::string> args)
{
	std::vector<Channel *>::iterator	it;
	std::vector<Channel *>				channels;
	std::string							msg;

	(void)args;
	channels = this->server->getChannels();
	for (it = channels.begin(); it != channels.end(); ++it)
	{
		msg.append((*it)->getName()).append(" ");
	}
	msg.append("\n");
	client->reply(msg);
}
