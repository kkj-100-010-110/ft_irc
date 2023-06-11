#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "User.hpp"
#include "UserControl.hpp"
#include "Receive.hpp"

class Channel : public UserControl
{

private:
    Channel();
    Channel(const Channel &ref){};
    /* data */
    std::string _channel_name;
    std::string _channel_topic;
    std::string _password;
    bool _has_password;
    bool _is_invite_only;
    bool _is_restricted;
    int _limit;

    std::map<std::string, User *> _user_list;

public:
    Channel(std::string channel_name, UserControl &user_control);
    ~Channel();
    Channel &operator=(const Channel &ref);

    std::string ft_get_topic() const { return this->_channel_topic; }
    std::string ft_get_password() const { return this->_password; }

    const int &ft_get_limit() { return this->_limit; }
    bool ft_get_has_password() const { return this->_has_password; }
    bool ft_get_restrict() const { return this->_is_restricted; }
    bool ft_get_invite() const { return this->_is_invite_only; }
    std::map<std::string, User *> &ft_get_user_list() { return this->_user_list; }

    void ft_set_limit(int limit) { this->_limit = limit; }
    void ft_set_password(const std::string &new_password) { this->_password = new_password; }
    void ft_set_restrict(bool on) { this->_is_restricted = on;}
    void ft_set_has_password(bool on) { this->_has_password = on; }
    void ft_set_invite(bool on) { this->_is_invite_only = on; }
    void ft_set_topic(const std::string &new_topic) { this->_channel_topic = new_topic; }

    bool ft_channel_join_user(User *user);
    void ft_channel_leave_user(User *user);
    void ft_send_all(std::string buf, std::string user_name);
    void ft_send_me(std::string buf, std::string user_name);
};

#endif
