#include "Command.hpp"

NickCommand::NickCommand(Server *server, int auth) : Command(server, auth) {}

NickCommand::~NickCommand() {}

void NickCommand::execute(Client *client, std::vector<std::string> args)
{
	if (args.size() == 0)
		client->reply(client->getNickname().append("\n"));
	else
		client->setNickname(args.at(0));
}
