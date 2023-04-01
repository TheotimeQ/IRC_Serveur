/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:10:11 by loumarti          #+#    #+#             */
/*   Updated: 2023/04/01 10:25:18 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELMANAGER_HPP
# define CHANNELMANAGER_HPP

# include "../Object/Channel.hpp"
# include "../Object/Client.hpp"
# include <iostream>

# define ERRCHAN_CREATION 	"channel creation error : "

typedef std::map<std::string, Channel>		t_mapChannel;

class ChannelManager {

 private :
	

	t_mapChannel			_chanList;

	bool	isChannelExists(std::string const &channelName)	const;
	void	log(std::string const &logMsg)					const;

	void	tryAddNewChannel(std::string const &name, Client &chop);
	void	rmChannel(std::string const &name);

 public :
	ChannelManager();
	~ChannelManager();
	ChannelManager(ChannelManager const &ori);
	ChannelManager	&operator=(ChannelManager const &righty);

	t_mapChannel const	&getChanList() const;

	void	addClientToChannel(Client &user, std::string const &channelName);
	void	rmClientToChannel(Client &user, std::string const &channelName);

};

std::ostream& operator<<(std::ostream	&o, t_mapChannel const &ChanList);

#endif