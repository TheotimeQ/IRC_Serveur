#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Client
{

	private:

		struct sockaddr_in6 	_Client_Address;
		socklen_t 				_Client_Address_Len;

	public:

		std::string 	_UserName;
		std::string	    _NickName;
        std::string	    _Password;
		std::string	    _Channel;
        int             _Type;
		std::string		_Data;
		int 			_Client_Socket;  
		int 			_Poll_Set_Index;  

		Client(); 
        Client(int Serveur_Socket); 
		Client& operator=(const Client& other);
		~Client();
};

std::ostream& operator<<(std::ostream& out, const Client& Client);

#endif
