#include <iostream>
#include <iomanip>

#include "Error.hpp"

Error::Error()
	: _message("Error: default")
{
	
}

Error::Error(std::string errormessege)
	: _message("Error: " + errormessege)
{

}

Error::~Error() throw() 
{
	return ;
}

const char* Error::what() const throw()
{
	std::cout << std::setw(15) << "\033[95m" << "[Error] " << "\033[38;5;160m" << this->_message << std::endl;
	return ("1");
}