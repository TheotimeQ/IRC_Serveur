#include "../incs/Client.hpp"

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

//--------------------Setters--------------------

void Client::Set_UserName(std::string UserName)
{
	this->_UserName = UserName;
}

void Client::Set_NickName(std::string NickeName)
{
	this->_NickName = NickeName;
}

//Set channel

void Client::Set_Password(std::string Password)
{
	this->_Password = Password;
}

void Client::Set_Type(int Type)
{
	this->_Type = Type;
}

//--------------------Getters--------------------
std::string Client::Get_UserName(void) const
{
	return (this->_UserName);
}

std::string Client::Get_NickName(void) const
{
	return (this->_NickName);
}

std::string Client::Get_Password(void) const
{
	return (this->_Password);
}

int Client::Get_Type(void) const
{
	return (this->_Type);
}

//--------------------Operator--------------------
std::ostream& operator<<(std::ostream &out, const Client &Client)
{
	out << "\nPrinting client data :"      << std::endl;
    out << "USER : " << Client.Get_UserName()      << std::endl;
	out << "NICK : " << Client.Get_NickName()      << std::endl;
    out << "PASS : " << Client.Get_Password()      << std::endl;
	out << "SOCK : " << Client._Client_Socket      << std::endl;
    out << "TYPE : " << Client.Get_Type()          << std::endl;
	return (out);
}
