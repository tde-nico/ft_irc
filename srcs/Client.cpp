#include "Client.hpp"

Client::Client(int fd, std::string hostname, int port)
{
	this->fd = fd;
	this->hostname = hostname;
	this->port = port;
	this->status = 0;
	this->channel = nullp;
}

Client::~Client() {}

std::string	Client::identify()
{
	std::string	msg;
	char		tmp[1000];

	sprintf(tmp, "%s:%d", this->getHostname().c_str(), this->getPort());
	msg.append(tmp);
	return (msg);
}

std::string	Client::log(std::string const &log)
{
	std::string	msg;
	char		tmp[1000];

	sprintf(tmp, "%s %s", this->identify().c_str(), log.c_str());
	msg.append(tmp);
	return (msg);
}

void	Client::reply(std::string const &msg)
{
	if (send(this->fd, msg.c_str(), strlen(msg.c_str()), 0) < 0)
		throw std::runtime_error("Error while sending");
}

void	Client::join(Channel *channel)
{
	std::string					users_string;
	std::vector<std::string>	users;
	std::string					msg;

	channel->addClient((this));
	this->channel = channel;
	users = channel->getNicknames();
	for (std::vector<std::string>::iterator it = users.begin(); it != users.end(); ++it)
		users_string.append((*it)).append(" ");
	users_string.append("\n");
	this->reply(users_string);
	msg = this->log("has joined ").append(channel->getName()).append(" as ").append(this->nickname);
	console_log(msg);
	msg.append("\n");
	channel->broadcast(msg);
}

void	Client::leave()
{
	if (this->channel == nullp)
		return ;
	this->channel->removeClient((this));
}
