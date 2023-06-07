#ifndef LOG_HPP
# define LOG_HPP

#include <string>
#include <iostream>

#include "Color.hpp"


class Log
{
private:
	/* data */
	std::string _fd_color;
	std::string _message_color;
	std::string _error_color;
	std::string _none_color;

	Log(const Log& ref);
	Log&	operator=(const Log& ref);

public:
	Log()
	{
		this->_fd_color = FG;
		this->_fd_color += "196m";
		this->_message_color = FG;
		this->_message_color += "196m";
		this->_error_color = FG;
		this->_error_color += "196m";
		this->_none_color = NO_COLOR;
	};
	
	~Log() {};


	void	ft_error_log(std::string )
	{
		std::cerr
	};
};

#endif
