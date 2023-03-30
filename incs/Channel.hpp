/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:17:45 by loumarti          #+#    #+#             */
/*   Updated: 2023/03/29 13:30:50 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

/*
Utiliser votre client de référence avec votre serveur devra être similaire à
l’utiliser avec un serveur IRC officiel. Cependant, seules les fonctionnalités
suivantes sont obligatoires :

◦ Vous devez pouvoir vous authentifier, définir un nickname, un username, re-
joindre un channel, envoyer et recevoir des messages privés, avec votre client
de référence.

◦ Tous les messages envoyés par un client dans un channel doivent être transmis
  à tous les clients ayant rejoint ce channel.

◦ Vous devez avoir des operators et des utilisateurs basiques.

◦ Vous devez donc implémenter les commandes spécifiques aux operators
------------------------------------------------------------------------------------------
Channel : 
- Contient un liste d'instance de client connecté a la channel 
- le nom de la channel.. autres ? 
- Methode : 
Envoi d' un objet message à tout les clients connecté  ( Faudra bien definir l'objet message )
Une methode pour deconnecter un client de la channel 
Une methode pour ajouter un client à la channe

*/

class Channel {
	




};















#endif