#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <cerrno>

using namespace std;

const int MAX_CLIENTS = 10;
const int BUFFER_SIZE = 1024;

//doc irc : https://modern.ircdocs.horse/#errneedmoreparams-461
//doc irssi : https://irssi.org/documentation/

//Pour se connecter au serveur : 

// Install IRSSI
// sudo apt-get install irssi

// Lancer IRSSI
// irssi

// Se connecter au serveur en local
// /connect ::1 12345
// CMD      LOCAL -> 1    PORT -> 12345
//          Sinon ip

void send_message(int client_sock, const string& message) {
    int bytes_sent = send(client_sock, message.c_str(), message.size(), 0);
    if (bytes_sent == -1) {
        cerr << "Erreur d'envoi du message : \n" << strerror(errno) << endl;
    } else {
        cout << "Message envoyé au client : \n" << message << endl;
    }
}

int main()
{
    // Créer le socket serveur
    int server_sock = socket(AF_INET6, SOCK_STREAM, 0);
    if (server_sock < 0) {
        cerr << "Erreur lors de la création du socket serveur" << endl;
        exit(1);
    }

    // Configuration de l'adresse serveur
    struct sockaddr_in6 server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_addr = in6addr_any;

    //port 12345 pour le moment .. à choisir mieux ? 
    server_addr.sin6_port = htons(6667);

    // Activer la réutilisation de l'adresse et du port
    int yes = 1;
    if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        cerr << "Erreur lors de la configuration du socket : " << strerror(errno) << endl;
        return 1;
    }

    // Lier le socket serveur à l'adresse
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        cerr << "Erreur lors du bind du socket serveur" << endl;
        exit(1);
    }

    // Mettre le socket serveur en mode écoute
    if (listen(server_sock, MAX_CLIENTS) < 0) {
        cerr << "Erreur lors de la mise en écoute du socket serveur" << endl;
        exit(1);
    }

    // Initialiser la structure de poll ( permet d'ecouter plusieur fd en meme temps )
    struct pollfd poll_set[MAX_CLIENTS + 1];
    memset(poll_set, 0, sizeof(poll_set));
    poll_set[0].fd = server_sock;
    poll_set[0].events = POLLIN;
    int nfds = 1;


    while (true) {

        // Attente des événements
        int ret = poll(poll_set, nfds, -1);

        if (ret < 0) {
            cerr << "Erreur lors de la récupération des événements" << endl;
            break;
        }

        // Vérifier les événements pour chaque socket
        for (int i = 0; i < nfds; ++i) 
        {
            if (poll_set[i].revents & POLLIN) 
            {
                // Nouvelle connexion entrante
                if (i == 0) 
                {
                    struct sockaddr_in6 client_addr;
                    socklen_t client_addr_len = sizeof(client_addr);
                    int client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_len);
                    
                    if (client_sock < 0) 
                    {
                        cerr << "Erreur lors de l'acceptation de la connexion entrante" << endl;
                        break;
                    }
                    cout << "Nouvelle connexion entrante" << endl;

                    // Ajouter le nouveau socket à la liste des sockets surveillés
                    poll_set[nfds].fd = client_sock;
                    poll_set[nfds].events = POLLIN;
                    ++nfds;
                } 

                // Données reçues d'un client existant
                else {

                    int client_sock = poll_set[i].fd;
                    char buffer[BUFFER_SIZE];
                    int nbytes = recv(client_sock, buffer, BUFFER_SIZE, 0);

                    if (nbytes < 0) {
                        cerr << "Erreur lors de la réception de données du client" << endl;
                        break;
                    } 

                    // Client déconnecté
                    // Fermer le socket et supprimer de la liste des sockets surveillés
                    else if (nbytes == 0) 
                    {
                        cout << "Client déconnecté" << endl;
                        close(client_sock);
                        poll_set[i] = poll_set[nfds - 1];
                        memset(&poll_set[nfds - 1], 0, sizeof(poll_set[nfds - 1]));
                        --nfds;
                    }

                    // Données reçues avec succès
                    else 
                    {
                        cout << "Données reçues : \n" << buffer << endl;
                        if (strncmp(buffer, "JOIN",4) == 0)
                        {
                            send_message(client_sock,":IRC 332 Zel test :cannal_de_test\n");
                            send_message(client_sock,":IRC 353 Zel = test :Zel Jerem Tristan\n");
                            send_message(client_sock,":IRC 356 Zel test :cannal_de_test\n");                            
                        }
                        else
                            send_message(client_sock,":IRC 001 Zel :BIENVENU SUR LE SERVEUR IRC\n ");
                        
                    }
                } 
            }
        }
    }
    // Fermer le socket serveur
    close(server_sock);

    return 0;
}

//Connection :

//Si SSL 6697 -> .

//Si pas SSL 6667 -> 
// Client -> PASS password
// Client -> NICK nickname
// Client -> USER username hostname servername :realname
// Serveur -> :servername 001 nickname :Welcome to the Internet Relay Network nickname!user@host

// Données reçues : 
// CAP LS 302

// Données reçues : 
// PASS coucou

// Données reçues : 
// NICK Zel
// USER Zelinsta_User 0 * :realname
