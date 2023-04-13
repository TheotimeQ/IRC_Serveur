/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 09:03:00 by tquere            #+#    #+#             */
/*   Updated: 2023/04/13 14:13:53 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Client.hpp"

Client::Client(): 
    UserName(""), 
    NickName(""), //PAR DEFAULT "" COLISION ?
    Password("Undefined"),
	HostName("localhost"),
	Away(0),
	Away_Str("Undefined"),
	Cap_End(1),
	Logged(0),
	Oper(0)
{
	_Client_Address_Len = sizeof(_Client_Address);
	Socket = -1;
	return;
}

Client::Client(int Serveur_Socket): 
    UserName(""), 
    NickName(""), //PAR DEFAULT "" COLISION ?
    Password("Undefined"),
	HostName("localhost"),
	Away(0),
	Away_Str("Undefined"),
	Cap_End(1),
	Logged(0),
	Oper(0)
{
	_Client_Address_Len = sizeof(_Client_Address);
	Socket = accept(Serveur_Socket, (struct sockaddr *)&_Client_Address, &_Client_Address_Len);
	
	return;
}

Client& Client::operator=(const Client& other)
{
	if (this != &other) 
    {
		this->UserName 				= other.UserName;
		this->NickName 				= other.NickName;
        this->Password 				= other.Password;
		this->HostName 				= other.HostName;
		this->Cap_End  				= other.Cap_End;	
		this->Logged   				= other.Logged;
		this->Away	   				= other.Away;
		this->Away_Str 				= other.Away_Str;
		this->_Client_Address_Len 	= other._Client_Address_Len;
		this->Socket 				= other.Socket;
		this->Oper 					= other.Oper;
	}
	return *this;
}

Client::~Client()
{
	return;
}

// make a "nickname!username@hostname" name format
std::string	Client::makeFullName() const {
	return NickName + "!" + UserName + "@" + HostName;
}

//--------------------Operator--------------------
std::ostream& operator<<(std::ostream &out, const Client &Client)
{
    out << "USER   : " << Client.UserName     	<< std::endl;
	out << "NICK   : " << Client.NickName   	<< std::endl;
    out << "PASS   : " << Client.Password      	<< std::endl;
	out << "HOST   : " << Client.HostName       << std::endl;
	out << "SOCK   : " << Client.Socket   		<< std::endl;
	out << "AWAY   : " << Client.Away       	<< std::endl;
	out << "CAP    : " << Client.Cap_End       	<< std::endl;
	out << "LOGGED : " << Client.Logged        	<< std::endl;
	return (out);
}

