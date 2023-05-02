/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:22:22 by zelinsta          #+#    #+#             */
/*   Updated: 2023/05/02 13:03:30 by zelinsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

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
#include <signal.h>

#include "../Object/Client.hpp"
#include "../Object/Channel.hpp"
#include "../Manager/ChannelManager.hpp"
#include "../Manager/Command_Manager.hpp"
#include "../Manager/Client_Manager.hpp"

static int Stop;

class Server
{
	private:

		std::string 		_Name;
		int 				_Port;
		std::string			_Password;

		int					_Server_Socket;
		struct sockaddr_in6 _Server_Address;
		struct pollfd 		_Poll_Set[MAX_CLIENTS + 1];

		ChannelManager		_ChnMng;
		Command_Manager		_CmdMng;
		Client_Manager		_CltMng;

		int		Setup_Client(const Client& Client);
		void	Deconnect_Client(Client& Client, int index);
		int 	Get_Data(Client *Client);
		void	log(std::string const &logMsg) const;

	public:
		
		Server(const std::string& name, int port, std::string password); 
		~Server();

	    int		Start_Server();
        int		Run(); 
        int		Stop_Server();
};

#endif
