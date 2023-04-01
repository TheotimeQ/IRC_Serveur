/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Miscellaneous.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/01 14:12:55 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//=====================================Miscellaneous messages======================================

// https://www.rfc-editor.org/rfc/rfc1459#section-4.6.1
void  KILL_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.6.2
void  PING_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.6.3
void  PONG_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.6.4
void  ERROR_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}



