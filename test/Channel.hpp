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
    std::string			_channel_name;
    std::map<std::string, User *>	_user_list;

public:
    Channel(std::string channel_name, UserControl &user_control);
    ~Channel();

    Channel&	operator=(const Channel& ref);

	void	ft_channel_join_user(User *user);
	void	ft_channel_leave_user(User *user);
	void	ft_send_all(std::string buf, std::string user_name);
	void	ft_send_me(std::string buf, std::string user_name);
};

#endif
