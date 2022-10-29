#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#pragma once

class Channel;

#include "Server.hpp"
#include "Client.hpp"
#include "utils.hpp"

class Channel
{
	private:
		std::string				name;
		std::vector<Client *>	clients;

	public:
		Channel(std::string const &name, Client *client);
		~Channel();

		std::string					getName() const { return (this->name); }

		std::vector<std::string>	getNicknames();
		void						broadcast(std::string const &msg, Client *except = nullp);
		void						addClient(Client *client);
		void						removeClient(Client *client);
		void						kick(Client *client, Client *target);

};

#endif
