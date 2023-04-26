/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Channel_Operation.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 08:38:09 by zelinsta          #+#    #+#             */
/*   Updated: 2023/04/26 09:45:43 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//=====================================Channel operations======================================

/* ==> PART <== */

// https://www.rfc-editor.org/rfc/rfc14m59#section-4.2.2
void  PART_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
	std::vector<std::string> 					channels;
	std::vector<std::string>::const_iterator	it;
	std::string 								leavingMsg;
	(void)Client_Manager;
	
	if (!Guard(Client, Args, "PART"))
		return ;
	channels = extractComaList(Args[1]);
	leavingMsg = catStringVector(Args, 2);
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
void  TOPIC_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
	int	ret;
	(void )Client_Manager;

	if (!Guard(Client, Args, "TOPIC"))
		return ;
	if (Args.size() == 2) {
		std::string rep;
		std::string theTopic;
		
		theTopic = Channel_Manager.getTopicOf(Args[1]);
		rep = BuildRep_Basic(332, Client->NickName, Args[1], theTopic);
		Send_Cmd(Client->Socket, rep);
	}
	else if (Args.size() > 2) {
		std::string	newTopic = catVectString(Args, 2, " ");
		ret = Channel_Manager.setTopicOf(Args[1], newTopic, (*Client));
		if (ret == GOOD) { 
			Channel_Manager.channelSend(Client->NickName, Args[1], BuildRep_Basic(333, Client->NickName, Args[1], Client->NickName + " " + getNow()), true);
			Channel_Manager.channelSend(Client->NickName, Args[1],  BuildRep_Basic(332, Client->NickName, Args[1], newTopic), true);
		} else if (ret == CM_NOTOPICPERM) { 
			Send_Cmd(Client->Socket, BuildRep_Basic(482, Client->NickName, Args[1], SERR_CHANOPRIVSNEEDED));
		}
	}
}

/* ==> LIST <== */

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

/* ==> INVITE <== */

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.7
void  INVITE_Command::Execute(Client *client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
	if (!Guard(client, Args, "INVITE"))
		return ;
	
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
}

void INVITE_Command::INVITE_user(Client *client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) {
	t_mapChannel::iterator		it;

	it = Channel_Manager.getChanListNC().find(Args[2]);
	if (it == Channel_Manager.getChanListNC().end()) {
		Log("INVITE", "INVITE_user() error");
		return;
	}
	rmFromVectString(it->second.bans, Args[1]);
	addInVectString(it->second.guests, Args[1]);	
	Send_Cmd(client->Socket, BuildRep_Basic(341, client->NickName, Args[1], Args[2]));
	Client *target = Client_Manager.Get_Client(Args[1]);
	if (target == NULL)
		return;
	Send_Cmd(target->Socket, BuildRep_RawCmde(client->NickName, "INVITE " + Args[1] + " " + Args[2]));
}

/* ==> KICK <== */

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

	// [1] Checking OPERATOR OR CHOP permission
	if (!Client->Oper && !Channel_Manager.isClientChopOf(Client->NickName, Args[1])) {
		Send_Cmd(Client->Socket, BuildRep_Basic(482, Client->NickName, Args[1], SERR_CHANOPRIVSNEEDED));
		return;
	}

	//[2] get Channels from Args[1] List (coma separated) and check if all valid
	channels = extractComaList(Args[1]);
	for (it = channels.begin(); it != channels.end(); ++it) {
		if (!Channel_Manager.isChannelExists(*it)) {
			Send_Cmd(Client->Socket, BuildRep_Basic(403, Client->NickName, *it, SERR_NOSUCHCHANNEL_KC));
			return ;
		}
	}
	
	//[3] kicking one by one each user listed in Args[2]
	users = extractComaList(Args[2]);
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


/* ==> NAMES ~ WHO <== */

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

// HexChat seems using NAMES rather than WHO (/names works in a channel whereas /who doesn't without exact syntax)
// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.5
void  NAMES_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
	WHO_Command who;
	who.Execute(Client, Args, Channel_Manager, Client_Manager);
}