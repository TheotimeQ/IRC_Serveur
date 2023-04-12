/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Registration.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/12 10:51:59 by zelinsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//=====================================Connection Registration======================================

// https://www.rfc-editor.org/rfc/rfc1459#section-4.1.1
//PASS 
void  PASS_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{

    // ERR_NEEDMOREPARAMS              
    // ERR_ALREADYREGISTRED
    
    (void )Channel_Manager;
    (void )Client_Manager;

    if (Args.size() < 2)
        return ;

    Client->Password = Args[1];
}

//https://www.rfc-editor.org/rfc/rfc1459#section-4.1.2
//NICK
void  NICK_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{

    // ERR_NONICKNAMEGIVEN             
    // ERR_ERRONEUSNICKNAME
    // ERR_NICKNAMEINUSE               
    // ERR_NICKCOLLISION

    (void) Channel_Manager;

    if (Args.size() < 2)
    {
        std::cout << ERROR_BAD_FORMAT << std::endl;
        return ;
    }

    if (Client_Manager.Get_Client(Args[1]) != NULL)
    {
        std::cout << ERROR_NICKNAME_ALREADY_USED << std::endl;
        // Send_Cmd(Client.Socket,":IRC ERR_NICKCOLLISION Zel :BIENVENU SUR LE Server IRC\n ");
        return ;
    }

    Client->NickName = Args[1];
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.1.3
//USER
void  USER_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    // ERR_NEEDMOREPARAMS              
    // ERR_ALREADYREGISTRED
    
    (void )Channel_Manager;
    (void )Client_Manager;

    if (Args.size() < 2)
        return ;

    if (Args[1] == "")
        return ;
    
    Client->UserName = Args[1];
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.1.5
//OPER
void  OPER_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{

    // ERR_NEEDMOREPARAMS              
    // RPL_YOUREOPER
    // ERR_NOOPERHOST                  
    // ERR_PASSWDMISMATCH
    
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;
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
            std::string Msg = ":" + std::string(SERVER_NAME) + " " + Client->NickName + " CAP * LS :" "\n";
            Send_Cmd(Client->Socket, Msg);
            Client->Cap_End = 0;
        }
        if (Args[1] == "END")
            Client->Cap_End = 1;
    }

}


