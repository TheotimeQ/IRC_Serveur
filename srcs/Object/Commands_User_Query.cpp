/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_User_Query.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/02 12:02:19 by zelinsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//=====================================User-based queries======================================

// https://www.rfc-editor.org/rfc/rfc1459#section-4.5.1
void  WHO_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager Channel_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.5.2
void  WHOIS_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager Channel_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.5.3
void  WHOWAS_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager Channel_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client;
}
