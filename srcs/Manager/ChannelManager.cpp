/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:33:48 by loumarti          #+#    #+#             */
/*   Updated: 2023/04/01 09:02:31 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../incs/Manager/ChannelManager.hpp"

void	ChannelManager::tryAddNewChannel(std::string const &name, Client &chop) {
	try {
		t_mapChannel::iterator	it;
		it = _chanList.find(name);
		if (it != _chanList.end())
			throw Channel::ErrorMsgException("this Channel already exists");
		_chanList[name] = Channel(name, chop);
	} catch(Channel::ErrorMsgException &e) {
		log(std::string(ERRCHAN_CREATION) + e.what());
		// [+] envoyer un message retour au client qui a mal fait son /join
	}
}

void	ChannelManager::rmChannel(std::string const &name) {
	t_mapChannel::iterator	it;
	
	it = _chanList.find(name);
	if (it != _chanList.end()) {
		_chanList.erase(it);
		log("Deleting channel : " + name);
	}
}






/* ~~~~~~~~~~~~~~~~~~~~~~~ private methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
// to print log message from  ChannelManager class
void	Server::log(std::string const &logMsg)	const {
	std::cout << "\033[38;5;102m";
	std::cout << "ChannelManager : " << logMsg << std::endl;
	std::cout << "\033[m";
}



/* ~~~~~~~~~~~~~~~~~~~~~~~ operator overload ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
std::ostream& operator<<(std::ostream &out, const t_mapChannel &ChanList) {
	t_mapChannel::const_iterator	it;
	
	it = ChanList.begin();
	while (it != ChanList.end()) {
		if (it != ChanList.begin())
			out << ", ";
		out << it->first;
		++it;
	}
	return (out);
}