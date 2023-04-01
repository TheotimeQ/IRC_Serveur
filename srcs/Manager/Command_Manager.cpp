/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command_Manager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:32:08 by tquere            #+#    #+#             */
/*   Updated: 2023/04/01 15:22:18 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Manager/Command_Manager.hpp"

Command_Manager::Command_Manager()
{
    //TEST
    Cmd_List["TEST"]    = new TEST_Command();
    
    //Connection Registration
    Cmd_List["PASS"]    = new PASS_Command();
    Cmd_List["NICK"]    = new NICK_Command(); 
    Cmd_List["USER"]    = new USER_Command();
    Cmd_List["OPER"]    = new OPER_Command();
    Cmd_List["QUIT"]    = new QUIT_Command();  

    //Channel operations
    Cmd_List["JOIN"]    = new JOIN_Command();
    Cmd_List["PART"]    = new PART_Command(); 
    Cmd_List["MODE"]    = new MODE_Command(); 
    Cmd_List["TOPIC"]   = new TOPIC_Command(); 
    Cmd_List["NAMES"]   = new NAMES_Command(); 
    Cmd_List["LIST"]    = new LIST_Command(); 
    Cmd_List["INVITE"]  = new INVITE_Command(); 
    Cmd_List["KICK"]    = new KICK_Command(); 

    //Server queries and commands 
    Cmd_List["VERSION"]   = new VERSION_Command(); 
    Cmd_List["STATS"]     = new STATS_Command(); 
    Cmd_List["ADMIN"]     = new ADMIN_Command(); 
    Cmd_List["INFO"]      = new INFO_Command();

    //Sending messages
    Cmd_List["PRIVMSG"]   = new PRIVMSG_Command(); 
    Cmd_List["NOTICE"]    = new NOTICE_Command();

    //User-based queries 
    Cmd_List["WHO"]       = new WHO_Command();
    Cmd_List["WHOIS"]     = new WHOIS_Command();  
    Cmd_List["WHOWAS"]    = new WHOWAS_Command(); 

    //Miscellaneous messages 
    Cmd_List["KILL"]     = new KILL_Command();
    Cmd_List["PING"]     = new PING_Command();  
    Cmd_List["PONG"]     = new PONG_Command(); 
    Cmd_List["ERROR"]    = new ERROR_Command(); 

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

int Command_Manager::Interpret_Data(std::vector<std::string>& Data, Client &Client, std::map<std::string, Channel>  Channels)
{
    for (std::vector<std::string>::const_iterator it = Data.begin(); it != Data.end(); ++it) 
    {
        std::vector<std::string> Args;
        Tokenize(*it, ' ', Args); 
        
        //DEBUG
        std::cout << "-> Received : "<< *it << std::endl;
        
        //PROBLEME SI JUSTE /TEST
        A_Command *Cmd = this->Get_Command(Args[0]);
        if (Cmd != NULL)
            Cmd->Execute(Client, Args, Channels);
    }
    return GOOD;
}
