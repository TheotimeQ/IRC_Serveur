#ifndef COMMAND_MANAGER_HPP
#define COMMAND_MANAGER_HPP

#include <iostream>
#include <vector>
#include <sstream>

#include "../Irc.hpp"
#include "../Object/Client.hpp"
#include "../Manager/Message_Manager.hpp"

// #define ERROR_SOCKET 		"Error: Can't create socket"
// #define EVENT_NEW_MSG 		"Log: Message sent : \n"

class Command_Manager
{

	private:

		void 	Tokenize(std::string const &str, const char delim, std::vector<std::string> &out);

	public:
		
		Command_Manager(); 
		~Command_Manager();
		
		int		Interpret_Data(std::vector<std::string>& Data, Client &Client);

};

#endif
