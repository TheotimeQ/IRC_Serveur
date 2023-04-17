/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:18:15 by loumarti          #+#    #+#             */
/*   Updated: 2023/04/17 14:10:32 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Channel.hpp"

// public pour faire une liste de map
Channel::Channel()
: _name("#default")
{
	initChannel();
}

Channel::~Channel() {
	log(" is destroyed");
}

// Utiliser un try-catch pour creer un channel -> throw exceptions
Channel::Channel(std::string const &name, Client &chop) 
: _name(name), _topic(""), _key("")
{
	log("creation in progress");
	initChannel();
	dealUsersStatus(chop);
}


///////////////////////* getters setters */////////////////////////

std::string const	&Channel::getName() const { return _name; }

t_mapClientStatus const	&Channel::getUsers() const { return _users; }

t_mapClientStatus	&Channel::getUsersNC() { return _users; }

std::string const	&Channel::getTopic() const { return _topic; }

std::string const	&Channel::getKey() const { return _key; }

void		Channel::setTopic(std::string const &newTopic) {
	 _topic = newTopic;
}

void		Channel::setKey(std::string const &newKey) {
	_key = newKey;
}

t_chanmode const	&Channel::getChanmode() const { return mode; }

// check if channel users is empty or only with ban clients
bool				Channel::isEmpty()	const {
	return (_users.size() < 1 ? true : false);
}

t_status const		&Channel::getStatusOf(std::string const &userName) const {
	t_mapClientStatus::const_iterator	it;

	it = _users.find(userName);
	if (it != _users.end()) {
		return it->second.status;
	} else {
		log(CHERR_USERNAME_NOTFOUND + userName);
		return _users.begin()->second.status;
	}
}



//////////////////////* methods *//////////////////////////

// Might be updated if implementing invisible mode for users
int	Channel::countUsers() const {
	return _users.size();
}

// if user is already in channel, nothing happens
void	Channel::addUser(Client const &newUser) {
	t_clientData clientData;

	clientData.him = newUser;
	clientData.status.chop = false;
	clientData.status.creator = false;
	clientData.status.voice = false;
	_users[newUser.NickName] = clientData;
}

// delete an user from channel
void	Channel::delUser(Client const &userToDel) {
	t_mapClientStatus::iterator	it;

	it = _users.find(userToDel.NickName);
	if (it != _users.end()) {
		_users.erase(it);
	}
}

bool	Channel::isClientIn(std::string const &nickname) const {
	t_mapClientStatus::const_iterator	it;

	it = _users.find(nickname);
	return (it != _users.end() ? true : false);
}

bool	Channel::isClientChop(std::string const &nickname) const {
	t_mapClientStatus::const_iterator	it;

	it = _users.find(nickname);
	if (it == _users.end()) {
		log("isClientChop() error");
		return false;
	}
	return it->second.status.chop;
}

// remove an user from channel operator map -> nothing happens if not in map
void	Channel::rmOpPrivilege(std::string const &username) {
	t_mapClientStatus::iterator	it;

	it = _users.find(username);
	if (it != _users.end()) {
		if (it->second.status.chop == true) {
			log("removing channel operatore privilege to " + it->first);
			it->second.status.chop = false;
		} else {
			log(it->first + " is not channel operator, can't remove privilege");
		}
	}
}

bool	Channel::canTalk(std::string const &nickname)	const {
	t_mapClientStatus::const_iterator	it;
	
	if (mode.m == false)
		return true;
	it = _users.find(nickname);
	if (it == _users.end()) {
		log("canTalk() error");
		return false;
	}
	if (it->second.status.chop || it->second.status.creator || it->second.status.voice)
		return true;
	return false;
}


// manage status/privilege channel operator + channel creator
void	Channel::dealUsersStatus(Client &chop) {
	t_clientData	clientData;
	

	if (_name[0] == '!')
		clientData.status.creator = true;
	if (_name[0] == '+')
		mode.t = true;
	if (_name[0] == '!' || _name[0] == '+' || _name[0] == '&')
		_name[0] = '#';
	clientData.status.chop = true;
	clientData.status.voice = true;
	clientData.him = chop;
	_users[chop.NickName] = clientData;
}

// can't use memset or bzero because there is a std::map<> in t_chanmode struct
void				Channel::initChannel() {
	bzero(&mode, sizeof(t_chanmode));
	_users.clear();
}

// to print log message from Channel class
void	Channel::log(std::string const &logMsg)	const {
	std::cout << "\033[38;5;24m";
	std::cout << "Channel : " + _name + " : " << logMsg << std::endl;
	std::cout << "\033[m";
}
//~~~~~~~~~~~~~~~~~~~~~ make formated string ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// @operator   !creator   %chanop   +voice 
std::string		Channel::makeUserStringList()	const {
	t_mapClientStatus::const_iterator	it;
	std::string list = "";

	for (it = _users.begin(); it != _users.end(); ++it) {
		if (it != _users.begin())
			list += " ";
		list += makePrefix(it->second);
		list += it->first;
	}
	return list;
}

std::string	Channel::makeUserStatusList(std::string const &username)	const {
	t_mapClientStatus::const_iterator	it;
	std::string							status = "";

	it = _users.find(username);
	if (it == _users.end()) {
		log("makeUserStatusList() error");
		return "";
	}
	if (it->second.status.creator)
		status += "channel creator(!) ";
	if (it->second.status.chop)
		status += "channel operator(%) ";
	if (!it->second.status.creator && !it->second.status.chop && it->second.status.voice)
		status += "voice(+)";
	if (!it->second.status.creator && !it->second.status.chop && !it->second.status.voice)
		status = "regular user";
	return status;
}

std::string		Channel::makePrefix(t_clientData const &data)	const {
	if (data.him.Oper)
		return "@";
	if (data.status.creator) // '!' not interpreted by HexChat
		return ""; 
	if (data.status.chop)
		return "%";
	if (data.status.voice)
		return "+";
	return "";
}

//~~~~~~~~~~~~~~~~~~~~~~~~~Debug~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void	Channel::showUsers()	const {
	t_mapClientStatus::const_iterator it;
	t_mapClientStatus users = getUsers();
	
	log ("CHANNEL USERS INFOS >>");
	std::cout << "\033[38;5;23m";
	for( it = users.begin(); it != users.end(); ++it) {
		std::cout << it->second.him << std::endl;
		std::cout << "-----------------------------" << std::endl;
	}
	std::cout << "\033[m";
}

//~~~~~~~~~~~~~~~~~~~~~~~~~Operators~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::ostream	&operator<<(std::ostream &o, t_mapClientStatus const &users) {
	t_mapClientStatus::const_iterator	it = users.begin();

	while (it != users.end()) {
		if (it->second.status.creator == true) {
			o << "!"; // channel creator tag (maybe it should be ~ instead)
		} else if (it->second.status.chop == true) {
			o << "@"; // channel operator tag
		}
		if (it != users.begin())
			o << ", ";
		o << it->second.him.NickName;
		it++;
	}
	return o;
}

std::ostream	&operator<<(std::ostream &o, Channel const &channel) {
	o << "channel : ";
	o << channel.getName();
	o << " -- users : ";
	o << channel.getUsers();
	/* add here if need displaying chan modes*/
	return o;
}
