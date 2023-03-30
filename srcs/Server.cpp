#include "../incs/Irc.hpp"
#include "../incs/Server.hpp"
#include "../incs/Client.hpp"

Server::Server(const std::string& name, int port) : 
    _Name(name), 
    _Port(port),
    _Nb_Clients(1)
{
	return;
}

Server::~Server()
{
	return;
}

//-------------------Function--------------------
int	Server::Start_Server()
{
    _Server_Socket = socket(AF_INET6, SOCK_STREAM, 0);
    if (_Server_Socket < 0) {
        std::cerr << ERROR_SOCKET << std::endl;
        return ERROR;
    }

    memset(&_Server_Address, 0, sizeof(_Server_Address));
    _Server_Address.sin6_family = AF_INET6;
    _Server_Address.sin6_addr = in6addr_any; 
    _Server_Address.sin6_port = htons(_Port);

    int yes = 1;
    if (setsockopt(_Server_Socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        std::cerr << ERROR_CONF_SOCKET << strerror(errno) << std::endl;
        return ERROR;
    }

    if (bind(_Server_Socket, (struct sockaddr *)&_Server_Address, sizeof(_Server_Address)) < 0) {
        std::cerr << ERROR_BIND << std::endl;
        return ERROR;
    }

    if (listen(_Server_Socket, MAX_CLIENTS) < 0) {
        std::cerr << ERROR_LISTEN << std::endl;
        return ERROR;
    }

    memset(_Poll_Set, 0, sizeof(_Poll_Set));
    _Poll_Set[0].fd = _Server_Socket;
    _Poll_Set[0].events = POLLIN;
    _Nb_Clients = 1;

    return GOOD;
}

int	Server::Run()
{
    while (true) 
    {
        //Update le pollset
        int ret = poll(_Poll_Set, _Nb_Clients, -1);
        if (ret < 0) 
        {
            std::cerr << ERROR_POLL << std::endl;
            break;
        }

        //Pour chaque client dans le poll, regarde si on a un nouvell event
        for (int i = 0; i < _Nb_Clients; ++i) 
        {
            if (_Poll_Set[i].revents & POLLIN) 
            {
                //NEW CLIENT
                if (i == 0) 
                {   
                    if (this->Setup_Client(Client(_Server_Socket)))
                        break;
                    _Clients[_Nb_Clients - 2].Set_UserName("ROBERT");
                    std::cout << *this << std::endl;
                }
                //FONCTION NEW DATA
                else 
                {
                    //GET DATA
                    int client_sock = _Poll_Set[i].fd;
                    char buffer[BUFFER_SIZE];
                    int nbytes = recv(client_sock, buffer, BUFFER_SIZE, 0);
                    if (nbytes < 0) {
                        std::cerr << ERROR_DATA << std::endl;
                        break;
                    } 
                    //DECONECTE CLIENT
                    else if (nbytes == 0) 
                    {
                        this->Deconnect_Client(i);
                    }
                    //INTERPRETE DATA
                    else 
                    {
                        this->Get_Msg(buffer);
                        this->Interpret_Message();
                        this->Send_Response();
                    }
                } 
            }
        }
    }
    return GOOD;
}

//Setup le client et l'ajoute au poll si la creation du socket fonctionne
int Server::Setup_Client(Client Client)
{
    //Verifie qu'on a pas atteint le max de client
    if (_Nb_Clients >= MAX_CLIENTS)
    {
        std::cerr << ERROR_MAX_CLIENT << std::endl;
        return ERROR;
    }       
    
    //Ajoute le socket au poll set
    if (Client._Client_Socket < 0) 
    {
        std::cerr << ERROR_CONNECTION << std::endl;
        return ERROR;
    }
    std::cout << EVENT_NEW_CLIENT << std::endl;
    _Poll_Set[_Nb_Clients].fd = Client._Client_Socket;
    _Poll_Set[_Nb_Clients].events = POLLIN;

    //Ajouter le client à la liste des client sur le Server 
    _Clients[_Nb_Clients - 1] = Client;
    
    ++_Nb_Clients;

    return GOOD;
}

void Server::Deconnect_Client(int index)
{
    std::cout << EVENT_DECONNECTED << _Clients[index - 1].Get_UserName() << std::endl;
    close(_Clients[index - 1]._Client_Socket);

    //Vire le client du poll
    _Poll_Set[index] = _Poll_Set[_Nb_Clients - 1];
    memset(&_Poll_Set[_Nb_Clients - 1], 0, sizeof(_Poll_Set[_Nb_Clients - 1]));

    //Vire le client de la liste des client
    _Clients[index - 1] = _Clients[_Nb_Clients - 2];
    // memset(&_Clients[_Nb_Clients - 2], 0, sizeof(Client));

    --_Nb_Clients;
}

void Server::Get_Msg(char *buffer)
{
    std::cout << EVENT_NEW_DATA << buffer << std::endl;
    //CREER UN OBJET MESSAGE RECEIVED 

    // return Message_Received;
}

void Server::Interpret_Message(void)
{
    //QUIT

    //JOIN

    //....ETC
}

void Server::Send_Response(void)
{
    // SEND LE MESSAGE 
    // if (strncmp(buffer, "JOIN",4) == 0)
    // {
    //     this->Send_Message(client_sock,":IRC 332 Zel test :cannal_de_test\n");
    //     this->Send_Message(client_sock,":IRC 353 Zel = test :Zel Jerem Tristan\n");
    //     this->Send_Message(client_sock,":IRC 356 Zel test :cannal_de_test\n");                            
    // }
    // else
    //     this->Send_Message(client_sock,":IRC 001 Zel :BIENVENU SUR LE Server IRC\n ");
}









//Recois le message du client

//Fais les action necessaire (change de channel , change le nickanme , les droit..)

//Envoi le message de reponse
    //Si repond juste au client -> creer la reponse

    //Si channel a toute une channel -> appel la methode send to all channel de la channel et lui passe le type de message 














// //Creer un objet message received
// int	Server::Get_Message()
// {
//     return GOOD;
// }

// //En fonction du l'objet message received , creer un objet message to send et l'envoi
// int	Server::Response()
// {
//     return GOOD;
// }

int	Server::Stop_Server()
{
    close(_Server_Socket);
    return GOOD;
}

//A modifier pour prendre un objet message en parametre
int Server::Send_Message(int client_sock, const std::string& message) 
{
    int bytes_sent = send(client_sock, message.c_str(), message.size(), 0);
    if (bytes_sent == -1) 
    {
        std::cerr << ERROR_SEND_MSG << strerror(errno) << std::endl;
        return ERROR;
    }
    std::cout << EVENT_NEW_MSG << message << std::endl;
    return GOOD;
}







//--------------------Getters--------------------
std::string Server::Get_Name(void) const
{
	return (this->_Name);
}

int Server::Get_Port(void) const
{
	return (this->_Port);
}

Client Server::Get_Clients(int index) const
{   
    // if (index < 0 || index > MAX_CLIENTS)
    //     return Client();
	return (this->_Clients[index]);
}

int Server::Get_Nb_Client() const
{   
	return (this->_Nb_Clients);
}







//--------------------Operator--------------------
std::ostream& operator<<(std::ostream &out, const Server &Server)
{
    out << Server.Get_Name()      << std::endl;
	out << Server.Get_Port()      << std::endl;
    for (int i = 0; i < Server.Get_Nb_Client() - 1; i++)
    {
        out << Server.Get_Clients(i).Get_UserName() << " | " << Server.Get_Clients(i)._Client_Socket << std::endl;
    }
	return (out);
}

