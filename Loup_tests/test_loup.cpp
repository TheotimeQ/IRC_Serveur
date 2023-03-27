/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_loup.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 06:51:40 by loumarti          #+#    #+#             */
/*   Updated: 2023/03/27 08:46:14 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "testouni.hpp"

// c++ -Wall -Wextra -Werror -std=c++98 test_loup.cpp -o irc_test_loup && ./irc_test_loup



int main() {
int	catch_error;

// [1] creation du socket serveur
	int server_socket = socket(AF_INET6, SOCK_STREAM, 0);

	if (server_socket < 0) {
		// Si fail on a le msg erreure avec errno
		cerr << "ircserv : socket() error : " << strerror(errno) << endl;
		exit(1);
	} else {
		// Si success on a le file descriptor du socket
		cout << "server_socket fd = " << server_socket << endl;
	}
///////////////////////////////////////////////////////////////

// [2]-[0] configuration de l'addresse serveur - man linux IPV6
struct sockaddr_in6	server_addr;

bzero(&server_addr, sizeof(server_addr));
server_addr.sin6_family = AF_INET6; // toujours !
// To bind an AF_INET6 socket to any process, the local address
// should be copied from the in6addr_any variable
server_addr.sin6_addr = in6addr_any;
// NADDR_ANY value for IP address means 
// the server's IP address will be assigned automatically

// port reserve IRC : 6667 (6697 for tls)
// 
// The htons() function translates a short integer 
// from host byte order to network byte order
// Network byte order is big endian, or most significant byte first
server_addr.sin6_port = htons(12345);

// [2]-[1] Lier le socket_server (1) a l'adresse configuree (2)
// man bind -> example
catch_error = bind(server_socket, \
	reinterpret_cast<struct sockaddr *>(&server_addr), sizeof(server_addr));
if (catch_error < 0) {
	cerr << "ircserv : bind() error : " << strerror(errno) << endl;
	exit(1);
}

// [2]-[2] socket_server -> Listen mode
catch_error = listen(server_socket, MAX_CLIENTS);
if (catch_error < 0) {
	cerr << "ircserv : listen() error : " << strerror(errno) << endl;
	exit(1);
}
///////////////////////////////////////////////////////////////////////

// [3] Initialiser la structure de poll -> gerer ecoute multiples fd
// The set of file descriptors to be monitored is specified in the fds argument,
// which is an array of structures
struct pollfd poll_set[MAX_CLIENTS + 1];
bzero(poll_set, sizeof(poll_set));
poll_set[0].fd = server_socket;
poll_set[0].events = POLLIN; // ther is data to read
int nfds = 1; // index du prochain client a add au poll_set (l'index 0 est reserve au serveur)

while (1) {
	// poll block -> attente des events
	int ret = poll(poll_set, nfds, -1);

	if (ret < 0) {
		cerr << "ircserv : poll() error : " << strerror(errno) << endl;
		break ;
	}

	// verification des events pour chaque socket
	for (int i = 0; i < nfds; ++i) {
		if (poll_set[i].revents & POLLIN) {
			
			// Nouvelle connexion entrante
			if (i == 0) {
				struct sockaddr_in6	client_addr;
				socklen_t client_addr_len = sizeof(client_addr);
				int client_socket; // Le socket / fd du nouveau client

				client_socket = accept(server_socket, \
					reinterpret_cast<struct sockaddr *>(&client_addr), \
					&client_addr_len);
				if (client_socket < 0) {
					cerr << "ircserv : accept() error : " << strerror(errno) << endl;
					break ;
				} else {
					cout << "Nouvelle connection entrante client_socket = " << client_socket << endl;
				}

				// Ajout du nouveau socket au poll_set (le fd du nouveau client)
				poll_set[nfds].fd = client_socket;
				poll_set[nfds].events = POLLIN;
				++nfds; // index up pour prochain nouveau client
				
			} 
			// Donnees recu d'un client deja enregistre
			else {
				int client_socket = poll_set[i].fd;
				char buffer[BUFFER_SIZE];
				int nbytes = recv(client_socket, buffer, BUFFER_SIZE, 0);

				if (nbytes < 0) {
					cerr << "ircserv : recv() error : " << strerror(errno) << endl;
					break ;
				}
				
				// 0 bytes recu correpond a une deco du client (reception de eof)
				else if (nbytes == 0) {
					cout << "Deconnection du client_socket : " << client_socket << endl;
					close(client_socket); // [+] gestion erreur de close() ?
					// on ecrase ce client deco avec la valeur du dernier client du set
					poll_set[i] = poll_set[nfds - 1]; // anh ! c'est malin !
					bzero(&poll_set[nfds - 1], sizeof(poll_set[nfds - 1]));
					--nfds;
				} 
				
				// les bytes sont recus -> le client a besoin d'un channel a priori
				else {
					cout << "from " << poll_set[i].fd << " : " << buffer << endl;
				}
			}
		}
	}
}

	close(server_socket);

	return (0);
}





/*
man listen()
NOTES
       To accept connections, the following steps are performed:

           1.  A socket is created with socket(2).

           2.  The  socket  is  bound to a local address using bind(2), so that other sockets may be
               connect(2)ed to it.

           3.  A willingness to accept incoming connections and a queue limit for  incoming  connec‐
               tions are specified with listen().

           4.  Connections are accepted with accept(2).
*/