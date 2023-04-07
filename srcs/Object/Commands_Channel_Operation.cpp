/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Channel_Operation.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 08:38:09 by zelinsta          #+#    #+#             */
/*   Updated: 2023/04/07 14:56:15 by loumarti         ###   ########lyon.fr   */
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
	// this->Send_Cmd(Client->Socket,":Zel!~a@localhost JOIN #test \n");

	// this->Send_Cmd(Client->Socket,":IRC 332 Zel #test :This is my cool channel! \n");

	// this->Send_Cmd(Client->Socket,":IRC 353 Zel = #test :@Zel Tristan\n");
	// this->Send_Cmd(Client->Socket,":IRC 366 Zel #test :End of /NAMES list \n");

	// return ;

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

			//JOIN SUCCEED : ":Zel!~a@localhost JOIN #test \n"
			std::string rep = BuildRep_CmdEvent(Args[0], Client->NickName, Args[1]);
			this->Send_Cmd(Client->Socket, rep);
			std::cout << "chan_list : " << Channel_Manager.getChanList() << std::endl; //checking

		} else { // toute forme d'erreur lie a un mauvais nom de channel
			// [!] Je peux pas repondre avec Args[1] => puisque c'est un mauvais nom de channel, 
			// [!] Comment on recupere le "current channel" du Client ???

			// [A] - Si le client est dans aucun channel : fonctionne bien ainsi :
			if (!Channel_Manager.isClientSomewhere(Client->NickName)) {
				std::string rep = BuildRep_Basic(403, Client->NickName, Args[1], "No such channel"); // utiliser messageprv ou notice a la place ?
				this->Send_Cmd(Client->Socket, rep);
			} else {
				// pas ideal le PRIVMSG ==> a voir si on trouve mieux
				// peut etre que repondre par la 403 dans tous les channs trouves
				// a suivre  ===> pour le moment reponse dans les channels ou est le client (solution la moins pire)
				t_mapChannel::const_iterator it;
				std::string rep;
				
				for (it = Channel_Manager.getChanList().begin(); it != Channel_Manager.getChanList().end(); ++it) {
					if (it->second.isClientIn(Client->NickName)) {
						rep = BuildRep_Basic(403, Client->NickName, it->first, " " + Args[1] + " : No such channel");
						this->Send_Cmd(Client->Socket, rep);
					}
				}
				// std::string Msg = ": PRIVMSG " + Client->NickName + " :" + Args[1] + ": No such channel" + "\n";
				// this->Send_Cmd(Client->Socket, Msg);
			}
		}
	}




	// [2] Le channel existe (Args[1]), on veut le rejoindre
	else {
		std::cout << "Log :" << Client->NickName << " want to join channel : " << Args[1] << std::endl; // checking
		// CONTINUER ICI -> faire rejoindre plrs user

		// [2]-[1] passer les differents checks -> build msgs

	/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CHECKS WALL ~~~~~~~~~~~~~~~~~~~~~~~~~~ */
			// si le client est deja dans le channel [facultatif HexChat a la securite]
			//443    ERR_USERONCHANNEL  "<user> <channel> :is already on channel"
			if (Channel_Manager.isClientIn(Client->NickName, Args[1])) {
				this->Send_Cmd(Client->Socket, BuildRep_Basic(443, Client->NickName, Args[1], "is already on channel"));
				return ;
			}
			// si taille user max (mode -> l)
			// 471    ERR_CHANNELISFULL "<channel> :Cannot join channel (+l)"
			if (!Channel_Manager.joinCheck_l(Args[1])) {
				this->Send_Cmd(Client->Socket, BuildRep_Basic(471, Client->NickName, Args[1], Args[1] + " :Cannot join channel (+l)"));
				// [+] A TESTER UNE FOIS MODE FAIT
				return ;
			}

			// si besoin une cle + assez d'Args du coup (mode +k)
			// 475    ERR_BADCHANNELKEY "<channel> :Cannot join channel (+k)
			if (!Channel_Manager.joinCheck_k(Args[1], (Args.size() > 2 ? Args[2] : ""))) {
				this->Send_Cmd(Client->Socket, BuildRep_Basic(475, Client->NickName, Args[1], Args[1] + " :Cannot join channel (+k)"));
				// [+] A TESTER UNE FOIS MODE FAIT
				return ;
			}

			// si invite-only (mode +i)
			// 473    ERR_INVITEONLYCHAN "<channel> :Cannot join channel (+i)"
			if (!Channel_Manager.joinCheck_i(Args[1])) {
				this->Send_Cmd(Client->Socket, BuildRep_Basic(475, Client->NickName, Args[1], Args[1] + " :Cannot join channel (+i)"));
				// [+] A TESTER UNE FOIS MODE FAIT
				return ;
			}

			// si l'user est dans la liste des bans/kicked
			// 474    ERR_BANNEDFROMCHAN "<channel> :Cannot join channel (+b)
			if (!Channel_Manager.joinCheck_bans(Client->NickName, Args[1])) {
				this->Send_Cmd(Client->Socket, BuildRep_Basic(474, Client->NickName, Args[1], Args[1] + " :Cannot join channel (+b)"));
				// [+] A TESTER UNE FOIS MODE FAIT
				return ;
			}

	/* ~~~~~~~~~~~~~~~~~~~~~~~~ CHECKS WALL DONE ~~~~~~~~~~~~~~~~~~~~~~ */
			// SINON tout est ok -> ajoute le client au channel + build reponse ()
			Channel_Manager.addClientToChannel(*Client, Args[1]);
			//JOIN SUCCEED : ":Zel!~a@localhost JOIN #test \n"
			std::string rep = BuildRep_CmdEvent(Args[0], Client->NickName, Args[1]);
			this->Send_Cmd(Client->Socket, rep);
	}
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.2
void  PART_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;
}

//. https://stackoverflow.com/questions/12886573/implementing-irc-rfc-how-to-respond-to-mode
// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.3
// Note that there is a maximum limit of three (3) changes per command for modes that take a parameter
void  MODE_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    // (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    // (void )Client;

	std::cout << "Args.size() = " << Args.size() << std::endl;	//checking
	std::cout << "Args[0] = " << Args[0] << std::endl;			//checking
	std::cout << "Args[1] = " << Args[1] << std::endl;			//checking

	// [1] Si l'utilisateur fait /mode dans aucun channel sans parametre
	// 461    ERR_NEEDMOREPARAMS "<command> :Not enough parameters"
	if (Args.size() == 2 && Args[1].compare("") == 0) {
		this->Send_Cmd(Client->Socket, BuildRep_Cmde(461, "MODE", "Not enough parameters"));
	}

	// [2] Si l'utilisateur fait /mode #nomChannel
	if (Args.size() == 2 && Is_Channel_Name_Arg(Args[1])) {
		Log("MODE", "get mode info from channel : " + Args[1]);

		// [2]-[1] Le channel n'existe pas ou le client n'est pas dans le channel
		// 441    ERR_USERNOTINCHANNEL "<nick> <channel> :They aren't on that channel"
		if (!Channel_Manager.isChannelExists(Args[1]) || !Channel_Manager.isClientIn(Client->NickName, Args[1])) {
			this->Send_Cmd(Client->Socket, BuildRep_Chan(441, Client->NickName + " " + Args[1], "They aren't on that channel"));
			// [!] comme dans join je sais pas afficher retour puisque le channel est pas bon
		}


		// [2]-[2] L'utilisateur fait partie du channel
		// 324    RPL_CHANNELMODEIS "<channel> <mode> <mode params>"
		else {

			this->Send_Cmd(Client->Socket, BuildRep_Basic(324, Client->NickName, Args[1], "000 +-+-+-+-+-"));
			// CONTINUER ici avec un Channel_Manager.getModeStringOf(Args[1])
			// this->Send_Cmd(Client->Socket, BuildRep_Basic(324, Client->NickName, Args[1], "mode  : +-+-+-+-+-"));
		}
	}
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.4

// [+] autre code a gere une fois join fini
// 442     ERR_NOTONCHANNEL "<channel> :You're not on that channel"
// 333     RPL_TOPICWHOTIME "<client> <channel> <nick> <setat>"
// Args[0] TOPIC  |  Args[1] #currentChannel  |  Args[2-+] new topic (vector string to join)
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
	// [+] gerer Si le topic existe pas ? (user peut faire /topic ET /topic #unknowchannel 
	//     ET /topic #unchannelOuilestpas ET /topic #unchannelprive etc. --> /[U_U]\ misere)
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
		//[2]-[A] --> join les Args pour construire le topic, 
		std::string	newTopic;
		std::vector<std::string>::iterator it = Args.begin() + 2;
		while (it != Args.end()) {
			if (it != Args.begin() + 2)
				newTopic += " ";
			newTopic += *it;
			++it;
		}
		ret = Channel_Manager.setTopicOf(Args[1], newTopic, (*Client));
		if (ret == GOOD) { // construire la reponse du changement de topic
			// la demande peut etre faite depuis n'importe quel channel
			// je ne sais pas trop comment gerer ca. (je laisse pour l'instant)

			
			//[2]-[B] --> formater le msg de changement de topic (avec setat -> infos temps)
			//":IRC 333 Zel #test dan!~d@localhost 1547691506 \n")
			this->Send_Cmd(Client->Socket, ":IRC 333 Zel #poumy Zel 1547691506 \n");
			// (optionnel ?) 
			// CONTINUER : formater le temps <setat> 
			// D'abord avancer JOIN pour voir ce qui est afficher chez differents users dans un meme channel

			//[2]-[C] --> passer le nouveau topic au channel + send_message le resultat
			this->Send_Cmd(Client->Socket, BuildRep_Basic(332, (*Client).NickName, Args[1], newTopic));
			//std::cout << "set topic is good" << std::endl; //checking

		} else if (ret == CM_NOTOPICPERM) { 
		// construire la reponse (mode +t)
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