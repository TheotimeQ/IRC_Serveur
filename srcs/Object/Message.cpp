/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:07:13 by loumarti          #+#    #+#             */
/*   Updated: 2023/03/31 11:34:55 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Message.hpp"

//Message::Message() {} // private

Message::~Message() { log("is destroyed"); }

// code a 0 pour le moment
Message::Message(Client const &autor, Channel const &channel, std::string content)
: _autor(autor), _chanSrc(channel), _chanDst(channel), _code(0), _content(content)
{
	log(" creation");
}


/* ~~~~~~~~~~~~~~~~~~~~~~~ getters setters ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
Client const		&Message::getAutor()	const { return _autor; }
Channel const		&Message::getChanSrc()	const { return _chanSrc; }
Channel const		&Message::getChanDst()	const { return _chanDst; }
int					Message::getCode()		const { return _code; }
std::string const	&Message::getContent()	const { return _content; }



/* ~~~~~~~~~~~~~~~~~~~~~~~ private methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
// to print log message from MessageRecv class
void	Message::log(std::string const &logMsg)	const {
	std::cout << "\033[38;5;66m";
	std::cout << "MessageRecv : [\"" + _content + "\"] : ";
	std::cout << logMsg << std::endl;
	std::cout << "\033[m";
}

