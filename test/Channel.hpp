#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "User.hpp"
#include "UserControl.hpp"

class Channel: public UserControl
{

private:
    /* data */
    User    *User_list;

public:
    Channel();
    Channel(const Channel& ref);
    ~Channel();

    Channel&	operator=(const Channel& ref);
};

#endif
