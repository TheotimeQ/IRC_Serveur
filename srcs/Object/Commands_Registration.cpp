/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Registration.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/02 17:00:07 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//=====================================Connection Registration======================================

// https://www.rfc-editor.org/rfc/rfc1459#section-4.1.1
//PASS 
void  PASS_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;

    Client.Password = Args[1];
}

//https://www.rfc-editor.org/rfc/rfc1459#section-4.1.2
//NICK
void  NICK_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void) Args;
    (void) Channel_Manager;
    (void) Client_Manager;

    //Verifier pas nick name en doucle

    //Verifier qu'on a un argument 1
    // Client.NickName = Args[1];

    //Si qqn a deja le nickname 
        //ERR_NICKCOLLISION
    // this->Send_Cmd(Client.Socket,":IRC 001 Zel :BIENVENU SUR LE Server IRC\n ");

    //CHECK SI IL EST LOG
    
    // Client_Manager.Check_If_Can_Log(Client);

    std::cout << "LOGGED" << std::endl;
    Client.Logged = 1;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.1.3
//USER
void  USER_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;

    //Verifier qu'on a un argument 1
    
    Client.UserName = Args[1];
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.1.5
//OPER
void  OPER_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.1.6
//QUIT
void  QUIT_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;
}

