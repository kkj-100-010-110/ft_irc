#include <iostream>
#include <iomanip>

#include <map>

#include <sys/socket.h>

#include "Channel.hpp"

Channel::Channel()
{
    std::cout << std::setw(15) << "[Channel] " << "create!!" << std::endl;
}

Channel::Channel(std::string channel_name, UserControl &user_control):
	_channel_name(channel_name), UserControl(user_control)
{
    std::cout << std::setw(15) << "[Channel] " << "create!!" << std::endl;
}

Channel::~Channel()
{
    std::cout << std::setw(15) << "[Channel] " << "delete!!" << std::endl;
}

Channel&	Channel::operator=(const Channel& ref)
{
    *this=ref;
    std::cout << std::setw(15) << "[Channel] " << "operator=!!" << std::endl;
    return (*this);
}

bool	Channel::ft_channel_join_user(User *user)
{
	if (this->_ben_list.at(user->ft_get_user_name()))
		return (false);
	user->ft_set_channel_name(this->_channel_name);
	this->_user_list.insert( std::pair<std::string, User *>(user->ft_get_user_name(), user));
	return (true);
}


void	Channel::ft_channel_leave_user(User *user)
{
	std::map<std::string, User *>::iterator it = this->_user_list.find(user->ft_get_user_name());
	if (it != this->_user_list.end())
	{
		this->_user_list.erase(user->ft_get_user_name());
		user->ft_set_channel_name("defualt");
	}
}

bool	Channel::ft_channel_ben_user(User *user)
{
	if (!this->_ben_list.at(user->ft_get_user_name()))
		this->_ben_list.insert(user->ft_get_user_name(), user);
}


void	Channel::ft_send_all(std::string buf, std::string user_name)
{
	 std::map<std::string, User *>::iterator it = this->_user_list.begin();
	 while (it != this->_user_list.end())
	 {
		if ((*it).first != user_name)
			send((*it).second->ft_get_fd(), buf.c_str(), buf.length(), 0);
		it++;
	 }
	 
}

void	Channel::ft_send_me(std::string buf, std::string user_name)
{
	send(this->_user_list.at(user_name)->ft_get_fd(), buf.c_str(), buf.length(), 0);
}