#include "../incs/Irc.hpp"
#include "../incs/Object/Server.hpp"
#include "../incs/Object/Client.hpp"

int check_port(const char *port)
{

    if (port == NULL) {
        return ERROR;
    }

    if (*port == '\0') {
        std::cerr << ERROR_PORT_EMPTY << port <<  std::endl;
        return ERROR;
    }

    errno = 0;
    long int num = strtol(port, NULL, 10);
	if (num < 0 || num > INT_MAX || errno == ERANGE) 
    {
		std::cerr << ERROR_PORT_MAX << std::endl;
		return ERROR;
	} 

    for (int i = 0; port[i] != '\0'; i++) {
        if (!isdigit(port[i])) 
        {
            std::cerr << ERROR_PORT_NO_DIGIT << ( port + i ) <<  std::endl;
            return ERROR;
        }
    }

	num = static_cast<int>(num); 
    if (num < 1 || num > 65535) {
        std::cerr << ERROR_PORT_RANGE << num << std::endl;
        return ERROR;
    }

    return GOOD;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        std::cerr << ERROR_SERVER_PARAM <<  std::endl;
        return 1;
    }

    if (check_port(argv[1])) 
        return 1;

    Server Serv = Server(SERVER_NAME, std::atoi(argv[1]), argv[2]);
    if (Serv.Start_Server())
        return ERROR;

    if (Serv.Run())
        return ERROR;

    Serv.Stop_Server();

    return (GOOD);
}

//TO DO

//LOUP 
// - Ajout commande Who
// - Finir les commandes sur le channel

//Theo
// - Remove client de toutes les channel a la sortie + prevenir tout le monde
// - Ajout commande Oper 
// - KICK .. etc (Commande operator)?
// - notice all user in channel on : MODE KICK PART QUIT             PRIVMSG NOTICE
// - [+] - avec netcat, si on envoie juste \n -> crash

//Celui qui a une idee
// - comment repondre a une commande entree avec un mauvais nom de chan, depuis un bon chan
//   et que la reponse parvienne ecrite dans le bon chan ||-> tracker le dernier chan utilise ?
// (oui c'est   s u p e r   clair ! ^_^)  ---> voir les  [!] dans JOIN

//JSP 
// - SEGFAULT SUR QUIT FAUTE DE LOUP
// - Faire des test avec plusieru client 
// - TEST BIG COMMANDE
// - Trouver un test comparatif avec un vrai serveur ?
// - Ajout d'un bot rapidos ?
// - Envoi de fichier 
// - Enlever les commentaire et clean les fichier pour le rendu 
// - Demander a un stud de nous le casser 
// - Rendre



















//    Once a user has joined a channel, they receive notice about all
//    commands their server receives which affect the channel.  This
//    includes MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE.  

//    JOIN command needs to be broadcast to all servers so that each server
//    knows where to find the users who are on the channel.  This allows
//    optimal delivery of PRIVMSG/NOTICE messages to the channel.

//    If a JOIN is successful, the user is then sent the channel's topic
//    (using RPL_TOPIC) and the list of users who are on the channel (using
//    RPL_NAMREPLY), which must include the user joining.


//CHANNEL MODE : 
// +m (modéré) : Ce mode restreint la capacité des utilisateurs à envoyer des messages dans le salon de discussion. Seuls les utilisateurs avec le statut d'opérateur ou de voix peuvent envoyer des messages, tandis que les autres utilisateurs ne peuvent que les lire.
// +n (aucun message externe) : Ce mode empêche les messages provenant d'utilisateurs qui ne sont pas dans le salon de discussion d'être affichés. Cela peut être utilisé pour éviter le spam ou les messages indésirables de la part d'utilisateurs externes.
// +s (secret) : Ce mode rend un salon de discussion invisible dans la liste des salons de discussion publics. Seuls les utilisateurs qui connaissent le nom du salon de discussion peuvent y accéder.
// +t (sujet restreint) : Ce mode empêche les utilisateurs normaux de modifier le sujet du salon de discussion. Seuls les opérateurs peuvent modifier le sujet.

//USER MODE
// +i (invisible) : Ce mode permet à un utilisateur de se cacher des autres utilisateurs, de sorte qu'il n'apparaît pas dans la liste des utilisateurs connectés à un salon de discussion (channel). Cela peut être utile pour éviter d'être dérangé ou pour observer discrètement une conversation.
// +w (muet) : Ce mode empêche un utilisateur de parler dans un salon de discussion. L'utilisateur ne peut pas envoyer de messages texte tant que ce mode est activé.
// +o (opérateur) : Ce mode accorde à un utilisateur les privilèges d'opérateur dans un salon de discussion. Les opérateurs ont généralement des pouvoirs spéciaux, tels que l'expulsion d'autres utilisateurs, la modification des paramètres du salon de discussion, etc.
// +v (voix) : Ce mode permet à un utilisateur de parler dans un salon de discussion même s'il est normalement muet. Cela peut être utile pour donner la parole à des utilisateurs spécifiques, même s'ils ne sont pas des opérateurs.
// +b (banni) : Ce mode interdit à un utilisateur d'accéder à un salon de discussion. L'utilisateur banni ne peut pas envoyer de messages dans le salon de discussion tant que le bannissement est en vigueur.


