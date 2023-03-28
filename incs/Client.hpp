#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <iostream>

// #include <iostream>
// #include <cstring>
// #include <cstdio>
// #include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
// #include <arpa/inet.h>
// #include <poll.h>
// #include <cerrno>

class Client
{

	private:

		std::string 	_UserName;
		std::string	    _NickName;
        std::string	    _Password;
        int             _Type;

		struct sockaddr_in6 	_Client_Address;
		socklen_t 				_Client_Address_Len;
		int 					_Client_Socket;  

	public:

        Client(); 
		Client(std::string& UserName, std::string& NickName, std::string& Password, int Type); 
		Client(const Client& other);
		~Client();
		Client& operator=(const Client& other);

        std::string Get_UserName(void)  const;
        std::string Get_NickName(void)  const;
        std::string Get_Password(void)  const;
        int         Get_Type(void)      const;
};

std::ostream& operator<<(std::ostream& out, const Client& Client);

#endif
