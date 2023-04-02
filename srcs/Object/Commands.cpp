/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/02 12:02:18 by zelinsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//=====================================TEST======================================

// https://www.rfc-editor.org/rfc/rfc1459#section-4.2.1
void  TEST_Command::Execute(Client &Client, std::vector<std::string> Args, ChannelManager Channel_Manager) 
{
    (void )Args;
    (void )Channel_Manager;

    // std::cout << Client << std::endl;

    this->Send_Cmd(Client._Client_Socket,":IRC 366 Zel #test :End of /NAMES list \n");
}
