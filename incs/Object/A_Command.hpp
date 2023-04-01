#ifndef A_COMMAND_HPP
#define A_COMMAND_HPP

#include <iostream>
#include <cerrno>
#include <vector>
#include <sstream>

#include "../Irc.hpp"
#include "../Object/Client.hpp"
#include "../Object/Message.hpp"

#define ERROR_SEND_MSG 		"Error: Can't send message : \n"

#define EVENT_NEW_MSG 		"Log: Message sent : \n"

class A_Command
{

	private:


	public:
		
		A_Command(); 
		virtual ~A_Command();

		virtual void 	Execute(Client &Client, std::vector<std::string> Args);
		int 			Send_Cmd(int client_sock, const std::string& Cmd);

};

#endif
