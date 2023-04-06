/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:10:11 by loumarti          #+#    #+#             */
/*   Updated: 2023/04/05 10:49:49 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELMANAGER_HPP
# define CHANNELMANAGER_HPP

# include "../Object/Channel.hpp"
# include "../Object/Client.hpp"
# include <iostream>

# define ERRCHAN_CREATION	"channel creation error : "
# define ERRCHAN_WRONGNAME	"[!] Channel Manager can't find : "

# define LOGCHAN_NOTOPICPERM	" : has no topic set permission in channel : "

// channel manager errors -> en faire une enum ?
# define CM_ERROR 1
# define CM_NOCHANNEL 2
# define CM_NOTOPICPERM 3
# define CM_WRONGNAMEFORMAT 4

typedef std::map<std::string, Channel>		t_mapChannel;

class ChannelManager {

 private :
	t_mapChannel			_chanList;

	void	log(std::string const &logMsg)					const;


 public :
	ChannelManager();
	~ChannelManager();
	ChannelManager(ChannelManager const &ori);
	ChannelManager	&operator=(ChannelManager const &righty);


	// BASIC MANAGEMENT
	bool	isChannelExists(std::string const &channelName)			const;
	bool	isClientIn(std::string const &nickname, std::string const &channelName)	const;
	bool	isClientSomewhere(std::string const &nickname)			const;
	int		addNewChannel(std::string const &name, Client &chop);
	int		checkChanName(std::string const &name)					const; // au niveau du manager -> try catch pas pratique ici
	void	rmChannel(std::string const &name);

	t_mapChannel const	&getChanList()								const;
	Channel const 		&getChannel(std::string const &channelName)	const;

	void	addClientToChannel(Client &user, std::string const &channelName);
	void	rmClientToChannel(Client &user, std::string const &channelName);

	//USERS STATUS
	t_status const &getStatusOfIn(Client const &user, std::string const &channelName) const;

	//TOPIC
	std::string	getTopicOf(std::string const &channelName) const;
	int			setTopicOf(std::string const &channelName, std::string const &newTopic, Client const &user);

};

std::ostream& operator<<(std::ostream	&o, t_mapChannel const &ChanList);

#endif