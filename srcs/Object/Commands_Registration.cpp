/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Registration.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/05/02 10:23:36 by zelinsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//=====================================Connection Registration======================================

// https://www.rfc-editor.org/rfc/rfc1459#section-4.1.1
void  PASS_Command::Execute(Client *Clt, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{        
    
    (void )Channel_Manager;
    (void )Client_Manager;

    // ERR_NEEDMOREPARAMS              
    if (Args.size() < 2 || Args[1] == "")
    {
        Log("PASS",ERROR_BAD_FORMAT);
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_NEEDMOREPARAM) + " " + Clt->NickName + " " + Args[0] + " :Not enough parameters" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }
    
    // ERR_ALREADYREGISTRED
    if (Clt->Logged == 1)
    {
        Log("PASS",ERROR_PASS_ALREADY_SET);
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_ALREADYREGISTRED) + " " + Clt->NickName + " :You may not reregister" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }

    Clt->Password = Args[1];
}

//https://www.rfc-editor.org/rfc/rfc1459#section-4.1.2
void  NICK_Command::Execute(Client *Clt, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{

    (void) Channel_Manager;
    (void) Client_Manager;
       
    // ERR_NONICKNAMEGIVEN      
    if (Args.size() < 2 || Args[1] == "")
    {
        Log("NICK",ERROR_BAD_FORMAT);
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_NONICKNAMEGIVEN) + " " + Clt->NickName + " :No nickname given   " + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }

    // ERR_NICKNAMEINUSE
    if (Client_Manager.Get_Client(Args[1]) != NULL)
    {
        Log("NICK",ERROR_NICKNAME_ALREADY_USED);
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_NICKNAMEINUSE) + " " + Clt->NickName + " " + Args[1] + " :Nickname is already in use" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }

    // ERR_ERRONEUSNICKNAME
    if (Is_Valide_Nick(Args[1]))
    {
        Log("NICK",ERROR_NICKNAME_BAD_FORMAT);
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_NICKNAMEINUSE) + " " + Clt->NickName + " " + Args[1] + " :Erroneus nickname" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;      
    }

    //NOT USED -> Its for server to server communication
    // ERR_NICKCOLLISION
    // "<nick> :Nickname collision KILL"

    Log("NICK","Changing nickname from " + Clt->NickName + " to " + Args[1]);
    std::string Msg = ":"+ Clt->NickName + " NICK " + Args[1] + "\n";
    Clt->NickName = Args[1];
    Client_Manager.Send_To_All(Msg);
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.1.3
void  USER_Command::Execute(Client *Clt, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    
    (void )Channel_Manager;
    (void )Client_Manager;

    // ERR_NEEDMOREPARAMS              
    if (Args.size() < 2 || Args[1] == "")
    {
        Log("USER",ERROR_BAD_FORMAT);
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_NEEDMOREPARAM) + " " + Clt->NickName + " " + Args[0] + " :Not enough parameters" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }

    // ERR_ALREADYREGISTRED
    if (Clt->Logged == 1)
    {
        Log("USER",ERROR_USER_ALREADY_SET);
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_ALREADYREGISTRED) + " " + Clt->NickName + " :You may not reregister" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }
       
    Log("USER","Changing username from " + Clt->UserName + " to " + Args[1]);
    Clt->UserName = Args[1];
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.1.5
void  OPER_Command::Execute(Client *Clt, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{              

    (void )Channel_Manager;
    (void )Client_Manager;

    // ERR_NEEDMOREPARAMS              
    if (Args.size() < 3 || Args[1] == "")
    {
        Log("OPER",ERROR_BAD_FORMAT);
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_NEEDMOREPARAM) + " " + Clt->NickName + " " + Args[0] + " :Not enough parameters" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }

    if (Clt->Oper)
    {
        Log("OPER",Clt->NickName + "already logged as operator");
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_NOOPERHOST) + " " + Clt->NickName + " :Already logged as operator" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }

    if (Clt->NickName != Args[1])
    {
        Log("OPER",Clt->NickName + " doesn't match " + Args[1]);
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_NOOPERHOST) + " " + Clt->NickName + " :Use your nickname to connect" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }

    // ERR_NOOPERHOST
    std::string* Pass = Client_Manager.Get_Oper_Pass(Clt->NickName);
    if (Pass == NULL)
    {
        Log("OPER",Clt->NickName + " is not know as operator ");
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_NOOPERHOST) + " " + Clt->NickName + " :No O-lines for your host" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }
    
    // ERR_PASSWDMISMATCH
    if (Args[2] != *Pass)
    {
        Log("OPER",Clt->NickName + " sent the wrong password : " + Args[2] + " (" + *Pass + ")");
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_PASSWDMISMATCH) + " " + Clt->NickName + " :Password incorrect" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }

    // RPL_YOUREOPER
    if (Args[2] == *Pass)
    {
        Log("OPER",Clt->NickName + " is not now logged as operator ");
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(RPL_YOUREOPER) + " " + Clt->NickName + " :You are now an IRC operator" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        Clt->Oper = 1;

        Channel_Manager.allChannelSend(":IRC MODE ", " +o " + Clt->NickName + "\n");
        return ;
    }
}

void  CAP_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;

    if (Args.size() >= 2)
    {
        if (Args[1] == "LS")
        {
            Log("CAP ","Sending cap response");
            std::string Msg = ":" + std::string(SERVER_NAME) + " " + Client->NickName + " CAP * LS : None " "\n";
            Send_Cmd(Client->Socket, Msg);
            Client->Cap_End = 0;
        }
        if (Args[1] == "END")
        {
            Log("CAP ","Ended cap exchange");
            Client->Cap_End = 1;
        }
    }
}


