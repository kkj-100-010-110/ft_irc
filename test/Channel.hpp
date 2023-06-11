#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "User.hpp"
#include "UserControl.hpp"
#include "Receive.hpp"

class Channel : public UserControl, public Receive
{

private:
    Channel();
    Channel(const Channel &ref){};
    /* data */
    std::string _channel_name;
    User *_user_list;
    std::string _topic;

public:
    Channel(std::string channel_name, UserControl &user_control);
    ~Channel();

    Channel &operator=(const Channel &ref);
};

#endif
