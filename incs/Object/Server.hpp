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
		void	Deconnect_Client(Client& Client, int index);
		int 	Get_Data(Client *Client);

	public:
		
		Server(const std::string& name, int port, std::string password); 
		~Server();

	    int		Start_Server();
        int		Run(); 
        int		Stop_Server();
};

#endif
