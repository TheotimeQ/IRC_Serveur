/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_channel.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:59:50 by loumarti          #+#    #+#             */
/*   Updated: 2023/04/02 15:36:45 by tquere           ###   ########.fr       */
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

// 	leChef.NickName = "leChef_n";
// 	leChef.UserName = "M. Boss_u";
// 	unPelo.NickName = "unPelo_n";
// 	unPelo.UserName = "pelo_u";
// 	unePelotte.NickName = "unePelotte_n";
// 	unePelotte.UserName = "pelotte_u";

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

	leChef.SetNickName("leChef_n");
	leChef.SetUserName("M. Boss_u");
	unPelo.SetNickName("unPelo_n");
	unPelo.SetUserName("pelo_u");
	unePelotte.SetNickName("unePelotte_n");
	unePelotte.SetUserName("pelotte_u");

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