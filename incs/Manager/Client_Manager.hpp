#ifndef CLIENT_MANAGER_HPP
#define CLIENT_MANAGER_HPP

#include <map>
#include <string>
#include <sstream>
#include <cstdio>

#include "../Irc.hpp"
#include "../Object/Client.hpp"

#define ERROR_MAX_CLIENT	"Error: Can't add new client , max reached"
#define ERROR_RTN_CLIENT	"Error: Can't return client , wrong index"
#define ERROR_DEL_CLIENT	"Error: Can't add remove client , no such client"
#define ERROR_FID_CLIENT	"Error: Can't find client , no such : "

class Client_Manager
{
	private:

		std::map<std::string, Client>          _All_Clients;
		std::map<std::string, std::string>     _All_Credentials;

	public:

		int					Nb_Clients;
		
		Client_Manager(); 
		~Client_Manager();

		Client         *Get_Client_by_fd(int index);
		Client         *Get_Client(std::string NickName);
		int             Add_Client(const Client &Client);
		int             Remove_Client(const Client &Client);
		void            Print_Clients(void);

		int             Check_If_Can_Log(const Client& Clt);
};

#endif
