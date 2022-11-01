#include "IrcBot.hpp"

IrcBot::IrcBot(std::string const &host, std::string const &port, std::string const &password)
{
	this->host = host;
	std::istringstream(port) >> this->port;
	this->password = password;
	this->sock = this->createSocket();
	this->name = "Marvin";
}

IrcBot::~IrcBot()
{
	close(this->sock);
	console_log("Shutting down the IrcBot");
}

int	IrcBot::createSocket()
{
	int	sockfd;

	// open the socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		throw std::runtime_error("Error while opening socket");
	// setup the connection informations
	struct sockaddr_in addr = {};
	bzero((char *)&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(this->port);
	// connect to the server
	if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		throw std::runtime_error("Error while connecting to the server");

	return (sockfd);
}

void	IrcBot::reply(std::string const &msg)
{
	std::string	to_send;

	console_log(msg);
	to_send.append(msg).append("\n");
	send(this->sock, to_send.c_str(), to_send.size(), 0);
}

void	IrcBot::login()
{
	std::string	msg;
	char		buffer[1024];
	int			length;
	std::string	tmp;

	length = recv(this->sock, buffer, 1024, 0);
	buffer[length] = '\0';
	console_log((std::string)(buffer));
	this->reply(this->password);
	length = recv(this->sock, buffer, 1024, 0);
	buffer[length] = '\0';
	tmp.append(buffer);
	tmp.erase(std::remove(tmp.begin(), tmp.end(), '\n'), tmp.cend());
	console_log(tmp);
	msg.append("/nick ").append(this->name);
	this->reply(msg);
	// tmp join
	msg = "/join bot";
	this->reply(msg);
	length = recv(this->sock, buffer, 1024, 0);
	buffer[length] = '\0';
	tmp = "";
	tmp.append(buffer);
	tmp.erase(std::remove(tmp.begin(), tmp.end(), '\n'), tmp.cend());
	console_log(tmp);
}

void	IrcBot::start()
{
	char	buffer[1024];
	int		length;

	this->login();
	while ((length = recv(this->sock, buffer, 1024, 0)) > 0)
	{
		buffer[length] = '\0';
		this->handleMessage((std::string)(buffer));
	}
}

void	IrcBot::handleMessage(std::string const &msg)
{
	std::string					tmp;
	std::vector<std::string>	message;

	tmp.append(msg);
	tmp.erase(std::remove(tmp.begin(), tmp.end(), '\n'), tmp.cend());
	message = ft_split(tmp);
	// replies
	console_log(tmp);
	if (tmp.find("has joined") <= tmp.length())
		this->reply("Life? Don't talk to me about life");
	else if (tmp.find("quitted from") <= tmp.length())
		this->reply("Do you want me to sit in a corner and rust, or just fall apart where I'm standing?");
	else if (tmp.find("idea") <= tmp.length())
		this->reply("I have a million ideas. They all point to certain death");
	else
		this->reply("I think you ought to know I'm feeling very depressed");
}
