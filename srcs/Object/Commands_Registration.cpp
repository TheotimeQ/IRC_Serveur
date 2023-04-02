/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Registration.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/02 12:02:25 by zelinsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//=====================================Connection Registration======================================

// https://www.rfc-editor.org/rfc/rfc1459#section-4.1.1
//PASS 
void  PASS_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager Channel_Manager) 
{
    (void )Args;
    (void )Channel_Manager;

    Client._Password = Args[1];
}

//https://www.rfc-editor.org/rfc/rfc1459#section-4.1.2
//NICK
void  NICK_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager Channel_Manager) 
{
    (void )Args;
    (void )Channel_Manager;

    //Verifier pas nick name en doucle

    //Verifier qu'on a un argument 1
    Client._NickName = Args[1];

    //Si qqn a deja le nickname 
        //ERR_NICKCOLLISION
    // this->Send_Cmd(Client._Client_Socket,":IRC 001 Zel :BIENVENU SUR LE Server IRC\n ");
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.1.3
//USER
void  USER_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager Channel_Manager) 
{
    (void )Args;
    (void )Channel_Manager;

    //Verifier qu'on a un argument 1
    
    Client._UserName = Args[1];
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.1.5
//OPER
void  OPER_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager Channel_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.1.6
//QUIT
void  QUIT_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager Channel_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client;
}

