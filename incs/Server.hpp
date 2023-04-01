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

#include "../incs/Client.hpp"
#include "../incs/Channel.hpp"
#include "../incs/Message_Manager.hpp"
#include "../incs/ChannelManager.hpp"
#include "../incs/Command_Manager.hpp"

const int MAX_CLIENTS = 10;
const int BUFFER_SIZE = 1024;

#define ERROR_SOCKET 		"Error: Can't create socket"
#define ERROR_CONF_SOCKET 	"Error: Can't configure socket "
#define ERROR_BIND 			"Error: Can't bind socket"
#define ERROR_LISTEN 		"Error: Can't listen on socket"
#define ERROR_POLL 			"Error: Can't get poll event"
#define ERROR_CONNECTION 	"Error: Can't while accept new client"
#define ERROR_DATA 			"Error: Can't while getting data from client"
#define ERROR_MAX_CLIENT	"Error: Can't add new client , max reached"
#define ERROR_DATA 			"Error: Can't while getting data from client"

#define EVENT_NEW_CLIENT 	"Log: New connection"
#define EVENT_DECONNECTED 	"Log: Client deconnected : "



#define EVENT_NEW_DATA 		"Log: Data received : \n"

// #define EVENT_CHANNEL_CREATION_FAILED 	"Channel creation error : "

// typedef std::map<std::string, Channel> t_mapChannel;

class Server
{

	private:

		std::string 		_Name;
		int 				_Port;
		int					_Nb_Clients;
        Client              _Clients[MAX_CLIENTS];

		int					_Server_Socket;
		struct sockaddr_in6 _Server_Address;
		struct pollfd 		_Poll_Set[MAX_CLIENTS + 1];
		
		// t_mapChannel 		_Chan_List;

		ChannelManager		_ChnMng;
		Message_Manager		_MsgMng;
		Command_Manager		_CmdMng;

		int		Setup_Client(Client Client);
		void	Deconnect_Client(int index);
		int 	Get_Data(int socket_fd, std::vector<std::string>& Data);
		void	log(std::string const &logMsg)	const;
		
		/* Channel deal with methods */ // private for now
		// void	Try_Add_New_Channel(std::string const &name, Client &chop);
		// void	Rm_Channel(std::string const &name);
		// void	log(std::string const &logMsg)	const;
		
	public:
		
		Server(const std::string& name, int port); 
		~Server();

	    int		Start_Server();
        int		Run(); 
        int		Stop_Server();

		std::string Get_Name(void)  			const;
        int			Get_Port(void)  			const;
		Client 		Get_Clients(int index) 		const;
		int 		Get_Nb_Client()			 	const;
};

std::ostream& operator<<(std::ostream& out, const Server& Server);
// std::ostream& operator<<(std::ostream& out, const t_mapChannel& ChanList);

#endif
