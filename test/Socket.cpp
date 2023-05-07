#include <iostream>
#include <iomanip>
#include <arpa/inet.h> // inet_addr
#include <unistd.h>
#include <sys/socket.h>

#include <sys/poll.h>
#include "Socket.hpp"

Socket::Socket()
{
	std::cout << std::setw(15) << "[Socket] " << "create!!" << std::endl;
}


Socket::Socket(const char *IP, const char *port, struct addrinfo hints)
	: _IP(IP), _port(port), _hints(hints)
{
	if (!IP)
		this->ft_create_socket();
	else
	{
			this->ft_ip_check(); // throw check error
			this->ft_find_socker(); // throw NULL prompt
	}
}
Socket::Socket(const Socket& ref)
{
	*this=ref;
	std::cout << std::setw(15) << "[Socket] " << "copy!!" << std::endl;
}

Socket::~Socket()
{
	close(this->_socket_fd);
	std::cout << std::setw(15) << "[Socket] " << "delete!!" << std::endl;
}

Socket&	Socket::operator=(const Socket& ref)
{
	this->_socket_fd = ref._socket_fd;
	this->_IP = ref._IP;
	this->_port = ref._port;
	this->_hints = ref._hints;
	std::cout << std::setw(15) << "[Socket] " << "operator=!!" << std::endl;
	return (*this);
}


int	Socket::ft_get_socket_fd()
{
	return (this->_socket_fd);
}


void	Socket::ft_ip_check()
{
	int IP_result = inet_addr(this->_IP);
	if (IP_result == INADDR_NONE)
    	throw Error("inet_addr failed and returned INADDR_NONE\n");
	if (IP_result == INADDR_ANY)
		throw Error("inet_addr failed and returned INADDR_NONE\n");
}

void	Socket::ft_find_socker()
{
	struct addrinfo	*prompt, *info;
	int				option_value = 1;

	if (getaddrinfo(this->_IP, this->_port, &this->_hints, &info) != 0)
		throw Error("getaddrinfo"); // gai_strerror()  getaddrinfo(IP, port, &this->_hints, &this->_info) need return value
	for (prompt = info;prompt != NULL; prompt = prompt->ai_next) //	_info->ai_next // 하나의 도메인에 여러개의 아이피가 존제할 수 있음
	{
		try 
		{
			if ((this->_socket_fd = socket(prompt->ai_family, prompt->ai_socktype, prompt->ai_protocol)) == -1)
				throw Error("Error socker");
			if (setsockopt(this->_socket_fd, SOL_SOCKET, SO_REUSEADDR, &option_value, sizeof(int)) == -1)
				throw Error("Error setsocketopt");
			break ;
		}
		catch ( const std::exception& e )
		{
			std::cerr << e.what() << '\n';
			if (this->_socket_fd)
				close(this->_socket_fd);
		}
	}
	if (prompt == NULL)
		throw Error("Error : getaddrinfo no socket");
	std::cout << "find socket and create " << std::endl;
	freeaddrinfo(info);
}

void	Socket::ft_create_socket()
{
	memset(&this->_ip4addr, 0, sizeof(struct sockaddr_in));
	this->_ip4addr.sin_family = this->_hints.ai_family;
	this->_ip4addr.sin_port = htons(std::atoi(this->_port));
	this->_ip4addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if ((this->_socket_fd = socket(this->_hints.ai_family, this->_hints.ai_socktype, this->_hints.ai_protocol)) == -1)
		throw Error("socket fd == -1");
	if (bind(this->_socket_fd, (struct sockaddr*)&this->_ip4addr, sizeof(struct sockaddr_in)) == -1)
		throw Error("bind fd == -1");
}

void	Socket::ft_listen(int backlog)
{
	if (backlog <= 0)
		backlog = BACKLOG;
	if (backlog > SOMAXCONN)
		throw Error("BACKLOG > SOMAXCONN listen overflow");
	if (listen(this->_socket_fd, backlog) == -1)
		throw Error("error listen");
}

Socket	*Socket::ft_accept()
{
	Socket *client = new Socket();
	struct sockaddr_in   client_addr;
	struct pollfd pfd;

	pfd.fd = this->_socket_fd;
	pfd.events = POLLIN;

	socklen_t   client_addr_size = sizeof(struct sockaddr_in);

	if (poll(&pfd, 1, 100) > 0)
	{
		if ((client->_socket_fd = accept(this->_socket_fd, (struct sockaddr*)&client->_ip4addr, &client_addr_size)) == -1)
			throw Error("accept fd == -1");
		return client;
	}
	return (NULL);
}