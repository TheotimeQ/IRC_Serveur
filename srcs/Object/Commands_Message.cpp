/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Message.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/02 12:02:30 by zelinsta         ###   ########.fr       */
=======
/*   Updated: 2023/04/02 15:54:43 by tquere           ###   ########.fr       */
>>>>>>> refs/remotes/origin/master
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//=====================================Sending messages======================================

// https://www.rfc-editor.org/rfc/rfc1459#section-4.4.1
<<<<<<< HEAD
void  PRIVMSG_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager Channel_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
=======
void  PRIVMSG_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    // (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
>>>>>>> refs/remotes/origin/master
    (void )Client;

    std::cout << "Args : " << std::endl;;
    for (unsigned i = 0; i < Args.size(); ++i) {
        std::cout << "|" << Args[i].c_str() << "|" << std::endl;
    }
    std::cout << std::endl;

    // this->Send_Cmd(Client.Socket,":Zel!~a@localhost PRIVMSG Zel :yes I'm receiving it !receiving it ! \n");


}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.4.2
<<<<<<< HEAD
void  NOTICE_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager Channel_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
=======
void  NOTICE_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;
>>>>>>> refs/remotes/origin/master
    (void )Client;
}
