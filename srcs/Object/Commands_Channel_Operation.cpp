/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Channel_Operation.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 08:38:09 by zelinsta          #+#    #+#             */
/*   Updated: 2023/04/18 13:06:34 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//=====================================Channel operations======================================

/* ==> JOIN <== */

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.1
void  JOIN_Command::Execute(Client *client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
	showStringVector("Args", Args); //cheking debug

	if (!Guard(client, Args, "JOIN"))
		return ;
	// [1] Le channel n'existe pas -> c'est donc une creation
	// 403    SERR_NOSUCHCHANNEL "<channel name> :No such channel" 
	//- Used to indicate the given channel name is invalid
	if (!Channel_Manager.isChannelExists(Args[1])) {

		int ret = Channel_Manager.addNewChannel(Args[1], (*client));
		
		if (ret == 0) { // le channel est bien ajoute

			//JOIN SUCCEED : ":Zel!~a@localhost JOIN #test \n"
			Send_Cmd(client->Socket, BuildRep_CmdEvent(*client, Args[0], Args[1]));
			Log("JOIN",client->NickName + " join " + Args[1]);
			
			// DEBUG
			// std::cout << "chan_list : " << Channel_Manager.getChanList() << std::endl; //checking
			// std::cout << "usersList :" << Channel_Manager.getUsersOf(Args[1]) << std::endl; //checking
			// std::cout << "[wtf]" << std::endl;
			// Channel_Manager.getChannel(Args[1]).showUsers();
			// DEBUG

		} else { // toute forme d'erreur lie a un mauvais nom de channel
		Send_Cmd(client->Socket, BuildRep_Basic(403, client->NickName, Args[1], SERR_NOSUCHCHANNEL));
		}
	}
	// [2] Le channel existe (Args[1]), on veut le rejoindre
	else {
		// std::cout << "Log :" << Client->NickName << " want to join channel : " << Args[1] << std::endl; // checking

		// DEBUG
			// std::cout << "chan_list : " << Channel_Manager.getChanList() << std::endl; //checking
			std::cout << "usersList :" << Channel_Manager.getUsersOf(Args[1]) << std::endl; //checking
			Channel_Manager.getChannel(Args[1]).showUsers();
		// DEBUG

		// [2]-[1] passer les differents checks -> build msgs

	/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CHECKS WALL ~~~~~~~~~~~~~~~~~~~~~~~~~~ */
			// si le client est deja dans le channel [facultatif HexChat a la securite]
			//443    SERR_USERONCHANNEL  "<user> <channel> :is already on channel"
			if (Channel_Manager.isClientIn(client->NickName, Args[1])) {
				Log("JOIN", "join refused client already in the channel");
				Send_Cmd(client->Socket, BuildRep_Basic(443, client->NickName, Args[1], SERR_USERONCHANNEL));
				return ;
			}
			// si taille user max (mode -> l)
			// 471    SERR_CHANNELISFULL "<channel> :Cannot join channel (+l)"
			if (!Channel_Manager.joinCheck_l(Args[1])) {
				Log("JOIN", "join refused joinCheck_l");
				Send_Cmd(client->Socket, BuildRep_BasicChan(471, client->NickName, Args[1], SERR_CHANNELISFULL));
				return ;
			}

			// si besoin une cle + assez d'Args du coup (mode +k)
			// 475    SERR_BADCHANNELKEY "<channel> :Cannot join channel (+k)
			if (!Channel_Manager.joinCheck_k(Args[1], (Args.size() > 2 ? Args[2] : ""))) {
				Log("JOIN", "join refused joinCheck_k");
				Send_Cmd(client->Socket, BuildRep_Basic(475, client->NickName, Args[1], SERR_BADCHANNELKEY));
				return ;
			}

			// si invite-only (mode +i)
			// 473    SERR_INVITEONLYCHAN "<channel> :Cannot join channel (+i)"
			if (!Channel_Manager.joinCheck_i(Args[1], client->NickName)) {
				Log("JOIN", "join refused joinCheck_i");
				Send_Cmd(client->Socket, BuildRep_Basic(473, client->NickName, Args[1], SERR_INVITEONLYCHAN));
				return ;
			}

			// si l'user est dans la liste des bans/kicked
			// 474    SERR_BANNEDFROMCHAN "<channel> :Cannot join channel (+b)
			if (!Channel_Manager.joinCheck_bans(client->NickName, Args[1])) {
				Send_Cmd(client->Socket, BuildRep_Basic(474, client->NickName, Args[1], SERR_BANNEDFROMCHAN));
				return ;
			}

	/* ~~~~~~~~~~~~~~~~~~~~~~~~ CHECKS WALL DONE ~~~~~~~~~~~~~~~~~~~~~~ */
			// SINON tout est ok -> ajoute le client au channel + build reponse ()
			Channel_Manager.addClientToChannel(*client, Args[1]);

			// + annonce a tte la chan (lui compris)
			Channel_Manager.channelSend(client->NickName, Args[1], ":" + client->makeFullName() + " JOIN " + Args[1], true);
	
			Log("JOIN",client->NickName + " join " + Args[1]);

			// [+] donner le topic s'il y en a un ==> [!] fonction a part ?
			if (Channel_Manager.getTopicOf(Args[1]).compare("") != 0) {
				Send_Cmd(client->Socket, BuildRep_Basic(332, client->NickName, Args[1], Channel_Manager.getTopicOf(Args[1])));
			}

			// [+] update hexchat users pannel if the joinning client is an Oper  [!] ==> fonction a part
			if (client->Oper) {
				std::vector<std::string> userList = Channel_Manager.makeUserListOf(Args[1]);
				std::vector<std::string>::iterator it;
				for (it = userList.begin(); it != userList.end(); ++it) {
					Client *target;
					target = Client_Manager.Get_Client(*it);
					if (target != NULL) {
						WHO_Command who;
						who.Execute(target, Args, Channel_Manager, Client_Manager);
					}
				}
			}

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

// HexChat seems using NAMES rather than WHO (/names works in a channel whereas /who doesn't without exact syntax)
// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.5
void  NAMES_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
	WHO_Command who;
	who.Execute(Client, Args, Channel_Manager, Client_Manager);
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.6
void  LIST_Command::Execute(Client *client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Client_Manager;
	std::vector<std::pair<std::string, std::string> >::iterator it;
	std::string topic;

	std::vector<std::pair<std::string, std::string> > chanToList = getChanToList(client, Args, Channel_Manager);
	for (it = chanToList.begin(); it != chanToList.end(); ++it) {
		topic = (it->second == "" ? ":no topic yet" : it->second);
		std::string nb = Channel_Manager.howManyIn(it->first) + " ";
		Send_Cmd(client->Socket, BuildRep_Basic(322, client->NickName, it->first, nb + topic));
	}
	Send_Cmd(client->Socket, BuildRep_Basic(323, client->NickName, "", SRPL_LISTEND));
}

std::vector<std::pair<std::string, std::string> >	LIST_Command::getChanToList(Client *client, std::vector<std::string> const &Args,  ChannelManager &Channel_Manager) {
	std::vector<std::pair<std::string, std::string> > list;
	if (Args.size() == 1) {
		list = Channel_Manager.makeChannelList(client);
	}
	return list;
}

// INVITE <nickname> <channel>
// 4 Recv : INVITE Boys #summerParty
// Args       0     1     2
// Only the user inviting and the user being invited will receive notification of the invitation.
// invite-only flag set, only channel operators may issue INVITE command
// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.7
void  INVITE_Command::Execute(Client *client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
	if (!Guard(client, Args, "INVITE"))
		return ;
	
	/* INVITE PROCESS */
	// [1] Checking OPERATOR OR CHOP permission
	if (!client->Oper && !Channel_Manager.isClientChopOf(client->NickName, Args[2])) {
		Send_Cmd(client->Socket, BuildRep_Basic(482, client->NickName, Args[2], SERR_CHANOPRIVSNEEDED));
		return;
	}

	// [2] Checking that Args[2] is a valid channel
	if (!Channel_Manager.isChannelExists(Args[2])) {
		Send_Cmd(client->Socket, BuildRep_Basic(403, client->NickName, Args[2], SERR_NOSUCHCHANNEL));
			return ;
	}

	// [3] Checking that Args[1] is a valid user and not away
	Client *target = Client_Manager.Get_Client(Args[1]);
	if (target == NULL) {
		Send_Cmd(client->Socket, BuildRep_Basic(401, client->NickName, Args[2], Args[1] + " : " + SERR_NOSUCHNICK));
		return;
	} else if (target->Away) {
		Send_Cmd(client->Socket, BuildRep_Basic(301, client->NickName, "", Args[1] + " : " + target->Away_Str));
		return;
	}

	// [4] remove user from ban list (if he's there), add him to guestlist (if not already in)
	Log("INVITE", client->NickName + " is inviting " + Args[1] + " into " + Args[2]);
	INVITE_user(client, Args, Channel_Manager, Client_Manager);
	// 
}

// INVITE <nickname> <channel>
// 4 Recv : INVITE Boys #summerParty
// Args       0     1     2
// 341    RPL_INVITING  "<channel> <nick>"
void INVITE_Command::INVITE_user(Client *client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) {
	t_mapChannel::iterator		it;

	it = Channel_Manager.getChanListNC().find(Args[2]);
	if (it == Channel_Manager.getChanListNC().end()) {
		Log("INVITE", "INVITE_user() error");
		return;
	}
	rmFromVectString(it->second.bans, Args[1]);
	addInVectString(it->second.guests, Args[1]);
	showStringVector(Args[2] + ">>>banlist", it->second.bans); //checking
	showStringVector(Args[2] + ">>>guestlist", it->second.guests); //checking
	
	// Messages to both users, the guest and the invitation sender
	Send_Cmd(client->Socket, BuildRep_Basic(341, client->NickName, Args[1], Args[2]));

	Client *target = Client_Manager.Get_Client(Args[1]);
	if (target == NULL)
		return;
	// [!] trouver la bonne syntaxe ou utiliser un message prive ou ?
	Send_Cmd(target->Socket, BuildRep_Basic(341, Args[1], Args[1], Args[2]));
}


// KICK <channel> *( "," <channel> ) <user> *( "," <user> ) [<comment>]
// -> 4 Recv : KICK #fopi pelow :c'est un malpoli
//		Args	0     1     2         (3)
// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.8
void  KICK_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
	if (!Guard(Client, Args, "KICK"))
		return ;
	std::vector<std::string> 					channels;
	std::vector<std::string> 					users;
	std::vector<std::string>::const_iterator	it;
	std::string comment = (Args.size() > 2 ? "Kicking - " + catVectString(Args, 3, " ") : "Kicking");
	if (comment.size() > 200)
		comment = comment.substr(0, 200);

	/* KICKING PROCESS */
	// [1] Checking OPERATOR OR CHOP permission
	if (!Client->Oper && !Channel_Manager.isClientChopOf(Client->NickName, Args[1])) {
		Send_Cmd(Client->Socket, BuildRep_Basic(482, Client->NickName, Args[1], SERR_CHANOPRIVSNEEDED));
		return;
	}

	//[2] get Channels from Args[1] List (coma separated) and check if all valid
	channels = extractComaList(Args[1]);
	showStringVector("channels", channels); //DEBUG //checking
	for (it = channels.begin(); it != channels.end(); ++it) {
		if (!Channel_Manager.isChannelExists(*it)) {
			Send_Cmd(Client->Socket, BuildRep_Basic(403, Client->NickName, *it, SERR_NOSUCHCHANNEL_KC));
			return ;
		}
	}
	
	//[3] kicking one by one each user listed in Args[2]
	users = extractComaList(Args[2]);
	showStringVector("users", users); //DEBUG //checking
	for (it = channels.begin(); it != channels.end(); ++it) {
		Log("KICK", "Kicking from channel " + *it + " " + catStringVector(users, 0));
		KICK_userList(Client, Channel_Manager, Client_Manager, *it, users, comment);
	}
}

void KICK_Command::KICK_userList(Client *client, ChannelManager &Channel_Manager, Client_Manager &Client_Manager, std::string const &channelName, std::vector<std::string> &users, std::string const &comment) {
	std::vector<std::string>::iterator	it;

	for (it = users.begin(); it != users.end(); ++it) {
		if (!Channel_Manager.isClientIn(*it, channelName)) {
			Send_Cmd(client->Socket, BuildRep_Basic(441, client->NickName, *it, SERR_USERNOTINCHANNEL));
			Log("KICK", *it + " doesn't belong to channel " + channelName);
			continue ;
		}
	Client *target;
	target = Client_Manager.Get_Client(*it);
	if (target == NULL)
		return;
	Channel_Manager.channelSend(client->NickName, channelName, BuildRep_CmdEvent(*target, "PART", channelName + " " + comment + " - by " + client->NickName) , true);
	Channel_Manager.rmFromGuests(channelName, *it);
	Channel_Manager.rmClientToChannel(*target, channelName);
	}
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
void  WHO_Command::Execute(Client *client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
	(void) Client_Manager;

	if (!Guard(client, Args, "WHO"))
		return ;
	if (!Channel_Manager.isChannelExists(Args[1])) {
		Send_Cmd(client->Socket, BuildRep_Basic(403, client->NickName, Args[1], SERR_NOSUCHCHANNEL));
		return ;
	}
	if (Channel_Manager.isClientIn(client->NickName, Args[1])) {
		std::string addon = Channel_Manager.makeUserStringList(Args[1]);
		std::string symbol = "=";
		Send_Cmd(client->Socket, BuildRep_Basic(353, client->NickName, symbol + " " + Args[1], addon));
		Send_Cmd(client->Socket, BuildRep_Basic(366, client->NickName, Args[1], ":END of who"));
	} else
		Send_Cmd(client->Socket, BuildRep_Basic(441, client->NickName, Args[1], SERR_USERNOTINCHANNEL));
}
