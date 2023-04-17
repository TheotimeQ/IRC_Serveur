/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/13 12:27:31 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//=====================================TEST======================================

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.1
void  DEBUG_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    Client_Manager.Print_Clients();

    std::string Msg = ":nick!user@hostname PRIVMSG #5 :Salut a tous\n";
    Send_Cmd(4, Msg);

    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
    (void )Client;
}


