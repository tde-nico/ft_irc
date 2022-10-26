#include "Server.hpp"

Server::Server(std::string const &port, std::string const &password)
{
	this->host = "127.0.0.1";
	this->port = port;
	this->password = password;
	this->running = 1;
	this->sock = this->create_socket();
	console_log("Main Socket Created");
}

Server::~Server()
{
	close(this->sock);
	console_log("Main Socket Closed");
}

void	Server::start()
{
	struct pollfd *poll_fds;
	poll_fds = (struct pollfd *)calloc(1, sizeof(struct pollfd));
	poll_fds[0].fd = this->sock;
	poll_fds[0].events = POLLIN;
	while (this->running)
	{
		if (poll(poll_fds, 1, -1) < 0)
			throw std::runtime_error("Error while polling");
		if ((poll_fds->revents & POLLIN) == POLLIN)
		{
			console_log("connected");
			struct sockaddr_in addr = {};
			socklen_t s_size = sizeof(addr);
			int fd = accept(this->sock, (struct sockaddr *)&addr, &s_size);
			if (fd < 0)
				throw std::runtime_error("Error while accepting");
			console_log("accepted");
			char hostname[NI_MAXHOST];
			getnameinfo((struct sockaddr *) &addr, sizeof(addr), hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV);
			std::cout << hostname << "  " << fd << "\n";
			char buffer[1024];
			recv(fd, buffer, 1024, 0);
			std::cout << buffer << "\n";
		}
		if ((poll_fds->revents & POLLHUP) == POLLHUP)
			console_log("disconnected");
	}
}

int	Server::create_socket()
{
	int	sockfd;
	int	int_port;

	// open the socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		throw std::runtime_error("Error while opening socket");
	// set to non-blocking mode
	if (fcntl(sockfd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("Error while setting socket to NON-BLOCKING");
	// setup the binding informations
	struct sockaddr_in addr = {};
	bzero((char *)&addr, sizeof(addr));
	std::istringstream(this->port) >> int_port;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(int_port);
	// bind the socket
	if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		throw std::runtime_error("Error while binding socket");
	// listen on the socket
	if (listen(sockfd, MAX_CONNECTIONS) < 0)
		throw std::runtime_error("Error while listening in socket");
	return (sockfd);
}

