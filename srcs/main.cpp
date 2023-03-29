#include "../incs/Irc.hpp"
#include "../incs/Server.hpp"
#include "../incs/Client.hpp"

#define SERVER_NAME "IRC"
#define SERVER_PORT 6667

int main(){

    Server Serv = Server(SERVER_NAME, SERVER_PORT);
    if (Serv.Start_Server())
        return ERROR;

    if (Serv.Run())
        return ERROR;

    Serv.Stop_Server();

    return (GOOD);
}