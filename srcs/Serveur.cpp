#include "../incs/Irc.hpp"
#include "../incs/Serveur.hpp"
#include "../incs/Client.hpp"

Serveur::Serveur(const std::string& name, int port) : 
    _Name(name), 
    _Port(port)
{
	return;
}

Serveur::Serveur(const Serveur &other)
{
	*this = other;
}

Serveur& Serveur::operator=(const Serveur& other)
{
	if (this != &other) 
    {
		this->_Name = other._Name;
		this->_Port = other._Port;

		for (int i = 0; i < MAX_CLIENTS; i++) 
        	this->_Clients[i] = other._Clients[i];
	}
	return *this;
}

Serveur::~Serveur()
{
	return;
}

//-------------------Function--------------------
int	Serveur::Start_Serveur()
{
    _Serveur_Socket = socket(AF_INET6, SOCK_STREAM, 0);
    if (_Serveur_Socket < 0) {
        std::cerr << ERROR_SOCKET << std::endl;
        return ERROR;
    }

    memset(&_Server_Address, 0, sizeof(_Server_Address));
    _Server_Address.sin6_family = AF_INET6;
    _Server_Address.sin6_addr = in6addr_any; 
    _Server_Address.sin6_port = htons(_Port);

    int yes = 1;
    if (setsockopt(_Serveur_Socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        std::cerr << ERROR_CONF_SOCKET << strerror(errno) << std::endl;
        return ERROR;
    }

    if (bind(_Serveur_Socket, (struct sockaddr *)&_Server_Address, sizeof(_Server_Address)) < 0) {
        std::cerr << ERROR_BIND << std::endl;
        return ERROR;
    }

    if (listen(_Serveur_Socket, MAX_CLIENTS) < 0) {
        std::cerr << ERROR_LISTEN << std::endl;
        return ERROR;
    }

    memset(_Poll_Set, 0, sizeof(_Poll_Set));
    _Poll_Set[0].fd = _Serveur_Socket;
    _Poll_Set[0].events = POLLIN;
    _Last_Fd_index = 1;

    return GOOD;
}

int	Serveur::Run()
{
    while (true) 
    {
        int ret = poll(_Poll_Set, _Last_Fd_index, -1);
        if (ret < 0) {
            std::cerr << ERROR_POLL << std::endl;
            break;
        }

        for (int i = 0; i < _Last_Fd_index; ++i) 
        {
            if (_Poll_Set[i].revents & POLLIN) 
            {
                //NEW CLIENT
                if (i == 0) 
                {
                    struct sockaddr_in6 client_addr;
                    socklen_t client_addr_len = sizeof(client_addr);
                    int client_sock = accept(_Serveur_Socket, (struct sockaddr *)&client_addr, &client_addr_len);
                    if (client_sock < 0) 
                    {
                        std::cerr << ERROR_CONNECTION << std::endl;
                        break;
                    }
                    std::cout << EVENT_NEW_CLIENT << std::endl;

                    _Poll_Set[_Last_Fd_index].fd = client_sock;
                    _Poll_Set[_Last_Fd_index].events = POLLIN;
                    ++_Last_Fd_index;
                } 

                //New data from client
                else {

                    int client_sock = _Poll_Set[i].fd;
                    char buffer[BUFFER_SIZE];
                    int nbytes = recv(client_sock, buffer, BUFFER_SIZE, 0);

                    if (nbytes < 0) {
                        std::cerr << ERROR_DATA << std::endl;
                        break;
                    } 

                    else if (nbytes == 0) 
                    {
                        std::cout << EVENT_DECONNECTED << std::endl;
                        //Afficher qui leave
                        close(client_sock);
                        _Poll_Set[i] = _Poll_Set[_Last_Fd_index - 1];
                        memset(&_Poll_Set[_Last_Fd_index - 1], 0, sizeof(_Poll_Set[_Last_Fd_index - 1]));
                        --_Last_Fd_index;
                    }

                    else 
                    {
                        std::cout << EVENT_NEW_DATA << buffer << std::endl;
                        if (strncmp(buffer, "JOIN",4) == 0)
                        {
                            this->Send_Message(client_sock,":IRC 332 Zel test :cannal_de_test\n");
                            this->Send_Message(client_sock,":IRC 353 Zel = test :Zel Jerem Tristan\n");
                            this->Send_Message(client_sock,":IRC 356 Zel test :cannal_de_test\n");                            
                        }
                        else
                            this->Send_Message(client_sock,":IRC 001 Zel :BIENVENU SUR LE SERVEUR IRC\n ");
                        
                    }
                } 
            }
        }
    }
    return GOOD;
}

//Creer un objet message received
int	Serveur::New_Client()
{
    return GOOD;
}

//Creer un objet message received
int	Serveur::get_message()
{
    return GOOD;
}

//En fonction du l'objet message received , creer un objet message to send et l'envoi
int	Serveur::response()
{
    return GOOD;
}

int	Serveur::stop_server()
{
    close(_Serveur_Socket);
    return GOOD;
}

//A modifier pour prendre un objet message en parametre
int Serveur::Send_Message(int client_sock, const std::string& message) 
{
    int bytes_sent = send(client_sock, message.c_str(), message.size(), 0);
    if (bytes_sent == -1) {
        std::cerr << ERROR_SEND_MSG << strerror(errno) << std::endl;
        return ERROR;
    }
    std::cout << EVENT_NEW_MSG << message << std::endl;
    return GOOD;
}

//--------------------Getters--------------------
std::string Serveur::Get_Name(void) const
{
	return (this->_Name);
}

int Serveur::Get_Port(void) const
{
	return (this->_Port);
}

Client Serveur::Get_Clients(int index) const
{   
    // if (index < 0 || index > MAX_CLIENTS)
    //     return Client();
	return (this->_Clients[index]);
}

//--------------------Operator--------------------
std::ostream& operator<<(std::ostream &out, const Serveur &Serveur)
{
    std::cout << Serveur.Get_Name()      << std::endl;
	std::cout << Serveur.Get_Port()      << std::endl;
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        std::cout << Serveur.Get_Clients(i).Get_NickName() << std::endl;
    }
	return (out);
}

