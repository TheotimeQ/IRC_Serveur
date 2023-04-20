/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:17:45 by loumarti          #+#    #+#             */
/*   Updated: 2023/04/20 10:37:38 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

/* -----------------------------------------------------------------------------
Command: MODE
Parameters: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>]

   The MODE command is provided so that channel operators may change the
   characteristics of `their' channel.  It is also required that servers
   be able to change channel modes so that channel operators may be
   created.

   The various modes available for channels are as follows:

           o - give/take channel operator privileges;
           p - private channel flag;
           s - secret channel flag;
           i - invite-only channel flag;
           t - topic settable by channel operator only flag;
           n - no messages to channel from clients on the outside;
           m - moderated channel;
           l - set the user limit to channel;
-----------------------------------------------------------------------------*/

# include <iostream>
# include "Client.hpp"
# include <vector>
# include <map>
# include <exception>
# include <cstring>
# include "../utils.hpp"

# define NOTOPIC "no topic is set"

typedef struct s_status {
	bool	creator;
	bool	chop;
	bool	voice;

}			t_status;

typedef struct s_clientData {
	Client		him;
	t_status	status;
}	t_clientData;

typedef std::map<std::string, t_clientData> t_mapClientStatus;
typedef std::map<std::string, Client> t_mapClient;

typedef struct s_chanmode {
	bool			p;	// private channel flag;
	bool			s;	// secret channel flag;
	bool			i;	// invite-only channel flag;
	bool			t;	// topic settable by channel operator only flag;
	bool			n;	// n - no messages from outside clients;
	bool			m;	// moderated channel;
	int				l;	// set the user limit to channel; (value 0 means unlimited)
	bool			k;	// set a channel key (password).
}	t_chanmode; 

class Channel {
 private :
	
	std::string					_name;
	t_mapClientStatus			_users;
	std::string					_topic;
	std::string					_key;

	/* private methods */
	void				dealUsersStatus(Client &chop);
	void				initChannel();
	void				log(std::string const &logMsg)	const;

 public :
	/* public attribute */
	t_chanmode					mode;
	std::vector<std::string>	bans;
	std::vector<std::string>	guests;
	
	Channel();
	~Channel();
	Channel(std::string const &name, Client &chop);

	/* getters setters */

	std::string const		&getName()									const;
	t_mapClientStatus const	&getUsers()									const;
	t_mapClientStatus		&getUsersNC();
	int						countUsers()								const;
	std::string const		&getTopic()									const;
	std::string const		&getKey()									const;
	t_chanmode const		&getChanmode()								const;
	void					setTopic(std::string const &newTopic);
	void					setKey(std::string const &newKey);
	bool					isEmpty()									const;
	t_status const			&getStatusOf(std::string const &userName)	const;


	/* public methods */
		// basics
	void				addUser(Client const &newUser);
	void				delUser(Client const &userToDel);
	bool				isClientIn(std::string const &nickname)			const;

		// mode management
	void				rmOpPrivilege(std::string const &username);
	bool				isClientChop(std::string const &nickname)		const;
	bool				canTalk(std::string const &nickname)			const;
	bool				isAGuest(std::string const &username)			const;

		// make formated string
	std::string			makeUserStringList()							const;
	std::string			makeUserStatusList(std::string const &username)	const;
	std::string			makePrefix(t_clientData const &status)			const;
	std::vector<std::string>	makeUserList()							const;

		//debug
	void				showUsers()										const;

};

std::ostream	&operator<<(std::ostream &o, Channel const &channel);
std::ostream	&operator<<(std::ostream &o, t_mapClientStatus const &users);

#endif