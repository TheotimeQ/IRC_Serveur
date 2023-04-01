/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/01 13:16:05 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

// ◦Vous devez pouvoir :
// - vous authentifier, 
// - définir un nickname, 
// - un username, re-
// - joindre un channel, 
// - envoyer et recevoir des messages privés, avec votre client de référence.

// ◦Tous les messages envoyés par un client dans un channel doivent être transmis
// à tous les clients ayant rejoint ce channel.

// ◦Vous devez avoir des operators et des utilisateurs basiques.

// ◦Vous devez donc implémenter les commandes spécifiques aux operators


// https://www.rfc-editor.org/rfc/rfc1459#section-6.2



//=====================================CMD A IMPLENTER======================================

// :SERVEUR_NAME CODE_NUMERIC ARGS \n"

//=====================================CMD A IMPLENTER======================================



//Authentification

    //NICK 
    //USER
    //PASS
    //OPER
    //MODE

//Nickname

    //WHOIS
    //NAMES
    //WHO

//Channel

    //JOIN
    //INVITE
    //LIST
    //PART
    //QUIT

//Envoyer un message prive

    //QUERY
    //MSG
    //NOTICE

//Operateur

    //MODE
    //KICK
    //BAN
    //UNBAN
    //INVITE
    //TOPIC
    //KILL
    //GLOBOPS
    //RESTART

//=====================================AUTHENTIFICATION======================================

//NICK
void  NICK_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
    // this->Send_Cmd(Client._Client_Socket,":IRC 001 Zel :BIENVENU SUR LE Server IRC\n ");
}

//USER
void  USER_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

//PASS
void  PASS_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

//OPER
void  OPER_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

//MODE
void  MODE_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

//=====================================NICKNAME======================================

//WHOIS
void  WHOIS_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

//NAMES
void  NAMES_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

//WHO
void  WHO_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

//=====================================CHANNEL======================================

//JOIN
void  JOIN_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

//INVITE
void  INVITE_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

//LIST
void  LIST_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

//PART
void  PART_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

//QUIT
void  QUIT_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

//=====================================PRIVATE_MSG======================================

//QUERY
void  QUERY_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

//MSG
void  MSG_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

//NOTICE
void  NOTICE_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

//=====================================OPERATOR======================================

//KICK
void  KICK_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

//BAN
void  BAN_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

//UNBAN
void  UNBAN_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

//TOPIC
void  TOPIC_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

//KILL
void  KILL_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

//GLOBOPS
void  GLOBOPS_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}

//RESTART
void  RESTART_Command::Execute(Client &Client, std::vector<std::string> Args, std::map<std::string, Channel>  Channels) 
{
    (void )Args;
    (void )Channels;
    (void )Client;
}