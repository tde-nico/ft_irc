#ifndef SERVER_HPP
#define SERVER_HPP

#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <sstream>
#include <poll.h>
#include <vector>
#include <cerrno>

class Server;

#include "utils.hpp"
#include "Client.hpp"
#include "CommandHandler.hpp"

#define MAX_CONNECTIONS 200


class ServerQuitException: public std::exception
{
	public:
		virtual const char	*what() const throw ()  { return (((std::string)"Quitting from server").c_str()); }
};

class Server
{
	private:
		std::string				host;
		std::string				port;
		std::string				password;
		int						sock;
		int						running;
		std::vector<pollfd>		poll_fds;
		std::map<int, Client *>	clients;
		CommandHandler			*handler;

	public:
		Server(std::string const &port, std::string const &password);
		~Server();

		void		start();
		int			create_socket();
		void		handle_connection();
		std::string	recive(int fd);
		int			handle_message(int fd);
		void		handle_disconnection(int fd);
};

#endif
