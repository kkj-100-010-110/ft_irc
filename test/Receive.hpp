#ifndef RECEIVE_HPP
#define RECEIVE_HPP

#include "Command.hpp"
#include <iostream>
#include <string>
#include <vector>

class Receive : public Command
{
	enum
	{
		// when in the public channel & general command
		SLASH,
		AT,
		JOIN,
		HELP,
		// when users are in a non-public channel
		KICK,
		INVITE,
		TOPIC,
		MODE,
		END
	};

private:
	int _sign;
	std::string _username;
	std::string _cmd;
	char _option;
	std::string _arg;
	std::string _msg;

public:
	/* getter */
	int getSign() const { return _sign; }
	std::string getUsername() const { return _username; }
	std::string getCmd() const { return _cmd; }
	std::string getMsg() const { return _msg; }

	void receiveMsg(std::string input)
	{
		std::string::size_type n = input.find(' ');
		if (input.at(0) == '@')
		{
			if (n != 1)
			{
				_sign = AT;
				_username = input.substr(1, n);
				if ()
				{
				}
				else
				{
				}
				// check if the user exists
				_msg = input.substr(n + 1);
			}
			else
			{
				help();
			}
		}
		else if (input.at(0) == '/')
		{
			if (n != 1)
			{
				if () // public or channel
				{
				}
				else
				{
				}
				_sign = SLASH;
				_cmd = input.substr(1, n);
				// check if the command exists
				// cmd check if there is an option
				// if option & target exists
				//_option = input.substr();
				//_arg = input.substr();
				// else
				_msg = input.substr(n + 1);
			}
			else
			{
				help();
			}
		}
		else
		{
			_msg = input;
		}
	}

	void parseCmd()
	{
	}
};

#endif