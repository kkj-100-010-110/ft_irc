#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <string>

class Command
{
private:


public:


	void list()
	{
		// list the users 
	}

	// KICK, INVITE, TOPIC, MODE(OPERATORS)

	void kick()
	{
		// kick user out of the channel
		
		//if target exists
		//kick
		//else
		std::cout << "There is no such user." std::endl;
		
	}

	std::string invite()
	{
		// invite user in the public channel to this channel
		// the user can deny
		// what if the user in another channel?
		
		// if target exists
		// invite
		// else
		std::cout << "There is no such user." std::endl;
	}

	std::string topic()
	{
		// can change the topic of the channel
		// & view the topic
		
		// make two options?

	}

	std::string mode()
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
