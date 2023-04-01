/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 09:03:00 by tquere            #+#    #+#             */
/*   Updated: 2023/04/01 11:52:40 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Client.hpp"

Client::Client(): 
    _UserName("Undefined"), 
    _NickName("Undefined"),
    _Password("Undefined"),
    _Type(-1)
{
	_Client_Address_Len = sizeof(_Client_Address);
	_Client_Socket = -1;
	return;
}

Client::Client(int Serveur_Socket): 
    _UserName("Undefined"), 
    _NickName("Undefined"),
    _Password("Undefined"),
    _Type(-1)
{
	_Client_Address_Len = sizeof(_Client_Address);
	_Client_Socket = accept(Serveur_Socket, (struct sockaddr *)&_Client_Address, &_Client_Address_Len);
	return;
}

Client& Client::operator=(const Client& other)
{
	if (this != &other) 
    {
		this->_UserName = other._UserName;
		this->_NickName = other._NickName;
        this->_Password = other._Password;
        this->_Type     = other._Type;
		this->_Client_Address_Len = other._Client_Address_Len;
		this->_Client_Socket = other._Client_Socket;
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
	out << "\nPrinting client data :"      		<< std::endl;
    out << "USER : " << Client._UserName     	<< std::endl;
	out << "NICK : " << Client._NickName   		<< std::endl;
    out << "PASS : " << Client._Password      	<< std::endl;
	out << "SOCK : " << Client._Client_Socket   << std::endl;
    out << "TYPE : " << Client._Password        << std::endl;
	return (out);
}
