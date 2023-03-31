/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MsgManager.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:45:57 by loumarti          #+#    #+#             */
/*   Updated: 2023/03/31 11:30:40 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "MsgManager.hpp"



/* ~~~~~~~~~~~~~~~~~~~~~~~ private methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
// to print log message from MsgManager class
void	Message::log(std::string const &logMsg)	const {
	std::cout << "\033[38;5;64m";
	std::cout << "MsgManager : ";
	std::cout << logMsg << std::endl;
	std::cout << "\033[m";
}

