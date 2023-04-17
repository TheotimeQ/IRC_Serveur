/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:33:48 by loumarti          #+#    #+#             */
/*   Updated: 2023/04/17 14:24:52 by loumarti         ###   ########lyon.fr   */
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



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ BASIC MANAGEMENT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

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
	if (!isChannelExists(channelName)) {
		log("rmClientToChannel() error");
		return;
	}
	
	_chanList[channelName].delUser(user); //[!] segfault ?

	if (_chanList[channelName].isEmpty())
		rmChannel(channelName);
}

// option 
void	ChannelManager::rmClientFromAll(Client &user, std::string Msg) {
	t_mapChannel::const_iterator	it;

	for (it = _chanList.begin(); it != _chanList.end(); ++it) {
		if (isClientIn(user.NickName, it->first)) 
		{
			channelSend(user.NickName, it->first, Msg, false);
			rmClientToChannel(user, it->first);
		}
	}
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
// if channel name is valid to create one, its first char will be '#'
int	ChannelManager::addNewChannel(std::string const &name, Client &chop) {
	t_mapChannel::iterator	it;
	std::string		sharpName;
	
	int ret2 = checkChanName(name);
	if (ret2 != 0)
		return ret2;
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
		log("Deleting channel : " + name);
		_chanList.erase(it);
	}
}

bool	ChannelManager::isChannelExists(std::string const &channelName) const {
	t_mapChannel::const_iterator	it;

	it = _chanList.find(channelName);
	return (it != _chanList.end() ? true : false);
}

bool	ChannelManager::isChannelEmpty(std::string const &channelName) const {
	t_mapChannel::const_iterator	it;

	it = _chanList.find(channelName);
	if (it == _chanList.end()) {
		log("isChannelEmpty() error");
		return false;
	}
	return it->second.isEmpty();
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

bool	ChannelManager::isClientChopOf(std::string const &nickname, std::string const &channelName)	const {
	t_mapChannel::const_iterator	it;

	it = _chanList.find(channelName);
	if (it == _chanList.end()) {
		log("isClientChopOf() error");
		return false;
	}
	return it->second.isClientChop(nickname);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ADVANCED FEATURES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// Send a message from user to all channel, checks if channel is +m too (moderated)
void	ChannelManager::channelSend(std::string const &user, std::string const &channelName, std::string const &msg, bool self) const {
	t_mapChannel::const_iterator		it;
	t_mapClientStatus					usersStats;
	t_mapClientStatus::const_iterator	its;

	it = _chanList.find(channelName);
	if (it == _chanList.end()) {
		log("channelSend() error");
		return ;
	}
	if (!it->second.canTalk(user))
		return ;
	usersStats = getUsersOf(channelName);
	for (its = usersStats.begin(); its != usersStats.end(); ++its) {
		// [?] secu pour par s'envoyer a lui meme ? (voir apres) // booleen a penser si besoin ok
		if (!self && its->first.compare(user) == 0)
			continue ;

		//log("client : " + its->second.him.NickName + "socket : " + I_To_S(its->second.him.Socket));
		
		//std::string nameFull = ":" + its->second.him.NickName + "!" + its->second.him.UserName + "@" + its->second.him.HostName + " "; 
		Send_Cmd(its->second.him.Socket, msg + "\n");
	}
}

void	ChannelManager::allChannelSend(std::string const &msg_1, std::string const &msg_2) const
{
	t_mapChannel::const_iterator		it;

	for (it = _chanList.begin(); it != _chanList.end(); ++it) {
		t_mapClientStatus clientStatus = it->second.getUsers();
		std::string msg = msg_1 + it->first + msg_2;
		channelSend(clientStatus.begin()->first, it->first, msg, true);
	}
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
	std::vector<std::string>::const_iterator		itb;

	it = _chanList.find(channelName);
	if (it == _chanList.end()) {
		log("joinCheck_bans() error");
		return false;
	}
	for (itb = it->second.bans.begin(); itb != it->second.bans.end(); ++itb) {
		if (itb->compare(user) == 0)
			return false;
	}
	return true;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MODE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

std::string	ChannelManager::getModeAsString(std::string const &channelName) const {
	t_mapChannel::const_iterator	it;
	std::string						modeList;
	
	it = _chanList.find(channelName);
	if (it == _chanList.end()) {
		log("getModeAsString() error");
		return "";
	}
	if (it->second.mode.p)
		modeList += "+p ";
	if (it->second.mode.s)
		modeList += "+s ";
	if (it->second.mode.i)
		modeList += "+i ";
	if (it->second.mode.t)
		modeList += "+t ";
	if (it->second.mode.n)
		modeList += "+n ";
	if (it->second.mode.m)
		modeList += "+m ";
	if (it->second.mode.l > 0) {
		std::ostringstream oss;
		oss << it->second.mode.l;
		modeList += "+l(" + oss.str() + ") ";
	}
	if (it->second.mode.k)
		modeList += "+k ";
	return modeList;
}

std::string	ChannelManager::getUserModeAsString(std::string const &user, std::string const &channelName)	const {
	t_mapChannel::const_iterator	it;

	it = _chanList.find(channelName);
	if (it == _chanList.end()) {
		log("getUserModeAsString() error");
		return "";
	}
	return (it->second.makeUserStatusList(user));
}

void	ChannelManager::setModesOfAs(std::string const &channelName, bool isPlus, std::string const &flags) {
	t_mapChannel::iterator	it;

	it = _chanList.find(channelName);
	if (it == _chanList.end()) {
		log("setModesOfAs() error");
		return ;
	}
	for (unsigned i = 1; i < flags.size(); ++i) {
		char f = toupper(flags[i]);
		switch (f) {
			case 'N' :
					it->second.mode.n = isPlus;
					break;
			case 'T' :
					it->second.mode.t = isPlus;
					break;
			case 'M' :
					it->second.mode.m = isPlus;
					break;
			case 'S' :
					it->second.mode.s = isPlus;
					break;
			case 'I' :
					it->second.mode.i = isPlus;
					break;
			case 'P' :
					it->second.mode.p = isPlus;
					break;
			default :
					log("setModesOfAs() default case reached");
		}
	}
}

void		ChannelManager::setUserModesOfAs(std::string const &channelName, std::string const &username, bool isPlus, std::string const &flags) {
	t_mapChannel::iterator	it;
	t_mapClientStatus::iterator itc;

	it = _chanList.find(channelName);
	if (it == _chanList.end()) {
		log("setUserModesOfAs() [1] error");
		return ;
	}
	itc = it->second.getUsersNC().find(username);
	if (itc == it->second.getUsersNC().end()) {
		log("setUserModesOfAs() [2] error");
		return ;
	}
	for (unsigned i = 1; i < flags.size(); ++i) { 
		char f = toupper(flags[i]);
		switch (f) {
			case 'O' :
					itc->second.status.chop = isPlus;
					break;
			case 'V' :
					itc->second.status.voice = isPlus;
					break;
			case 'B' :
					if (isPlus) {
						addInVectString(it->second.bans, username);
						rmFromVectString(it->second.guests, username);
					} else {
						rmFromVectString(it->second.bans, username);
					}
					break;
			default :
					log("setUserModesOfAs() default case reached");
		}
	}
}

void	ChannelManager::setLimitModeOfAsWith(std::string const &channelName, bool isPlus, std::string const &option) {
	t_mapChannel::iterator	it;
	long	lvalue;
	int		value;

	it = _chanList.find(channelName);
	if (it == _chanList.end()) {
		log("setLimitModeOfAsWith() error");
		return ;
	}
	errno = 0;
	lvalue = strtol(option.c_str(), NULL, 10);
	if (lvalue < 0 || lvalue > INT_MAX || errno == ERANGE) {
		log("setLimitModeOfAsWith() overflow or negative value reached");
		value = 0;
	} else
		value = static_cast<int>(lvalue); 
	if (!isPlus)
		it->second.mode.l = 0;
	else
		it->second.mode.l = value;
}

void	ChannelManager::setKeyModeOfAsWith(std::string const &channelName, bool isPlus, std::string const &option) {
	t_mapChannel::iterator	it;

	it = _chanList.find(channelName);
	if (it == _chanList.end()) {
		log("setKeyModeOfAsWith() error");
		return ;
	}
	if (isPlus == false || option.compare("") == 0) {
		it->second.mode.k = false;
	} else {
		it->second.mode.k = true;
		it->second.setKey(option);
	}
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ WHO ~ NAMES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
std::string	ChannelManager::makeUserStringList(std::string const &channelName)	const {
	t_mapChannel::const_iterator	it;

	it = _chanList.find(channelName);
	if (it == _chanList.end()) {
		log("makeUserStringList() error");
		return "";
	}
	return it->second.makeUserStringList();
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ LIST ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
// List all channel wich are not secret for the client in a vector<pair<#channelName, topic>>
std::vector<std::pair<std::string, std::string> >	ChannelManager::makeChannelList(Client *client) const {
	std::vector<std::pair<std::string, std::string> > list;
	t_mapChannel::const_iterator	it;
	std::string						topic; // stamp-topic

	it = _chanList.begin();
	while (it != _chanList.end()) {
		if (it->second.mode.s && !isClientIn(client->NickName, it->first) && !client->Oper) {
			++it;
			continue;
		}
		if (it->second.mode.p && !isClientIn(client->NickName, it->first) && !client->Oper)
			topic = ":private topic";
		else
			topic = it->second.getTopic();
		std::pair<std::string, std::string>	pair(it->first, topic);
		list.push_back(pair);
		++it;
	}
	showVectStringPair(list); //checking - debug
	return list;
}

std::string	ChannelManager::howManyIn(std::string const &channelName) const {
	t_mapChannel::const_iterator	it;

	it = _chanList.find(channelName);
	if (it == _chanList.end()) {
		log("howManyIn() error");
		return "0";
	}
	return I_To_S(it->second.countUsers());
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ getter setters ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

t_mapChannel const	&ChannelManager::getChanList() const { return _chanList; }

t_mapChannel		&ChannelManager::getChanListNC() { return _chanList; }

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

t_mapClientStatus const	&ChannelManager::getUsersOf(std::string const &channelName)	const {
	t_mapChannel::const_iterator	it;

	it = _chanList.find(channelName);
	if (it != _chanList.end()) {
		return it->second.getUsers();
	} else {
		log("[!] getChannel() : error, channel not found");
		return _chanList.begin()->second.getUsers();
	}
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ private methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// to print log message from  ChannelManager class
void	ChannelManager::log(std::string const &logMsg)	const {
	std::cout << "\033[38;5;102m";
	std::cout << "ChannelManager :      " << logMsg << std::endl;
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