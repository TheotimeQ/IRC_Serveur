/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client_Manager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:32:08 by tquere            #+#    #+#             */
/*   Updated: 2023/04/06 11:37:55 by zelinsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Manager/Client_Manager.hpp"
#include "../../incs/Object/Client.hpp"

Client_Manager::Client_Manager(): Nb_Clients(1)
{
    _All_Credentials["Zel"]     = "0000";
    _All_Credentials["Loup"]    = "1234";
    _All_Credentials["root"]    = "666";

    return;
}

Client_Manager::~Client_Manager()
{

	return;
}

std::string* Client_Manager::Get_Client_Pass(std::string NickName)
{
    std::map<std::string, std::string>::iterator it;
    
    for (it = _All_Credentials.begin(); it != _All_Credentials.end(); ++it)
    {
        if (it->first == NickName)
            return (&(it->second));
    }

    return NULL;
}

void Client_Manager::Check_Log(Client* Clt)
{
    if (Clt->UserName == "")
        return;

    std::string* Pass = this->Get_Client_Pass(Clt->NickName);

    if (Pass == NULL)
    {
        std::cout << ERROR_NICKNAME_UNKOW << Clt->NickName << std::endl;
        return;
    }
    if (Clt->Password == *Pass)
    {
        Clt->Logged = 1;
        std::cout << EVENT_LOGGED << Clt->NickName << std::endl;
    }
    else
        Clt->Logged = 0;
}

void Client_Manager::Print_Clients(void)
{
    std::vector<Client>::iterator it;
    
    for (it = _All_Clients.begin(); it != _All_Clients.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
}

Client *Client_Manager::Get_Client_by_fd(int fd)
{
    std::vector<Client>::iterator it;

    for (it = _All_Clients.begin(); it != _All_Clients.end(); ++it)
    {
        if ((*it).Socket == fd)
            return &(*it);
    }
	return NULL;
}

Client *Client_Manager::Get_Client(std::string NickName)
{
    std::vector<Client>::iterator it;

    for (it = _All_Clients.begin(); it != _All_Clients.end(); ++it)
    {
        if ((*it).NickName == NickName)
            return &(*it);
    }  
	return NULL;
}

int Client_Manager::Add_Client(const Client& Client)
{
    if (this->Nb_Clients >= MAX_CLIENTS)
    {
        std::cout << ERROR_MAX_CLIENT << std::endl;
        return ERROR;
    }   
    _All_Clients.push_back(Client);
    this->Nb_Clients++;
    
	return GOOD;
}

int Client_Manager::Remove_Client(const Client& Clt) 
{
    std::vector<Client>::iterator it;

    for (it = _All_Clients.begin(); it != _All_Clients.end(); ++it)
    {
        if ((*it).NickName == Clt.NickName)
        {
            _All_Clients.erase(it);
            return GOOD;
        }
    }

    std::cout << ERROR_DEL_CLIENT << std::endl;
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