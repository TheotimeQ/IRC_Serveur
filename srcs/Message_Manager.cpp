/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message_Manager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:31:18 by tquere            #+#    #+#             */
/*   Updated: 2023/04/01 08:49:37 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Message_Manager.hpp"

Message_Manager::Message_Manager()
{
	return;
}

Message_Manager::~Message_Manager()
{
	return;
}

//A modifier pour prendre un objet message en parametre
int Message_Manager::Send_Message(int client_sock, const std::string& message) 
{
    int bytes_sent = send(client_sock, message.c_str(), message.size(), 0);
    if (bytes_sent == -1) 
    {
        std::cerr << ERROR_SEND_MSG << strerror(errno) << std::endl;
        return ERROR;
    }
    std::cout << EVENT_NEW_MSG << message << std::endl;
    return GOOD;
}

// to print log message from MsgManager class
void Message_Manager::log(std::string const &logMsg)	const 
{
	std::cout << "\033[38;5;64m";
	std::cout << "MsgManager : ";
	std::cout << logMsg << std::endl;
	std::cout << "\033[m";
}