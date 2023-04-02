/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Channel_Operation.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/02 12:02:32 by zelinsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"



//=====================================Channel operations======================================

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.1
void  JOIN_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager Channel_Manager) 
{
    (void )Args;
    (void )Channel_Manager;

    //Quelques test pour t'aider un peu a voir ou aller :D

    //Lance irc , connecte toi et fais /join #test (mets zel en username)

    this->Send_Cmd(Client._Client_Socket,":IRC 332 Zel #test Rien a dire \n");
    this->Send_Cmd(Client._Client_Socket,":Zel!~a@localhost JOIN #test \n");
    this->Send_Cmd(Client._Client_Socket,":IRC 332 Zel #test :This is my cool channel! \n");
    this->Send_Cmd(Client._Client_Socket,":IRC 333 Zel #test dan!~d@localhost 1547691506 \n");
    this->Send_Cmd(Client._Client_Socket,":IRC MODE #test +nt \n");
    this->Send_Cmd(Client._Client_Socket,":IRC 353 Zel = #test :@Zel Tristan\n");
    this->Send_Cmd(Client._Client_Socket,":IRC 366 Zel #test :End of /NAMES list \n");
    // this->Send_Cmd(Client._Client_Socket,":IRC 475 Zel #test :Cannot join channel (+k) - bad key \n");
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.2
void  PART_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager Channel_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.3
void  MODE_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager Channel_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.4
void  TOPIC_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager Channel_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.5
void  NAMES_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager Channel_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.6
void  LIST_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager Channel_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.7
void  INVITE_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager Channel_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.8
void  KICK_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager Channel_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client;
}