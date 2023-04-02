/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:18:15 by loumarti          #+#    #+#             */
/*   Updated: 2023/04/02 11:57:59 by loumarti         ###   ########lyon.fr   */
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
	//log(" is destroyed");
}

// Utiliser un try-catch pour creer un channel -> throw exceptions
Channel::Channel(std::string const &name, Client &chop) 
: _topic(""), _key("")
{
	//log(" creation in progress");
	initChannel();
	checkChanName(name);
	dealUsersStatus(chop);
}


///////////////////////* getters setters */////////////////////////

std::string const	&Channel::getName() const { return _name; }

t_mapClientStatus const	&Channel::getUsers() const { return _users; }

std::string const	&Channel::getTopic() const { return _topic; }

void				Channel::setTopic(std::string const &newTopic) {
	 _topic = newTopic;
}

t_chanmode const	&Channel::getChanmode() const { return _mode; }

// check if channel users is empty or only with ban clients
bool				Channel::isEmpty()	const {
	return (_users.size() < 1 ? true : false);
}


//////////////////////* public methods *//////////////////////////

// Envoi d' un objet message à tout les clients connecté
// ( Faudra bien definir l'objet message ) -> string pour l'instant
void				Channel::announce(std::string msg) const {
	t_mapClientStatus::const_iterator	it = _users.begin();

	while (it != _users.end()) {
		log("sending message : " + msg + " to : " + it->first);
		// ici utiliser la vrai classe message lorsqu'elle sera prete
		it++;
	}
}

// if user is already in channel, nothing happens
void				Channel::addUser(Client const &newUser) {
	t_status status;

	status.him = newUser;
	status.chop = false;
	status.creator = false;
	_users[newUser._UserName] = status;
}

// delete an user from channel
void				Channel::delUser(Client const &userToDel) {
	t_mapClientStatus::iterator	it;

	it = _users.find(userToDel._UserName);
	if (it != _users.end()) {
		_users.erase(it);
	}
}

// remove an user from channel operator map -> nothing happens if not in map
// aura surment besoin de 
void				Channel::rmOpPrivilege(std::string const &username) {
	t_mapClientStatus::iterator	it;

	it = _users.find(username);
	if (it != _users.end()) {
		if (it->second.chop == true) {
			log("removing channel operatore privilege to " + it->first);
			it->second.chop = false;
		} else{
			log(it->first + " is not channel operator, can't remove privilege");
		}
	}
}


////////////////////////* private methods *////////////////////////

// channel's name is [200]length prefixed by &, #, +, ! => gestion de '#' et '!'
// forbidden characters : space, comma, semi-colon
void			Channel::checkChanName(std::string const &name) {
	if (name.size() < 2)
		throw ErrorMsgException(CHERR_FORMAT);
	else if ((name[0] != '#' && name[0] != '!'))
		throw ErrorMsgException(CHERR_FORMAT_PRE);
	else if (name.size() > 200)
		throw ErrorMsgException(CHERR_FORMAT_TOOLONG);
	for (unsigned i = 0; i < name.size(); ++i) {
		if (name[i] == ' ' || name[i] == ',' || name[i] == ':')
			throw ErrorMsgException(CHERR_FORMAT_FCHAR);
	}
}

// manage status/privilege channel operator + channel creator
void				Channel::dealUsersStatus(Client &chop) {
	t_status	status;
	
	if (_name[0] == '!') {
		_name[0] = '#';
		status.creator = true;
	}
	status.chop = true;
	_users[chop._UserName] = status;
}

// can't use memset or bzero because there is a std::map<> in t_chanmode struct
void				Channel::initChannel() {
	bzero(&_mode, sizeof(t_chanmode));
	_users.clear();
}

// to print log message from Channel class
void	Channel::log(std::string const &logMsg)	const {
	std::cout << "\033[38;5;24m";
	std::cout << "Channel : " + _name + " : " << logMsg << std::endl;
	std::cout << "\033[m";
}



//~~~~~~~~~~~~~~~~~~~~~~~~~Operators~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::ostream	&operator<<(std::ostream &o, t_mapClientStatus const &users) {
	t_mapClientStatus::const_iterator	it = users.begin();

	while (it != users.end()) {
		if (it->second.creator == true) {
			o << "!"; // channel creator tag (maybe it should be ~ instead)
		} else if (it->second.chop == true) {
			o << "@"; // channel operator tag
		}
		if (it != users.begin())
			o << ", ";
		o << it->second.him._NickName;
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
