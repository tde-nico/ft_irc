#ifndef COMMAND_HPP
#define COMMAND_HPP

#pragma once

class Command;

#include "utils.hpp"
#include "Server.hpp"
#include "Client.hpp"

class Command
{
	protected:
		Server	*server;
		int		auth; // requires auth = 0: no, 1: yes
	
	public:
		Command(Server *server, int auth = 0) { this->server = server; this->auth = auth; }
		virtual ~Command() {}

		int				getAuth() const { return (this->auth); }
		virtual void	execute(Client *client, std::vector<std::string> args) = 0;
};

class ExitCommand : public Command
{
public:
	ExitCommand(Server *server, int auth = 0);
	~ExitCommand();

	void execute(Client *client, std::vector<std::string> arguments);
};

#endif
