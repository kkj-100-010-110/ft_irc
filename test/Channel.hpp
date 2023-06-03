#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "User.hpp"
#include "UserAll.hpp"

class Channel: public UserAll
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
