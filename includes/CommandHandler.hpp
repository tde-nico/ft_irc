#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#pragma once

class CommandHandler;

#include "utils.hpp"
#include "Client.hpp"
#include "Server.hpp"

class CommandHandler
{
	private:
		Server		*server;
		std::string	password;

	public:
		CommandHandler(Server *server, std::string const &password);
		~CommandHandler();

		int	handle_command(Client *client, std::string cmd);

};

#endif
