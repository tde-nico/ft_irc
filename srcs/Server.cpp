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
	pollfd	server_fd = {this->sock, POLLIN, 0};
	poll_fds.push_back(server_fd);

	console_log("Server waiting for connections");

	while (this->running)
	{
		// waiting for events
		if (poll(poll_fds.begin().base(), poll_fds.size(), -1) < 0)
			throw std::runtime_error("Error while polling");
		// event handling
		for (std::vector<pollfd>::iterator it = poll_fds.begin(); it != poll_fds.end(); ++it)
		{
			// no events
			if (it->revents == 0)
				continue ;
			// on connect
			if ((it->revents & POLLIN) == POLLIN)
			{
				if (it->fd == this->sock)
				{
					this->handle_connection();
					break ;
				}
			}
			// on disconnect
			if ((it->revents & POLLHUP) == POLLHUP)
			{
				this->handle_disconnection(it->fd);
				break ;
			}
		}
	}

	/*poll_fds = (struct pollfd *)calloc(1, sizeof(struct pollfd));
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
	}*/
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

void	Server::handle_connection()
{
	int			fd;
	sockaddr_in	addr = {};
	socklen_t 	size;
	//char		msg[1000];

	// accept connection
	size = sizeof(addr);
	fd = accept(this->sock, (sockaddr *)&addr, &size);
	if (fd < 0)
		throw std::runtime_error("Error while accepting new client");
	pollfd	poll_fd = {fd, POLLIN, 0};
	this->poll_fds.push_back(poll_fd);

	//Client *client = new Client(fd, hostname, ntohs(s_address.sin_port));
	//_clients.insert(std::make_pair(fd, client));

	//sprintf(msg, "%s:%d has connected", client->getHostname().c_str(), client->getPort());
	//console_log(msg);
	console_log("TODO connection");
}

void	Server::handle_disconnection(int fd)
{
	try
	{
		// TODO disconnect
		console_log("TODO disconnection");
	}
	catch (std::out_of_range const &err) {}
}

