#include "../incs/Client.hpp"

Client::Client(void) : 
    _UserName("Undefined"), 
    _NickName("Undefined"),
    _Password("Undefined"),
    _Type(-1)
{
	return;
}

Client::Client(std::string& UserName, std::string& NickName, std::string& Password, int Type) : 
    _UserName(UserName), 
    _NickName(NickName),
    _Password(Password),
    _Type(Type)
{
	return;
}

Client::Client(const Client &other)
{
	*this = other;
}

Client& Client::operator=(const Client& other)
{
	if (this != &other) 
    {
		this->_UserName = other._UserName;
		this->_NickName = other._NickName;
        this->_Password = other._Password;
        this->_Type     = other._Type;
	}
	return *this;
}

Client::~Client()
{
	return;
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
    std::cout << Client.Get_UserName()      << std::endl;
	std::cout << Client.Get_NickName()      << std::endl;
    std::cout << Client.Get_Password()      << std::endl;
    std::cout << Client.Get_Type()          << std::endl;
	return (out);
}
