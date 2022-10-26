#ifndef SERVER_HPP
#define SERVER_HPP

#pragma once

#include "utils.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>
#include <sstream>
#include <poll.h>
#include <vector>
#include <netdb.h>


#include <stdlib.h>

class Server
{
	private:
		std::string		host;
		std::string		port;
		std::string		password;
		int				sock;
		int				running;

	public:
		Server(std::string const &port, std::string const &password);
		~Server();

		void	start();
		int		create_socket();
};

#endif
