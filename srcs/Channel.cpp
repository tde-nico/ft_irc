#include "Channel.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "Client.hpp"
/*
Channel::Channel()
{
	
}

std::string		Channel::get_time()
{
	time_t		raw_time;
	struct tm	*time_info;
	char		buffer[80];

	time(&raw_time);
	time_info = localtime(&raw_time);
	strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", time_info);
	std::string now(buffer);

	return (now);
}

void     Channel::getwelcomeMessage()
{
	std::cout << "[NAME CHANNEL : " << get_nameChannel() << "]\n";
	std::cout << "[admin :" << this->get_admin() << "]\n";
	std::cout << "[Channel #" << get_nameChannel() << " created ";
	std::cout << get_start_date() << "\n";
};

void            Channel::setNewChannel(Client *client, Channel *new_channel, std::string channel_name)
{
	new_channel->set_users(client);
    new_channel->set_nameChannel(channel_name);
    new_channel->set_admin(client->getNickname());
    new_channel->set_currentFd(client->getFd());
    new_channel->set_hostname(client->getHostname());
    new_channel->set_start_date(get_time());
}
*/


