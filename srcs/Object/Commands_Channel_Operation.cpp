/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Channel_Operation.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 08:38:09 by zelinsta          #+#    #+#             */
/*   Updated: 2023/04/04 08:34:04 by zelinsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//=====================================Channel operations======================================

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.1
void  JOIN_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;


    //Regarde si tu peux join

    //Si c'est bon
	this->Send_Cmd(Client->Socket,":Zel!~a@localhost JOIN #test \n");

	this->Send_Cmd(Client->Socket,":IRC 332 Zel #test :This is my cool channel! \n");

	this->Send_Cmd(Client->Socket,":IRC 353 Zel = #test :@Zel Tristan\n");
	this->Send_Cmd(Client->Socket,":IRC 366 Zel #test :End of /NAMES list \n");

	return ;
    // //Si tu peux pas message d'erreur


    // this->Send_Cmd(Client.Socket,":IRC 332 Zel #test Rien a dire \n");
    // this->Send_Cmd(Client.Socket,":IRC 333 Zel #test dan!~d@localhost 1547691506 \n"); //set topic
    // this->Send_Cmd(Client.Socket,":IRC MODE #test +nt \n");
    // this->Send_Cmd(Client.Socket,":IRC 475 Zel #test :Cannot join channel (+k) - bad key \n");


	// [1] Le channel n'existe pas -> c'est donc une creation
	// 403    ERR_NOSUCHCHANNEL "<channel name> :No such channel" 
	//- Used to indicate the given channel name is invalid
	if (!Channel_Manager.isChannelExists(Args[1])) {
		int ret = Channel_Manager.addNewChannel(Args[1], (*Client));
		
		if (ret == 0) { // le channel est bien ajoute

			//A BUILD POUR CONTINUER : ":Zel!~a@localhost JOIN #test \n"
			// std::string rep = "";
			std::cout << "new chan process reponse" << std::endl; //checking
			std::cout << "chan_list : " << Channel_Manager.getChanList() << std::endl; //checking

		} else { // toute forme d'erreur lie a un mauvais nom de channel
			std::string rep = BuildRep_Basic(403, Client->NickName, Args[1], " :No such channel");
			this->Send_Cmd(Client->Socket, rep);
		}
	}




	// [2] Le channel existe, on veut le rejoindre
		// [2]-[1] passer les differents checks -> build msgs
			// si taille user max (mode -> l)

			// si besoin une cle + assez d'Args du coup (mode +k)

			// si private (mode +p)

			// si invite-only (mode +i)

			// si l'user est dans la liste des bans/kicked

			// SINON tout est ok -> ajoute le client au channel + build reponse ()
}

/* JE GARDE CECI POUR LE MOMENT*/
// void  JOIN_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
// {
//     (void )Args;
//     (void )Channel_Manager;
//     (void )Client_Manager;


//     //Regarde si tu peux join

//     //Si c'est bon
//         this->Send_Cmd(Client.Socket,":Zel!~a@localhost JOIN #test \n");

//         this->Send_Cmd(Client.Socket,":IRC 332 Zel #test :This is my cool channel! \n");

//         this->Send_Cmd(Client.Socket,":IRC 353 Zel = #test :@Zel Tristan\n");
//         this->Send_Cmd(Client.Socket,":IRC 366 Zel #test :End of /NAMES list \n");

//     //Si tu peux pas message d'erreur


//     this->Send_Cmd(Client.Socket,":IRC 332 Zel #test Rien a dire \n");
//     this->Send_Cmd(Client.Socket,":IRC 333 Zel #test dan!~d@localhost 1547691506 \n"); //set topic
//     this->Send_Cmd(Client.Socket,":IRC MODE #test +nt \n");
//     this->Send_Cmd(Client.Socket,":IRC 475 Zel #test :Cannot join channel (+k) - bad key \n");
// }

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.2
void  PART_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.3
void  MODE_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.4

// [+] autre code a gere une fois join fini
// 442     ERR_NOTONCHANNEL "<channel> :You're not on that channel"
void  TOPIC_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
	int	ret;
	// Memo :  Args[1] is Channel Name;
	//         Args[2] is newtopic

    // (void )Args;
    // (void )Channel_Manager;
    // (void )Client;
    (void )Client_Manager;

	// [1] si nb Args == 2 (exemple Topic #test) --> demande le topic
	if (Args.size() == 2) {
		std::string rep;
		std::string theTopic;
		
		theTopic = Channel_Manager.getTopicOf(Args[1]);
		rep = BuildRep_Basic(332, (*Client).NickName, Args[1], theTopic);
		//buildRep = ":" + std::string(SERVER_NAME) + " 332 " + Client.NickName + " " + Args[1] + " :" + theTopic + " \n";
		this->Send_Cmd(Client->Socket, rep);
	}

	// [+] a tester une fois JOIN et MODE faits
	// [2] sinon c'est une tentative pour changer le Topic
	else if (Args.size() > 2) {
		ret = Channel_Manager.setTopicOf(Args[1], Args[2], (*Client));
		if (ret == GOOD) { // construire la reponse du changement de topic
			//":IRC 333 Zel #test dan!~d@localhost 1547691506 \n")
			// [+] a finir
			std::cout << "set topic is good" << std::endl;

		} else if (ret == CM_NOTOPICPERM) { 
		// construire la reponse
		// 482 ERR_CHANOPRIVSNEEDED "<channel> :You're not channel operator"
			// [+] a finir
		}
			
	}
	


	
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.5
void  NAMES_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.6
void  LIST_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.7
void  INVITE_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;
}
// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.8
void  KICK_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;
}