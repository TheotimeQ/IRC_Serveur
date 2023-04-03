/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:10:11 by loumarti          #+#    #+#             */
/*   Updated: 2023/04/03 10:03:31 by loumarti         ###   ########lyon.fr   */
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
# define CM_NOCHANNEL 1
# define CM_NOTOPICPERM 2


typedef std::map<std::string, Channel>		t_mapChannel;

class ChannelManager {

 private :
	t_mapChannel			_chanList;

	void	log(std::string const &logMsg)					const;

	void	tryAddNewChannel(std::string const &name, Client &chop);
	void	rmChannel(std::string const &name);

 public :
	ChannelManager();
	~ChannelManager();
	ChannelManager(ChannelManager const &ori);
	ChannelManager	&operator=(ChannelManager const &righty);

	t_mapChannel const	&getChanList() const;
	bool	isChannelExists(std::string const &channelName)	const;

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