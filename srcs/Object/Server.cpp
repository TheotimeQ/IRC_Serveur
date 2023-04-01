#include "../../incs/Irc.hpp"
#include "../../incs/Object/Server.hpp"
#include "../../incs/Object/Client.hpp"
#include "../../incs/Manager/Message_Manager.hpp"
#include "../../incs/Manager/ChannelManager.hpp"
#include "../../incs/Manager/Command_Manager.hpp"

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
    if (setsockopt(_Server_Socket, SOL_SOCKET, SO_REUSEADDR, &(yes), sizeof(int)) == -1) {
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

    // Command_Manager _CmdMng = Command_Manager();
    // Message_Manager _MsgMng = Message_Manager();
    // ChannelManager _ChnMng = ChannelManager();

    return GOOD;
}

int	Server::Run()
{
	// // [ajout de mes tests channel ici]
	// Client clientTest = Client();
	// log("channel list : ");
	// std::cout << _Chan_List << std::endl;
	
	// Try_Add_New_Channel("#SuperGenialChannel", clientTest);
	// Try_Add_New_Channel("#SuperGenialChannel", clientTest);
	// Try_Add_New_Channel("#SuperGenia:lChannel", clientTest);
	// Try_Add_New_Channel("#SuperGenialChannelEncorePlus", clientTest);
	// Try_Add_New_Channel("#CeChannelSpouerk", clientTest);
	// Try_Add_New_Channel("#ChannelLouche", clientTest);
	// Try_Add_New_Channel("#ChannelPourPervers", clientTest);
	// Try_Add_New_Channel("#Channel_musique_classique", clientTest);
	
	// std::cout << _Chan_List << std::endl;
	
	// Rm_Channel("#channel_inexistant");
	// Rm_Channel("#CeChannelSpouerk");
	
	// std::cout << _Chan_List << std::endl;
	// // [fin de mes tests channel]
	
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
                }
                //NEW DATA
                else 
                {
                    std::vector<std::string> Data;

                    if(this->Get_Data(_Poll_Set[i].fd, Data))
                        this->Deconnect_Client(i);
                    else
                        this->_CmdMng.Interpret_Data(Data, this->_Clients[i - 1]);
                    // std::cout << _Clients[i - 1] << std::endl;
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

    //Ferme le socket
    close(_Clients[index - 1]._Client_Socket);

    //Vire le client du poll
    _Poll_Set[index] = _Poll_Set[_Nb_Clients - 1];
    memset(&_Poll_Set[_Nb_Clients - 1], 0, sizeof(_Poll_Set[_Nb_Clients - 1]));

    //Vire le client de la liste des client
    _Clients[index - 1] = _Clients[_Nb_Clients - 2];
    // memset(&_Clients[_Nb_Clients - 2], 0, sizeof(Client));

    --_Nb_Clients;
}

int Server::Get_Data(int socket_fd, std::vector<std::string>& All_Data) 
{
    char            Buffer[BUFFER_SIZE];
    std::string     Data;
    ssize_t         Bytes;

    // Lecture du socket tant qu'il y a des données à lire
    while ((Bytes = recv(socket_fd, Buffer, BUFFER_SIZE, 0)) > 0) 
    {
        Data.append(Buffer, Bytes);                                                     // Ajout des données lues dans la chaîne de caractères
        size_t pos;

        while ((pos = Data.find("\n")) != std::string::npos && Data.length() != 0) {    // Recherche de la première occurrence de "\n"
            std::string ligne = Data.substr(0, pos);                                    // Extraction de la ligne
            All_Data.push_back(ligne);  
            Data.erase(0, pos + 1);                                                     // Suppression de la ligne lue de la chaîne de caractères
        }

        if (Bytes < BUFFER_SIZE)
            break;
    }

    // Client deconnecté
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

// to print log message from Server class
// void	Server::log(std::string const &logMsg)	const {
// 	std::cout << "\033[38;5;102m";
// 	std::cout << "Server : " + _Name + " : " << logMsg << std::endl;
// 	std::cout << "\033[m";
// }









































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

// std::ostream& operator<<(std::ostream &out, const t_mapChannel &ChanList) {
// 	t_mapChannel::const_iterator	it;
	
// 	it = ChanList.begin();
// 	while (it != ChanList.end()) {
// 		if (it != ChanList.begin())
// 			out << ", ";
// 		out << it->first;
// 		++it;
// 	}
// 	return (out);
// }
