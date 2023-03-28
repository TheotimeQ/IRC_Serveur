#ifndef SERVEUR_HPP
#define SERVEUR_HPP

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

const int MAX_CLIENTS = 10;
const int BUFFER_SIZE = 1024;

#define ERROR_SOCKET 		"Error: Can't create socket"
#define ERROR_CONF_SOCKET 	"Error: Can't configure socket "
#define ERROR_BIND 			"Error: Can't bind socket"
#define ERROR_LISTEN 		"Error: Can't listen on socket"
#define ERROR_POLL 			"Error: Can't get poll event"
#define ERROR_CONNECTION 	"Error: Can't while accept new client"
#define ERROR_DATA 			"Error: Can't while getting data from client"

#define ERROR_SEND_MSG 		"Error: Can't send message : \n"
#define ERROR_DATA 			"Error: Can't while getting data from client"

#define EVENT_NEW_CLIENT 	"Log: New connection"
#define EVENT_DECONNECTED 	"Log: Client deconnected"
#define EVENT_NEW_DATA 		"Log: Data received : \n"
#define EVENT_NEW_MSG 		"Log: Message sent : \n"

class Client;

class Serveur
{

	private:

		std::string 		_Name;
		int 				_Port;
        Client              _Clients[MAX_CLIENTS];

		int					_Serveur_Socket;
		struct sockaddr_in6 _Server_Address;
		struct pollfd 		_Poll_Set[MAX_CLIENTS + 1];
		int					_Last_Fd_index;

		int 	Send_Message(int client_sock, const std::string& message);
		int		New_Client();
        int		get_message();
        int		response();
	
	public:

		Serveur(const std::string& name, int port); 
		Serveur(const Serveur& other);
		~Serveur();
		Serveur& operator=(const Serveur& other);

		std::string Get_Name(void)  		const;
        int			Get_Port(void)  		const;
		Client 		Get_Clients(int index) 	const;

	    int		Start_Serveur();     //CONST ? 
        int		Run(); 
        int		stop_server();

		// class Error : public std::exception
		// {
		// 	public:
		// 		const char* what() const throw()
		// 		{
		// 			return "Error: Serveur";
		// 		}
		// };
};

std::ostream& operator<<(std::ostream& out, const Serveur& Serveur);

#endif
