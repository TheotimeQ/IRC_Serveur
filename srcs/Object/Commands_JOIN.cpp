/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_JOIN.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:51:34 by loumarti          #+#    #+#             */
/*   Updated: 2023/04/20 10:16:57 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//==================================== Channel operations =====================================
/* =========================================> JOIN <======================================== */

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.1
void  JOIN_Command::Execute(Client *client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
	if (!Guard(client, Args, "JOIN"))
		return ;
	if (!Channel_Manager.isChannelExists(Args[1]))
		joinningNewChannel(client, Args, Channel_Manager);
	else {
		if (!passAllChecks(client, Args, Channel_Manager))
			return ;
		Channel_Manager.addClientToChannel(*client, Args[1]);
		Channel_Manager.channelSend(client->NickName, Args[1], ":" + client->makeFullName() + " JOIN " + Args[1], true);
		Log("JOIN",client->NickName + " join " + Args[1]);
		if (Channel_Manager.getTopicOf(Args[1]).compare(NOTOPIC) != 0) {
			Send_Cmd(client->Socket, BuildRep_Basic(332, client->NickName, Args[1], Channel_Manager.getTopicOf(Args[1])));
		}
		if (client->Oper) {
			operJoinning(Args, Channel_Manager, Client_Manager);
		}
	}
}

void	JOIN_Command::joinningNewChannel(Client *client, std::vector<std::string> Args, ChannelManager &Channel_Manager) const {
		int ret;
		
		ret = Channel_Manager.addNewChannel(Args[1], (*client));
		if (ret == 0) { 
			Send_Cmd(client->Socket, BuildRep_CmdEvent(*client, Args[0], Args[1]));
			Log("JOIN",client->NickName + " join " + Args[1]);
		} else {
		Send_Cmd(client->Socket, BuildRep_Basic(403, client->NickName, Args[1], SERR_NOSUCHCHANNEL));
		}
}

bool JOIN_Command::passAllChecks(Client *client, std::vector<std::string> Args, ChannelManager &Channel_Manager) const {
	if (client->Oper)
		return true;
	
	// 443    SERR_USERONCHANNEL  "<user> <channel> :is already on channel"
	if (Channel_Manager.isClientIn(client->NickName, Args[1])) {
		Log("JOIN", "join refused client already in the channel");
		Send_Cmd(client->Socket, BuildRep_Basic(443, client->NickName, Args[1], SERR_USERONCHANNEL));
		return false;
	}
	
	// 471    SERR_CHANNELISFULL "<channel> :Cannot join channel (+l)"
	if (!Channel_Manager.joinCheck_l(Args[1])) {
		Log("JOIN", "join refused joinCheck_l");
		Send_Cmd(client->Socket, BuildRep_BasicChan(471, client->NickName, Args[1], SERR_CHANNELISFULL));
		return false;
	}

	// 475    SERR_BADCHANNELKEY "<channel> :Cannot join channel (+k)
	if (!Channel_Manager.joinCheck_k(Args[1], (Args.size() > 2 ? Args[2] : ""))) {
		Log("JOIN", "join refused joinCheck_k");
		Send_Cmd(client->Socket, BuildRep_Basic(475, client->NickName, Args[1], SERR_BADCHANNELKEY));
		return false;
	}

	// 473    SERR_INVITEONLYCHAN "<channel> :Cannot join channel (+i)"
	if (!Channel_Manager.joinCheck_i(Args[1], client->NickName)) {
		Log("JOIN", "join refused joinCheck_i");
		Send_Cmd(client->Socket, BuildRep_Basic(473, client->NickName, Args[1], SERR_INVITEONLYCHAN));
		return false;
	}

	// 474    SERR_BANNEDFROMCHAN "<channel> :Cannot join channel (+b)
	if (!Channel_Manager.joinCheck_bans(client->NickName, Args[1])) {
		Send_Cmd(client->Socket, BuildRep_Basic(474, client->NickName, Args[1], SERR_BANNEDFROMCHAN));
		return false;
	}
	return true;
}

void	JOIN_Command::operJoinning(std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) const {
	std::vector<std::string>::iterator it;
	std::vector<std::string> userList = Channel_Manager.makeUserListOf(Args[1]);

	for (it = userList.begin(); it != userList.end(); ++it) {
		Client *target = Client_Manager.Get_Client(*it);
		if (target != NULL) {
			WHO_Command who;
			who.Execute(target, Args, Channel_Manager, Client_Manager);
		}
	}
}
