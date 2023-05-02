/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command_Manager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:32:08 by tquere            #+#    #+#             */
/*   Updated: 2023/05/02 11:51:35 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Manager/Command_Manager.hpp"

Command_Manager::Command_Manager()
{
    // Cmd_List["DEBUG"]   = new DEBUG_Command();
    
    //Connection Registration
    Cmd_List["PASS"]    = new PASS_Command();
    Cmd_List["NICK"]    = new NICK_Command(); 
    Cmd_List["USER"]    = new USER_Command();
    Cmd_List["OPER"]    = new OPER_Command();
    Cmd_List["CAP"]     = new CAP_Command();

    //Channel operations
    Cmd_List["JOIN"]    = new JOIN_Command();
    Cmd_List["PART"]    = new PART_Command(); 
    Cmd_List["MODE"]    = new MODE_Command(); 
    Cmd_List["TOPIC"]   = new TOPIC_Command(); 
    Cmd_List["NAMES"]   = new NAMES_Command(); 
    Cmd_List["LIST"]    = new LIST_Command(); 
    Cmd_List["INVITE"]  = new INVITE_Command(); 
    Cmd_List["KICK"]    = new KICK_Command();
    Cmd_List["WHO"]     = new WHO_Command(); 

    //Sending messages
    Cmd_List["PRIVMSG"]   = new PRIVMSG_Command(); 
    Cmd_List["NOTICE"]    = new NOTICE_Command();
    Cmd_List["AWAY"]      = new AWAY_Command();

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
		Log(EVENT_CMDFOUND + it->first);
        return it->second;
    }
	Log(ERROR_CMDNOTFOUND + str);
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

int Command_Manager::Interpret_Data(Client *Clt, ChannelManager &Channel_Manager, Client_Manager &Client_Manager)
{
    for (std::vector<std::string>::const_iterator it = (*Clt).All_Cmd.begin(); it != (*Clt).All_Cmd.end(); ++it) 
    {
        std::vector<std::string> Args;
        Tokenize(*it, ' ', Args); 
        
		std::cout << "\033[38;5;180m";
        std::cout << "          -> " << Clt->Socket << " Recv : " << *it << std::endl;
		std::cout << "\033[m";

        if (Args.size() == 0 || Args[0] == "")
        {
            Log("No command found");
            continue;
        }

        if (Args[0] == "QUIT")
        {
            Log(EVENT_CMDFOUND + Args[0]);

            if (Args.size() >= 2)
                Clt->Quit_Msg = Join_End(1, Args);
            
            return QUIT;
        }
            
        A_Command *Cmd = this->Get_Command(Args[0]);

        if ((*Clt).Logged == 0)
        {
            if (Args[0] == "USER" || Args[0] == "PASS" || Args[0] == "NICK" || Args[0] == "CAP")
            {
                if (Cmd != NULL)
                    Cmd->Execute(Clt, Args, Channel_Manager, Client_Manager);
                Client_Manager.Check_Log(Clt);
            }
            else
                Log("Can't , not logged yet");
        }
        else   
            if (Cmd != NULL)
                Cmd->Execute(Clt, Args, Channel_Manager, Client_Manager);
    }
    
    (*Clt).All_Cmd.clear();

    return GOOD;
}

void		Command_Manager::Log(std::string const &msg)	const {
	std::cout << "\033[38;5;108m";
	std::cout << "CommandManager      : " << msg << std::endl;
	std::cout << "\033[m";
}
