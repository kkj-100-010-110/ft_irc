#ifndef RECEIVE_HPP
#define RECEIVE_HPP

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
	int			_sign;
	std::string	_username;
	std::string	_cmd;
	char		_option;
	std::string	_target;
	std::string	_msg;

public:
	/* getter */
	int getSign() const { return _sign; }
	std::string getUsername() const { return _username; }
	std::string getCmd() const { return _cmd; }
	std::string getMsg() const { return _msg; }
	{

	}

	void displayHelp()
	{
		std::cout << "-HELP-" << std::endl;
		std::cout << std::endl;
		std::cout << "[Usage for Sending Private messages]" << std::endl;
		std::cout << "\"@user_name message\"" << std::endl;
		std::cout << std::endl;
		std::cout << "[Command List in the Public Channel or General]" << std::endl;
		std::cout << "-JOIN- \"/join channel_name\" : join a channel or create a channel if not exist." << std:: endl;
		std::cout << "-LIST- \"/list channels(or users)\" : list channels(or users)." << std:: endl;
		std::cout << "-HELP- \"/help\" : display HELP." << std:: endl;
		std::cout << "[Command List in a Channel]" << std::endl;
		std::cout << "-KICK- \"/kick user_name\" : kick the user out of the channel." << std:: endl;
		std::cout << "-INVITE- \"/invite user_name\" : invite the user." << std:: endl;
		std::cout << "-TOPIC- \"/topic topic_content(or empty)\" : change the topic as topic_content or view the topic if empty." << std:: endl;
		std::cout << "-MODE- \"/mode options(i, t, k, o, l)\"" << std:: endl;
		std::cout << "       \"/mode i private(or public)\" : make the channel private(or public)." << std::endl;
		std::cout << "       \"/mode t\" : set/remove the restrictions of the TOPIC command to channel operators." << std::endl;
		std::cout << "       \"/mode k pwon(pwoff) password\" : set/remove the channel key." << std::endl;
		std::cout << "       \"/mode o user_name\" : give/take channel operator privilege to nick_name." << std::endl;
		std::cout << "       \"/mode l number(or r)\" : set/remove the user limit to channel." << std::endl;
	}

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
				displayHelp();
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
				//cmd check if there is an option
				//if option & target exists
				//_option = input.substr();
				//_target = input.substr();
				//else
				_msg = input.substr(n + 1);
			}
			else
			{
				displayHelp();
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
