/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:33:48 by loumarti          #+#    #+#             */
/*   Updated: 2023/04/02 14:47:36 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "../../incs/Manager/ChannelManager.hpp"

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



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ public methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// if user is already in channel, nothing happens
void	ChannelManager::addClientToChannel(Client &user, std::string const &channelName) {


	if (!isChannelExists(channelName))
		tryAddNewChannel(channelName, user);
	if (isChannelExists(channelName)) {
		_chanList[channelName].addUser(user);
	}
}

// After removing a user, check if channel is empty to remove it
void	ChannelManager::rmClientToChannel(Client &user, std::string const &channelName) {
	if (!isChannelExists(channelName))
		return; // [?] besoin de gerer erreure ici ?
	_chanList[channelName].delUser(user);
	if (_chanList[channelName].isEmpty())
		rmChannel(channelName);
}

std::string	ChannelManager::getTopicOf(std::string const &channelName) const {
	t_mapChannel::const_iterator	it;
	
	it = _chanList.find(channelName);
	if (it != _chanList.end()) {
		return it->second.getTopic();
	} else {
		return "";
	}
}

// try to set a topic, return values : 0 on success | > 0 if errors
int			ChannelManager::setTopicOf(std::string const &channelName, std::string const &newTopic) {
	t_mapChannel::const_iterator	it;
	
	it = _chanList.find(channelName);
	if (it != _chanList.end()) {
		
	} else {
		return CM_NOCHANNEL;
	}
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ private methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

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

bool	ChannelManager::isChannelExists(std::string const &channelName) const {
	t_mapChannel::const_iterator	it;

	it = _chanList.find(channelName);
	return (it != _chanList.end() ? true : false);
}


// to print log message from  ChannelManager class
void	ChannelManager::log(std::string const &logMsg)	const {
	std::cout << "\033[38;5;102m";
	std::cout << "ChannelManager : " << logMsg << std::endl;
	std::cout << "\033[m";
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~ getter setters ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

t_mapChannel const	&ChannelManager::getChanList() const { return _chanList; }

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