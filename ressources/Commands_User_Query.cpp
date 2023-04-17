/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_User_Query.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/13 17:02:21 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//=====================================User-based queries======================================

// https://www.rfc-editor.org/rfc/rfc1459#section-4.5.1
void  WHO_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;Channel_Manager, Client_Manager);

            }
return GOOD;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.5.2
void  WHOIS_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;Channel_Manager, Client_Manager);
                //CHECK IF CAN LOG
            }
return GOOD;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.5.3
void  WHOWAS_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;Channel_Manager, Client_Manager);
                //CHECK IF CAN LOG
            }
return GOOD;
}
