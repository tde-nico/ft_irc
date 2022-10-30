#include "Command.hpp"

UserCommand::UserCommand(Server *server, int auth) : Command(server, auth) {}

UserCommand::~UserCommand() {}

void UserCommand::execute(Client *client, std::vector<std::string> args)
{
	if (args.size() == 0)
		client->reply(client->getUsername().append("\n"));
	else
		client->setUsername(args.at(0));
}
