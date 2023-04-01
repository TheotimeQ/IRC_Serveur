/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/01 10:47:02 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

void  Join_Command::Execute(Client &Client, std::vector<std::string> Args) 
{
    (void )Args;
    std::cout << "JOIN command executed" << std::endl; 
    this->Send_Cmd(Client._Client_Socket,":IRC 001 Zel :BIENVENU SUR LE Server IRC\n ");
}

void  Kick_Command::Execute(Client &Client, std::vector<std::string> Args) 
{
    (void )Args;
    std::cout << "KICK command executed" << std::endl; 
    this->Send_Cmd(Client._Client_Socket,":IRC 001 Zel :BIENVENU SUR LE Server IRC\n ");
}

void  Nick_Command::Execute(Client &Client, std::vector<std::string> Args) 
{
    (void )Args;
    std::cout << "NICK command executed" << std::endl; 
    this->Send_Cmd(Client._Client_Socket,":IRC 001 Zel :BIENVENU SUR LE Server IRC\n ");
}

void  User_Command::Execute(Client &Client, std::vector<std::string> Args) 
{
    (void )Args;
    std::cout << "USER command executed" << std::endl; 
    this->Send_Cmd(Client._Client_Socket,":IRC 001 Zel :BIENVENU SUR LE Server IRC\n ");
}
