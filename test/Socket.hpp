#ifndef SOCKET_HPP
# define SOCKET_HPP

#include <sys/socket.h>
#include <netdb.h>
#include <exception>

#ifndef BACKLOG
# define BACKLOG 50
#endif

#include "tool/Error.hpp"

class Socket : public Error
{
private:
	/* data */
	int			_socket_fd;
	struct sockaddr_in _ip4addr;

	const char		*_IP;
	const char		*_port;
	struct addrinfo	_hints;

	void	ft_ip_check();
	void	ft_find_socker();
	void	ft_create_socket();
public:
	Socket();
	Socket(const char *IP, const char *port, struct addrinfo hints);
	Socket(const Socket& ref);
	~Socket();

	Socket&	operator=(const Socket& ref);

	
	int		ft_get_socket_fd();
	Socket	*ft_accept();
	void	ft_listen(int backlog);
};

#endif
