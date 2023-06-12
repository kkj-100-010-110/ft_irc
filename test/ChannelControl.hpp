#ifndef CHANNELCONTROL_HPP
# define CHANNELCONTROL_HPP

#include <map>
#include <string>
#include "Channel.hpp"


class ChannelControl
{
private:
    /* data */

	std::map<const std::string, Channel *> *_channel_map;

    
public:
    ChannelControl();
    ChannelControl(const ChannelControl& ref);
    ~ChannelControl();

    ChannelControl&	operator=(const ChannelControl& ref);

    void ft_append_channel(const Channel &ch);
    Channel * ft_get_channel(const std::string &channel_name);
    ChannelControl &ft_get_channel_control_class() { return (*this); }




    std::map<const std::string, Channel *> *ft_get_channel_map() { return this->_channel_map; }
};

#endif
