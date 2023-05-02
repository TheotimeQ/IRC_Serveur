/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:29:16 by tquere            #+#    #+#             */
/*   Updated: 2023/05/02 13:29:17 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

#include <string>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <cerrno>
#include <vector>
#include <map>
#include <sstream>
#include <climits>

const int BUFFER_SIZE = 1024;

#define GOOD    0
#define ERROR   1

#define BOT_NAME 	                "Bot"
#define IP                          "127.0.0.1"

#define ERROR_BOT_PARAM 	        "Usage: ./bot <port> <password>"
#define ERROR_PORT_EMPTY 	        "Error: port empty : "
#define ERROR_PORT_NO_DIGIT         "Error: port contain no digit caractere : "
#define ERROR_PORT_MAX		        "Error: wtf bro? What are those test.. folow the correction sheet :D"
#define ERROR_PORT_RANGE 	        "Error: 1 <= port <= 65535 : "
#define ERROR_IP            		"Error: Can't setup ip"
#define ERROR_CONNECTION    		"Error: Can't connect to serveur"
#define ERROR_SOCKET 		        "Error: Can't create socket"
#define ERROR_CONF_SOCKET 	        "Error: Can't configure socket "
#define ERROR_RECEIVE 		        "Error: Can't read on socket"

class Bot
{
	private:

		int					_Bot_Socket;
		struct sockaddr_in6 _Bot_Address;
		std::string 		_Name;
		int 				_Port;
		std::string			_Password;
		std::string			_Ip;

		void	            log(std::string const &logMsg) const;

	public:
		
		Bot(const std::string& name, int port, std::string password, const std::string& ip); 
		~Bot();

	    int		Start_Bot();
        int		Run(); 
        int		Stop_Bot();
};

#endif
