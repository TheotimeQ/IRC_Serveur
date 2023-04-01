/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:45:57 by loumarti          #+#    #+#             */
/*   Updated: 2023/03/31 11:30:40 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <iostream>
# include "Client.hpp"
# include "Channel.hpp"
// # include <vector>
// # include <map>
// # include <exception>
// # include <cstring>

class Message {
 private :
	Message();
//	Message(Message const &ori);
//	Message &operator=(Message const &righty);
	

	Client			_autor;
	Channel			_chanSrc; // channel source (toujours un des que co)
	Channel			_chanDst; // channel dest (par defaut le meme)
	int				_code; // type de message ( authent ? join ? ...)
	std::string		_content;
	/* more attributes ? */

	/* private methods */
	void				log(std::string const &logMsg)	const;

 public :
	~Message();
	
	// Constructeur ou channel src == channel dest
	Message(Client const &autor, Channel const &channel, std::string content);

	/* getters setters */
	Client const		&getAutor()		const;
	Channel const		&getChanSrc()	const;
	Channel const		&getChanDst()	const;
	int					getCode()		const;
	std::string const	&getContent()	const;

};


#endif
