/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client_Manager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:32:08 by tquere            #+#    #+#             */
/*   Updated: 2023/04/12 11:00:41 by zelinsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Manager/Client_Manager.hpp"
#include "../../incs/Object/Client.hpp"
#include "../../incs/utils.hpp"
#include "../../incs/Object/Commands.hpp"

Client_Manager::Client_Manager(): 
    Nb_Clients(1)
{
    return;
}

Client_Manager::~Client_Manager()
{

	return;
}

void Client_Manager::Set_Password(std::string &password)
{
    _Password = password;
}

void Client_Manager::Check_Log(Client* Clt)
{
    if (Clt->UserName == "")
        return;

    if (Clt->NickName == "")
        return;

    if (Clt->Cap_End != 1)
        return;

    if (Clt->Password == this->_Password)
    {
        Clt->Logged = 1;
        std::cout << EVENT_LOGGED << Clt->NickName << std::endl;
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(RPL_WELCOME)  + " " + Clt->NickName + " :BIENVENU SUR LE SERVEUR IRC" + "\n";
        Send_Cmd(Clt->Socket, Msg);
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
