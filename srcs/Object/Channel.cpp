/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:18:15 by loumarti          #+#    #+#             */
/*   Updated: 2023/05/02 11:23:04 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Channel.hpp"

Channel::Channel()
: _name("#default")
{
	initChannel();
}

Channel::~Channel() {}

Channel::Channel(std::string const &name, Client &chop) 
: _name(name), _topic(NOTOPIC), _key("")
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
	if (mode.m)
		clientData.status.voice = false;
	else
		clientData.status.voice = true;
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

	if (_users.empty())
		return false;
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
	
	if (mode.m == false && mode.n == false)
		return true;
	if (mode.n == true && _users.find(nickname) == _users.end())
		return false;
	if (mode.m == true) {
		it = _users.find(nickname);
		if (it == _users.end()) {
			log("canTalk() can't find " + nickname + " in " + _name);
			return false;
		}
		if (it->second.status.chop || it->second.status.creator || it->second.status.voice)
			return true;
		return false;
	}
	return true;
}

// To be a guest, user must be in guests AND musn't be in bans
bool	Channel::isAGuest(std::string const &username)	const {
	std::vector<std::string>::const_iterator itgb;

	itgb = std::find(bans.begin(), bans.end(), username);
	if (itgb != bans.end())
		return false;
	itgb = std::find(guests.begin(), guests.end(), username);
	return (itgb != guests.end() ? true : false);
}


// manage status/privilege channel operator + channel creator
void	Channel::dealUsersStatus(Client &chop) {
	t_clientData	clientData;
	

	if (_name[0] == '!')
		clientData.status.creator = true;
	else
		clientData.status.creator = false;
	if (_name[0] == '+')
		mode.t = true;
	if (_name[0] == '!' || _name[0] == '+' || _name[0] == '&')
		_name[0] = '#';
	clientData.status.chop = true;
	clientData.status.voice = true;
	clientData.him = chop;
	_users[chop.NickName] = clientData;
}

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

	if (_users.empty())
		return list;
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
	std::string							str = "";

	it = _users.find(username);
	if (it == _users.end()) {
		log("makeUserStatusList() error");
		return "";
	}
	if (it->second.status.creator)
		str += "channel creator(!) ";
	if (it->second.status.chop)
		str += "channel operator(%) ";
	if (!it->second.status.creator && !it->second.status.chop && it->second.status.voice)
		str += "voice(+)";
	if (!it->second.status.creator && !it->second.status.chop && !it->second.status.voice)
		str = "regular user";
	return str;
}

std::string		Channel::makePrefix(t_clientData const &data)	const {

	if (data.him.Oper)
		return "@";
	if (data.status.chop)
		return "@";
	else if (data.status.voice)
		return "+";
	else
		return "";
}

std::vector<std::string>	Channel::makeUserList()	const {
	t_mapClientStatus::const_iterator	it;
	std::vector<std::string> userList;

	for (it = _users.begin(); it != _users.end(); ++it)
		userList.push_back(it->first);
	return userList;
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
			o << "!"; // channel creator tag
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
