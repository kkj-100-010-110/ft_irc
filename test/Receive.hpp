#ifndef RECEIVE_HPP
#define RECEIVE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Command.hpp"

class Receive : public Command
{
	enum
	{
		// when in the public channel & general command
		LIST,
		JOIN,
		HELP,
		// when users are in a non-public channel (defualt channel)
		KICK,
		INVITE,
		TOPIC,
		MODE,
		END
	};

private:
	std::vector<std::string> _option;
	std::vector<std::string> _arg;
	std::map<std::string, int> _cmd = {
		{"list", LIST},
		{"join", JOIN},
		{"help", HELP},
		{"kick", KICK},
		{"invite", INVITE},
		{"topic", TOPIC},
		{"mode", MODE}};

public:
	int ft_receive_msg(std::string input, User *user, std::map<std::string, Channel *> channel_list)
	{
		this->_option.clear();
		this->_arg.clear();

		input = input.substr(input.find_first_not_of(' '));
		switch (input[0])
		{
		case '@':
			return (ft_whisper(input, user));
		case '/':
			return (ft_cmd(input, user, channel_list));
		default:
			break;
		}
		return (0);
	}

	int ft_whisper(std::string input, User *user)
	{
		input = input.substr(1);
		if (input[0] == ' ')
			return (-1);
		this->_arg.push_back(input.substr(0, input.find_first_of(" \f\n\r\t\v"))); // user_name
		input = input.substr(0, input.find_first_of(" \f\n\r\t\v"));
		if (input.size() <= 1)
			return (-1);
		this->_arg.push_back(input.substr(1)); // msg
		if (this->ft_get_user(this->_arg[0]))
			send(this->ft_get_user(this->_arg[0])->ft_get_fd(), this->_arg[1].c_str(), this->_arg[1].size(), 0);
	}

	int ft_cmd(std::string input, User *user, std::map<std::string, Channel *> channel_list)
	{
		input = input.substr(1);
		if (input[0] == ' ')
			return (-1);
		this->_arg.push_back(input.substr(0, input.find_first_of(" \f\n\r\t\v"))); // cmd

		if (this->_cmd.find(this->_arg[0]) == this->_cmd.end())
			return (-1);
		switch (this->_cmd.at(this->_arg[0]))
		{
		case LIST:
			return (ft_cmd_list(input, user, channel_list));
		case JOIN:
			return (ft_cmd_join(input, user, channel_list));
		case HELP:
			/* code */
			break;

		case KICK:
			/* code */
			break;

		case INVITE:
			/* code */
			break;

		case TOPIC:
			/* code */
			break;

		case MODE:
			/* code */
			break;
		}
	}
};

#endif