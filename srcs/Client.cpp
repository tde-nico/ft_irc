#include "Client.hpp"

Client::Client(int fd, std::string hostname, int port)
{
	this->fd = fd;
	this->hostname = hostname;
	this->port = port;
	this->status = 0;
}

Client::~Client() {}
