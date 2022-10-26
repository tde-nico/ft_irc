#ifndef SERVER_HPP
#define SERVER_HPP

#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>
#include <string>
#include <sstream>
#include <poll.h>
#include <vector>

#include "utils.hpp"

#define MAX_CONNECTIONS 200


class Server
{
	private:
		std::string			host;
		std::string			port;
		std::string			password;
		int					sock;
		int					running;
		std::vector<pollfd>	poll_fds;

	public:
		Server(std::string const &port, std::string const &password);
		~Server();

		void	start();
		int		create_socket();
		void	handle_connection();
		void	handle_disconnection(int fd);
};

#endif
