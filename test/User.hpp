#ifndef USER_HPP
#define USER_HPP

#include <string>
#include "Receive.hpp"

class User : public Receive
{

private:
    /* data */
	const int			_fd;
	const std::string	_user_name;
	std::string			_nick_name;
	std::string			_channel_name;
	int					_auth;

public:
	enum
	{
		OWNER,
		OPERATOR,
		USER,
		END
	};
	User(int fd, std::string user_name);
	User(const User &ref);
	~User();

	User &operator=(const User &ref);

    const int &ft_get_fd();
    const std::string &ft_get_user_name();
    const std::string &ft_get_nick_name();
    const std::string &ft_get_channel_name();
	const int &ft_get_auth() { return this->_auth; }
    void    ft_set_nick_name(std::string nick_name);
    void    ft_set_channel_name(std::string channel_name);
	void ft_set_auth(int num)
	{
		this->_auth = num;
	}
};

#endif
