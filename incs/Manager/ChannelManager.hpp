/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:10:11 by loumarti          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/14 09:18:45 by tquere           ###   ########.fr       */
=======
/*   Updated: 2023/04/14 09:42:03 by loumarti         ###   ########lyon.fr   */
>>>>>>> b7bff797a1c4a9c3274618a828b7f20713177f91
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELMANAGER_HPP
# define CHANNELMANAGER_HPP

# include "../Object/Channel.hpp"
# include "../Object/Client.hpp"
# include "../utils.hpp"

# include <iostream>
# include <climits>
# include <cstdlib>
# include <cerrno>

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
	bool	isChannelEmpty(std::string const &channelName)			const;
	bool	isClientIn(std::string const &nickname, std::string const &channelName)	const;
	bool	isClientSomewhere(std::string const &nickname)			const;
	bool	isClientChopOf(std::string const &nickname, std::string const &channelName)	const;
	int		addNewChannel(std::string const &name, Client &chop);
	int		checkChanName(std::string const &name)					const;
	void	rmChannel(std::string const &name);
	
	// ADVANCED FEATURES
	void	channelSend(std::string const &user, std::string const &channelName, std::string const &msg, bool self) const;

	/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ getter setters ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
	t_mapChannel const		&getChanList()								const;
	Channel const 			&getChannel(std::string const &channelName)	const;
	t_mapClientStatus const	&getUsersOf(std::string const &channelName)	const;

	void	addClientToChannel(Client &user, std::string const &channelName);
	void	rmClientToChannel(Client &user, std::string const &channelName);
	void	rmClientFromAll(Client &user, std::string msg);

	//USERS STATUS
	t_status const &getStatusOfIn(Client const &user, std::string const &channelName) const;

	//TOPIC
	std::string	getTopicOf(std::string const &channelName) const;
	int			setTopicOf(std::string const &channelName, std::string const &newTopic, Client const &user);

	//JOIN CHECK
	bool	joinCheck_l(std::string const &channelName)								const;
	bool	joinCheck_k(std::string const &channelName, std::string const &key)		const;
	bool	joinCheck_i(std::string const &channelName)								const;
	bool	joinCheck_bans(std::string const &user, std::string const &channelName)	const;

	//MODE
	std::string	getModeAsString(std::string const &channelName)						const;
	void		setModesOfAs(std::string const &channelName, bool isPlus, std::string const &flags);
	void		setLimitModeOfAsWith(std::string const &channelName, bool isPlus, std::string const &option);
	void		setKeyModeOfAsWith(std::string const &channelName, bool isPlus, std::string const &option);

	// WHO ~ NAMES
	std::string	makeUserStringList(std::string const &channelName)	const;

	//Ajout pour fonction theotime
	Channel		*Get_Channel(std::string &Channel_Name);
};

std::ostream& operator<<(std::ostream	&o, t_mapChannel const &ChanList);

#endif