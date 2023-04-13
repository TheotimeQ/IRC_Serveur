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
#include <sys/time.h>

#include "../Irc.hpp"
#include "../utils.hpp"
#include "../Object/Client.hpp"
#include "../Object/Channel.hpp"
#include "../Manager/ChannelManager.hpp"
#include "../Manager/Client_Manager.hpp"

#define MODE_BASIC_ARGS		"ntmsipNTMSIP"
#define MODE_ADVANCED_ARGS	"lkLK"

class A_Command
{

	private:

	public:
		
		A_Command(); 
		virtual ~A_Command();

		virtual void	Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager);

		void			Log(std::string const &cmde, std::string const &msg) const;

		/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Build reponse mehod-tool ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

			//     [Basic REP] -> ":IRC 332 Zel #test :This is my cool channel! \n"
			//     [Basic REP] -> ":<server> <code> <user> <channel> :<msg_to_send> \n"
			// [BasicChan REP] -> ":<server> <code> <user> <channel> :<channel : msg_to_send> \n"
		std::string	BuildRep_Basic(int code, std::string const &nick, std::string const &channel, std::string const &addon) const;
		std::string	BuildRep_BasicChan(int code, std::string const &nick, std::string const &channel, std::string const &addon) const;


			//     [Home REP] -> there is no channel to answer -> send message to 'home' with 000 code
			//     [Home REP] -> ":<server> <000> <user> <msg_to_send> \n"
			// [HomeChan REP] -> ":<server> <000> <user> <channel : msg_to_send> \n"
		std::string	BuildRep_Home(std::string const &nick, std::string const &addon) const;
		std::string	BuildRep_HomeChan(std::string const &nick, std::string const &channel, std::string const &addon) const;


	/* (a ameliorer remplacer)*/

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
		bool	Is_Channel_Mode_BArgs(std::string const &args) const;
		bool	Is_Channel_Mode_AArgs(std::string const &args) const;

		/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ other-tool ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
		std::string					getNow()	const;
		std::vector<std::string>	extractComaList(std::string const &comaList)	const;
		std::string					catStringVector(std::vector<std::string>  const &vector, unsigned start) const;

		/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ debug-tool ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
		void	showStringVector(std::string const &title, std::vector<std::string> const  &vect) const;
};

#endif
