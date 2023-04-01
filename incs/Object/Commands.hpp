/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:12:57 by tquere            #+#    #+#             */
/*   Updated: 2023/04/01 13:13:19 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "../../incs/Object/A_Command.hpp"

//Authentification

    //NICK 
    //USER
    //PASS
    //OPER
    //MODE

//Nickname

    //NICK
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
    //OPER
    //KILL

    //GLOBOPS
    //RESTART

//=====================================AUTHENTIFICATION======================================

//NICK
class NICK_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};

//USER
class USER_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};

//PASS
class PASS_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};

//OPER
class OPER_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};

//MODE
class MODE_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};

//=====================================NICKNAME======================================

//WHOIS
class WHOIS_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};

//NAMES
class NAMES_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};

//WHO
class WHO_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};

//=====================================CHANNEL======================================

//JOIN
class JOIN_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};
//INVITE
class INVITE_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};

//LIST
class LIST_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};
//PART
class PART_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};

//QUIT
class QUIT_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};

//=====================================PRIVATE_MSG======================================

//QUERY
class QUERY_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};

//MSG
class MSG_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};

//NOTICE
class NOTICE_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};
//=====================================OPERATOR======================================

//KICK
class KICK_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};

//BAN
class BAN_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};

//UNBAN
class UNBAN_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};

//TOPIC
class TOPIC_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};

//KILL
class KILL_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};

//GLOBOPS
class GLOBOPS_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};
//RESTART
class RESTART_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels);
};

#endif