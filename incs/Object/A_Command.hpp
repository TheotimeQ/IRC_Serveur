#ifndef A_COMMAND_HPP
#define A_COMMAND_HPP

#include <iostream>
#include <string>
#include <cerrno>
#include <vector>
#include <map>
#include <sstream>

#include <string>
#include <cstring>

#include "../Irc.hpp"
#include "../Object/Client.hpp"
#include "../Object/Channel.hpp"
#include "../Manager/ChannelManager.hpp"
#include "../Manager/Client_Manager.hpp"

#define ERROR_SEND_MSG 		"Error: Can't send message : \n"
#define EVENT_NEW_MSG 		"Log: Message sent : "

class A_Command
{

	private:

	public:
		
		A_Command(); 
		virtual ~A_Command();

		virtual void	Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager);
		int				Send_Cmd(int client_sock, const std::string& Cmd);


		/* Build reponse mehod-tool */

			// [Basic REP] -> ":IRC 332 Zel #test :This is my cool channel! \n"
			// [Basic REP] -> ":<server> <code> <user> <channel> :<msg_to_send> \n"
		std::string	BuildRep_Basic(int code, std::string const &nick, std::string const &channel, std::string const &addon);

			// [Command Event REP] -> ":Zel!~a@localhost JOIN #test \n"
		std::string	BuildRep_CmdEvent(std::string const &cmde, std::string const &nick, std::string const &channel);


};

#endif
