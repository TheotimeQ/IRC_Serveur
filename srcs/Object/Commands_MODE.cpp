/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_MODE.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:10:23 by loumarti          #+#    #+#             */
/*   Updated: 2023/04/17 14:31:51 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//==================================== Channel operations =====================================
/* =========================================> MODE <======================================== */

//. https://stackoverflow.com/questions/12886573/implementing-irc-rfc-how-to-respond-to-mode
// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.3
// Note that there is a maximum limit of three (3) changes per command for modes that take a parameter
void  MODE_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
	/* MODE PROCESS */

	// [1] /mode (no parameters)
	if (!Guard(Client, Args, "MODE"))
		return ;

	// [2] to go further, channel must exist
	if (!Channel_Manager.isChannelExists(Args[1])) { 
		Send_Cmd(Client->Socket, BuildRep_Basic(403, Client->NickName, Args[1], SERR_NOSUCHCHANNEL));
		return ;
	}

	// [3] /mode #channelName
	if (Args.size() == 2 && Is_Channel_Name_Arg(Args[1])) {
		Exe_Channel_Info(Client, Args, Channel_Manager, Client_Manager);
		return ;
	}

	// [4] to go further, user must be chop or OPER
	if (!Channel_Manager.isClientChopOf(Client->NickName, Args[1]) && !Client->Oper) {
		Send_Cmd(Client->Socket, BuildRep_Basic(482, Client->NickName, Args[1], SERR_CHANOPRIVSNEEDED));
		return ;
	}

	//[5] now, we can dispatch into our three kind of MODE_SUBCOMANDE : CHANNEL or USER
	Hub(Client, Args, Channel_Manager, Client_Manager);
}

//  HUB to MODE_SUBCOMANDE : CHANNEL or USER
// /mode #channelName <params to filter in the hub>   -   We made sure that : channel exists + client is chop or OPER
void	MODE_Command::Hub(Client *client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) const {

	// CHANNEL MODE - Basic
	//[1] /mode #nomChannel <[+-][ntmsipNTMSIP]> 
	if (Args.size() == 3 && Is_Channel_Name_Arg(Args[1]) && Is_Channel_Mode_BArgs(Args[2])) {
		Exe_Basic_Settings(client, Args, Channel_Manager, Client_Manager);
	}

	// CHANNEL MODE - Advanced
	//[2] /mode #nomChannel <[+-][lkbLKB]> *<Unsigned/key/target> 
	else if ((Args.size() == 3 || Args.size() == 4) && Is_Channel_Name_Arg(Args[1]) && Is_Channel_Mode_AArgs(Args[2])) {
		Exe_Advanced_Settings(client, Args, Channel_Manager, Client_Manager);
	}

	//USER MODE
	//[3] /mode #nomChannel <nickname> *<+-| ov> 
	else if ((Args.size() >= 3) && Is_Channel_Name_Arg(Args[1]) && !Is_Channel_Mode_AArgs(Args[2])) {
		Exe_user_MODE(client, Args, Channel_Manager, Client_Manager);
	}

	// [4] if nothing matched
	else {
		Send_Cmd(client->Socket, BuildRep_Basic(472, client->NickName, Args[1], SERR_UNKNOWNMODE));
	}
}

// when user prompt is /mode #channelName -- user must be operator to get info from outside
void	MODE_Command::Exe_Channel_Info(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) const {
	Log("MODE", "get mode info from channel : " + Args[1]);
	if (Client->Oper) {
		Send_Solo_RPL_CHANNELMODEIS(Client, Args, Channel_Manager, Client_Manager);
		return ;
	}
	if (!Channel_Manager.isClientIn(Client->NickName, Args[1])) {
		Send_Cmd(Client->Socket, BuildRep_Basic(441, Client->NickName, Args[1], SERR_USERNOTINCHANNEL));
	}
	else 
		Send_Solo_RPL_CHANNELMODEIS(Client, Args, Channel_Manager, Client_Manager);
}

// CHANNEL MODE - Basic
// when user prompt is /mode #channelName <[+-][ntmsipNTMSIP]>
void	MODE_Command::Exe_Basic_Settings(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager) const {
	(void)Client_Manager;
	bool	isPlus = (Args[2][0] == '+' ? true : false);

	Log("MODE", "basic channel mode setting : " + Args[2]);
	Channel_Manager.setModesOfAs(Args[1], isPlus, Args[2]);
	Send_RPL_CHANNELMODEIS(Client, Args, Channel_Manager, Client_Manager);
}

// CHANNEL MODE - Advanced
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

// 324    RPL_CHANNELMODEIS "<channel> <mode> <mode params>" send to all channel after a mode setting
void	MODE_Command::Send_RPL_CHANNELMODEIS(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) const {
	(void)Client_Manager;

	std::string ModeList = Channel_Manager.getModeAsString(Args[1]);
	Channel_Manager.channelSend(Client->NickName, Args[1], BuildRep_Basic(324, Client->NickName, Args[1], ModeList), true);
}

// 324    RPL_CHANNELMODEIS "<channel> <mode> <mode params>" send only to client
void	MODE_Command::Send_Solo_RPL_CHANNELMODEIS(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) const {
	(void)Client_Manager;

	std::string ModeList = Channel_Manager.getModeAsString(Args[1]);
	Send_Cmd(Client->Socket, BuildRep_Basic(324, Client->NickName, Args[1], ModeList));
}

// USER MODE
// /mode #nomChannel <nickname> <*args>
void	MODE_Command::Exe_user_MODE(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) const {
	std::string umode;

	// [1] checking that <nickname> is an user of current channel
	if (!Channel_Manager.isClientIn(Args[2], Args[1])) {
		Send_Cmd(Client->Socket, BuildRep_Basic(441, Client->NickName, Args[1], SERR_USERNOTINCHANNEL));
		return ;
	}

	// [2] no <args>, displaying mode of a user
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
		// [3] there is <args> setting user status and guests/bans in Channel object
		Exe_user_SET_MODE(Client, Args, Channel_Manager, Client_Manager);
	}
}

// /mode #nomChannel <nickname> <+-| bovBOV> 
void	MODE_Command::Exe_user_SET_MODE(Client *client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) const {
	bool isPlus;

	if (!Is_Channel_Mode_UArgs(Args[3])) {
		Send_Cmd(client->Socket, BuildRep_Basic(472, client->NickName, Args[1], SERR_UNKNOWNMODE));
		return ;
	}
	Log("MODE", "user mode setting : " + Args[3] + " to " + Args[2]);
	isPlus = (Args[3][0] == '+' ? true : false);
	Channel_Manager.setUserModesOfAs(Args[1], Args[2], isPlus, Args[3]);
	
	// case b or B (ban) -> sending back info to client
	if (findSetInString("bB", Args[3]) && isPlus) {
		Client *target = Client_Manager.Get_Client(Args[2]);
		if (target == NULL)
			return;
		Channel_Manager.channelSend(client->NickName, Args[1], BuildRep_CmdEvent(*target, "PART", Args[1] + " " + "BAN" + " - by " + client->NickName) , true);
		Channel_Manager.rmClientToChannel(*target, Args[1]);
	}
}