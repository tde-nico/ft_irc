#include "CommandHandler.hpp"

CommandHandler::CommandHandler(Server *server, std::string const &password)
{
	this->server = server; // remove if not used
	this->password = password;
	
	// commands
	this->commands["/exit"] = new ExitCommand(server);
	this->commands["/a"] = new ExitCommand(server, 1);
}

CommandHandler::~CommandHandler()
{
	std::map<std::string, Command *>::iterator	it;

	for (it = this->commands.begin(); it != this->commands.end(); ++it)
		delete it->second;
}

int	CommandHandler::handle_command(Client *client, std::string cmd)
{
	if (client->getStatus() == 0) // not logged
		return (this->log_in(client, cmd));
	else if (client->getStatus()) // logged
		return (exec_cmd(cmd, client));
	return (0);
}

int	CommandHandler::log_in(Client *client, std::string cmd)
{
	std::string	pass;

	// password check
	pass.append(this->password).append("\n");
	if (cmd.compare(pass))
	{
		// wrong password
		client->reply(WRONG_PASS);
		client->reply(INSERT_PASS);
		console_log(client->log("failed to log"));
		return (0);
	}
	// successful log in
	client->reply(CORRECT_PASS);
	// set the status to logged
	client->setStatus(1);
	console_log(client->log("has logged in"));
	return (0);
}

int	CommandHandler::exec_cmd(std::string cmd, Client *client)
{
	std::stringstream	ss_cmd(cmd);
	std::string			parsed;
	int					length;
	std::string			name;

	while (std::getline(ss_cmd, parsed))
	{
		std::string	msg;
		// parse lines
		length = parsed.length();
		if (parsed[parsed.length() - 1] == '\n')
			length -= 1; 
		parsed = parsed.substr(0, length);
		// parse command
		name = parsed.substr(0, parsed.find(' '));
		try
		{
			// get the command
			Command						*command = this->commands.at(name);
			std::vector<std::string>	args;
			std::stringstream			ss_args(parsed.substr(name.length(), parsed.length()));
			std::string					arg;

			// if he has no authorization
			if (client->getStatus() == 1 && command->getAuth() == 1) // admin check
			{
				msg.append("Command Denied : ").append(name).append("\n");
				client->reply(msg);
				console_log(client->log(msg.substr(0, msg.length() -1)));
				return (0);
			}
			// get the args
			while (ss_args >> arg)
				args.push_back(arg);
			// log the command
			msg.append("Executed: ").append(name);
			console_log(client->log(msg));
			// execute the command
			command->execute(client, args);
		}
		catch (const std::out_of_range &err)
		{
			// error when searching for command
			msg.append("Unknown Command : ").append(name).append("\n");
			client->reply(msg);
			console_log(client->log(msg.substr(0, msg.length() -1)));
		}
		if (!name.compare("/exit"))
			return (1);
	}
	return (0);
}
