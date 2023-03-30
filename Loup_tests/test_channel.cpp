/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_channel.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:59:50 by loumarti          #+#    #+#             */
/*   Updated: 2023/03/30 13:24:42 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// c++ -Wall -Wextra -Werror -g -fsanitize=address -std=c++98 ../srcs/Channel.cpp ../srcs/Client.cpp -I ../incs/ test_channel.cpp -o irc_test_loup && ./irc_test_loup

#include "../incs/Client.hpp"
#include "../incs/Channel.hpp"
#include <iostream>
#include <exception>

int main() {

	Client leChef = Client(); 
	Client unPelo = Client();

	leChef.Set_NickName("leChef");
	leChef.Set_UserName("M. Boss");
	unPelo.Set_NickName("unPelo");
	unPelo.Set_UserName("pelo");

	//std::cout << leChef << std::endl;

	try {
		Channel chan1 = Channel("#WonderfullLand", leChef);
		chan1.addUser(unPelo);
		std::cout << chan1 << std::endl;
	} catch(std::exception &e) {
		// [+] envoyer un message a l'utilisateur qui a foire son /join
		std::cout << "Channel creation error : " << e.what() << std::endl;
	}



}