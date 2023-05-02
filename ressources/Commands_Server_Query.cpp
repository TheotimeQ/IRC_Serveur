/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Server_Query.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/05/02 11:51:35 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//=====================================Server queries and commands======================================

// https://www.rfc-editor.org/rfc/rfc1459#section-4.3.1
void  VERSION_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;Channel_Manager, Client_Manager);
                //CHECK IF CAN LOG
            }
return GOOD;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.3.2
void  STATS_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;Channel_Manager, Client_Manager);
                //CHECK IF CAN LOG
            }
return GOOD;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.3.7
void  ADMIN_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;Channel_Manager, Client_Manager);
                //CHECK IF CAN LOG
            }
return GOOD;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.3.8
void  INFO_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;Channel_Manager, Client_Manager);
                //CHECK IF CAN LOG
            }
return GOOD;
}
