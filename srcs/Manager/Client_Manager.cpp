/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client_Manager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:32:08 by tquere            #+#    #+#             */
/*   Updated: 2023/05/02 13:52:10 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Manager/Client_Manager.hpp"
#include "../../incs/Object/Client.hpp"
#include "../../incs/utils.hpp"
#include "../../incs/Object/Commands.hpp"

Client_Manager::Client_Manager(): 
    Nb_Clients(1)
{
    _Creds_Oper["Zel"]              = "0000";
    _Creds_Oper["Loup"]             = "1234";
    _Creds_Oper["Out"]              = "standing";

    return;
}

Client_Manager::~Client_Manager()
{
    for (std::vector<Client>::iterator it = _All_Clients.begin(); it != _All_Clients.end(); ++it)
    {
        close((*it).Socket);
    }
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
        log(EVENT_LOGGED + Clt->NickName);
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(RPL_WELCOME)  + " " + Clt->NickName + " :" + MSG_BIENVENU + "\n";
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
    if (this->Nb_Clients > MAX_CLIENTS)
    {
        log(ERROR_MAX_CLIENT);
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
            this->Nb_Clients--;
            return GOOD;
        }
    }

    log(ERROR_DEL_CLIENT);
    return ERROR;
}

void Client_Manager::Send_To_All(std::string Msg)
{
    std::vector<Client>::iterator it;

    for (it = _All_Clients.begin(); it != _All_Clients.end(); ++it)
    {
        Send_Cmd((it)->Socket, Msg);
    }
}

std::string* Client_Manager::Get_Oper_Pass(std::string NickName)
{
    std::map<std::string, std::string>::iterator it;

    for (it = _Creds_Oper.begin(); it != _Creds_Oper.end(); ++it)
    {
        if (it->first == NickName)
            return (&(it->second));
    }

    return NULL;
}

bool Client_Manager::Is_Client_Oper(std::string const &NickName)
{
    Client *Clt = this->Get_Client(NickName);
    if (Clt && Clt->Oper)
        return true;
    return false;
}

void Client_Manager::log(std::string const &logMsg)	const {
	std::cout << "\033[38;5;11m";
	std::cout << "Client_Manager      : " << logMsg << std::endl;
	std::cout << "\033[m";
}