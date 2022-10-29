#include "Channel.hpp"

Channel::Channel(std::string const &name, Client *client)
{
	this->name = name;
	client->setStatus(2);
}

Channel::~Channel() {}

std::vector<std::string>	Channel::getNicknames()
{
	std::vector<std::string>	nicknames;

	for (std::vector<Client *>::iterator it = this->clients.begin(); it != this->clients.end(); ++it)
	{
		nicknames.push_back((*it)->getNickname());
	}
	return (nicknames);
}

void	Channel::broadcast(std::string const &msg, Client *except)
{
	for (std::vector<Client *>::iterator it = this->clients.begin(); it != this->clients.end(); ++it)
	{
		if (*it == except)
			continue ;
		(*it)->reply(msg);
	}
}

void	Channel::addClient(Client *client)
{
	this->clients.push_back(client);
}

void	Channel::removeClient(Client *client)
{
	std::vector<Client *>::iterator	it;
	std::string						msg;

	for (it = this->clients.begin(); it != this->clients.end(); ++it)
	{
		if ((*it) == client)
		{
			this->clients.erase(it);
			break ;
		}
	}
	client->setChannel(nullp);
	msg.append(client->log(client->getNickname())).append(" quitted from ").append(this->name);
	console_log(msg);
	msg.append("\n");
	this->broadcast(msg);
}

void	Channel::kick(Client *client, Client *target)
{
	std::string	msg;

	msg.append(" kicked ").append(target->getNickname());
	console_log(client->log(msg));
	removeClient(target);
}
