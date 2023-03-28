#include "../incs/Irc.hpp"
#include "../incs/Serveur.hpp"
#include "../incs/Client.hpp"

#define SERVEUR_NAME "IRC"
#define SERVEUR_PORT 6667

int main(){

    Serveur Serv = Serveur(SERVEUR_NAME, SERVEUR_PORT);
    if (Serv.Start_Serveur())
        return ERROR;

    if (Serv.Run())
        return ERROR;

    Serv.stop_server();

    return (GOOD);
}