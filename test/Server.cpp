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

	while (!this->_socket.empty())
	{
		socket_del = this->_socket.front();
		this->_socket.pop();
		delete socket_del;
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

	while (this->_socket.size() < 3)
	{
		accept_socket = this->_server->ft_accept();
		if (accept_socket)
			this->_socket.push(accept_socket);
		this->ft_server_check_socket_fd();
		this->ft_server_input();
	}
}

void	Server::ft_server_check_socket_fd()
{
	struct pollfd	pfd;
	struct stat		sb;
	char			buf[4096 + 1];
	int				socket_size;
	Socket			*socket_front;

	socket_size = this->_socket.size();
	while(socket_size--)
	{
		// 끊어 졋는지 확인 코드가 필요 지금 꺼져있는 fd close 필요
		socket_front = this->_socket.front();
		pfd.fd = socket_front->ft_get_socket_fd();
		pfd.events = POLLSTANDARD;
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
			
			if (len == 1 && buf[0] == '\n')
			{
				delete socket_front;
				this->_socket.pop();
				continue ;
			}
			else if (socket_front->ft_get_socket_level() == 1) // 페스워드 체킹
			{
				if (this->_password.compare(buf))
				{
					std::cout 
					<< FG_RED << std::left << std::setw(15) <<  "[ ERROR ]" << "not password matching!! \n"
					<< FG_LGREEN << "[" << socket_front->ft_get_socket_fd() << "] " << "len : " << len << "\n"
					<< FG_LYELLOW <<  "diff " << this->_password.compare(buf) << " => '" << buf << "'" << NO_COLOR 
					<< std::endl;
				}
				else
				{
					std::cout 
					<< FG_LGREEN << "[" << socket_front->ft_get_socket_fd() << "] " 
					<< FG_LGREEN << "password pass" << NO_COLOR << std::endl;
					socket_front->ft_increase_level();
				}
			}
			else
			{
				if (buf[len - 1] == '\n')
					buf[len - 1] = '\0';
				std::cout 
				<< FG_LGREEN << "[" << socket_front->ft_get_socket_fd() << "]"
				<< NO_COLOR << " : " << buf << std::endl;
			}
		}
		this->_socket.pop();
		this->_socket.push(socket_front);
	}
}

void	Server::ft_server_input()
{
	std::string	buf;
	struct pollfd pfd = {.fd = 0, .events = POLLIN};
	int ret_poll;

	ret_poll = poll(&pfd, 1, 0);
	if (ret_poll > 0)
	{
		std::getline(std::cin, buf);
		std::cout << FG_LMAGENTA << std::left << std::setw(15) << "[Server] " 
			<< FG_LCYAN << buf << NO_COLOR << std::endl;
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

	try {
		server = new Server(port_str, password_str);
		server->ft_server_on();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	delete server;
	system("leaks server");
	return 0;
}