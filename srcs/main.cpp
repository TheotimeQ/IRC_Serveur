#include "../incs/Irc.hpp"
#include "../incs/Object/Server.hpp"
#include "../incs/Object/Client.hpp"

int main(){

    Server Serv = Server(SERVER_NAME, SERVER_PORT);
    if (Serv.Start_Server())
        return ERROR;

    if (Serv.Run())
        return ERROR;

    Serv.Stop_Server();

    return (GOOD);
}

//http://chi.cs.uchicago.edu/chirc/irc_examples.html
//https://dd.ircdocs.horse/refs/commands/join
//https://dd.ircdocs.horse/refs/commands/