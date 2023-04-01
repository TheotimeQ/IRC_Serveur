/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command_Manager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:32:08 by tquere            #+#    #+#             */
/*   Updated: 2023/04/01 10:51:48 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Manager/Command_Manager.hpp"

Command_Manager::Command_Manager()
{
    Cmd_List["JOIN"] = new Join_Command();
    Cmd_List["KICK"] = new Kick_Command();
    Cmd_List["NICK"] = new Nick_Command();
    Cmd_List["USER"] = new User_Command();

    return;
}

Command_Manager::~Command_Manager()
{
    std::map<std::string, A_Command*>::iterator it;
    
    for (it = Cmd_List.begin(); it != Cmd_List.end(); ++it) {
        delete it->second;
    }
	return;
}

A_Command* Command_Manager::Get_Command(std::string str) 
{
    std::map<std::string, A_Command*>::iterator it = Cmd_List.find(str);

    if (it != Cmd_List.end())
    {
        std::cerr << EVENT_CMDFOUND << it->first << std::endl;
        return it->second;
    }
    std::cerr << ERROR_CMDNOTFOUND << str << std::endl;
    return NULL;
}

void Command_Manager::Tokenize(std::string const &str, const char delim, std::vector<std::string> &out) 
{ 
    std::stringstream ss(str); 
 
    std::string s; 
    while (std::getline(ss, s, delim)) { 
        out.push_back(s); 
    } 
} 

int Command_Manager::Interpret_Data(std::vector<std::string>& Data, Client &Client)
{
    for (std::vector<std::string>::const_iterator it = Data.begin(); it != Data.end(); ++it) 
    {
        // std::cout << Client.Get_UserName() << " -> " << *it << std::endl;
        std::vector<std::string> Args; 

        Tokenize(*it, ' ', Args); 
        
        A_Command *Cmd = this->Get_Command(Args[0]);
        if (Cmd)
            Cmd->Execute(Client, Args, Channels);
    }
    return GOOD;
}
