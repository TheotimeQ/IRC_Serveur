/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageRecv.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:07:13 by loumarti          #+#    #+#             */
/*   Updated: 2023/03/31 11:34:55 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/MessageRecv.hpp"

//MessageRecv::MessageRecv() {} // private

MessageRecv::~MessageRecv() { log("is destroyed"); }

// code a 0 pour le moment
MessageRecv::MessageRecv(Client const &sender, Channel const &channel, std::string content)
: _sender(sender), _channel(channel), _code(0), _content(content)
{
	log(" creation");
}


/* ~~~~~~~~~~~~~~~~~~~~~~~ getters setters ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
Client const		&MessageRecv::getSender()	const { return _sender; }
Channel const		&MessageRecv::getChannel()	const { return _channel; }
int					MessageRecv::getCode()		const { return _code; }
std::string const	&MessageRecv::getContent()	const { return _content; }



















































////////////////////////* private methods *////////////////////////

// to print log message from MessageRecv class
void	MessageRecv::log(std::string const &logMsg)	const {
	std::cout << "\033[38;5;66m";
	std::cout << "MessageRecv : [\"" + _content + "\"] : ";
	std::cout << logMsg << std::endl;
	std::cout << "\033[m";
}

///////////////////////////////////////////////////////////////////
