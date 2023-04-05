/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command_Manager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:32:08 by tquere            #+#    #+#             */
/*   Updated: 2023/04/05 09:16:56 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Manager/Command_Manager.hpp"

Command_Manager::Command_Manager()
{
    //TEST
    Cmd_List["DEBUG"]   = new DEBUG_Command();
    
    //Connection Registration
    Cmd_List["PASS"]    = new PASS_Command();
    Cmd_List["NICK"]    = new NICK_Command(); 
    Cmd_List["USER"]    = new USER_Command();
    Cmd_List["OPER"]    = new OPER_Command();

    //Channel operations
    Cmd_List["JOIN"]    = new JOIN_Command();
    Cmd_List["PART"]    = new PART_Command(); 
    Cmd_List["MODE"]    = new MODE_Command(); 
    Cmd_List["TOPIC"]   = new TOPIC_Command(); 
    Cmd_List["NAMES"]   = new NAMES_Command(); 
    Cmd_List["LIST"]    = new LIST_Command(); 
    Cmd_List["INVITE"]  = new INVITE_Command(); 
    Cmd_List["KICK"]    = new KICK_Command(); 

    //Sending messages
    Cmd_List["PRIVMSG"]   = new PRIVMSG_Command(); 
    Cmd_List["NOTICE"]    = new NOTICE_Command();

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
        std::cout << EVENT_CMDFOUND << it->first << std::endl;
        return it->second;
    }
    std::cout << ERROR_CMDNOTFOUND << str << std::endl;
    return NULL;
}

void Command_Manager::Tokenize(std::string const &str, const char delim, std::vector<std::string> &out) 
{ 
    std::string Cleaned = "";

    for (int i = 0; i < (int)str.length(); i++) {
        if (str[i] != '\r') {
            Cleaned += str[i];
        }
    }

    std::stringstream ss(Cleaned); 
 
    std::string s; 
    while (std::getline(ss, s, delim)) { 
        out.push_back(s); 
    } 
} 

int Command_Manager::Interpret_Data(Client *Client, ChannelManager &Channel_Manager, Client_Manager &Client_Manager)
{
    for (std::vector<std::string>::const_iterator it = (*Client).All_Cmd.begin(); it != (*Client).All_Cmd.end(); ++it) 
    {
        std::vector<std::string> Args;
        Tokenize(*it, ' ', Args); 
        
        //DEBUG
		std::cout << "\033[38;5;180m";
        std::cout << "      -> Received   : "<< *it << std::endl;
		std::cout << "\033[m";
		//DEBUG

        if (Args[0] == "QUIT")
        {
            std::cout << EVENT_CMDFOUND << Args[0] << std::endl;
            return QUIT;
        }
            
        A_Command *Cmd = this->Get_Command(Args[0]);

        if ((*Client).Logged == 0)
        {
            if (Args[0] == "USER" || Args[0] == "PASS" || Args[0] == "NICK")
            {
                if (Cmd != NULL)
                    Cmd->Execute(Client, Args, Channel_Manager, Client_Manager);
                //CHECK IF CAN LOG
            }
            else
                std::cout << "Can't , not logged yet" << std::endl;
        }
        else   
            if (Cmd != NULL)
                Cmd->Execute(Client, Args, Channel_Manager, Client_Manager);
    }
    
    (*Client).All_Cmd.clear();

    return GOOD;
}
