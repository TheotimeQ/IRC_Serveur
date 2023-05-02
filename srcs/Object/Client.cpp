/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 09:03:00 by tquere            #+#    #+#             */
/*   Updated: 2023/05/02 11:51:35 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Client.hpp"

Client::Client(): 
    UserName(""), 
    NickName(""),
    Password("Undefined"),
	HostName("localhost"),
	Away(0),
	Away_Str("Undefined"),
	Cap_End(1),
	Logged(0),
	Oper(0),
	Quit_Msg("")
{
	_Client_Address_Len = sizeof(_Client_Address);
	Socket = -1;
	return;
}

Client::Client(int Serveur_Socket): 
    UserName(""), 
    NickName(""),
    Password("Undefined"),
	HostName("localhost"),
	Away(0),
	Away_Str("Undefined"),
	Cap_End(1),
	Logged(0),
	Oper(0),
	Quit_Msg("")
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
		this->Quit_Msg				= other.Quit_Msg;
	}
	return *this;
}

Client::~Client()
{
	return;
}

std::string	Client::makeFullName() const {
	return NickName + "!" + UserName + "@" + HostName;
}

//--------------------Operator--------------------
std::ostream& operator<<(std::ostream &out, const Client &Client)
{
    out << "USER    : " << Client.UserName     		<< std::endl;
	out << "NICK    : " << Client.NickName   		<< std::endl;
    out << "PASS    : " << Client.Password      	<< std::endl;
	out << "HOST    : " << Client.HostName       	<< std::endl;
	out << "SOCK    : " << Client.Socket   			<< std::endl;
	out << "AWAY    : " << Client.Away       		<< std::endl;
	out << "CAP     : " << Client.Cap_End       	<< std::endl;
	out << "LOGGED  : " << Client.Logged        	<< std::endl;
	out << "OPER    : " << Client.Oper        		<< std::endl;
	out << "QUITMSG : " << Client.Quit_Msg        	<< std::endl;
	return (out);
}

