#include "Command.hpp"

HelpCommand::HelpCommand(Server *server, int auth) : Command(server, auth)
{
	this->help["exit"] = "disconnects from the server";
	this->help["join"] = "joins the channel specified";
	this->help["quit"] = "quits from the channel";
	this->help["list"] = "lists all the channels";
	this->help["nick"] = "displays the nickname, /nick [name]: sets the nickname";
	this->help["kick"] = "kicks out from a channel the users specified (requires admin)";
	this->help["help"] = "show the useful informations of a command, /help [cmd]: shows the specific command info";

}

HelpCommand::~HelpCommand() {}

void	HelpCommand::execute(Client *client, std::vector<std::string> args)
{
	if (args.size() == 0)
	{
		std::map<std::string, std::string>::iterator	it;
		std::string										msg;
		for (it = this->help.begin(); it != this->help.end(); ++it)
			msg.append(it->first).append(": ").append(it->second).append("\n");
		client->reply(msg);
	}
	else
	{
		std::vector<std::string>::iterator	it;
		std::string							msg;
		for (int i = 0; i != (int)args.size(); ++i)
		{
			std::map<std::string, std::string>::iterator	cmd = this->help.find(args.at(i));
			if (cmd != this->help.end())
				msg.append(args.at(i)).append(": ").append(this->help[args.at(i)]).append("\n");
			else
				msg.append(args.at(i)).append(": Command not found\n");
		}
		client->reply(msg);
	}
}
