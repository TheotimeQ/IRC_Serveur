#include "../incs/Irc.hpp"
#include "../incs/Server.hpp"
#include "../incs/Client.hpp"

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