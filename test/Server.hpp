#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <string>
#include <queue>
#include <map>

#include "Socket.hpp"
#include "Error.hpp"
#include "Channel.hpp"
#include "UserControl.hpp"

class Server: public UserControl
{
private:
	/* data */
	std::string	_IP;
	std::string	_port;
	std::string _password;

	Socket	*_server;
	std::queue<Socket *> _socket;
	std::map<std::string, Channel *> _channel_list;

public:
	Server();
	Server(std::string port, std::string password);
	~Server();

	void	ft_server_on();
	void	ft_server_check_socket_fd();
	void	ft_server_input();




	void	ft_pollin(Socket *socket_front);
	bool	ft_password_check(Socket *socket_front, int check);
	bool	ft_user_all_add(Socket *socket_front, std::string user_name);
	bool	ft_user_set_nick_name(Socket *socket_front, std::string user_name);
};

#endif
