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

		void			Log(std::string const &cmde, std::string const &msg) const;


		/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Build reponse mehod-tool ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

			// [Basic REP] -> ":IRC 332 Zel #test :This is my cool channel! \n"
			// [Basic REP] -> ":<server> <code> <user> <channel> :<msg_to_send> \n"
		std::string	BuildRep_Basic(int code, std::string const &nick, std::string const &channel, std::string const &addon) const;

			// [Cmde REP] -> ":IRC 461 <command> :Not enough parameters"
			// [Cmde REP] -> ":<server> <code> <cmde> :<msg_to_send> \n"
		std::string	BuildRep_Cmde(int code, std::string const &cmde, std::string const &addon) const;

			// [Chan REP ] -> ":IRC 442 <channel> :You're not on that channel"
			// [Chan REP ] -> ":<server> <code> <channel> :<msg_to_send> \n"
		std::string	BuildRep_Chan(int code, std::string const &channel, std::string const &addon) const;
		// Au final Chan et Cmde sont identiques a part le nom des arguments

			// [Command Event REP] -> ":Zel!~a@localhost JOIN #test \n"
		std::string	BuildRep_CmdEvent(std::string const &cmde, std::string const &nick, std::string const &channel) const;


		/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Parsing precheck mehod-tool ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
		bool	Is_Channel_Name_Arg(std::string const &arg) const;

};

#endif
