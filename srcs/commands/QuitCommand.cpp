#include "Command.hpp"

QuitCommand::QuitCommand(Server *server, int auth) : Command(server, auth) {}

QuitCommand::~QuitCommand() {}

void QuitCommand::execute(Client *client, std::vector<std::string> args)
{
	(void)args;
	client->leave();
}
