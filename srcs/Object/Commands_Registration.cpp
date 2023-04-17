/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Registration.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/17 10:44:43 by zelinsta         ###   ########.fr       */
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
        std::cout << ERROR_BAD_FORMAT << std::endl;
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_NEEDMOREPARAM) + " " + Clt->NickName + " " + Args[0] + " :Not enough parameters" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }
    
    // ERR_ALREADYREGISTRED
    if (Clt->Logged == 1)
    {
        std::cout << ERROR_PASS_ALREADY_SET << std::endl;
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
        std::cout << ERROR_BAD_FORMAT << std::endl;
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_NONICKNAMEGIVEN) + " " + Clt->NickName + " :No nickname given   " + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }

    // ERR_NICKNAMEINUSE
    if (Client_Manager.Get_Client(Args[1]) != NULL)
    {
        std::cout << ERROR_NICKNAME_ALREADY_USED << std::endl;
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_NICKNAMEINUSE) + " " + Clt->NickName + " " + Args[1] + " :Nickname is already in use" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }

    // ERR_ERRONEUSNICKNAME
    if (Is_Valide_Nick(Args[1]))
    {
        std::cout << ERROR_NICKNAME_BAD_FORMAT << std::endl;
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_NICKNAMEINUSE) + " " + Clt->NickName + " " + Args[1] + " :Erroneus nickname" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;   
    }

    //NOT USED -> Its for server to server communication
    // ERR_NICKCOLLISION
    // "<nick> :Nickname collision KILL"

    //Previent les autres clients que le client a changer de pseudo

    // :WiZ NICK Kilroy                ; WiZ changed his nickname to Kilroy.

    Clt->NickName = Args[1];
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.1.3
void  USER_Command::Execute(Client *Clt, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    
    (void )Channel_Manager;
    (void )Client_Manager;

    // ERR_NEEDMOREPARAMS              
    if (Args.size() < 2 || Args[1] == "")
    {
        std::cout << ERROR_BAD_FORMAT << std::endl;
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_NEEDMOREPARAM) + " " + Clt->NickName + " " + Args[0] + " :Not enough parameters" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }

    // ERR_ALREADYREGISTRED
    if (Clt->Logged == 1)
    {
        std::cout << ERROR_USER_ALREADY_SET << std::endl;
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_ALREADYREGISTRED) + " " + Clt->NickName + " :You may not reregister" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }
    
    Clt->UserName = Args[1];
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.1.5
void  OPER_Command::Execute(Client *Clt, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{              

    (void )Channel_Manager;
    (void )Client_Manager;

    // ERR_NEEDMOREPARAMS              
    if (Args.size() < 2 || Args[1] == "")
    {
        std::cout << ERROR_BAD_FORMAT << std::endl;
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_NEEDMOREPARAM) + " " + Clt->NickName + " " + Args[0] + " :Not enough parameters" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }

    // RPL_YOUREOPER
    // ERR_NOOPERHOST                  
    // ERR_PASSWDMISMATCH









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
            std::string Msg = ":" + std::string(SERVER_NAME) + " " + Client->NickName + " CAP * LS : Aucunes" "\n";
            Send_Cmd(Client->Socket, Msg);
            Client->Cap_End = 0;
        }
        if (Args[1] == "END")
            Client->Cap_End = 1;
    }
}


