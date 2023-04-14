/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Channel_Operation.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 08:38:09 by zelinsta          #+#    #+#             */
/*   Updated: 2023/04/14 16:21:05 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//=====================================Channel operations======================================

/* ==> JOIN <== */

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.1
void  JOIN_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Client_Manager;

	showStringVector("Args", Args);
	// std::cout << *Client << std::endl; //chekcing 

	if (!Guard(Client, Args, "JOIN"))
		return ;
	// [1] Le channel n'existe pas -> c'est donc une creation
	// 403    SERR_NOSUCHCHANNEL "<channel name> :No such channel" 
	//- Used to indicate the given channel name is invalid
	if (!Channel_Manager.isChannelExists(Args[1])) {

		int ret = Channel_Manager.addNewChannel(Args[1], (*Client));
		
		if (ret == 0) { // le channel est bien ajoute

			//JOIN SUCCEED : ":Zel!~a@localhost JOIN #test \n"
			Send_Cmd(Client->Socket, BuildRep_CmdEvent(*Client, Args[0], Args[1]));
			Log("JOIN",Client->NickName + " join " + Args[1]);
			
			// DEBUG
			// std::cout << "chan_list : " << Channel_Manager.getChanList() << std::endl; //checking
			// std::cout << "usersList :" << Channel_Manager.getUsersOf(Args[1]) << std::endl; //checking
			// std::cout << "[wtf]" << std::endl;
			// Channel_Manager.getChannel(Args[1]).showUsers();
			// DEBUG

		} else { // toute forme d'erreur lie a un mauvais nom de channel
		Send_Cmd(Client->Socket, BuildRep_Basic(403, Client->NickName, Args[1], SERR_NOSUCHCHANNEL));
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
			//443    SERR_USERONCHANNEL  "<user> <channel> :is already on channel"
			if (Channel_Manager.isClientIn(Client->NickName, Args[1])) {
				Send_Cmd(Client->Socket, BuildRep_Basic(443, Client->NickName, Args[1], SERR_USERONCHANNEL));
				return ;
			}
			// si taille user max (mode -> l)
			// 471    SERR_CHANNELISFULL "<channel> :Cannot join channel (+l)"
			if (!Channel_Manager.joinCheck_l(Args[1])) {
				Send_Cmd(Client->Socket, BuildRep_BasicChan(471, Client->NickName, Args[1], SERR_CHANNELISFULL));
				return ;
			}

			// si besoin une cle + assez d'Args du coup (mode +k)
			// 475    SERR_BADCHANNELKEY "<channel> :Cannot join channel (+k)
			if (!Channel_Manager.joinCheck_k(Args[1], (Args.size() > 2 ? Args[2] : ""))) {
				Send_Cmd(Client->Socket, BuildRep_Basic(475, Client->NickName, Args[1], SERR_BADCHANNELKEY));
				return ;
			}

			// si invite-only (mode +i)
			// 473    SERR_INVITEONLYCHAN "<channel> :Cannot join channel (+i)"
			if (!Channel_Manager.joinCheck_i(Args[1])) {
				Send_Cmd(Client->Socket, BuildRep_Basic(475, Client->NickName, Args[1], SERR_INVITEONLYCHAN));
				return ;
			}

			// si l'user est dans la liste des bans/kicked
			// 474    SERR_BANNEDFROMCHAN "<channel> :Cannot join channel (+b)
			if (!Channel_Manager.joinCheck_bans(Client->NickName, Args[1])) {
				Send_Cmd(Client->Socket, BuildRep_Basic(474, Client->NickName, Args[1], SERR_BANNEDFROMCHAN));
				return ;
			}

	/* ~~~~~~~~~~~~~~~~~~~~~~~~ CHECKS WALL DONE ~~~~~~~~~~~~~~~~~~~~~~ */
			// SINON tout est ok -> ajoute le client au channel + build reponse ()
			Channel_Manager.addClientToChannel(*Client, Args[1]);

			// + annonce a tte la chan (lui compris)
			Channel_Manager.channelSend(Client->NickName, Args[1], ":" + Client->makeFullName() + " JOIN " + Args[1], true);
	
			Log("JOIN",Client->NickName + " join " + Args[1]);
	}
}

/* ==> PART <== */

// https://www.rfc-editor.org/rfc/rfc14m59#section-4.2.2
// SERR_NEEDMOREPARAMS - SERR_NOSUCHCHANNEL - SERR_NOTONCHANNEL
// Parameters: <channel> *( "," <channel> ) [ <Part Message> ]
void  PART_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void)Client_Manager;

	std::vector<std::string> 					channels;
	std::vector<std::string>::const_iterator	it;
	std::string 								leavingMsg;
	
	if (!Guard(Client, Args, "PART"))
		return ;

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
			Send_Cmd(Client->Socket, BuildRep_Basic(403, Client->NickName, *it, SERR_NOSUCHCHANNEL));
		} else if (!Channel_Manager.isClientIn(Client->NickName, *it)) {
			Send_Cmd(Client->Socket, BuildRep_Basic(441, Client->NickName, *it, SERR_USERNOTINCHANNEL));
		} else {
			leavingProcess(Client, *it, Channel_Manager, leavingMsg);
		}
	}
}

void	PART_Command::leavingProcess(Client *Client, std::string const &channelName, ChannelManager &Channel_Manager, std::string &leavingMsg) {
	if (leavingMsg.size() > 200)
		leavingMsg = leavingMsg.substr(0, 200);
	Channel_Manager.channelSend(Client->NickName, channelName, BuildRep_CmdEvent(*Client, "PART", channelName + " " + leavingMsg) , true);
	Channel_Manager.rmClientToChannel(*Client, channelName);
}

/* ==> MODE <== */

//. https://stackoverflow.com/questions/12886573/implementing-irc-rfc-how-to-respond-to-mode
// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.3
// Note that there is a maximum limit of three (3) changes per command for modes that take a parameter
void  MODE_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
	// showStringVector("Args", Args); //DEBUG //checking

	// [1] Si l'utilisateur fait /mode dans aucun channel sans parametre
	// 461    SERR_NEEDMOREPARAMS "<command> :Not enough parameters"
	if (!Guard(Client, Args, "MODE"))
		return ;

	// [2] Sinon Si l'utilisateur fait /mode #nomChannel
	if (Args.size() == 2 && Is_Channel_Name_Arg(Args[1])) {
		Log("MODE", "get mode info from channel : " + Args[1]);

		// [2]-[1] Le channel n'existe pas ou le client n'est pas dans le channel
		// 441    SERR_USERNOTINCHANNEL "<nick> <channel> :They aren't on that channel"
		if (!Channel_Manager.isChannelExists(Args[1]) || !Channel_Manager.isClientIn(Client->NickName, Args[1])) {
			// Send_Cmd(Client->Socket, BuildRep_Chan(441, Client->NickName + " " + Args[1], "They aren't on that channel"));
			// [!] comme dans join je sais pas afficher retour puisque le channel est pas bon
			Send_Cmd(Client->Socket, BuildRep_Basic(441, Client->NickName, Args[1], SERR_USERNOTINCHANNEL));
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
		Send_Cmd(Client->Socket, BuildRep_Basic(441, Client->NickName, Args[1], SERR_USERNOTINCHANNEL));
		// Ce bloc est idem  que + haut en [2]-[1] ==> a faire une fonction + tard
	} 
	// [3 -suite] et l'user doit etre chanop OU OPER
	else if (!Channel_Manager.isClientChopOf(Client->NickName, Args[1]) && !Client->Oper) {
		// 482    SERR_CHANOPRIVSNEEDED "<channel> :You're not channel operator"
		Send_Cmd(Client->Socket, BuildRep_Basic(482, Client->NickName, Args[1], SERR_CHANOPRIVSNEEDED));
	}
	//[4] Sinon si l'utilisateur fait /mode #nomChannel <[+-][ntmsipNTMSIP]>
	else if (Args.size() == 3 && Is_Channel_Name_Arg(Args[1]) && Is_Channel_Mode_BArgs(Args[2])) {
		Exe_Basic_Settings(Client, Args, Channel_Manager, Client_Manager);
	}
	//[5] Sinon si l'utilisateur fait /mode #nomChannel <[+-][lkLK]> *<Unsigned/key>
	else if ((Args.size() == 3 || Args.size() == 4) && Is_Channel_Name_Arg(Args[1]) && Is_Channel_Mode_AArgs(Args[2])) {
		Exe_Advanced_Settings(Client, Args, Channel_Manager, Client_Manager);
	}

	//[6] Sinon si l'utilisateur fait /mode #nomChannel <nickname> *<+-| ov>
	else if ((Args.size() >= 3) && Is_Channel_Name_Arg(Args[1]) && !Is_Channel_Mode_AArgs(Args[2])) {
		Exe_user_MODE(Client, Args, Channel_Manager, Client_Manager);
	}


	// [7] si rien de passer message mauvais args
	// 472    SERR_UNKNOWNMODE "<char> :is unknown mode char to me for <channel>
	else {
		Send_Cmd(Client->Socket, BuildRep_Basic(472, Client->NickName, Args[1], SERR_UNKNOWNMODE));
	}
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
	Channel_Manager.channelSend(Client->NickName, Args[1], BuildRep_Basic(324, Client->NickName, Args[1], ModeList), true);
	// Send_Cmd(Client->Socket, BuildRep_Basic(324, Client->NickName, Args[1], ModeList));
}

// /mode #nomChannel <nickname>
void	MODE_Command::Exe_user_MODE(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) const {
	std::string umode;

	// [1] verif si le nickname/Args[2] est un user de la channel
	if (!Channel_Manager.isClientIn(Args[2], Args[1])) {
		Send_Cmd(Client->Socket, BuildRep_Basic(441, Client->NickName, Args[1], SERR_USERNOTINCHANNEL));
		return ;
	}

	// [2] Si pas d'argument en plus
	// RPL_UMODEIS (221) "<client> <user modes>"
	if (Args.size() == 3) {
		
		if (Client_Manager.Is_Client_Oper(Args[2]))
			umode = "operator";
		else
			umode = Channel_Manager.getUserModeAsString(Args[2], Args[1]);
		Send_Cmd(Client->Socket, BuildRep_Basic(221, Client->NickName, Args[1], Args[2] + " modes : " + umode));
		return ;
	}
	else {
		// [3] arguments, on set le mode
		Exe_user_SET_MODE(Client, Args, Channel_Manager, Client_Manager);
	}
}

// /mode #nomChannel <nickname> *<+-| ov>
void	MODE_Command::Exe_user_SET_MODE(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) const {
	(void) Args;
	(void) Channel_Manager;
	(void) Client_Manager;
	(void) Client;
	bool isPlus;

	if (!Is_Channel_Mode_UArgs(Args[3])) {
		Send_Cmd(Client->Socket, BuildRep_Basic(472, Client->NickName, Args[1], SERR_UNKNOWNMODE));
		return ;
	}
	Log("MODE", "user mode setting : " + Args[3] + " to " + Args[2]);
	isPlus = (Args[3][0] == '+' ? true : false);
	Channel_Manager.setUserModesOfAs(Args[1], Args[2], isPlus, Args[3]);
}



/* ==> TOPIC <== */

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.4

// [+] autre code a gere une fois join fini
// 442     SERR_NOTONCHANNEL "<channel> :You're not on that channel"
// 333     RPL_TOPICWHOTIME "<client> <channel> <nick> <setat>"
// Args[0] TOPIC  |  Args[1] #currentChannel  |  Args[2-+] new topic (vector string to join)
void  TOPIC_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
	int	ret;
	// Memo :  Args[1] is Channel Name;
	//         Args[2] is newtopic
    (void )Client_Manager;
	if (!Guard(Client, Args, "TOPIC"))
		return ;

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
		std::string	newTopic = catVectString(Args, 2, " ");
		// std::vector<std::string>::iterator it = Args.begin() + 2;
		// while (it != Args.end()) {
		// 	if (it != Args.begin() + 2)
		// 		newTopic += " ";
		// 	newTopic += *it;
		// 	++it;
		// }
		ret = Channel_Manager.setTopicOf(Args[1], newTopic, (*Client));
		if (ret == GOOD) { // construire la reponse du changement de topic
			// la demande peut etre faite depuis n'importe quel channel
			// je ne sais pas trop comment gerer ca. (je laisse pour l'instant)

			
			//[2]-[B] --> formater le msg de changement de topic (avec setat -> infos temps)
			//":IRC 333 Zel #test dan!~d@localhost 1547691506 \n")
			//Send_Cmd(Client->Socket, ":IRC 333 Zel #poumy Zel 1547691506 \n");
			Channel_Manager.channelSend(Client->NickName, Args[1], BuildRep_Basic(333, Client->NickName, Args[1], Client->NickName + " " + getNow()), true);

			//[2]-[C] --> passer le nouveau topic au channel + send_message le resultat
			Channel_Manager.channelSend(Client->NickName, Args[1],  BuildRep_Basic(332, Client->NickName, Args[1], newTopic), true);
			// Send_Cmd(Client->Socket, BuildRep_Basic(332, Client->NickName, Args[1], newTopic));

		} else if (ret == CM_NOTOPICPERM) { 
		// 482 SERR_CHANOPRIVSNEEDED "<channel> :You're not channel operator"
			Send_Cmd(Client->Socket, BuildRep_Basic(482, Client->NickName, Args[1], SERR_CHANOPRIVSNEEDED));
		}
	}
}


/* ==> NAMES <== */

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.5
void  NAMES_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;
	std::vector<std::string> 					channels;
	std::vector<std::string>::const_iterator	it;
	std::string 								leavingMsg;
	
	if (!Guard(Client, Args, "NAMES"))
		return ;
	/* Memo Args */
	//	Args[0] = "NAMES"
	//	Args[1] = "#channelCurrent" OU #channelAupif OU #chan1,#chan2,#chan3
	//	Args[2 et +] --> pas a gerer : target serveur
	
	// [A] NAMES sans argts
	if (Args.size() == 1) {
		// fais un Name de tous les channels accessibles
		// Les channels +p +s sont aussi utilise seulement l'utilisateur est dedans
		//   vector<std::string> = Channel_Manager.getAAChannels(Client->NickName); //All Accessible 
		// puis sur chaque vector getNamesIn(channelName,  >>>)
		return ;
	} 

	// [!] pas fini ! on vire/ou fait tout une fois WHO finie, je garde pour m'inspirer

	// [B] NAMES + channels list

	//[1] get Channels from Args[1] List (coma separated)
	channels = extractComaList(Args[1]);
	

}

/* ==> [...] <== */

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




Channel	*ChannelManager::Get_Channel(std::string &Channel_Name)
{
	std::map<std::string, Channel>::iterator	it;

	it = _chanList.find(Channel_Name);

	if (it != _chanList.end()) 
		return &(it->second);

	else 
		return NULL;
}

// t_mapClientStatus *ChannelManager::Get_Users(std::string const &channelName)
// {
// 	Channel *Chn = Channel_Manager.Get_Channel(Args[1]);

// 	if (!Chn)
// 		return NULL;

// 	return &(Chn->getUsers());
// }

// https://www.rfc-editor.org/rfc/rfc1459#section-4.5.1


void  WHO_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void) Client_Manager;
    (void) Channel_Manager;
    (void) Client;
    (void) Args;
	// SERR_NOSUCHSERVER 402
    // RPL_WHOREPLY     352
	// RPL_ENDOFWHO     315

	if (!Guard(Client, Args, "WHO"))
		return ;

	// [1] si le channel existe et que l'user en fait partie
	if (Channel_Manager.isChannelExists(Args[1]) && Channel_Manager.isClientIn(Client->NickName, Args[1])) {
		std::string addon = Channel_Manager.makeUserStringList(Args[1]);
		std::string symbol = "="; // [+] fction getSymbol en fonction du type de channel

		Send_Cmd(Client->Socket, BuildRep_Basic(353, Client->NickName, symbol + " " + Args[1], addon));
		Send_Cmd(Client->Socket, BuildRep_Basic(366, Client->NickName, Args[1], ":END of who"));
	}
}

// RPL_ENDOFWHO (315)    "<client> <mask> :End of WHO list"
// RPL_ENDOFNAMES (366)  "<client> <channel> :End of /NAMES list"

/*
//         Send_Cmd(Client.Socket,":IRC 353 Zel = #test :@Zel Tristan\n");
//         Send_Cmd(Client.Socket,":IRC 366 Zel #test :End of /NAMES list \n");
 353    RPL_NAMREPLY
              "( "=" / "*" / "@" ) <channel>
               :[ "@" / "+" ] <nick> *( " " [ "@" / "+" ] <nick> )
         - "@" is used for secret channels, "*" for private
           channels, and "=" for others (public channels).

       366    RPL_ENDOFNAMES
              "<channel> :End of NAMES list"

         - To reply to a NAMES message, a reply pair consisting
           of RPL_NAMREPLY and RPL_ENDOFNAMES is sent by the
           server back to the client.  If there is no channel
           found as in the query, then only RPL_ENDOFNAMES is
           returned.  The exception to this is when a NAMES
           message is sent with no parameters and all visible
           channels and contents are sent back in a series of
           RPL_NAMEREPLY messages with a RPL_ENDOFNAMES to mark
           the end.
*/

//RPL_WHOREPLY (352) "<client> <channel> <username> <host> <server> <nick> <flags> :<hopcount> <realname>"
void	WHO_Command::Send_RPL_WHOREPLY(Client *client, Client const &who, std::vector<std::string> const &Args, ChannelManager &Channel_Manager) {
	// std::string addon = "";

	// addon += who.makeFullName() + " "; // <client> ?
	// addon += Args[1] + " "; // <channel>
	// addon += who.UserName + " "; // <username>
	// addon += who.UserName + " "; // <host>
	// // http://chi.cs.uchicago.edu/chirc/irc_examples.html

	(void) Args;
	(void) Channel_Manager;
	(void) who;
	(void) client;

	// Send_Cmd(client->Socket, BuildRep_Basic(352, client->NickName, Args[1], addon));
}
