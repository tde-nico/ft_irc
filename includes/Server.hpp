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
#include <map>
#include <cerrno>

class Server;
class Channel;

#include "utils.hpp"
#include "Client.hpp"
#include "CommandHandler.hpp"
#include "Channel.hpp"

#define MAX_CONNECTIONS 200


class ServerQuitException: public std::exception
{
	public:
	//	std::string	what() { return ("Quitting from server"); }
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
		std::map<int, Client *>	*clients;
		CommandHandler			*handler;
		std::vector<Channel*> 	*channels;
	public:
		Server(std::string const &port, std::string const &password);
		~Server();

		void		start();
		int			create_socket();
		void		handle_connection();
		std::string	recive(int fd);
		int			handle_message(int fd);
		void		handle_disconnection(int fd);
		std::vector<Channel*>	*get_channels(){return this->channels;};
		std::map<int, Client *> *get_clients(){return this->clients;}
};

#endif
