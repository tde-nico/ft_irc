#ifndef IRCBOT_HPP
#define IRCBOT_HPP

#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <sstream>

#include "utils.hpp"

class IrcBot
{
	private:
		std::string	host;
		int			port;
		std::string	password;

		int			sock;
		std::string	name;

	public:
		IrcBot(std::string const &host, std::string const &port, std::string const &password);
		~IrcBot();

		int		createSocket();
		void	reply(std::string const &msg);
		void	login();
		void	start();
		void	handleMessage(std::string const &msg);

};

#endif
