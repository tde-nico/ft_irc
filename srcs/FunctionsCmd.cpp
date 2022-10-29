#include "CommandHandler.hpp"
#include "Server.hpp"
#include "Client.hpp"

int			CommandHandler::nickFun(std::vector<std::string> args, Client *client)
{
    char str[100];
    
    if (args.size() == 1)
    {
        sprintf(str, "Your NickName is : %s\n", client->getNickname().c_str());
        if (send(client->getFd(), str, strlen(str), 0) == -1)
            throw std::runtime_error("Error while showing Nickname");
    }
    else
    {
        client->setNickname(args.at(1));
        sprintf(str, "You're now known as : %s\n", client->getNickname().c_str());
         if (send(client->getFd(), str, strlen(str), 0) == -1)
            throw std::runtime_error("Error while showing Nickname");
        sprintf(str, "host %s has changed Nickname : %s\n",client->getHostname().c_str(), client->getNickname().c_str());
        console_log(str);
    }
    return (1);
}

int     CommandHandler::joinFun(std::vector<std::string> args, Client *client, std::vector<Channel*> *channels)
{
    char        str[100];

    if (args.size() == 1)
        throw std::runtime_error("Error : Join command need an argument");
    else if (args.size() == 2)
    {
        size_t i = 0;

        while (i < channels->size())
        {
            if (channels->at(i)->get_nameChannel().compare(args[1]) == 0)
            {
                sprintf(str, "host %s has joined a channel : %s\n",client->getHostname().c_str(), channels->at(i)->get_nameChannel().c_str());
                console_log(str);
                channels->at(i)->get_users()->push_back(client);
               // channels->at(i)->get_users().push_back(client);
                joinChannel(client, channels->at(i));
                //entra in channel mode
                //quando entri il client id la variabile channelMode è attiva
                //quando esce si disattiva
                break;
            }
            i++;
        }
        if (i == channels->size())
        {
            console_log(str);
            Channel *new_channel = new Channel;
            setNewChannel(client, new_channel, args[1]);
            channels->push_back(new_channel);
            sprintf(str, "host %s has created a new channel : %s\n", client->getHostname().c_str(), channels->at(i)->get_nameChannel().c_str());
            console_log(str);
            joinChannel(client, new_channel);
        }
    }
    return (1);
}

std::string		CommandHandler::get_time()
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

std::string     CommandHandler::getwelcomeMessage(Channel *channel)
{
    char str[150];

    sprintf(str, "[NAME CHANNEL :  %s ]\n[admin : %s ]\n[Channel # %s created %s\n", \
    channel->get_nameChannel().c_str(), channel->get_admin().c_str(),\
    channel->get_nameChannel().c_str(),channel->get_start_date().c_str() );
   return (str);
};

void            CommandHandler::setNewChannel(Client *client, Channel *new_channel, std::string channel_name)
{
	new_channel->set_users(client);
    new_channel->set_nameChannel(channel_name);
    new_channel->set_admin(client->getNickname());
    new_channel->set_currentFd(client->getFd());
    new_channel->set_hostname(client->getHostname());
    new_channel->set_start_date(get_time());
}

void	CommandHandler::joinChannel(Client *client, Channel *channel)
{
    if (client->getChannelmode() == OFF)
        client->setChannelmode(ON);
    client->setChannelName(channel->get_nameChannel());
    if (send(client->getFd(), getwelcomeMessage(channel).c_str(), strlen(getwelcomeMessage(channel).c_str()), 0) == -1)
            throw std::runtime_error("Error while sending Welcome Message");
}