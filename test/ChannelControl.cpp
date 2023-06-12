#include <iostream>
#include <iomanip>

#include "ChannelControl.hpp"

ChannelControl::ChannelControl()
{
    this->_channel_map = new std::map<const std::string, Channel *>;

    std::cout << std::setw(15) << "[ChannelControl] " << "create!!" << std::endl;
}

ChannelControl::ChannelControl(const ChannelControl& ref)
    :_channel_map(ref._channel_map)
{
    std::cout << std::setw(15) << "[ChannelControl] " << "copy!!" << std::endl;
}

ChannelControl::~ChannelControl()
{
    std::cout << std::setw(15) << "[ChannelControl] " << "delete!!" << std::endl;
}

ChannelControl&	ChannelControl::operator=(const ChannelControl& ref)
{
    this->_channel_map = ref._channel_map;
    std::cout << std::setw(15) << "[ChannelControl] " << "operator=!!" << std::endl;
    return (*this);
}




void ft_append_channel(const Channel &ch)
{

}



Channel *ChannelControl::ft_get_channel(const std::string &channel_name)
{
	std::map<const std::string, Channel *>::iterator it = this->_channel_map->find(channel_name);
	if (it == this->_channel_map->end())
		return (NULL);
	return (this->_channel_map->at(channel_name));
}