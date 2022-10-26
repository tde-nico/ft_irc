#ifndef CLIENT_HPP
#define CLIENT_HPP

#pragma once

#include "utils.hpp"


class Client
{
	private:
		int			fd;
		std::string	hostname;
		int			port;

		std::string	nickname;
		std::string	username;
		std::string	realname;

	public:
		Client(int fd, std::string hostname, int port);
		~Client();

		int			getFd() const { return (fd); }
		std::string	getHostname() const { return (hostname); }
		int			getPort() const { return (port); }
		std::string	getNickname() const { return (nickname); }
		std::string	getUsername() const { return (username); }
		std::string	getRealname() const { return (realname); }
		
		void		setFd(int fd) { this->fd = fd; }
		void		setHostname(std::string hostname) { this->hostname = hostname; }
		void		setPort(int port) { this->port = port; }
		void		setNickname(std::string nickname) { this->nickname = nickname; }
		void		setUsername(std::string username) { this->username = username; }
		void		setRealname(std::string realname) { this->realname = realname; }

};


#endif
