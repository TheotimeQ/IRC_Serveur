/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:18:15 by loumarti          #+#    #+#             */
/*   Updated: 2023/03/30 13:23:33 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Channel.hpp"

Channel::Channel() {} //private

Channel::~Channel() {
	std::cout << "Channel : " << _name << "is destroyed" << std::endl;
}

// Utiliser un try-catch pour creer un channel -> throw exceptions
Channel::Channel(std::string const &name, Client &chop) 
: _name(name), _chop(chop) , _topic("")
{
	checkChanName(name);
	//bzero(&_mode, sizeof(t_chanmode)); // hum  sizeof une map dans struct ?
	// interdit Segfault !
	_mode.o[chop.Get_UserName()] = chop;
	_users[chop.Get_UserName()] = chop;
}



/* getters setters */

std::string const	&Channel::getName() const { return _name; }

Client const		&Channel::getChop() const { return _chop; }

t_mapClient const	&Channel::getUsers() const { return _users; }

std::string const	&Channel::getTopic() const { return _topic; }

void				Channel::setTopic(std::string const &newTopic) {
	 _topic = newTopic;
}

t_chanmode const	&Channel::getChanmode() const { return _mode; }



/* public methods */

	// Envoi d' un objet message à tout les clients connecté
	// ( Faudra bien definir l'objet message ) -> string pour l'instant
	void				Channel::announce(std::string msg) const {
		(void)msg;
	}

	void				Channel::addUser(Client const &newUser) {
		(void)newUser;
	}

	void				Channel::delUser(Client const &userToDel) {
		(void)userToDel;
	}








/* private methods */

// channel's name is [200]length prefixed by &, #, +, ! => on va garder que '#'
// forbidden characters : space, comma, semi-colon
void				Channel::checkChanName(std::string const &name) const {
	if (name.size() < 2 || name[0] != '#')
		throw ErrorMsgException("channel name format: <#name>");
	else if (name.size() > 200)
		throw ErrorMsgException("channel name can't exceed 200 character long");
}





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
	return o;
}