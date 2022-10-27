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

		// 0: not logged
		// 1: logged
		// 2: admin
		int			status;

	public:
		Client(int fd, std::string hostname, int port);
		~Client();

		int			getFd() const { return (fd); }
		std::string	getHostname() const { return (hostname); }
		int			getPort() const { return (port); }
		std::string	getNickname() const { return (nickname); }
		std::string	getUsername() const { return (username); }
		std::string	getRealname() const { return (realname); }
		int			getStatus() const { return (status); }
		
		void		setFd(int fd) { this->fd = fd; }
		void		setHostname(std::string hostname) { this->hostname = hostname; }
		void		setPort(int port) { this->port = port; }
		void		setNickname(std::string nickname) { this->nickname = nickname; }
		void		setUsername(std::string username) { this->username = username; }
		void		setRealname(std::string realname) { this->realname = realname; }
		void		setStatus(int status) { this->status = status; }
		void		printUserInfo(){std::cout << "nickname: " << getNickname() << "\n";};
};


#endif
