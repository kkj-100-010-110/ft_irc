#include <iostream>
#include <iomanip>
#include <sys/socket.h>

#include <netdb.h>


#include "Server.hpp"

#include <arpa/inet.h> // inet_addr
#include <arpa/inet.h>
#include <unistd.h>

#include <sys/poll.h>
#include <sys/stat.h>


Server::Server()
{
	std::cout << std::setw(15) << "[Server] " << "create!!" << std::endl;
}

Server::Server(std::string port, std::string password)
	:_IP("127.0.0.1"), _port(port), _password(password)
{
	struct addrinfo hints, *info;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE; // use my IP

	getaddrinfo(NULL, port.c_str(), &hints, &info);


	hints.ai_addr = new struct sockaddr();
	hints.ai_addr->sa_family = (unsigned char)AF_INET;
	*(in_port_t *)hints.ai_addr->sa_data = htons(std::atoi(this->_port.c_str()));
	hints.ai_addr->sa_data[2] = htonl(INADDR_ANY);

	try { 
		this->_server = new Socket(NULL, this->_port.c_str(), hints);
		}
	catch ( ... ){ throw Error(" socket error"); }

	std::cout << std::setw(15) << "[Server] " << "create!!" << std::endl;
}


Server::~Server()
{
	std::cout << std::setw(15) << "[Server] " << "delete!!" << std::endl;
}

Server&	Server::operator=(const Server& ref)
{
	*this=ref;
	std::cout << std::setw(15) << "[Server] " << "operator=!!" << std::endl;
	return (*this);
}

void Server::ft_server_on()
{
	this->_server->ft_listen(20); // throw listen error
	
	struct pollfd pfd;
	struct stat sb;
	char buf[4096 + 1];

	while (1)
	{
		
		this->_socket.push_back(this->_server->ft_accept());
		if (this->_socket.back() == NULL)
			this->_socket.pop_back();
		for (std::vector<Socket *>::iterator i = this->_socket.begin(); \
			i != this->_socket.end(); \
			i++)
		{
			// 끊어 졋는지 확인 코드가 필요 지금 꺼져있는 fd close 필요
			
			pfd.fd = (*i)->ft_get_socket_fd();
			pfd.events = POLLIN;
			printf("fstat : %d\n", fstat(pfd.fd, &sb));
			if (sb.st_size > 0)
			{
				if (poll(&pfd, 1, -1) == -1)
				{
					if (pfd.revents & POLLERR)
						throw Error("poll POLLERR");
				}
				ssize_t len = recv(pfd.fd, &buf, 4096, 0);
				if (len < 0)
					printf("recv() failed");
				if (len == 0)
					printf("Connection closed");
				buf[len] = '\0';
				printf("%s",buf);
			}
		}
	}
		
}


int main(int argc, char const *argv[])
{
	
	Server a("422","123");
	a.ft_server_on();

	return 0;
}