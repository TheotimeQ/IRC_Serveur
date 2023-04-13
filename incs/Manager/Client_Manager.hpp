#ifndef CLIENT_MANAGER_HPP
#define CLIENT_MANAGER_HPP

#include <map>
#include <string>
#include <sstream>
#include <cstdio>

#include "../Irc.hpp"
#include "../Object/Client.hpp"

class Client_Manager
{
	private:

		std::vector<Client>    					_All_Clients;
		std::string    							_Password;
		std::map<std::string, std::string>		_All_Credentials;

	public:

		int					Nb_Clients;
		
		Client_Manager(); 
		~Client_Manager();

		Client         *Get_Client_by_fd(int index);
		Client         *Get_Client(std::string NickName);
		int             Add_Client(const Client &Client);
		int             Remove_Client(const Client &Client);
		void            Print_Clients(void);

		void			Set_Password(std::string &password);

		void 			Check_Log(Client *Clt);

		int				Set_Client_Nickname(Client &Client, std::string New_Nickname);

		// std::string* 	Get_Oper_Pass(std::string NickName);
		// void 			Check_Log_Oper(Client* Clt);
};

#endif
