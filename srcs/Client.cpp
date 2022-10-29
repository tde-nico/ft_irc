#include "Client.hpp"

Client::Client(int fd, std::string hostname, int port)
{
	this->fd = fd;
	this->hostname = hostname;
	this->port = port;
	this->status = 0;
	this->ChannelMode = OFF;

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
