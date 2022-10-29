#include "Command.hpp"

ExitCommand::ExitCommand(Server *server, int auth) : Command(server, auth) {}

ExitCommand::~ExitCommand() {}

void	ExitCommand::execute(Client *client, std::vector<std::string> args)
{
	(void)args;
	this->server->handle_disconnection(client->getFd());
}
