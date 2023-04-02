#ifndef CLIENT_MANAGER_HPP
#define CLIENT_MANAGER_HPP

#include <map>
#include <string>

#include "../Irc.hpp"
#include "../Object/Client.hpp"

#define ERROR_MAX_CLIENT	"Error: Can't add new client , max reached"
#define ERROR_RTN_CLIENT	"Error: Can't return client , wrong index"
#define ERROR_RMV_CLIENT	"Error: Can't add remove client , wrong index"

// #define EVENT_CMDFOUND		"Log: Executing : "
// #define EVENT_NEW_MSG 		"Log: Message sent : \n"

class Client_Manager
{

	private:

        Client              _Clients[MAX_CLIENTS];

	public:

		int					Nb_Clients;
		
		Client_Manager(); 
		~Client_Manager();

        Client         &Get_Client(int index);
        int             Add_Client(Client Client);
        int             Remove_Client(int index);
};

#endif
