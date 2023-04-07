/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:33:48 by loumarti          #+#    #+#             */
/*   Updated: 2023/04/07 12:53:00 by loumarti         ###   ########lyon.fr   */
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

// channel's name is [200]length prefixed by &, #, +, !
// forbidden characters : space, comma, semi-colon
// To update check too -> A_Command.Is_Channel_Name_Arg() method
int		ChannelManager::checkChanName(std::string const &name) const {
	if (name.size() < 2) {
		log("name too short : " + name);
		return CM_WRONGNAMEFORMAT;
	}
		
	else if ((name[0] != '#' && name[0] != '!' && name[0] != '+' && name[0] != '&')) {
		log("wrong name prefix : " + name);
		return CM_WRONGNAMEFORMAT;
	}
	else if (name.size() > 200) {
		log("name exceeded max length");
		return CM_WRONGNAMEFORMAT;
	}
	for (unsigned i = 0; i < name.size(); ++i) {
		if (name[i] == ' ' || name[i] == ',' || name[i] == ':') {
			log("forbidden character found in : " + name);
			return CM_WRONGNAMEFORMAT;
		}
	}
	return 0;
}



// if user is already in channel, nothing happens
void	ChannelManager::addClientToChannel(Client &user, std::string const &channelName) {
	if (!isChannelExists(channelName))
		addNewChannel(channelName, user);
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
	std::cout << ERRCHAN_WRONGNAME << channelName << std::endl;
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


// Management convention : All channel name will be save starting with '#'
int	ChannelManager::addNewChannel(std::string const &name, Client &chop) {
	t_mapChannel::iterator	it;
	std::string		sharpName;
	
	sharpName = name;
	sharpName[0] = '#';
	it = _chanList.find(sharpName);
	if (it == _chanList.end()) {
		int ret = checkChanName(sharpName);
		if (ret == 0) {
			_chanList[sharpName] = Channel(sharpName, chop);
		}
		return ret;
	} else {
		log("addNewChannel() : error");
		return CM_ERROR;
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

bool	ChannelManager::isClientIn(std::string const &nickname, std::string const &channelName) const {
	return (getChannel(channelName).isClientIn(nickname));
}

// True if client is into at least one channel
bool	ChannelManager::isClientSomewhere(std::string const &nickname)	const {
	t_mapChannel::const_iterator	it;

	for (it = _chanList.begin(); it != _chanList.end(); ++it) {
		if (it->second.isClientIn(nickname)) {
			//log("Client " + nickname + " found in channel : " + it->second.getName());
			return true;
		}
	}
	return false;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ join checks ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~ [true] if check is ok [false] if not ~~~~~~~~~~~~~~~~~~ */

bool	ChannelManager::joinCheck_l(std::string const &channelName) const {
	t_mapChannel::const_iterator	it;
	t_chanmode						mode;

	it = _chanList.find(channelName);
	if (it == _chanList.end()) {
		log("joinCheck_l() error");
		return false;
	}
	mode = it->second.getChanmode();
	if (mode.l == 0)
		return true;
	else
		return (it->second.getUsers().size() < static_cast<unsigned>(mode.l) ? true : false);
}

bool	ChannelManager::joinCheck_k(std::string const &channelName, std::string const &key) const {
	t_mapChannel::const_iterator	it;
	t_chanmode						mode;

	it = _chanList.find(channelName);
	if (it == _chanList.end()) {
		log("joinCheck_k() error");
		return false;
	}
	mode = it->second.getChanmode();
	if (mode.k == 0)
		return true;
	else
		return (it->second.getKey().compare(key) == 0 ? true : false);
}

bool	ChannelManager::joinCheck_i(std::string const &channelName) const {
	t_mapChannel::const_iterator	it;
	t_chanmode						mode;

	it = _chanList.find(channelName);
	if (it == _chanList.end()) {
		log("joinCheck_i() error");
		return false;
	}
	mode = it->second.getChanmode();
	return !mode.i;
}

bool	ChannelManager::joinCheck_bans(std::string const &user, std::string const &channelName)	const {
	t_mapChannel::const_iterator	it;
	t_mapClient						banList;
	t_mapClient::const_iterator		itb;

	it = _chanList.find(channelName);
	if (it == _chanList.end()) {
		log("joinCheck_bans() error");
		return false;
	}
	banList = it->second.getBans();
	itb = banList.find(user);
	return (itb == banList.end() ? true : false);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ getter setters ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

t_mapChannel const	&ChannelManager::getChanList() const { return _chanList; }

Channel const		&ChannelManager::getChannel(std::string const &channelName)	const {
	t_mapChannel::const_iterator	it;

	it = _chanList.find(channelName);
	if (it != _chanList.end()) {
		return it->second;
	} else {
		log("[!] getChannel() : error, channel not found");
		return _chanList.begin()->second;
	}
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ private methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// to print log message from  ChannelManager class
void	ChannelManager::log(std::string const &logMsg)	const {
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