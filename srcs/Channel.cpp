#include "Channel.hpp"

Channel::Channel(std::string const &name)
{
	this->name = name;
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
	if (this->clients.size() == 1)
		client->setStatus(2);
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
	if (client->getStatus() == 2)
	{
		msg = "";
		client->setStatus(1);
		if (this->clients.size() > 0)
		{
			this->clients.at(0)->setStatus(2);
			msg.append(this->clients.at(0)->getNickname()).append(" is now the admin of ").append(this->name);
			console_log(msg);
			msg.append("\n");
			this->broadcast(msg);
		}
	}
}

void	Channel::kick(Client *client, Client *target)
{
	std::string	reply;
	std::string	msg;

	removeClient(target);
	reply.append("you have been kicked out from ").append(this->name);
	reply.append(" by ").append(client->getNickname()).append("\n");
	target->reply(reply);
	msg.append("kicked ").append(target->getNickname());
	console_log(client->log(msg));
}
