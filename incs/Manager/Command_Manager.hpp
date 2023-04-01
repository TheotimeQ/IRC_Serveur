#ifndef COMMAND_MANAGER_HPP
#define COMMAND_MANAGER_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <functional>

#include "../Irc.hpp"
#include "../Object/A_Command.hpp"
#include "../Object/Client.hpp"
#include "../Object/Commands.hpp"

#define ERROR_CMDNOTFOUND 	"Error: Command not found : "
#define ERROR_SEND_MSG 		"Error: Can't send message : \n"

#define EVENT_CMDFOUND		"Log: Command found : "
#define EVENT_NEW_MSG 		"Log: Message sent : \n"

class Command_Manager
{

	private:

		std::map<std::string, A_Command*> Cmd_List;

		A_Command* 	Get_Command(std::string str);
		void 		Tokenize(std::string const &str, const char delim, std::vector<std::string> &out);

	public:
		
		Command_Manager(); 
		~Command_Manager();
		
		int		Interpret_Data(std::vector<std::string>& Data, Client &Client);

};

#endif
