/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Channel_Operation.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/02 14:55:42 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"



//=====================================Channel operations======================================

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.1
void  JOIN_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;


    //Regarde si tu peux join

    //Si c'es bon
        this->Send_Cmd(Client._Client_Socket,":Zel!~a@localhost JOIN #test \n");

        this->Send_Cmd(Client._Client_Socket,":IRC 332 Zel #test :This is my cool channel! \n");

        this->Send_Cmd(Client._Client_Socket,":IRC 353 Zel = #test :@Zel Tristan\n");
        this->Send_Cmd(Client._Client_Socket,":IRC 366 Zel #test :End of /NAMES list \n");

    //Si tu peux pas meesage d'erreur


    this->Send_Cmd(Client._Client_Socket,":IRC 332 Zel #test Rien a dire \n");
    this->Send_Cmd(Client._Client_Socket,":IRC 333 Zel #test dan!~d@localhost 1547691506 \n");
    this->Send_Cmd(Client._Client_Socket,":IRC MODE #test +nt \n");
    this->Send_Cmd(Client._Client_Socket,":IRC 475 Zel #test :Cannot join channel (+k) - bad key \n");
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.2
void  PART_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;

    

}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.3
void  MODE_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.4
void  TOPIC_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
	int	ret;

    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;
	// [1] si nb Args == 2 (exemple Topic #test) --> demande le topic
	if (Args.size() == 2) {
		this->Send_Cmd(Client._Client_Socket, ":IRC 332 " + Client._NickName + " " + Args[1] + " :" + "demande du channel topic" + " \n");
	}

	// sinon c'est une tentative pour changer le Topic
	


	
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.5
void  NAMES_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.6
void  LIST_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.7
void  INVITE_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.8
void  KICK_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;
}