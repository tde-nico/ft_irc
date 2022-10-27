#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#pragma once

class CommandHandler;

#include "utils.hpp"
#include "Client.hpp"
#include "Server.hpp"

#define	connect			500
#define	disconnect		501
#define join			502
#define part			503
#define set_nick		504
#define nick			505
#define whois			506
#define msg				507
#define kick			508
#define ban				509

class CommandHandler
{
	private:
		Server						*server;
		std::string					password;
		std::vector<std::string>	_splitted_cmd;

	public:
		CommandHandler(Server *server, std::string const &password);
		~CommandHandler();

		int	handle_command(Client *client, std::string cmd);
		int			parse_cmd(std::string cmd);
		int			exec_cmd(int cmd, Client *client);
		int			nickFun(std::vector<std::string> args, Client *client);

};

#endif
