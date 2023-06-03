#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <string>
#include <queue>

#include "Socket.hpp"
#include "Error.hpp"

class Server
{
private:
	/* data */
	std::string	_IP;
	std::string	_port;
	std::string _password;

	Socket	*_server;
	std::queue<Socket *> _socket;

public:
	Server();
	Server(std::string port, std::string password);
	~Server();

	void	ft_server_on();
	void	ft_server_check_socket_fd();
	void	ft_server_input();
};

#endif
