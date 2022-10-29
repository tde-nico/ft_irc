#include "CommandHandler.hpp"
#include "Channel.hpp"
#include "Server.hpp"

CommandHandler::CommandHandler(Server *server, std::string const &password)
{
	this->server = server; // remove if not used
	this->password = password;
	this->prefix.append("[");
}

CommandHandler::~CommandHandler() {}

int	CommandHandler::handle_command(Client *client, std::string cmd, Server *server)
{
	char		_msg[100];
	int			ret;

	if (client->getStatus() == 0) // not logged
		return (this->log_in(client, cmd));
	else if (client->getStatus() == 1) // logged
	{
		ret = exec_cmd(parse_cmd(cmd), client, server, cmd);
		if (ret == 0)
		{
			sprintf(_msg, "Unknown command : %s", cmd.c_str());
			if (send(client->getFd(), _msg, strlen(_msg), 0) < 0 )
				throw std::runtime_error("Error while sending failed command");
		}
		else if (ret == 2)
			return (1);
	}
	if (client->getStatus() == 2) // admin
	{
		// TODO admin commands
	}
	return (0);
}

int	CommandHandler::log_in(Client *client, std::string cmd)
{
	std::string	pass;

	pass.append(this->password).append("\n");
	if (cmd.compare(pass))
	{
		if (send(client->getFd(), WRONG_PASS, strlen(WRONG_PASS), 0) == -1)
			throw std::runtime_error("Error while requesting the password");
		if (send(client->getFd(), INSERT_PASS, strlen(INSERT_PASS), 0) == -1)
			throw std::runtime_error("Error while requesting the password");
		console_log(client->log("failed to log"));
		return (0);
	}
	client->setStatus(1);
	console_log(client->log("has logged in"));
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
	if (_splitted_cmd.front().compare("exit") == 0) return (EXIT);
	return (0);
}

int	CommandHandler::exec_cmd(int cmd, Client *client, Server *server, std::string str)
{
	//if u are in a channel send all messages only
	//to channel's member
	if (client->getChannelmode() == ON || client->getChannelmode() == ON_SECOND_ENTRY)
	{
		size_t i = 0;
		size_t end = server->get_channels()->size();
		while (i < end)
		{
			//trovo il canale
			if (strcmp(server->get_channels()->at(i)->get_nameChannel().c_str(), client->getNameChannel().c_str()) == 0)
			{
				sendToChannel(server->get_channels()->at(i), str, client);
				break;
			}
			i++;
		}
		return (1);
	}
	else
	{
		//return 1 if a cmd it's found or 0 if not
		switch (cmd)
		{
		case nick : return nickFun(this->_splitted_cmd, client); 
		case join : return joinFun(this->_splitted_cmd, client, server->get_channels());
		case part : console_log("CMD: comando scelto part");return 1;
		case set_nick : console_log("CMD: comando scelto set nick");return 1;
		case whois : console_log("CMD: comando scelto  whois");return 1;
		case msg : console_log("CMD: comando scelto  msg");return 1;
		case kick : console_log("CMD: comando scelto set kick");return 1;
		case ban : console_log("CMD: comando scelto  ban");return 1;
		case EXIT : return 2;

		default: console_log("CMD: Command not found");
		break;
	}
	}
	
	return 0;
}

void	CommandHandler::sendToChannel(Channel *channel, std::string str, Client *client)
{
	size_t z = 0;
	std::string prefix = "[";
	prefix.append(this->get_time());
	prefix.append("] ");
	prefix.append("@");
	prefix.append(client->getNickname());
	prefix.append(": ");
	prefix.append(str);
	while (channel->get_users()->size() > z)
	{
		send(channel->get_users()->at(z)->getFd(), prefix.c_str(), strlen(prefix.c_str()), 0);
		z++;
	}
}
