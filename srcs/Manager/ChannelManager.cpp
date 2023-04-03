/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:33:48 by loumarti          #+#    #+#             */
/*   Updated: 2023/04/03 08:52:02 by loumarti         ###   ########lyon.fr   */
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
		if (it->second.getTopic() == "")
			return "No topic is set";
		else
			return it->second.getTopic();
	} else {
	std::cerr << ERRCHAN_WRONGNAME << channelName << std::endl;
		return "No topic is set";
	}
}

t_status const &ChannelManager::getStatusOfIn(Client const &user, std::string const &channelName) const {
	t_mapChannel::const_iterator	it;

	it = _chanList.find(channelName);
	if (it != _chanList.end()) {
		return it->second.getStatusOf(user.NickName);
	} else {
		log(ERRCHAN_WRONGNAME + channelName);
		return _chanList.begin()->second.getStatusOf(user.NickName);
	}
}




// try to set a topic, return values : 0 on success | > 0 if errors
int			ChannelManager::setTopicOf(std::string const &channelName, std::string const &newTopic, Client const &user) {
	t_mapChannel::iterator	it;
	// int	ret;
	(void) user;

	it = _chanList.find(channelName);
	if (it != _chanList.end()) {

		// Si le channel a le mode +t --> topic settable by channel operator only flag
		if (it->second.mode.t == true) {
			t_status status = getStatusOfIn(user, channelName);
			if (status.creator == false && status.chop == false) {
				log(user.NickName + LOGCHAN_NOTOPICPERM + channelName);
				return CM_NOTOPICPERM;
			}
		}
		
		// si le mode autorise changement de topic () // +si le client a les droits
		it->second.setTopic(newTopic);
		return 0; //GOOD
		// constinuer ici (...)
		
		// sinon retour err CM_TOPICLOCK
	} else {
		log(ERRCHAN_WRONGNAME + channelName);
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
		// NON -> utiliser des code erreures a remonter jusqua la commande par le biais du ChManager
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
	std::cerr << "\033[38;5;102m";
	std::cerr << "ChannelManager : " << logMsg << std::endl;
	std::cerr << "\033[m";
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