#ifndef CHANNELCONTROL_HPP
# define CHANNELCONTROL_HPP

#include <map>
#include <Channel.hpp>

class ChannelControl
{
private:
    /* data */

	std::map<const std::string, Channel *> _channel_map;

    
public:
    ChannelControl();
    ChannelControl(const ChannelControl& ref);
    ~ChannelControl();

    ChannelControl&	operator=(const ChannelControl& ref);
};

#endif
