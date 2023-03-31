//
//  test_MsgRecv.cpp
//  ft_irc_REPO
//
//  Created by Loup Martineau on 31/03/2023.
//

// c++ -Wall -Wextra -Werror -g -fsanitize=address -std=c++98 ../srcs/Channel.cpp ../srcs/Client.cpp  ../srcs/MessageRecv.cpp -I ../incs/ test_MsgRecv.cpp -o irc_test_loup && ./irc_test_loup

#include "../incs/Client.hpp"
#include "../incs/Channel.hpp"
#include "../incs/MessageRecv.hpp"
#include <iostream>
#include <exception>


int main() {
	
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
		
		MessageRecv msg = MessageRecv(unPelo, chan1, "Salutations à mes amis du channel");
		
		
		
		
		
	} catch(Channel::ErrorMsgException &e) {
		// [+] envoyer un message a l'utilisateur qui a foire son /join
		std::cout << "Channel creation error : " << e.what() << std::endl;
	}
	
	return 0;
}
