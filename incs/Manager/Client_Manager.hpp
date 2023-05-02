/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client_Manager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:21:30 by tquere            #+#    #+#             */
/*   Updated: 2023/05/02 11:51:35 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		std::map<std::string, std::string>		_Creds_Oper;

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
		bool			Is_Client_Oper(std::string const &NickName);

		void 			Send_To_All(std::string Msg);

		void			log(std::string const &logMsg) const;

		std::string* 	Get_Oper_Pass(std::string NickName);
};

#endif
