#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "User.hpp"
#include "UserControl.hpp"

class Channel: public UserControl
{

private:
    Channel();
    Channel(const Channel& ref) { };
    /* data */
    std::string     _channel_name;
    User  			 *_user_list;

public:
    Channel(std::string channel_name, UserControl &user_control);
    ~Channel();

    Channel&	operator=(const Channel& ref);
};

#endif
