/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_channel.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:59:50 by loumarti          #+#    #+#             */
/*   Updated: 2023/04/01 13:50:05 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// c++ -Wall -Wextra -Werror -g -fsanitize=address -std=c++98 ../srcs/Channel.cpp ../srcs/Client.cpp -I ../incs/ test_channel.cpp -o irc_test_loup && ./irc_test_loup

#include "../incs/Client.hpp"
#include "../incs/Channel.hpp"
#include <iostream>
#include <exception>

int main() {


// /*	coucou je reviens degueulasser ta partie avec des test */
// 	Client leChef = Client(); 
// 	Client unPelo = Client();
// 	Client unePelotte = Client();

// 	leChef._NickName = "leChef_n";
// 	leChef._UserName = "M. Boss_u";
// 	unPelo._NickName = "unPelo_n";
// 	unPelo._UserName = "pelo_u";
// 	unePelotte._NickName = "unePelotte_n";
// 	unePelotte._UserName = "pelotte_u";

// 	_ChnMng.addClientToChannel(leChef, "#mauvaisCannal::");
// 	_ChnMng.addClientToChannel(leChef, "MauvaisCannal2");
// 	_ChnMng.addClientToChannel(leChef, "#GoodCannal");
// 	_ChnMng.addClientToChannel(unePelotte, "#SuperCoolishCannal");

// 	std::cout << "chanList : " << _ChnMng.getChanList() << std::endl;

// 	_ChnMng.rmClientToChannel(unePelotte, "#SuperCoolishCannal");

// 	std::cout << "chanList : " << _ChnMng.getChanList() << std::endl;

// /*	end tests */



	Client leChef = Client(); 
	Client unPelo = Client();
	Client unePelotte = Client();

	leChef.Set_NickName("leChef_n");
	leChef.Set_UserName("M. Boss_u");
	unPelo.Set_NickName("unPelo_n");
	unPelo.Set_UserName("pelo_u");
	unePelotte.Set_NickName("unePelotte_n");
	unePelotte.Set_UserName("pelotte_u");

	//std::cout << leChef << std::endl;

	try {
		Channel chan1 = Channel("#WonderfullLand", leChef);
		chan1.addUser(unPelo);
		chan1.addUser(unPelo);
		chan1.addUser(unePelotte);
		std::cout << chan1 << std::endl;
		chan1.announce("Hello dears !");

		chan1.delUser(unPelo);
		chan1.delUser(unPelo);
		std::cout << chan1 << std::endl;
	} catch(Channel::ErrorMsgException &e) {
		// [+] envoyer un message a l'utilisateur qui a foire son /join
		std::cout << "Channel creation error : " << e.what() << std::endl;
	}

	std::cout << std::endl << std::endl;

	try {
		Channel chan2 = Channel("1#WonderfullLand", leChef);
		std::cout << "ERROR(1) IF DISPLAYING THIS LINE" << std::endl; 
	} catch(Channel::ErrorMsgException &e) {
		// [+] envoyer un message a l'utilisateur qui a foire son /join
		std::cout << "Channel creation error : " << e.what() << std::endl;
	}

	try {
		Channel chan2 = Channel("#LKLK 1WonderfullLand", leChef);
		std::cout << "ERROR(2) IF DISPLAYING THIS LINE" << std::endl; 
	} catch(Channel::ErrorMsgException &e) {
		// [+] envoyer un message a l'utilisateur qui a foire son /join
		std::cout << "Channel creation error : " << e.what() << std::endl;
	}

	try {
		Channel chan2 = Channel("#WonderfullLand:nope", leChef);
		std::cout << "ERROR(3) IF DISPLAYING THIS LINE" << std::endl; 
	} catch(Channel::ErrorMsgException &e) {
		// [+] envoyer un message a l'utilisateur qui a foire son /join
		std::cout << "Channel creation error : " << e.what() << std::endl;
	}

	try {
		Channel chan2 = Channel("#WonderfullLandnopejkhkjkjhkjhkjhk" \
		"jhsddddddddddddddddddddddddddddddddddjhddddddddddddddddddb" \
		"jhsddddddddddddddddddddddddddddddddddjhddddddddddddddddddb" \
		"jhsddddddddddddddddddddddddddddddddddjhddddddddddddddddddb" \
		"jhsddddddddddddddddddddddddddddddddddjhddddddddddddddddddb" \
		"jhsddddddddddddddddddddddddddddddddddjhddddddddddddddddddb"
		, leChef);
		std::cout << "ERROR(4) IF DISPLAYING THIS LINE" << std::endl; 
	} catch(Channel::ErrorMsgException &e) {
		// [+] envoyer un message a l'utilisateur qui a foire son /join
		std::cout << "Channel creation error : " << e.what() << std::endl;
	}

}