#ifndef CLIENT_HPP
# define CLIENT_HPP

class Client
{
private:
	/* data */

public:
	Client();
	Client(const Client& ref);
	~Client();

	Client&	operator=(const Client& ref);
};

#endif
