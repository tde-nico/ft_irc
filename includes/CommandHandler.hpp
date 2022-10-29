#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#pragma once

class CommandHandler;

#include "utils.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Command.hpp"

#define WRONG_PASS "Wrong Password, Try again.\n"
#define CORRECT_PASS "Welcome Back.\n"
#define INSERT_PASS "Please insert the password: "


class CommandHandler
{
	private:
		Server								*server;
		std::string							password;
		std::map<std::string, Command *>	commands;
		std::vector<std::string>			_splitted_cmd;

	public:
		CommandHandler(Server *server, std::string const &password);
		~CommandHandler();

		int		handle_command(Client *client, std::string cmd);
		int		log_in(Client *client, std::string cmd);
		int		exec_cmd(std::string cmd, Client *client);

};

#endif
