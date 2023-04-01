/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/01 14:42:22 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//=====================================TEST======================================

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.1
void  TEST_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;

    std::cout << Client << std::endl;
}