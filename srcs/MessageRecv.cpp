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

MessageRecv::MessageRecv() { log("[ERROR]"); } // private 

MessageRecv::~MessageRecv() { log("is destroyed"); }












































////////////////////////* private methods *////////////////////////

// to print log message from MessageRecv class
void	MessageRecv::log(std::string const &logMsg)	const {
	std::cout << "\033[38;5;66m";
	std::cout << "MessageRecv : [\"" + _content + "\"] : ";
	std::cout << logMsg << std::endl;
	std::cout << "\033[m";
}

///////////////////////////////////////////////////////////////////