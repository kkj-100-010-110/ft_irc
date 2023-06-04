#include <iostream>
#include <iomanip>

#include "Channel.hpp"

Channel::Channel()
{
    std::cout << std::setw(15) << "[Channel] " << "create!!" << std::endl;
}

Channel::Channel(const Channel& ref)
{
    *this=ref;
    std::cout << std::setw(15) << "[Channel] " << "copy!!" << std::endl;
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
