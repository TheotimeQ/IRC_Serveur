/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_MODE.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:10:23 by loumarti          #+#    #+#             */
/*   Updated: 2023/04/15 11:12:18 by loumarti         ###   ########lyon.fr   */
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
		Log("MODE", "check - ici - [1] ");
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