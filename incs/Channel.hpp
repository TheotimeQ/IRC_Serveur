/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:17:45 by loumarti          #+#    #+#             */
/*   Updated: 2023/03/31 11:21:32 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

/*
Utiliser votre client de référence avec votre serveur devra être similaire à
l’utiliser avec un serveur IRC officiel. Cependant, seules les fonctionnalités
suivantes sont obligatoires :

◦ Vous devez pouvoir vous authentifier, définir un nickname, un username, re-
joindre un channel, envoyer et recevoir des messages privés, avec votre client
de référence.

◦ Tous les messages envoyés par un client dans un channel doivent être transmis
  à tous les clients ayant rejoint ce channel.

◦ Vous devez avoir des operators et des utilisateurs basiques.

◦ Vous devez donc implémenter les commandes spécifiques aux operators

◦ All the channel operation commands should be tested
  (remove one point for each feature that is not working)
------------------------------------------------------------------------------------------
Channel : 
- Contient un liste d'instance de client connecté a la channel 
- le nom de la channel.. autres ? 
- Methode : 
Envoi d' un objet message à tout les clients connecté  ( Faudra bien definir l'objet message )
Une methode pour deconnecter un client de la channel 
Une methode pour ajouter un client à la channe


Command: MODE
Parameters: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>]
               [<ban mask>]

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

*/
# define CHERR_FORMAT			"channel name format : <#name>"
# define CHERR_FORMAT_TOOLONG	"channel name can't exceed 200 character long"
# define CHERR_FORMAT_FCHAR		"channel name can't have spaces, coma or semicolon"


# include <iostream>
# include "Client.hpp"
# include <vector>
# include <map>
# include <exception>
# include <cstring>

// Des qu'on veut lister des client : une map <Username, Client>
// Client passe par reference & ?
typedef std::map<std::string, Client> t_mapClient;

typedef struct s_chanmode {
	t_mapClient		o;	// liste des users avec mode chanop;
	bool			p;	// private channel flag;
	bool			s;	// secret channel flag;
	bool			i;	// invite-only channel flag;
	bool			t;	// topic settable by channel operator only flag;
	bool			n;	// n - no messages to channel from clients on the outside;
	bool			m;	// moderated channel;
	int				l;	// set the user limit to channel; -> 0 == pas de limite ?
}	t_chanmode; 
// ==> integer ces deux typedef a la class en private~public ?


class Channel {
 private :
 	
	
	std::string			_name;
	Client				_chop; // channel operator
	t_mapClient			_users;
	std::string			_topic;
	t_chanmode			_mode; // all mode data

	/* private methods */
	void				checkChanName(std::string const &name) const;
	void				initChanmode();
	void				log(std::string const &logMsg)	const;
	

 public :
	Channel(); // besoin pour utiliser en map avec []
	~Channel();
	// creation d'un channel basique => UTILISER UN TRY CATCH
	Channel(std::string const &name, Client &chop);

	/* getters setters */

	std::string const	&getName()		const;
	t_mapClient const	&getUsers()		const;
	Client const		&getChop()		const;
	std::string const	&getTopic()		const;
	t_chanmode const	&getChanmode()	const;
	void				setTopic(std::string const &newTopic);
	// setter du chanmode un par un ?? a voir ...


	/* public methods */
		// bases
	void				announce(std::string msg) const;
	void				addUser(Client const &newUser);
	void				delUser(Client const &userToDel);
	
		// mode management
	void				rmOpPrivilege(std::string const &username);

	/* exception */
	// lors du catch de l'exception -> envoi message retour d'erreur au client
	class	ErrorMsgException : public std::exception {
		private :
			char const	*_msg;
		public :
			ErrorMsgException(char const *msg) : _msg(msg) {}
			char const	*what() const throw() { return const_cast<char *>(_msg); }
	};
	
};



std::ostream	&operator<<(std::ostream &o, Channel const &channel);
std::ostream	&operator<<(std::ostream &o, t_mapClient const &users);



#endif
