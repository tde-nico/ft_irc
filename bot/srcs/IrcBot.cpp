#include "IrcBot.hpp"

IrcBot::IrcBot(std::string const &host, std::string const &port, std::string const &password)
{
	this->host = host;
	std::istringstream(port) >> this->port;
	this->password = password;
	this->sock = this->createSocket();
	this->nickname = "Marvin";
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

	console_log(msg); // DEBUG
	to_send.append(msg).append("\r\n");
	send(this->sock, to_send.c_str(), to_send.size(), 0);
}

void	IrcBot::sendPrivMsg(std::string const &source, std::string const &msg)
{
	this->reply("PRIVMSG " + source + " :" + msg);
}

void	IrcBot::login()
{
	this->reply("PASS " + this->password);
	this->reply("NICK " + this->nickname);
	this->reply("USER ircbot 0 * :42_irc_bot");
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
	std::string					source;
	std::string					nickname;
	std::string					type;
	std::string::size_type		pos;

	tmp.append(msg);
	tmp.erase(std::remove(tmp.begin(), tmp.end(), '\n'), tmp.cend());
	message = ft_split(tmp);
	if (message.size() < 2)
		return ;
	source = message.at(0);
	type = message.at(1);
	pos = source.find('!');
	if (pos != std::string::npos)
		nickname = source.substr(1, pos - 1);
	else
		nickname = source;
	message = std::vector<std::string>(message.begin() + 2, message.end());
	// replies
	console_log(tmp); // DEBUG
	if (!type.compare("PRIVMSG"))
	{
		std::cout << message.size() << " " << message.at(1) << "\n"; // DEBUG
		this->sendPrivMsg(nickname, "I think you ought to know I'm feeling very depressed");
	}
	/*
	"Life? Don't talk to me about life"
	"Do you want me to sit in a corner and rust, or just fall apart where I'm standing?"
	"I have a million ideas. They all point to certain death"
	"I think you ought to know I'm feeling very depressed"
	*/
}
