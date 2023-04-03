/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:50:43 by tquere            #+#    #+#             */
/*   Updated: 2023/04/03 16:03:03 by zelinsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Irc.hpp"
#include "../../incs/Object/Server.hpp"
#include "../../incs/Object/Client.hpp"
#include "../../incs/Manager/ChannelManager.hpp"
#include "../../incs/Manager/Command_Manager.hpp"
#include "../../incs/Manager/Client_Manager.hpp"

Server::Server(const std::string& name, int port) : 
    _Name(name), 
    _Port(port)
{
	return;
}

Server::~Server()
{
	return;
}

int	Server::Start_Server()
{
    _Server_Socket = socket(AF_INET6, SOCK_STREAM, 0);
    if (_Server_Socket < 0) {
        std::cout << ERROR_SOCKET << std::endl;
        return ERROR;
    }

    memset(&_Server_Address, 0, sizeof(_Server_Address));
    _Server_Address.sin6_family = AF_INET6;
    _Server_Address.sin6_addr = in6addr_any; 
    _Server_Address.sin6_port = htons(_Port);

    int yes = 1;
    if (setsockopt(_Server_Socket, SOL_SOCKET, SO_REUSEADDR, &(yes), sizeof(int)) == -1) {
        std::cout << ERROR_CONF_SOCKET << strerror(errno) << std::endl;
        return ERROR;
    }

    if (bind(_Server_Socket, (struct sockaddr *)&_Server_Address, sizeof(_Server_Address)) < 0) {
        std::cout << ERROR_BIND << std::endl;
        return ERROR;
    }

    if (listen(_Server_Socket, MAX_CLIENTS) < 0) {
        std::cout << ERROR_LISTEN << std::endl;
        return ERROR;
    }

    memset(_Poll_Set, 0, sizeof(_Poll_Set));
    _Poll_Set[0].fd = _Server_Socket;
    _Poll_Set[0].events = POLLIN;

    return GOOD;
}

int	Server::Run()
{
    int ret = 0;

    while (true) 
    {
        int ret = poll(_Poll_Set, _CltMng.Nb_Clients, -1);
        if (ret < 0) 
        {
            std::cout << ERROR_POLL << std::endl;
            break;
        }

        for (int i = 0; i < _CltMng.Nb_Clients; ++i) 
        {
            if (_Poll_Set[i].revents & POLLIN) 
            {   
                if (i == 0) 
                {   
                    if (this->Setup_Client(Client(_Server_Socket)))
                        break;
                }
                else 
                {
                    Client *Cur_Client = _CltMng.Get_Client_by_fd(_Poll_Set[i].fd);
                    if (!Cur_Client)
                        break;
                        
                    if(this->Get_Data(Cur_Client))
                        this->Deconnect_Client((*Cur_Client), i);
                    else
                        ret = this->_CmdMng.Interpret_Data(Cur_Client, _ChnMng, _CltMng);
                        
                    if (ret == QUIT)
                        this->Deconnect_Client((*Cur_Client), i);
                }
            }
        }
    }
    return ret;
}

int Server::Setup_Client(const Client& Client)
{    
    if (Client.Socket < 0) 
    {
        std::cout << ERROR_CONNECTION << std::endl;
        return ERROR;
    }

    if (_CltMng.Add_Client(Client))
        return ERROR;

    _Poll_Set[_CltMng.Nb_Clients - 1].fd = Client.Socket;
    _Poll_Set[_CltMng.Nb_Clients - 1].events = POLLIN;
    
    std::cout << EVENT_NEW_CLIENT << std::endl;

    return GOOD;
}

void Server::Deconnect_Client(const Client &Client, int index)
{
    std::cout << EVENT_DECONNECTED << Client.NickName << std::endl;

    close(Client.Socket);

    _Poll_Set[index] = _Poll_Set[_CltMng.Nb_Clients - 1];
    memset(&_Poll_Set[_CltMng.Nb_Clients - 1], 0, sizeof(_Poll_Set[_CltMng.Nb_Clients - 1]));

    _CltMng.Remove_Client(Client);
}

int Server::Get_Data(Client *Client) 
{
    char        Buffer[BUFFER_SIZE];  
    size_t      Bytes;

    (*Client).All_Cmd.clear();

    while ((Bytes = recv((*Client).Socket, Buffer, BUFFER_SIZE, 0)) > 0) 
    {
        (*Client).Data.append(Buffer, Bytes);                                                            
        size_t pos;

        while ((pos = (*Client).Data.find("\n")) != std::string::npos)
        {
            std::string ligne = (*Client).Data.substr(0, pos);                                            
            (*Client).All_Cmd.push_back(ligne);  
            (*Client).Data.erase(0, pos + 1);                                                             
        }

        if (Bytes < BUFFER_SIZE)
            break;
    }

    if (Bytes == 0) {
        return ERROR;
    }
    
    return GOOD;
}

int	Server::Stop_Server()
{
    close(_Server_Socket);
    return GOOD;
}
