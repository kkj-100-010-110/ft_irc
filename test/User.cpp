#include <iostream>
#include <iomanip>

#include "User.hpp"


User::User(int fd, std::string user_name)
    :_fd(fd), _user_name(user_name), _channel_name("defualt")
{
    std::cout << std::setw(15) << "[User] " << "create!!" << std::endl;
}

User::User(const User& ref):
	_fd(ref._fd), _user_name(ref._user_name), _channel_name("defualt")
{
    *this=ref;
    std::cout << std::setw(15) << "[User] " << "copy!!" << std::endl;
}

User::~User()
{
    std::cout << std::setw(15) << "[User] " << "delete!!" << std::endl;
}

User&	User::operator=(const User& ref)
{
    *this=ref;
    std::cout << std::setw(15) << "[User] " << "operator=!!" << std::endl;
    return (*this);
}


const int &User::ft_get_fd()
{
	return (this->_fd);
}

const std::string &User::ft_get_user_name()
{
	return (this->_user_name);
}

const std::string &User::ft_get_nick_name()
{
	return (this->_nick_name);
}

const std::string &User::ft_get_channel_name()
{
	return (this->_channel_name);
}

void    User::ft_set_nick_name(std::string nick_name)
{
    this->_nick_name = nick_name;
}
