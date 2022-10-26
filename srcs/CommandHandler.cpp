#include "CommandHandler.hpp"

CommandHandler::CommandHandler(Server *server, std::string const &password)
{
	this->server = server;
	this->password = password;
}

CommandHandler::~CommandHandler() {}

int	CommandHandler::handle_command(Client *client, std::string cmd)
{
	if (client->getStatus() == 0) // not logged
	{
		std::string	pass;
		char		msg[100];

		pass.append(this->password).append("\n");
		if (cmd.compare(pass))
		{
			if (send(client->getFd(), "Wrong password\n", strlen("Wrong password\n"), 0) == -1)
				throw std::runtime_error("Error while requesting the password");
			//this->server->handle_disconnection(client->getFd());
			// request the password at the client
			if (send(client->getFd(), "Please insert the password: ", strlen("Please insert the password: "), 0) == -1)
				throw std::runtime_error("Error while requesting the password");
			console_log("A client failed to enter the correct password");
			return (0);
		}
		client->setStatus(1);
		sprintf(msg, "%s:%d has logged in", client->getHostname().c_str(), client->getPort());
		console_log(msg);
		return (0);
	}
	else if (client->getStatus() == 1)
	{
		console_log(cmd);
		if (!cmd.compare("exit\n"))
			throw std::runtime_error("exit");
	}
	if (client->getStatus() == 2)
	{
		// TODO admin commands
	}
	return (0);
}
