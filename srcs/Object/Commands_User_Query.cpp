/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_User_Query.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/01 14:17:52 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//=====================================User-based queries======================================

// https://www.rfc-editor.org/rfc/rfc1459#section-4.5.1
void  WHO_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.5.2
void  WHOIS_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.5.3
void  WHOWAS_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}
