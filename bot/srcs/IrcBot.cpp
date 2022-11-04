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
	addr.sin_addr.s_addr = inet_addr(this->host.c_str());
	addr.sin_port = htons(this->port);
	// connect to the server
	if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		throw std::runtime_error("Error while connecting to the server");

	// get this machine's ip
	socklen_t	size = sizeof(addr);
	if (getsockname(sockfd, (struct sockaddr *)&addr, &size) != 0)
		throw std::runtime_error("Error while getting ip");
	this->ip = inet_ntoa(addr.sin_addr);

	return (sockfd);
}

void	IrcBot::reply(std::string const &msg)
{
	std::string	to_send;

	to_send.append(msg).append("\r\n");
	send(this->sock, to_send.c_str(), to_send.size(), 0);
}

void	IrcBot::sendPrivMsg(std::string const &source, std::string const &msg)
{
	if (DEBUG)
		console_log(msg);
	this->reply("PRIVMSG " + source + " :" + msg);
}

void	IrcBot::login()
{
	this->reply("PASS " + this->password);
	this->reply("NICK " + this->nickname);
	this->reply("USER ircbot 0 * :42_irc_bot");
	console_log("Logged on server");
}

void	handle_sigint(int sig)
{
	(void)sig;
	throw BotQuitException();
}

void	IrcBot::start()
{
	char	buffer[1024];
	int		length;

	if (!MAC_OS)
		signal(SIGINT, handle_sigint);
	this->login();
	while ((length = recv(this->sock, buffer, 1024, 0)) > 0)
	{
		buffer[length] = '\0';
		this->handleMessage((std::string)(buffer));
	}
}

void	IrcBot::sendFile(std::string const &source, std::string const &fname, std::string const &name)
{
	FILE		*fd = fopen(fname.c_str(), "rb");
	char		buffer[1024];
	std::string	content;

	// get the file's content
	while (!feof(fd))
	{
		int size = fread(&buffer, 1, 1024, fd);
		if (size < 0)
			break;
		content.append(buffer, size);
	}
	fclose(fd);


	// create the socket
	int	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
		throw std::runtime_error("Error while opening socket");

	// set the socket options
	int	tmp = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(tmp)))
		throw std::runtime_error("Error while setting socket options");

	// set the bind otions
	struct sockaddr_in serv_address = {};
	int serv_address_len = sizeof(serv_address);
	bzero((char *) &serv_address, serv_address_len);
	serv_address.sin_family = AF_INET;
	serv_address.sin_addr.s_addr = INADDR_ANY;
	serv_address.sin_port = htons(1096);

	// bind the socket
	if (bind(server_fd, (struct sockaddr *) &serv_address, serv_address_len) < 0)
		throw std::runtime_error("Error while binding socket");

	// send the dcc request
	std::stringstream	size;
	size << content.size();
	this->reply("PRIVMSG " + source + " :" + '\x01' + "DCC SEND " + name + " " + this->ip + " 1096 " + size.str());

	// listen for connections
	if (listen(server_fd, 1) < 0)
		throw std::runtime_error("Error while listening on socket");

	// accept the incoming connection
	int client_fd = accept(server_fd, (struct sockaddr *) &serv_address, (socklen_t *) &serv_address_len);
	if (client_fd < 0)
	{
		close(server_fd);
		content.clear();
		return ;
	}

	/*std::string			packet;
	long unsigned int	curr;
	curr = 0;
	while (curr < content.size())
	{
		if (content.size() - curr < 32768)
			packet = content.substr(curr, content.size());
		else
			packet = content.substr(curr, curr + 32768);

		// send the data
		if (send(client_fd, packet.c_str(), packet.size(), 0) < 0)
			throw std::runtime_error("Error while sending");

		// recive the acknoledgement
		if (recv(client_fd, buffer, 32768, 0) < 0)
			throw std::runtime_error("Error while reciving");
		
		curr += 32768;
	}*/


	// send the data
	if (send(client_fd, content.c_str(), content.size(), 0) < 0)
		throw std::runtime_error("Error while sending");

	// recive the acknoledgement
	if (recv(client_fd, buffer, 1024, 0) < 0)
		throw std::runtime_error("Error while reciving");


	// close connections
	close(client_fd);
	close(server_fd);
	// log
	console_log("Success on sending " + fname);
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
	tmp.erase(std::remove(tmp.begin(), tmp.end(), '\n'), tmp.end());
	if (DEBUG)
		console_log(tmp);
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
	if (!type.compare("PRIVMSG"))
	{
		if (!message.at(1).compare(":get"))
			this->sendFile(nickname, message.at(2), message.at(2));
		else
			this->sendPrivMsg(nickname, "I think you ought to know I'm feeling very depressed");
	}
	/*
	"Life? Don't talk to me about life"
	"Do you want me to sit in a corner and rust, or just fall apart where I'm standing?"
	"I have a million ideas. They all point to certain death"
	"I think you ought to know I'm feeling very depressed"
	*/
}
