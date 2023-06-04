#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <string>

class User
{
	enum 
	{
		OWNER,
		OPERATOR,
		USER,
		END
	};

private:
	std::string _nickname;
	std::string _username;
	int			_auth;

public:
};

#endif
