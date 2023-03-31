/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MsgManager.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:45:57 by loumarti          #+#    #+#             */
/*   Updated: 2023/03/31 11:30:40 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSGMANAGER_HPP
# define MSGMANAGER_HPP

# include <iostream>
# include "Client.hpp"
# include "Channel.hpp"
# include "Server.hpp"
# include "Message.hpp"
// # include <vector>
// # include <map>
// # include <exception>
// # include <cstring>

class MsgManager {
 private :
	MsgManager();
	
	
	Server			_server; // l'objet server passe en reference -> recup ses data
	/* autres besoins ? */
	
	/* private methods */
	void				log(std::string const &logMsg)	const;
	
 public :
	~MsgManager();
	
	void	sendMsg(Message const &msg);
	
	
	
	
};

#endif
