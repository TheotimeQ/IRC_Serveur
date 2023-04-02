/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client_Manager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:32:08 by tquere            #+#    #+#             */
/*   Updated: 2023/04/02 14:46:50 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Manager/Client_Manager.hpp"
#include "../../incs/Object/Client.hpp"

Client_Manager::Client_Manager(): Nb_Clients(1)
{

    return;
}

Client_Manager::~Client_Manager()
{

	return;
}

Client &Client_Manager::Get_Client(int index)
{
    if (index >= Nb_Clients || index < 0)
    {
        std::cerr << ERROR_RTN_CLIENT << std::endl;
        return _Clients[0];
    }

	return _Clients[index];
}


int Client_Manager::Add_Client(Client Client)
{
    if (this->Nb_Clients >= MAX_CLIENTS)
    {
        std::cerr << ERROR_MAX_CLIENT << std::endl;
        return ERROR;
    }   
    
    _Clients[this->Nb_Clients - 1] = Client;
    this->Nb_Clients++;

	return GOOD;
}

int Client_Manager::Remove_Client(int index)
{
    if (index >= Nb_Clients || index < 0)
    {
        std::cerr << ERROR_RMV_CLIENT << std::endl;
        return ERROR;
    }

    _Clients[index] = _Clients[this->Nb_Clients - 1];
    this->Nb_Clients--;

	return GOOD;
}
