/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client_Manager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:32:08 by tquere            #+#    #+#             */
/*   Updated: 2023/04/02 16:44:53 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Manager/Client_Manager.hpp"
#include "../../incs/Object/Client.hpp"

Client_Manager::Client_Manager(): Nb_Clients(1)
{
    _All_Credentials["Zel"]     = "0000";
    _All_Credentials["Loup"]    = "1234";

    return;
}

Client_Manager::~Client_Manager()
{

	return;
}

void Client_Manager::Print_Clients(void)
{
    std::map<std::string, Client>::iterator it;
    
    for (it = _All_Clients.begin(); it != _All_Clients.end(); ++it)
    {
        std::cout << it->second << std::endl;
    }
}

Client &Client_Manager::Get_Client_by_fd(int fd)
{
    std::map<std::string, Client>::iterator it;
    
    for (it = _All_Clients.begin(); it != _All_Clients.end(); ++it) 
    {
        if ((it->second).Socket == fd)
            return (it->second);
    }
    std::cerr << ERROR_FID_CLIENT << fd << std::endl;
	return _All_Clients.begin()->second;
}

Client &Client_Manager::Get_Client(std::string NickName)
{
    std::map<std::string, Client>::iterator it;
    
    for (it = _All_Clients.begin(); it != _All_Clients.end(); ++it) 
    {
        if ((it->second).NickName == NickName)
            return (it->second);
    }
    std::cerr << ERROR_FID_CLIENT << NickName << std::endl;
	return _All_Clients.begin()->second;
}

int Client_Manager::Add_Client(const Client& Client)
{
    if (this->Nb_Clients >= MAX_CLIENTS)
    {
        std::cerr << ERROR_MAX_CLIENT << std::endl;
        return ERROR;
    }   

    _All_Clients[Client.NickName] = Client;
    this->Nb_Clients++;

    this->Print_Clients();

	return GOOD;
}

int Client_Manager::Remove_Client(const Client& Clt) 
{
    std::map<std::string, Client>::iterator it = _All_Clients.find(Clt.NickName);

    if (it != _All_Clients.end()) {
        _All_Clients.erase(it);
        return GOOD;
    }
    std::cerr << ERROR_DEL_CLIENT << std::endl;
    return ERROR;
}




//Regarde si le client peut etre logge
int Client_Manager::Check_If_Can_Log(const Client& Client) 
{
    (void)Client;

    //Verifie si on conais le nickname
    return ERROR;

    //Verifie si bon mdp
    return ERROR;

    //Verifie si username a ete set
    return ERROR;
    
    return GOOD;
}