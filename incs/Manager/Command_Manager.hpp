/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command_Manager.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:21:40 by zelinsta          #+#    #+#             */
/*   Updated: 2023/05/02 11:21:44 by zelinsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_MANAGER_HPP
#define COMMAND_MANAGER_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <functional>

#include "../Irc.hpp"
#include "../Object/A_Command.hpp"
#include "../Object/Client.hpp"
#include "../Object/Commands.hpp"

class Command_Manager
{
	private:

		std::map<std::string, A_Command*> Cmd_List;

		A_Command* 	Get_Command(std::string str);
		void 		Tokenize(std::string const &str, const char delim, std::vector<std::string> &out);

		void		Log(std::string const &msg)	const;

	public:
		
		Command_Manager(); 
		~Command_Manager();
		
		int		Interpret_Data(Client *Client, ChannelManager &Channel_Manager, Client_Manager &Client_Manager);
};

#endif
