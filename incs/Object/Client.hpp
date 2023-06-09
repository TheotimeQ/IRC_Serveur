/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:21:58 by tquere            #+#    #+#             */
/*   Updated: 2023/05/02 11:51:35 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Client
{

	private:

		struct sockaddr_in6 					_Client_Address;
		socklen_t 								_Client_Address_Len;

	public:

		std::string 				UserName;
		std::string	    			NickName;
        std::string	    			Password;
		std::string	    			HostName;
        int             			Type;
		int							Away;
		std::string					Away_Str;
		int							Cap_End;
		int							Logged;
		int							Oper;
		std::string					Quit_Msg;

		int 						Socket;

		std::string					Data;
		std::vector<std::string> 	All_Cmd; 

		Client(); 
        Client(int Serveur_Socket); 
		Client& operator=(const Client& other);
		~Client();
		std::string	makeFullName() const;
};

std::ostream& operator<<(std::ostream& out, const Client& Client);

#endif
