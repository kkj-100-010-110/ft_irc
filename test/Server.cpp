#include <iostream>
#include <iomanip>
#include <utility> // pair

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
	this->_channel_list.insert(std::pair<std::string, Channel *>("defualt", new Channel("defualt", this->ft_get_user_control_class())));

	while (this->_socket.size() < 5)
	{
		accept_socket = this->_server->ft_accept();
		if (accept_socket)
			this->_socket.push(accept_socket);
		this->ft_server_check_socket_fd();
		// this->ft_server_input();
		sleep(1);
	}
}

void	Server::ft_server_check_socket_fd()
{
	int				revents;
	int				socket_size;
	Socket			*socket_front;

	socket_size = this->_socket.size();
	while(socket_size--)
	{
		// 끊어 졋는지 확인 코드가 필요 지금 꺼져있는 fd close 필요
		socket_front = this->_socket.front();
		revents = socket_front->ft_poll();
		if (revents & POLLERR)
		{
			std::cout << "test POLLERR " << std::endl;
		}
		else if ((revents & POLLRDNORM ))
		{
			this->ft_pollin(socket_front);
		}
		else
		{
			this->_socket.pop();
			this->_socket.push(socket_front);
		}
	}
}

void	Server::ft_pollin(Socket *socket_front)
{
	int		fd;
	char	buf[4096 + 1];
	ssize_t len;
	int		socket_send_loop;

	fd = socket_front->ft_get_socket_fd();
	len = recv(fd, &buf, 4096, 0);
	if (len < 0)
		throw Error("recv() failed"); 
	if (len == 0)
	{
		std::cout << "test Connection closed" << std::endl;
		this->_socket.pop();
		delete socket_front;
		return ;
	}
	buf[len] = '\0';
	
	if (len == 1 && buf[0] == '\n')
	{
		this->_socket.pop();
		delete socket_front;
		return ;
	}
	switch (socket_front->ft_get_socket_level())
	{
	case 1:
	{
		if (len > 0 && buf[len - 1] == '\n')
			buf[--len] = '\0';
		this->ft_password_check(socket_front, this->_password.compare(buf));
		break;
	}
	case 2:
	{
		if (len > 0 && buf[len - 1] == '\n')
			buf[--len] = '\0';
		this->ft_user_all_add(socket_front, std::string(buf));
		break;
	}
	case 3:
	{
		if (len > 0 && buf[len - 1] == '\n')
			buf[--len] = '\0';
		this->ft_user_set_nick_name(socket_front, std::string(buf));
		break;
	}
	default:
	{
		User *front_user = this->ft_get_user(socket_front->ft_get_socket_fd());
		Channel *front_channel = this->_channel_list.at(front_user->ft_get_channel_name());
		/**
		 * 명령어 체크
		*/
		std::cout << FG_LGREEN << "[" << fd << "]" << NO_COLOR << " : " << buf;
		if (buf[0] == '/')
			front_channel->ft_send_me("option test", front_user->ft_get_user_name());
		else
			front_channel->ft_send_all((std::string)buf, front_user->ft_get_user_name());
		break;
	}
	}
}


bool	Server::ft_password_check(Socket *socket_front, int check)
{
	int		fd;

	fd = socket_front->ft_get_socket_fd();
	if (check)
	{
		std::cout 
		<< FG_LGREEN << "[" << fd << "] "
		<< FG_RED << std::left << std::setw(15) <<  "[ ERROR ]" << "not password matching!! \n"
		<< NO_COLOR << std::endl;
		socket_front->ft_guide_send();
	}
	else
	{
		std::cout 
		<< FG_LGREEN << "[" << fd << "] " << FG_LGREEN << "password pass"
		<< NO_COLOR << std::endl;
		socket_front->ft_increase_level();
		socket_front->ft_guide_send();
	}
	return (!check);
}

bool	Server::ft_user_all_add(Socket *socket_front, std::string user_name)
{
	this->ft_append_user(new User(socket_front->ft_get_socket_fd(), user_name));
	socket_front->ft_increase_level();
	socket_front->ft_guide_send();
	return (1);
}

bool	Server::ft_user_set_nick_name(Socket *socket_front, std::string nick_name)
{
	this->ft_get_user(socket_front->ft_get_socket_fd())->ft_set_nick_name(nick_name);
	socket_front->ft_increase_level();
	this->_channel_list.at("defualt")->ft_channel_join_user(this->ft_get_user(socket_front->ft_get_socket_fd()));
	socket_front->ft_guide_send();
	return (1);
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