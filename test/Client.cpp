#include <iostream>
#include <iomanip>

#include "Client.hpp"

Client::Client()
{
	std::cout << std::setw(15) << "[Client] " << "create!!" << std::endl;
}

Client::Client(const Client& ref)
{
	*this=ref;
	std::cout << std::setw(15) << "[Client] " << "copy!!" << std::endl;
}

Client::~Client()
{
	std::cout << std::setw(15) << "[Client] " << "delete!!" << std::endl;
}

Client&	Client::operator=(const Client& ref)
{
	*this=ref;
	std::cout << std::setw(15) << "[Client] " << "operator=!!" << std::endl;
	return (*this);
}
