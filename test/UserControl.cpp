#include <iostream>
#include <iomanip>

#include "UserControl.hpp"


UserControl::UserControl()
{
	std::cout << std::setw(15) << "[UserControl] " << "create!!" << std::endl;
}

UserControl::UserControl(const UserControl& ref)
{
	*this=ref;
	std::cout << std::setw(15) << "[UserControl] " << "copy!!" << std::endl;
}

UserControl::~UserControl()
{
	std::cout << std::setw(15) << "[UserControl] " << "delete!!" << std::endl;
}

UserControl&	UserControl::operator=(const UserControl& ref)
{
	*this=ref;
	std::cout << std::setw(15) << "[UserControl] " << "operator=!!" << std::endl;
	return (*this);
}

void	UserControl::ft_append_user(User *user)
{
	this->_fd_map->insert( std::pair<const int, User *>(user->ft_get_fd(), user ));
	this->_name_map->insert( std::pair<std::string, const int>( user->ft_get_user_name(), user->ft_get_fd() ));
}

User   *UserControl::ft_get_user(const int &fd)
{
	std::map<const int, User *>::iterator it = this->_fd_map->find(fd);
	if (it == this->_fd_map->end())
		return (NULL);
	return ((*it).second);
}

User	*UserControl::ft_get_user(const std::string &user_name)
{
	std::map<const std::string, int>::iterator it = this->_name_map->find(user_name);
	if (it == this->_name_map->end())
		return (NULL);
	return (this->ft_get_user((*it).second));
}
