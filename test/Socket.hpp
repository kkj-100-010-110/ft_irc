#ifndef SOCKET_HPP
# define SOCKET_HPP

#include <sys/socket.h>
#include <netdb.h>
#include <exception>

#ifndef BACKLOG
# define BACKLOG 10
#endif

#include "Error.hpp"

class Socket
{
private:
	/* data */
	int			_socket_fd;
	struct sockaddr_in _ip4addr;

	const char		*_IP;
	const char		*_port;
	struct addrinfo	_hints;
	int				_level;

	void	ft_ip_check();
	void	ft_find_socker();
	void	ft_create_socket();
public:
	Socket();
	Socket(int fd);
	Socket(const char *IP, const char *port, struct addrinfo hints);
	~Socket();

	Socket&	operator=(const Socket& ref);

	int		ft_poll();
	
	int		ft_get_socket_fd();
	int		ft_get_socket_level();
	int		ft_set_socket_level(int level);
	int		ft_increase_level();
	Socket	*ft_accept();
	void	ft_listen(int backlog);

	void	ft_guide_send();
};

#endif
