/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageRecv.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:45:57 by loumarti          #+#    #+#             */
/*   Updated: 2023/03/31 11:30:40 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGERECV_HPP
# define MESSAGERECV_HPP

# include <iostream>
# include "Client.hpp"
# include "Channel.hpp"
// # include <vector>
// # include <map>
// # include <exception>
// # include <cstring>

class MessageRecv {
 private :
	MessageRecv();

	Client			_sender;
	Channel			_channel; // channel where it comes from
	int				_code; // type de message ( authent ? join ? ...)
	std::string		_content;
	/* more attributes ? */

	/* private methods */
	void				log(std::string const &logMsg)	const;

 public :
	~MessageRecv();
	MessageRecv(Client const &sender, Channel const &channel, std::string content);

	/* getters setters */
	Client const		&getSender()	const;
	Channel const		&getChannel()	const;
	int	const			getCode()		const;
	std::string const	&getContent()	const;

};


#endif