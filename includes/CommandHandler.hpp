#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#pragma once

class CommandHandler;

#include "utils.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Server.hpp"

#define WRONG_PASS "Wrong Password, Try again.\n"
#define INSERT_PASS "Please insert the password: "

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
#define EXIT			510

class CommandHandler
{
	private:
		Server						*server;
		std::string					password;
		std::vector<std::string>	_splitted_cmd;
		std::string                 prefix;

	public:
		CommandHandler(Server *server, std::string const &password);
		~CommandHandler();

		int		handle_command(Client *client, std::string cmd, Server *server);
		int		log_in(Client *client, std::string cmd);
		int		parse_cmd(std::string cmd);
		int		exec_cmd(int cmd, Client *client, Server *server, std::string str);
		int		nickFun(std::vector<std::string> args, Client *client);
		int		joinFun(std::vector<std::string> args, Client *client, std::vector<Channel *> *channels);
		void	setNewChannel(Client *client, Channel *new_channel, std::string channel_name);
		std::string	getwelcomeMessage(Channel *new_channel);
		void	joinChannel(Client *client, Channel *channel);
		void	sendToChannel(Channel *channel, std::string str, Client *client);
		std::string		get_time();
};

#endif
