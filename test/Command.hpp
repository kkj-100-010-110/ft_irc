#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <string>
#include <map>

#include "User.hpp"

class Command
{
private:
public:
	void list(std::map<std::string, std::map<int, User *>> list, const std::string &channel)
	{
		std::map<std::string, std::map<int, User *>>::iterator it = list.find(channel);
		if (it == list.end())
		{
			std::cout << "No such channel." << std::endl;
		}
		else
		{
			std::cout << "- Users in the channel -" << std::endl;
			for (std::map<int, User *>::iterator innerIt = it->second.begin(); innerIt != it->second.end(); innerIt++)
				std::cout << innerIt->second << std::endl;
			std::cout << "------------------------" << std::endl;
		}
	}

	void help()
	{
		std::cout << "--------------------------------------------------- HELP ---------------------------------------------------" << std::endl;
		std::cout << std::endl;
		std::cout << "[Usage for Sending Private messages]" << std::endl;
		std::cout << "\"@user_name message\"" << std::endl;
		std::cout << std::endl;
		std::cout << "[Command List in the Public Channel or General]" << std::endl;
		std::cout << "-  JOIN  -   \"/join channel_name\" : join a channel or create a channel if not exist." << std::endl;
		std::cout << "-  LIST  -   \"/list channels\" : list users in the channel." << std::endl;
		std::cout << "-  HELP  -   \"/help\" : display HELP." << std::endl;
		std::cout << "[Command List in a Channel]" << std::endl;
		std::cout << "-  KICK  -\"/kick user_name\" : kick the user out of the channel." << std::endl;
		std::cout << "- INVITE -\"/invite user_name\" : invite the user." << std::endl;
		std::cout << "-  TOPIC -\"/topic topic_content(or empty)\" : change the topic as topic_content or view the topic if empty." << std::endl;
		std::cout << "-  MODE  -\"/mode options(i, t, k, o, l)\"" << std::endl;
		std::cout << "          \"/mode i private(or public)\" : make the channel private(or public)." << std::endl;
		std::cout << "          \"/mode t\" : set/remove the restrictions of the TOPIC command to channel operators." << std::endl;
		std::cout << "          \"/mode k pwon(pwoff) password\" : set/remove the channel key." << std::endl;
		std::cout << "          \"/mode o user_name\" : give/take channel operator privilege to nick_name." << std::endl;
		std::cout << "          \"/mode l number(or r)\" : set/remove the user limit to channel." << std::endl;
		std::cout << "------------------------------------------------------------------------------------------------------------" << std::endl;
	}

	// KICK, INVITE, TOPIC, MODE(OPERATORS)

	void kick(std::map<std::string, std::map<int, User *>> list, const std::string &user)
	{
		// kick user out of the channel
		std::map<std::string, std::map<const std::string, int>>::iterator it = _channel_list.find(user);
		if (it != _channel_list.end())
		{
			_channel_list.erase(user);
			std::cout << "Kicked " << user << "." << std::endl;
		}
		else
		{
			std::cout << "There is no such user." << std::endl;
		}
	}

	std::string invite(const std::string &user)
	{
		// invite user in the public channel to this channel
		// the user can deny
		// what if the user in another channel?

		// if target exists
		// invite
		// else
		std::cout << "There is no such user." << std::endl;
	}

	std::string topic(const std::string &topic)
	{
		// can change the topic of the channel
		// & view the topic
		if (topic == "")
		{
			// display topic
		}
		else
		{
			// change topic
		}
	}

	std::string mode(char option, const std::string &arg)
	{
		// mode
		// option
		// i
		// t
		// k
		// o
		// l
	}
};

#endif
