#include "CommandHandler.hpp"

CommandHandler::CommandHandler(Server *server, std::string const &password)
{
	this->server = server;
	this->password = password;
}

CommandHandler::~CommandHandler() {}

int	CommandHandler::handle_command(Client *client, std::string cmd)
{
	char		_msg[100];
	if (client->getStatus() == 0) // not logged
	{
		std::string	pass;

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
		sprintf(_msg, "%s:%d has logged in", client->getHostname().c_str(), client->getPort());
		console_log(_msg);
		return (0);
	}
	else if (client->getStatus() == 1)
	{
		if (exec_cmd(parse_cmd(cmd), client) == 0)
		{
			sprintf(_msg, "Unknown command : %s", cmd.c_str());
			if (send(client->getFd(), _msg, strlen(_msg), 0) < 0 )
				throw std::runtime_error("Error while sending failed command");
		/*console_log(cmd);
		if (!cmd.compare("exit\n"))
			throw std::runtime_error("exit");
		*/
		}
		
		//client->printUserInfo();
	}
	if (client->getStatus() == 2)
	{
		// TODO admin commands
	}
	return (0);
}


std::vector<std::string>	splitted_vect(std::string cmd)
{
	int i = 0, z = 0;
	std::vector<std::string>	splitted;
	char						new_string[50];

	while (cmd[i])
	{
		z = 0;
		if (cmd[i] != ' ')
		{
			while (cmd[i]  && cmd[i] != ' ') 
				new_string[z++] = cmd[i++];
			if (new_string[z - 1] == '\n')
				new_string[z - 1] = '\0';
			else
				new_string[z] = '\0';
			splitted.push_back(new_string);
		}
		else
			i++;
	}
	return splitted;
}

int		CommandHandler::parse_cmd(std::string cmd)
{
	this->_splitted_cmd = splitted_vect(cmd);

	// Compare all commands if equal return a number greater than 0
	if (_splitted_cmd.front().compare("nick") == 0) return (nick);
	if (_splitted_cmd.front().compare("connect") == 0) return (connect);
	if (_splitted_cmd.front().compare("disconnect") == 0) return (disconnect);
	if (_splitted_cmd.front().compare("join") == 0) return (join);
	if (_splitted_cmd.front().compare("part") == 0) return (part);
	if (_splitted_cmd.front().compare("set_nick") == 0) return (set_nick);
	if (_splitted_cmd.front().compare("whois") == 0) return (whois);
	if (_splitted_cmd.front().compare("msg") == 0) return (msg);
	if (_splitted_cmd.front().compare("kick") == 0) return (kick);
	if (_splitted_cmd.front().compare("ban") == 0) return (ban);
	return (0);
}

int	CommandHandler::exec_cmd(int cmd, Client *client)
{
	//return 1 if a cmd it's found or 0 if not
	switch (cmd)
	{
	case nick : return nickFun(this->_splitted_cmd, client); 
	case join : console_log("CMD: comando scelto join\n");return 1;
	case part : console_log("CMD: comando scelto part\n");return 1;
	case set_nick : console_log("CMD: comando scelto set nick\n");return 1;
	case whois : console_log("CMD: comando scelto  whois\n");return 1;
	case msg : console_log("CMD: comando scelto  msg\n");return 1;
	case kick : console_log("CMD: comando scelto set kick\n");return 1;
	case ban : console_log("CMD: comando scelto  ban\n");return 1;

	default: console_log("CMD: Command not found\n");
	break;
	}
	
	return 0;
}
