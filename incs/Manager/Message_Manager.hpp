/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message_Manager.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:45:57 by loumarti          #+#    #+#             */
/*   Updated: 2023/04/01 09:01:18 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_MANAGER_HPP
#define MESSAGE_MANAGER_HPP

#include <iostream>
#include <cerrno>
#include <sys/socket.h>
#include <cstring>

#include "../Irc.hpp"

#define ERROR_SEND_MSG 		"Error: Can't send message : \n"

#define EVENT_NEW_MSG 		"Log: Message sent : \n"

class Message_Manager
{

	private:

		
	public:
		
		Message_Manager(); 
		~Message_Manager();

		int 	Send_Message(int client_sock, const std::string& message);
		void 	log(std::string const &logMsg)	const;

};

#endif

