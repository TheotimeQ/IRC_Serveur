/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_Command.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 09:03:06 by tquere            #+#    #+#             */
/*   Updated: 2023/04/03 16:24:57 by zelinsta         ###   ########.fr       */
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
    std::cout << EVENT_NEW_MSG << message << std::endl;
    return GOOD;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Build REP ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// [Basic REP] -> ":IRC 332 Zel #test :This is my cool channel! \n"
std::string	A_Command::BuildRep_Basic(int code, std::string const &nick, std::string const &channel, std::string const &addon) {
	std::ostringstream oss;
	oss << code;
	return (":" + std::string(SERVER_NAME) + " " + oss.str() + " " + nick + " " + channel + " :" + addon + " \n");
}