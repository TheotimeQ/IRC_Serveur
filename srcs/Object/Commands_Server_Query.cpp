/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Server_Query.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/01 14:37:18 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//=====================================Server queries and commands======================================

// https://www.rfc-editor.org/rfc/rfc1459#section-4.3.1
void  VERSION_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.3.2
void  STATS_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.3.7
void  ADMIN_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.3.8
void  INFO_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}