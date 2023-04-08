/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_Command.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 09:03:06 by tquere            #+#    #+#             */
/*   Updated: 2023/04/08 09:53:26 by loumarti         ###   ########lyon.fr   */
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

int A_Command::Send_Cmd(int client_sock, const std::string& message) 
{
    int bytes_sent = send(client_sock, message.c_str(), message.size(), 0);
    if (bytes_sent == -1) 
    {
        std::cout << ERROR_SEND_MSG << strerror(errno) << std::endl;
        return ERROR;
    }

	//DEBUG
	std::cout << "\033[38;5;182m";
    std::cout << "      <- Sent       : " << message << std::endl;
	std::cout << "\033[m";
	//DEBUG

    // std::cout << EVENT_NEW_MSG << message ;
    return GOOD;
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
std::string	A_Command::BuildRep_CmdEvent(std::string const &cmde, std::string const &nick, std::string const &channel) const {
	std::string host = "~a@localhost"; // surment a passer en arg pour que ce soit pas fixe
	// lie au client->Hostname ?

	return (":" + nick + "!" + host + " " + cmde + " " + channel + " \n");
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