#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <cerrno>
#include <vector>
#include <map>
#include <sstream>

#include "../Object/Client.hpp"
#include "../Object/Channel.hpp"
#include "../Manager/ChannelManager.hpp"
#include "../Manager/Command_Manager.hpp"
#include "../Manager/Client_Manager.hpp"

#define ERROR_SERVER_PARAM 	"Usage: ircserv <port> <password>"
#define ERROR_PORT_EMPTY 	"Error: port empty : "
#define ERROR_PORT_NO_DIGIT "Error: port contain no digit caractere : "
#define ERROR_PORT_MAX		"Error: wtf bro? What are those test.. folow the correction sheet :D"
#define ERROR_PORT_RANGE 	"Error: 1 <= port <= 65535 : "
#define ERROR_SOCKET 		"Error: Can't create socket"
#define ERROR_CONF_SOCKET 	"Error: Can't configure socket "
#define ERROR_BIND 			"Error: Can't bind socket"
#define ERROR_LISTEN 		"Error: Can't listen on socket"
#define ERROR_POLL 			"Error: Can't get poll event"
#define ERROR_CONNECTION 	"Error: Can't while accept new client"
#define ERROR_DATA 			"Error: Can't while getting data from client"
#define ERROR_DATA 			"Error: Can't while getting data from client"

#define EVENT_NEW_CLIENT 	"Log: New connection"
#define EVENT_DECONNECTED 	"Log: Client deconnected : "
#define EVENT_NEW_DATA 		"Log: Data received : \n"

class Server
{
	private:

		std::string 		_Name;
		int 				_Port;
		std::string			_Password;

		int					_Server_Socket;
		struct sockaddr_in6 _Server_Address;
		struct pollfd 		_Poll_Set[MAX_CLIENTS + 1];

		ChannelManager		_ChnMng;
		Command_Manager		_CmdMng;
		Client_Manager		_CltMng;

		int		Setup_Client(const Client& Client);
		void	Deconnect_Client(const Client& Client, int index);
		int 	Get_Data(Client *Client);

	public:
		
		Server(const std::string& name, int port, std::string password); 
		~Server();

	    int		Start_Server();
        int		Run(); 
        int		Stop_Server();
};

#endif
