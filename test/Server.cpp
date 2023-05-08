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

#include "Color.hpp"

Server::Server()
{
	std::cout << FG_LMAGENTA << std::left << std::setw(15) << "[Server] " << NO_COLOR
		<< FG_CYAN << " create!!" << std::endl;
}

Server::Server(std::string port, std::string password)
	:_IP("127.0.0.1"), _port(port), _password(password)
{
	struct addrinfo hints, *info;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE | SO_REUSEADDR; // use my IP

	getaddrinfo(NULL, port.c_str(), &hints, &info);


	hints.ai_addr = new struct sockaddr();
	hints.ai_addr->sa_family = (unsigned char)AF_INET;
	*(in_port_t *)hints.ai_addr->sa_data = htons(std::atoi(this->_port.c_str()));
	hints.ai_addr->sa_data[2] = htonl(INADDR_ANY);

	try { 
		this->_server = new Socket(NULL, this->_port.c_str(), hints);
		}
	catch ( ... ){ throw Error(" socket error"); }

	std::cout << FG_LMAGENTA << std::left << std::setw(15) << "[Server] " 
		<< FG_LYELLOW << CL_UDLINE << "<< port : " << this->_port << " >>" << NO_COLOR
		<< FG_CYAN << " create!!" << NO_COLOR << std::endl;
}


Server::~Server()
{
	Socket	*socket_del;

	for (std::vector<Socket *>::iterator i = this->_socket.begin(); \
		i != this->_socket.end(); \
		i++)
	{
		delete (*i);
	}
	delete this->_server;
	std::cout << FG_LMAGENTA << std::left << std::setw(15) << "[Server] " 
		<< FG_LYELLOW << CL_UDLINE << "<< port : " << this->_port << " >>" << NO_COLOR
		<< FG_LRED << " delete!!" << NO_COLOR << std::endl;
}

void Server::ft_server_on()
{
	Socket	*accept_socket;
	this->_server->ft_listen(20); // throw listen error

	while (this->_socket.size() < 4)
	{
		accept_socket = this->_server->ft_accept();
		if (accept_socket)
			this->_socket.push_back(accept_socket);
		this->ft_server_check_socket_fd();
	}
}

void	Server::ft_server_check_socket_fd()
{
	struct pollfd	pfd;
	struct stat		sb;
	char			buf[4096 + 1];
	
	for (std::vector<Socket *>::iterator i = this->_socket.begin(); \
		i != this->_socket.end(); \
		i++)
	{
		// 끊어 졋는지 확인 코드가 필요 지금 꺼져있는 fd close 필요
		
		pfd.fd = (*i)->ft_get_socket_fd();
		pfd.events = POLLIN | POLLERR | POLLHUP;
		fstat(pfd.fd, &sb);
		if (sb.st_size > 0)
		{
			if (poll(&pfd, 1, -1) == -1 && pfd.revents & POLLERR)
				throw Error("poll POLLERR");
			ssize_t len = recv(pfd.fd, &buf, 4096, 0);
			if (len < 0)
				throw Error("recv() failed"); 
			if (len == 0)
				throw Error("Connection closed");
			buf[len] = '\0';
			std::cout << FG_LGREEN << "[" << (*i)->ft_get_socket_fd() << "]"
			<< NO_COLOR << " : "<< buf << std::endl;
		}
	}
}




int main(int argc, char const *argv[])
{
	Server *server = NULL;
	std::string	port_str, password_str;

	if (argc != 3)
	{
		std::cerr << "\033[38;5;196m" << "[Error]" << NO_COLOR << " : "
		<< FG_LYELLOW << "argc != 3 \n" << NO_COLOR
		<< FG_CYAN << "[TIP] " << NO_COLOR <<  " ./server [port] [password] " << "\n";
		return (1);
	}
	port_str = argv[1];
	password_str = argv[2];
	if (port_str.find_first_not_of("0123456789") != std::string::npos) // std::all_of(str.begin(), str.end(), ::isdigit); // C++11
	{
		std::cerr << "\033[38;5;196m" << "[Error]" << NO_COLOR << " : "
		<< FG_LYELLOW << "port is not digit" << NO_COLOR << '\n'
		<< "port : [" << FG_LYELLOW << port_str << NO_COLOR << "]"<< "\n";
		return (2);
	}

	try { server = new Server(port_str, password_str); }
	catch(const std::exception& e) { std::cerr << e.what() << '\n'; }

	server->ft_server_on();

	system("leaks server");
	return 0;
}