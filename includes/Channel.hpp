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
		std::string				password;
		std::vector<Client *>	clients;
<<<<<<< HEAD
		std::vector<Client *>	*Ban;
		std::string				admin;
=======
>>>>>>> 1efdb1c7460416315c8ce97e65eddc4ec4cdfeca

	public:
		Channel(std::string const &name, std::string const &password);
		~Channel();

		std::string					getName() const { return (this->name); }
		std::string					getAdmin() const { return (this->admin); }
		std::string					getPassword() const { return (this->password); }

		std::vector<std::string>	getNicknames();
		void						broadcast(std::string const &msg, Client *except = nullp);
		void						addClient(Client *client);
		void						removeClient(Client *client);
		void						kick(Client *client, Client *target, std::string const &reason);
<<<<<<< HEAD
		std::vector<Client *>		*getfdBan(){return this->Ban;};
		std::vector<Client *>		getClients(){return this->clients;};
		int							CheckBan(Client *client);
		void						setAdmin(std::string str){this->admin = str;};
=======

>>>>>>> 1efdb1c7460416315c8ce97e65eddc4ec4cdfeca
};

#endif
