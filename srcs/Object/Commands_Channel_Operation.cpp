/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Channel_Operation.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 08:38:09 by zelinsta          #+#    #+#             */
/*   Updated: 2023/04/12 11:13:36 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//=====================================Channel operations======================================

/* ==> JOIN <== */

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.1
void  JOIN_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Client_Manager;

	// std::cout << *Client << std::endl; //chekcing 

	
	// [1] Le channel n'existe pas -> c'est donc une creation
	// 403    ERR_NOSUCHCHANNEL "<channel name> :No such channel" 
	//- Used to indicate the given channel name is invalid
	if (!Channel_Manager.isChannelExists(Args[1])) {
		int ret = Channel_Manager.addNewChannel(Args[1], (*Client));
		
		if (ret == 0) { // le channel est bien ajoute

			//JOIN SUCCEED : ":Zel!~a@localhost JOIN #test \n"
			std::string rep = BuildRep_CmdEvent(Args[0], Client->NickName, Args[1]);
			Send_Cmd(Client->Socket, rep);
			
			// DEBUG
			// std::cout << "chan_list : " << Channel_Manager.getChanList() << std::endl; //checking
			// std::cout << "usersList :" << Channel_Manager.getUsersOf(Args[1]) << std::endl; //checking
			// std::cout << "[wtf]" << std::endl;
			// Channel_Manager.getChannel(Args[1]).showUsers();
			// DEBUG

		} else { // toute forme d'erreur lie a un mauvais nom de channel
			// [!] Je peux pas repondre avec Args[1] => puisque c'est un mauvais nom de channel, 
			// [!] Comment on recupere le "current channel" du Client ???
			// [!] Solution alternative -> repondre dans 'Home'
		Send_Cmd(Client->Socket, BuildRep_HomeChan(Client->NickName, Args[1], ERR_NOSUCHCHANNEL));
			// [A] - Si le client est dans aucun channel : fonctionne bien ainsi :
			// if (!Channel_Manager.isClientSomewhere(Client->NickName)) {
			// 	std::string rep = BuildRep_Home(Client->NickName, Args[1] + " : No such channel");
			// 	Send_Cmd(Client->Socket, rep);
			// } else {
				// pas ideal le PRIVMSG ==> a voir si on trouve mieux
				// peut etre que repondre par la 403 dans tous les channs trouves
				// a suivre  ===> pour le moment reponse dans les channels ou est le client (solution la moins pire)
				// t_mapChannel::const_iterator it;
				// std::string rep;
				
				// for (it = Channel_Manager.getChanList().begin(); it != Channel_Manager.getChanList().end(); ++it) {
				// 	if (it->second.isClientIn(Client->NickName)) {
				// 		rep = BuildRep_Basic(403, Client->NickName, it->first, " " + Args[1] + " : No such channel");
				// 		Send_Cmd(Client->Socket, rep);
				// 	}
				// }
				// std::string Msg = ": PRIVMSG " + Client->NickName + " :" + Args[1] + ": No such channel" + "\n";
				// Send_Cmd(Client->Socket, Msg);
			// 	Send_Cmd(Client->Socket, BuildRep_Home(Client->NickName, Args[1] + " : No such channel"));
			// }
		}
	}




	// [2] Le channel existe (Args[1]), on veut le rejoindre
	else {
		std::cout << "Log :" << Client->NickName << " want to join channel : " << Args[1] << std::endl; // checking

		// DEBUG
			// std::cout << "chan_list : " << Channel_Manager.getChanList() << std::endl; //checking
			// std::cout << "usersList :" << Channel_Manager.getUsersOf(Args[1]) << std::endl; //checking
			// std::cout << "[wtf]" << std::endl;
			// Channel_Manager.getChannel(Args[1]).showUsers();
		// DEBUG

		// [2]-[1] passer les differents checks -> build msgs

	/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CHECKS WALL ~~~~~~~~~~~~~~~~~~~~~~~~~~ */
			// si le client est deja dans le channel [facultatif HexChat a la securite]
			//443    ERR_USERONCHANNEL  "<user> <channel> :is already on channel"
			if (Channel_Manager.isClientIn(Client->NickName, Args[1])) {
				Send_Cmd(Client->Socket, BuildRep_Basic(443, Client->NickName, Args[1], ERR_USERONCHANNEL));
				return ;
			}
			// si taille user max (mode -> l)
			// 471    ERR_CHANNELISFULL "<channel> :Cannot join channel (+l)"
			if (!Channel_Manager.joinCheck_l(Args[1])) {
				Send_Cmd(Client->Socket, BuildRep_BasicChan(471, Client->NickName, Args[1], ERR_CHANNELISFULL));
				// [+] A TESTER UNE FOIS MODE FAIT
				return ;
			}

			// si besoin une cle + assez d'Args du coup (mode +k)
			// 475    ERR_BADCHANNELKEY "<channel> :Cannot join channel (+k)
			if (!Channel_Manager.joinCheck_k(Args[1], (Args.size() > 2 ? Args[2] : ""))) {
				Send_Cmd(Client->Socket, BuildRep_Basic(475, Client->NickName, Args[1], ERR_BADCHANNELKEY));
				// [+] A TESTER UNE FOIS MODE FAIT
				return ;
			}

			// si invite-only (mode +i)
			// 473    ERR_INVITEONLYCHAN "<channel> :Cannot join channel (+i)"
			if (!Channel_Manager.joinCheck_i(Args[1])) {
				Send_Cmd(Client->Socket, BuildRep_Basic(475, Client->NickName, Args[1], ERR_INVITEONLYCHAN));
				// [+] A TESTER UNE FOIS MODE FAIT
				return ;
			}

			// si l'user est dans la liste des bans/kicked
			// 474    ERR_BANNEDFROMCHAN "<channel> :Cannot join channel (+b)
			if (!Channel_Manager.joinCheck_bans(Client->NickName, Args[1])) {
				Send_Cmd(Client->Socket, BuildRep_Basic(474, Client->NickName, Args[1], ERR_BANNEDFROMCHAN));
				// [+] A TESTER UNE FOIS MODE FAIT
				return ;
			}

	/* ~~~~~~~~~~~~~~~~~~~~~~~~ CHECKS WALL DONE ~~~~~~~~~~~~~~~~~~~~~~ */
			// SINON tout est ok -> ajoute le client au channel + build reponse ()
			Channel_Manager.addClientToChannel(*Client, Args[1]);
			//JOIN SUCCEED : ":Zel!~a@localhost JOIN #test \n"
			std::string rep = BuildRep_CmdEvent(Args[0], Client->NickName, Args[1]);
			Send_Cmd(Client->Socket, rep);
	}
}

/* ==> PART <== */

// https://www.rfc-editor.org/rfc/rfc14m59#section-4.2.2
// ERR_NEEDMOREPARAMS - ERR_NOSUCHCHANNEL - ERR_NOTONCHANNEL
// Parameters: <channel> *( "," <channel> ) [ <Part Message> ]
void  PART_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void)Args;
    (void)Channel_Manager;
    (void)Client_Manager;
    (void)Client;

	std::vector<std::string> 					channels;
	std::vector<std::string>::const_iterator	it;
	std::string 								leavingMsg;
	
	// Send_Cmd(Client->Socket, ":IRC 000 " + Client->NickName + " part command executed\n"); // test
	showStringVector("Args", Args); //DEBUG //checking
	/* Memo Args */
	//	Args[0] = "PART"
	//	Args[1] = "#channelCurrent" OU #channelAupif OU #chan1,#chan2,#chan3
	//	Args[2 et +] = ":Leaving"(default) OU ":MessagefromUserBeforeLeaving" a concat

	//[1] get Channels from Args[1] List (coma separated)
	channels = extractComaList(Args[1]);
	showStringVector("channels", channels); //DEBUG //checking

	// [2] concat leaving message (Args[2-end])
	leavingMsg = catStringVector(Args, 2);
	std::cout << "Leaving message -> " << leavingMsg << std::endl; //DEBUG //checking

	//[3] try part from each channel + [4] check & supprimer les channels vides
	for (it = channels.begin(); it != channels.end(); ++it) {
		if (!Channel_Manager.isChannelExists(*it)) {
			Send_Cmd(Client->Socket, BuildRep_HomeChan(Client->NickName, Args[1], ERR_NOSUCHCHANNEL));
		} else if (!Channel_Manager.isClientIn(Client->NickName, *it)) {
			Send_Cmd(Client->Socket, BuildRep_Home(Client->NickName, Args[1] + " : They aren't on that channel"));
		} else {
			leavingProcess(Client, *it, Channel_Manager, leavingMsg);
		}
	}
}

void	PART_Command::leavingProcess(Client *Client, std::string const &channelName, ChannelManager &Channel_Manager, std::string const &leavingMsg) {
	// [1] on enleve le client du channel
	Channel_Manager.rmClientToChannel(*Client, channelName);

	// [2] on customise le leaving message

	// [3] on renseigne le channel du depart avec le leaving message
	Channel_Manager.channelSend(Client->NickName, channelName, leavingMsg);

	// [4] on signale au client qu'il est parti du channel
	Send_Cmd(Client->Socket, BuildRep_CmdEvent("PART", Client->NickName, channelName));


	// [5] si l'user etait le dernier on detruit le chan
	if (Channel_Manager.isChannelEmpty(channelName))
		Channel_Manager.rmChannel(channelName);
}

/* ==> MODE <== */

//. https://stackoverflow.com/questions/12886573/implementing-irc-rfc-how-to-respond-to-mode
// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.3
// Note that there is a maximum limit of three (3) changes per command for modes that take a parameter
void  MODE_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Client_Manager;

	//showStringVector("Args", Args); //DEBUG //checking

	// [1] Si l'utilisateur fait /mode dans aucun channel sans parametre
	// 461    ERR_NEEDMOREPARAMS "<command> :Not enough parameters"
	if (Args.size() == 2 && Args[1].compare("") == 0) {
		Send_Cmd(Client->Socket, BuildRep_Cmde(461, "MODE", "Not enough parameters"));
		return ;
	}
	// [2] Sinon Si l'utilisateur fait /mode #nomChannel
	else if (Args.size() == 2 && Is_Channel_Name_Arg(Args[1])) {
		Log("MODE", "get mode info from channel : " + Args[1]);

		// [2]-[1] Le channel n'existe pas ou le client n'est pas dans le channel
		// 441    ERR_USERNOTINCHANNEL "<nick> <channel> :They aren't on that channel"
		if (!Channel_Manager.isChannelExists(Args[1]) || !Channel_Manager.isClientIn(Client->NickName, Args[1])) {
			// Send_Cmd(Client->Socket, BuildRep_Chan(441, Client->NickName + " " + Args[1], "They aren't on that channel"));
			// [!] comme dans join je sais pas afficher retour puisque le channel est pas bon
			Send_Cmd(Client->Socket, BuildRep_Home(Client->NickName, Args[1] + " : They aren't on that channel"));
		}
		// [2]-[2] L'utilisateur fait partie du channel
		// 324    RPL_CHANNELMODEIS "<channel> <mode> <mode params>"
		else 
			Send_RPL_CHANNELMODEIS(Client, Args, Channel_Manager, Client_Manager);
		return ;
	}

	// [3] pour aller plus loin le channel doit exister
	if (!Channel_Manager.isChannelExists(Args[1]) || !Channel_Manager.isClientIn(Client->NickName, Args[1])) { 
		// Send_Cmd(Client->Socket, BuildRep_Chan(441, Client->NickName + " " + Args[1], "They aren't on that channel"));
		Send_Cmd(Client->Socket, BuildRep_Home(Client->NickName, Args[1] + " : They aren't on that channel"));
		// Ce bloc est idem  que + haut en [2]-[1] ==> a faire une fonction + tard
	} 
	// [3 -suite] et l'user doit etre chanop
	else if (!Channel_Manager.isClientChopOf(Client->NickName, Args[1])) {
		// 482    ERR_CHANOPRIVSNEEDED "<channel> :You're not channel operator"
		Send_Cmd(Client->Socket, BuildRep_Basic(482, Client->NickName, Args[1], "You're not channel operator"));
	}
	//[4] Sinon si l'utilisateur fait /mode #nomChannel <[+-][ntmsipNTMSIP]>
	else if (Args.size() == 3 && Is_Channel_Name_Arg(Args[1]) && Is_Channel_Mode_BArgs(Args[2])) {
		Exe_Basic_Settings(Client, Args, Channel_Manager, Client_Manager);
	}


	//[5] Sinon si l'utilisateur fait /mode #nomChannel <[+-][lkLK]> *<Unsigned/key>
	else if ((Args.size() == 3 || Args.size() == 4) && Is_Channel_Name_Arg(Args[1]) && Is_Channel_Mode_AArgs(Args[2])) {
		Exe_Advanced_Settings(Client, Args, Channel_Manager, Client_Manager);
	}

	// [6] Au Secours ! va t on vraiment dans le bon sens ?
}

// when user prompt is /mode #channelName <[+-][ntmsipNTMSIP]>
void	MODE_Command::Exe_Basic_Settings(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager) const {
	(void)Client_Manager;
	bool	isPlus = (Args[2][0] == '+' ? true : false);

	Log("MODE", "basic channel mode setting : " + Args[2]);
	Channel_Manager.setModesOfAs(Args[1], isPlus, Args[2]);
	Send_RPL_CHANNELMODEIS(Client, Args, Channel_Manager, Client_Manager);
}

// when user prompt is /mode #nomChannel <[+-][lkLK]> *<Unsigned/key> (not needed if '-')
void	MODE_Command::Exe_Advanced_Settings(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager) const {
	(void)Client_Manager;
	
	bool	isPlus = (Args[2][0] == '+' ? true : false);
	std::string option = (Args.size() == 4 ? Args[3] : "");
	Log("MODE", "advanced channel mode setting : " + Args[2]);
	if (toupper(Args[2][1]) == 'L') {
		Channel_Manager.setLimitModeOfAsWith(Args[1], isPlus, option);
	} else {
		Channel_Manager.setKeyModeOfAsWith(Args[1], isPlus, option);
	}
	Send_RPL_CHANNELMODEIS(Client, Args, Channel_Manager, Client_Manager);
}

// 324    RPL_CHANNELMODEIS "<channel> <mode> <mode params>"
void	MODE_Command::Send_RPL_CHANNELMODEIS(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) const {
	(void)Client_Manager;

	std::string ModeList = Channel_Manager.getModeAsString(Args[1]);
	Send_Cmd(Client->Socket, BuildRep_Basic(324, Client->NickName, Args[1], ModeList));
}

/* ==> TOPIC <== */

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
    (void )Client_Manager;

	// [1] si nb Args == 2 (exemple Topic #test) --> demande le topic
	// [+] gerer Si le topic existe pas ? (user peut faire /topic ET /topic #unknowchannel 
	//     ET /topic #unchannelOuilestpas ET /topic #unchannelprive etc. --> /[U_U]\ misere)
	if (Args.size() == 2) {
		std::string rep;
		std::string theTopic;
		
		theTopic = Channel_Manager.getTopicOf(Args[1]);
		rep = BuildRep_Basic(332, Client->NickName, Args[1], theTopic);
		//buildRep = ":" + std::string(SERVER_NAME) + " 332 " + Client.NickName + " " + Args[1] + " :" + theTopic + " \n";
		Send_Cmd(Client->Socket, rep);
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
			//Send_Cmd(Client->Socket, ":IRC 333 Zel #poumy Zel 1547691506 \n");
			Send_Cmd(Client->Socket, BuildRep_Basic(333, Client->NickName, Args[1], Client->NickName + " " + getNow()));

			//[2]-[C] --> passer le nouveau topic au channel + send_message le resultat
			Send_Cmd(Client->Socket, BuildRep_Basic(332, Client->NickName, Args[1], newTopic));

		} else if (ret == CM_NOTOPICPERM) { 
		// 482 ERR_CHANOPRIVSNEEDED "<channel> :You're not channel operator"
			Send_Cmd(Client->Socket, BuildRep_Basic(482, Client->NickName, Args[1], "You're not channel operator"));
		}
	}
}

/* ==> [...] <== */

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