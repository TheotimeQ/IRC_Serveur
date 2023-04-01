/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:10:11 by loumarti          #+#    #+#             */
/*   Updated: 2023/04/01 09:56:41 by tquere           ###   ########.fr       */
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

 public :
	ChannelManager();
	~ChannelManager();
	ChannelManager(ChannelManager const &ori);
	ChannelManager	&operator=(ChannelManager const &righty);

	void	tryAddNewChannel(std::string const &name, Client &chop);
	void	rmChannel(std::string const &name);

	void	addClientToChannel(Client &user, std::string const &channelName);
	// [+] addclient to a channel
	// remove client from a channel (check si channel est vide apres)



};

std::ostream& operator<<(std::ostream	&o, t_mapChannel const &ChanList);

#endif