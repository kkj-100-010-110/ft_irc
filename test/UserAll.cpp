#include <iostream>
#include <iomanip>

#include "UserAll.hpp"

UserAll::UserAll()
{
	std::cout << std::setw(15) << "[UserAll] " << "create!!" << std::endl;
}

UserAll::UserAll(const UserAll& ref)
{
	*this=ref;
	std::cout << std::setw(15) << "[UserAll] " << "copy!!" << std::endl;
}

UserAll::~UserAll()
{
	std::cout << std::setw(15) << "[UserAll] " << "delete!!" << std::endl;
}

UserAll&	UserAll::operator=(const UserAll& ref)
{
	*this=ref;
	std::cout << std::setw(15) << "[UserAll] " << "operator=!!" << std::endl;
	return (*this);
}

void    UserAll::ft_new_user_all()
{
	this->_user_all = new std::map<std::string, User *>;
}

const std::map<std::string, User *> *UserAll::ft_get_user_all()
{
	return (this->_user_all);
}

void    UserAll::ft_set_user_all(std::map<std::string, User *> *user_all)
{
	this->_user_all = user_all;
}

void    UserAll::ft_add_user(User *user)
{
	this->_user_all->insert({user->ft_get_user_name(), user});
	
}