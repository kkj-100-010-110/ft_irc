#include <iostream>
#include <iomanip>

#include "ChannelControl.hpp"

ChannelControl::ChannelControl()
{
    this->_channel_map = new std::map<std::string, Channel *>;

    std::cout << std::setw(15) << "[ChannelControl] " << "create!!" << std::endl;
}

ChannelControl::ChannelControl(const ChannelControl& ref)
{
    *this=ref;
    std::cout << std::setw(15) << "[ChannelControl] " << "copy!!" << std::endl;
}

ChannelControl::~ChannelControl()
{
    std::cout << std::setw(15) << "[ChannelControl] " << "delete!!" << std::endl;
}

ChannelControl&	ChannelControl::operator=(const ChannelControl& ref)
{
    *this=ref;
    std::cout << std::setw(15) << "[ChannelControl] " << "operator=!!" << std::endl;
    return (*this);
}
