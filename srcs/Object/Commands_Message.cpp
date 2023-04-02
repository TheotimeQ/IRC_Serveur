/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Message.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/02 12:02:30 by zelinsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//=====================================Sending messages======================================

// https://www.rfc-editor.org/rfc/rfc1459#section-4.4.1
void  PRIVMSG_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager Channel_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client;

    this->Send_Cmd(Client._Client_Socket,":Zel!~a@localhost PRIVMSG Zel :yes I'm receiving it !receiving it ! \n");


}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.4.2
void  NOTICE_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager Channel_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client;
}
