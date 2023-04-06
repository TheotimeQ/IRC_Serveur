/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 09:03:00 by tquere            #+#    #+#             */
/*   Updated: 2023/04/06 11:37:49 by zelinsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Client.hpp"

Client::Client(): 
    UserName(""), 
    NickName("Undefined"),
    Password("Undefined"),
	HostName("Undefined"),
    Type(-1),
	Away(0),
	Away_Str("Undefined"),
	Logged(0)
{
	_Client_Address_Len = sizeof(_Client_Address);
	Socket = -1;
	return;
}

Client::Client(int Serveur_Socket): 
    UserName(""), 
    NickName("Undefined"),
    Password("Undefined"),
	HostName("Undefined"),
    Type(-1),
	Away(0),
	Away_Str("Undefined"),
	Logged(0)
{
	_Client_Address_Len = sizeof(_Client_Address);
	Socket = accept(Serveur_Socket, (struct sockaddr *)&_Client_Address, &_Client_Address_Len);
	
	std::stringstream ss;
    ss << Socket;
    NickName = ss.str();
	
	return;
}

Client& Client::operator=(const Client& other)
{
	if (this != &other) 
    {
		this->UserName = other.UserName;
		this->NickName = other.NickName;
        this->Password = other.Password;
		this->HostName = other.HostName;
        this->Type     = other.Type;	
		this->Logged   = other.Logged;
		this->Away	   = other.Away;
		this->Away_Str = other.Away_Str;

		this->_Client_Address_Len = other._Client_Address_Len;
		this->Socket = other.Socket;
	}
	return *this;
}

Client::~Client()
{
	return;
}

//--------------------Operator--------------------
std::ostream& operator<<(std::ostream &out, const Client &Client)
{
    out << "USER   : " << Client.UserName     	<< std::endl;
	out << "NICK   : " << Client.NickName   	<< std::endl;
    out << "PASS   : " << Client.Password      	<< std::endl;
	out << "HOST   : " << Client.HostName       << std::endl;
	out << "SOCK   : " << Client.Socket   		<< std::endl;
    out << "TYPE   : " << Client.Type       	<< std::endl;
	out << "AWAY   : " << Client.Away       	<< std::endl;
	out << "LOGGED : " << Client.Logged        	<< std::endl;
	return (out);
}
