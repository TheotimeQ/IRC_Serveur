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

// ---------------------------------------------------------------

// [!] SEGFAULT [!]
// - cas bizzarre :: si on ne compile PAS avec -fsanitize=address join puis quit un channel ==> SEGFAULT (QUIT seulement pas PART)


//LOUP 
// - regler le : #gogo They aren't on that channel --> message a mieux formater : HUm /'U_U'/
// - [+] le pb segfault avec QUIT sans fsanitize (voir au dessus)


// INVITE -> pb chanop chopOf() error
// NOTICE -> test avec netcat marchait pas + canTalk() valgrind error -> unitialazed values
// Pas de @Oper dans WHO 


// ---------------------------------------------------------------

//Theo
// - USER ajout recuperation hostname ?

// ---------------------------------------------------------------

//Nous deux quand on se verra avant de push
// - [+]Client->Oper >> prioritaire par rapport a >> canTalk() : ajouter condition canTalk() (on verra ensemble ca devrait etre rapide)
// - ajouter un slot Operator pour le correcteur (genre nickname : Outstanding - pass : giveme) ~> (")^_^'(")
// - Demander a un stud de nous le casser => on fait bosser un peu notre parain ? Aurel est ok avec nos Commandes
// - Enlever les commentaire ([!][?] debug checking) et clean les fichiers pour le rendu 
// - Rendre



// ---------------------------------------------------------------

// *** petits bugs ~ Anomalies ~ a reparer ou assumer ***
// Dans un channel +m (modere), hexchat permet d'ecrire mais ce n'est pas envoye aux autres users du channel
// HexChat choppe des sauts de ligne dans le 'home' 
// Privmsg ajoute un : , mais pas notice
// On peut envoyer des message à des gens pas log, ils ne peuvent pas reponbdre


// ---------------------------------------------------------------

//Implementation fontionnelles
// \O-O) JE ferais ce doc sur papier pour les correcteurs \O-O)


// - USER
//         USER <username> <hostname> <servername> <realname>
// - NICK
//         NICK <nickname>
// - QUIT
//         QUIT [<quit message>]
// - PASS
//         PASS <password>
// - CAP 
//         CAP <subcommand> [<subcommand parameters>]   ( Pas géré , CAP LS + CAP END )
// - PRIVMSG
//         PRIVMSG <receiver>{,<receiver>} <text to be sent>
// - NOTICE
//         NOTICE <receiver>{,<receiver>} <text to be sent>
// - OPER
//         OPER <name> <password>
// - AWAY 
//         AWAY [<message>]


// - TOPIC
//         TOPIC <channel> [<topic>]
// - WHO || NAMES
//         WHO [<mask>[,<mask>...]]         Mask ?? c'est #channelName
//         On fait pas un vrai WHO, on utilise les RPL NAMES c'est hybride-custom-hexchat
//         
// - JOIN
//         JOIN <channel> <*key>    Key ?? --> oui si le chan est en mode +k
//         mon join ne fais qu'un seul channel a la fois en argt
// - MODE
//         MODE <channel/user> <mode> [<mode parameters>]
// - PART
//         PART <channel>{,<channel>} [<part message>]
// - KICK
//         KICK <channel>{,<channel>} <user>{,<user>} [<comment>]
// - LIST 
//        LIST          ---> pas d'args [<channel>{,<channel>}] [<target>]

// Mode implémentés

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

// ---------------------------------------------------------------


