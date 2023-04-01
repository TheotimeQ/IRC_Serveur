/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:33:48 by loumarti          #+#    #+#             */
/*   Updated: 2023/04/01 09:11:14 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "../incs/ChannelManager.hpp"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~ Coplien Stuff & co ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
ChannelManager::ChannelManager() { log("default constructor"); }

ChannelManager::~ChannelManager() { log("destoyed"); }

ChannelManager::ChannelManager(ChannelManager const &ori) {
	log("copy constructor");
	*this = ori;
}

ChannelManager	&ChannelManager::operator=(ChannelManager const &righty) {
	if (this != &righty) {
		log("copy assignement using \'=\' operator");
		_chanList = righty._chanList;
	}
	return *this;
}



/* ~~~~~~~~~~~~~~~~~~~~~~~ Coplien stuff ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
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