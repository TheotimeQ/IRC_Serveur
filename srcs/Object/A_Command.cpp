/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_Command.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 09:03:06 by tquere            #+#    #+#             */
/*   Updated: 2023/04/13 16:22:56 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/A_Command.hpp"

A_Command::A_Command()
{

	return;
}

A_Command::~A_Command()
{
	return;
}

void  A_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager)
{
	(void)Client;
	(void)Args;
	(void)Channel_Manager;
    (void)Client_Manager;
}

void	A_Command::Log(std::string const &cmde, std::string const &msg) const {
	std::cout << "\033[38;5;47m";
	std::cout << cmde << " : ";
	std::cout << "\033[38;5;49m";
	std::cout << msg << std::endl;
	std::cout << "\033[m";

}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Build REP ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

	// [Basic REP] -> ":IRC 332 Zel #test :This is my cool channel! \n"
std::string	A_Command::BuildRep_Basic(int code, std::string const &nick, std::string const &channel, std::string const &addon) const {
	std::ostringstream oss;
	oss << code;
	return (":" + std::string(SERVER_NAME) + " " + oss.str() + " " + nick + " " + channel + " " + addon + " \n");
}

	// [BasicChan REP] -> ":<server> <code> <user> <channel> :<channel : msg_to_send> \n"

std::string	A_Command::BuildRep_BasicChan(int code, std::string const &nick, std::string const &channel, std::string const &addon) const {
	std::ostringstream oss;
	oss << code;
	return (":" + std::string(SERVER_NAME) + " " + oss.str() + " " + nick + " " + channel + " " + channel + " : " + addon + " \n");
}

	// [Home REP] -> there is no channel to answer -> send message to 'home' with 000 code
	// [Home REP] -> ":<server> <000> <user> <msg_to_send> \n"
std::string	A_Command::BuildRep_Home(std::string const &nick, std::string const &addon) const {
	return (":" + std::string(SERVER_NAME) + " 000 " + nick + " " + addon + " \n");
}

std::string	A_Command::BuildRep_HomeChan(std::string const &nick, std::string const &channel, std::string const &addon) const {
	return (":" + std::string(SERVER_NAME) + " 000 " + nick + " " + channel + " : " + addon + " \n");
}


/* (a ameliorer remplacer) */

	// [Cmde REP] -> ":IRC 461 <command> :Not enough parameters"
	// [Cmde REP] -> ":<server> <code> <user> <channel> :<msg_to_send> \n"
std::string	A_Command::BuildRep_Cmde(int code, std::string const &cmde, std::string const &addon) const {
	std::ostringstream oss;
	oss << code;
	return (":" + std::string(SERVER_NAME) + " " + oss.str() + " " + cmde + " :" + addon + " \n");
}

	// [Chan REP ] -> ":IRC 442 <channel> :You're not on that channel"
	// [Chan REP ] -> ":<server> <code> <channel> :<msg_to_send> \n"
std::string	A_Command::BuildRep_Chan(int code, std::string const &channel, std::string const &addon) const {
	std::ostringstream oss;
	oss << code;
	return (":" + std::string(SERVER_NAME) + " " + oss.str() + " " + channel + " :" + addon + " \n");
}

// [Command Event REP] -> ":Zel!~a@localhost JOIN #test \n"
std::string	A_Command::BuildRep_CmdEvent(Client const &user, std::string const &cmde, std::string const &channel) const {
	return (":" + user.makeFullName() + " " + cmde + " " + channel + "\n");
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Parsing precheck mehod-tool ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// To update check too -> ChannelManager.checkChanName() method
bool	A_Command::Is_Channel_Name_Arg(std::string const &arg) const {
	if (arg.size() < 2)
		return false;
	else if ((arg[0] != '#' && arg[0] != '!' && arg[0] != '+' && arg[0] != '&'))
		return false;
	else if (arg.size() > 200)
		return false;
	for (unsigned i = 0; i < arg.size(); ++i) {
		if (arg[i] == ' ' || arg[i] == ',' || arg[i] == ':') {
			return false;
		}
	}
	return true;
}

//  checking if valid Basic mode Arguments : <[+-][ntmsipNTMSIP]> (multi arg allowed)
bool	A_Command::Is_Channel_Mode_BArgs(std::string const &args) const {
	if (args.size() < 2)
		return false;
	if (args[0] != '+' && args[0] != '-')
		return false;
	for (unsigned i = 1; i < args.size(); ++i) {
		if (std::string(MODE_BASIC_ARGS).find_first_of(args[i]) == std::string::npos)
			return false;
	}
	return true;
}

//  checking if valid advanced mode Arguments : <[+-][lkLK]> (only one flag at once)
bool	A_Command::Is_Channel_Mode_AArgs(std::string const &args) const {
	if (args.size() != 2)
		return false;
	if (args[0] != '+' && args[0] != '-')
		return false;
	if (std::string(MODE_ADVANCED_ARGS).find_first_of(args[1]) == std::string::npos)
		return false;
	return true;
}

bool	A_Command::Guard(Client *Client, std::vector<std::string> const &Args, std::string const &Cmde) const {
	if (Args.size() == 1 || (Args.size() == 2 && Args[1].compare("") == 0)) {
		Send_Cmd(Client->Socket, BuildRep_Cmde(461, Cmde, "Not enough parameters"));
		return false;
	}
	return true;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ other-tool ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
std::string	A_Command::getNow()	const {
	struct timeval now;
	std::ostringstream oss;
	
	gettimeofday(&now, 0);
	oss << now.tv_sec;
	return oss.str();
}

std::vector<std::string>	A_Command::extractComaList(std::string const &comaList)	const {
	std::vector<std::string>	extract;
	std::string					stamp;
	std::stringstream			ss;

	ss << comaList;
	while (getline(ss, stamp, ',')) {
		extract.push_back(stamp);
	}
	return extract;
}

std::string		A_Command::catStringVector(std::vector<std::string> const &vector, unsigned start) const {
	std::vector<std::string>::const_iterator	it;
	std::string 								cat = "";

	for (it = vector.begin() + start; it != vector.end(); ++it) {
		if (it != vector.begin() + start)
			cat += " ";
		cat += *it;
	}
	return cat;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ debug-tool ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void	A_Command::showStringVector(std::string const &title, std::vector<std::string> const  &vect) const {
	std::cout << "\033[38;5;242m";
	std::cout << title << ".size() = " << vect.size() << std::endl;
	for (unsigned i = 0; i < vect.size(); ++i) {
		std::cout << title <<"[" << i << "] = " << "|" << vect[i] << "|" << std::endl;
	}
	std::cout << "\033[m";
}