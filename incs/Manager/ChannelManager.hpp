/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:10:11 by loumarti          #+#    #+#             */
/*   Updated: 2023/04/01 09:20:18 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELMANAGER_HPP
# define CHANNELMANAGER_HPP

# include "../Object/Server.hpp"

# define ERRCHAN_CREATION 	"channel creation error : "

typedef std::map<std::string, Channel>		t_mapChannel;

class ChannelManager {

 private :
	

	t_mapChannel			_chanList;

	void	log(std::string const &logMsg)	const;

 public :
	ChannelManager();
	~ChannelManager();
	ChannelManager(ChannelManager const &ori);
	ChannelManager	&operator=(ChannelManager const &righty);

	void	tryAddNewChannel(std::string const &name, Client &chop);
	void	rmChannel(std::string const &name);


	// [+] addclient to a channel
	// remove client from a channel (check si channel est vide apres)



};

std::ostream& operator<<(std::ostream	&o, t_mapChannel const &ChanList);

#endif