/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:18:15 by loumarti          #+#    #+#             */
/*   Updated: 2023/03/31 10:32:37 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Channel.hpp"

Channel::Channel() {} //private

Channel::~Channel() {
	std::cout << logIntro() << " is destroyed" << std::endl; // checking - log
}

// Utiliser un try-catch pour creer un channel -> throw exceptions
Channel::Channel(std::string const &name, Client &chop) 
: _name(name), _chop(chop) , _topic("")
{
	checkChanName(name);
	initChanmode();
	_mode.o[chop.Get_UserName()] = chop;
	_users[chop.Get_UserName()] = chop;
}


///////////////////////* getters setters */////////////////////////

std::string const	&Channel::getName() const { return _name; }

Client const		&Channel::getChop() const { return _chop; }

t_mapClient const	&Channel::getUsers() const { return _users; }

std::string const	&Channel::getTopic() const { return _topic; }

void				Channel::setTopic(std::string const &newTopic) {
	 _topic = newTopic;
}

t_chanmode const	&Channel::getChanmode() const { return _mode; }

//////////////////////////////////////////////////////////////////

//////////////////////* public methods *//////////////////////////

// Envoi d' un objet message à tout les clients connecté
// ( Faudra bien definir l'objet message ) -> string pour l'instant
void				Channel::announce(std::string msg) const {
	t_mapClient::const_iterator	it = _users.begin();

	while (it != _users.end()) {
		std::cout << logIntro() << "sending message : " << msg << " to : " << it->first << std::endl; // checking - log
		// ici utiliser la vrai classe message lorsqu'elle sera prete
		it++;
	}
}

void				Channel::addUser(Client const &newUser) {
	_users[newUser.Get_UserName()] = newUser;
}


// Si le chanop(1er createur) est del -> quelle gestion prevoir ? Rien pour le moment
// delete an user from channel
void				Channel::delUser(Client const &userToDel) {
	t_mapClient::iterator	it;

	it = _users.find(userToDel.Get_UserName());
	if (it != _users.end()) {
		rmOpPrivilege(it->first);
		_users.erase(it);
	}
}

// remove an user from channel operator map -> nothing happens if not in map
void				Channel::rmOpPrivilege(std::string const &username) {
	t_mapClient::iterator	it;

	it = _mode.o.find(username);
	if (it != _mode.o.end()) {
		_mode.o.erase(it);
	}
}

///////////////////////////////////////////////////////////////////

////////////////////////* private methods *////////////////////////

// channel's name is [200]length prefixed by &, #, +, ! => on va garder que '#'
// forbidden characters : space, comma, semi-colon
void				Channel::checkChanName(std::string const &name) const {
	if (name.size() < 2 || name[0] != '#')
		throw ErrorMsgException(CHERR_FORMAT);
	else if (name.size() > 200)
		throw ErrorMsgException(CHERR_FORMAT_TOOLONG);
	for (unsigned i = 0; i < name.size(); ++i) {
		if (name[i] == ' ' || name[i] == ',' || name[i] == ':')
			throw ErrorMsgException(CHERR_FORMAT_FCHAR);
	}
}

// can't use memset or bzero because there is a std::map<> in t_chanmode struct
void				Channel::initChanmode() {
	_mode.o.clear(); // probably useless
	_mode.p = false;
	_mode.s = false;
	_mode.i = false;
	_mode.t = false;
	_mode.n = false;
	_mode.m = false;
	_mode.l = 0;
}

// Used to introduce a log message with channel name
std::string const	Channel::logIntro() const {
	std::string logIntro;
	
	logIntro = "Channel : " + _name + " : ";
	return logIntro;
}

//////////////////////////////////////////////////////////////////



//~~~~~~~~~~~~~~~~~~~~~~~~~Operators~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::ostream	&operator<<(std::ostream &o, t_mapClient const &users) {
	t_mapClient::const_iterator	it = users.begin();

	while (it != users.end()) {
		if (it != users.begin())
			o << ", ";
		o << it->second.Get_NickName();
		it++;
	}
	return o;
}

std::ostream	&operator<<(std::ostream &o, Channel const &channel) {
	o << "channel : ";
	o << channel.getName();
	o << " -- operator : ";
	o << channel.getChop();
	o << " -- users : ";
	o << channel.getUsers();
	/* add here if need displaying chan modes*/
	return o;
}