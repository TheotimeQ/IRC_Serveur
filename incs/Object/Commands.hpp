/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:12:57 by tquere            #+#    #+#             */
/*   Updated: 2023/04/04 11:04:15 by zelinsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "../../incs/Object/A_Command.hpp"

#define RPL_AWAY                301
#define RPL_UNAWAY              305                     
#define RPL_NOWAWAY             306    
#define RPL_TOPIC               332
#define RPL_NAMREPLY            353
#define RPL_ENDOFNAMES          366
#define ERR_CANNOTSENDTOCHAN    404
#define ERR_WASNOSUCHNICK       406
#define ERR_TOOMANYTARGETS      407
#define ERR_NORECIPIENT         411     
#define ERR_NOTEXTTOSEND        412 

#define ERROR_BAD_FORMAT 	"Error: Bad format \n"

//=============================================TEST=================================================

class DEBUG_Command : public A_Command { 
    public:
        virtual void Execute(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager); };

//=====================================Connection Registration======================================

class PASS_Command : public A_Command { 
    public:
        virtual void Execute(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager); };

class NICK_Command : public A_Command { 
    public:
        virtual void Execute(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager); };

class USER_Command : public A_Command { 
    public:
        virtual void Execute(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager); };

class OPER_Command : public A_Command { 
    public:
        virtual void Execute(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager); };

//=====================================Channel operations======================================

class JOIN_Command : public A_Command { 
    public:
        virtual void Execute(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager); };

class PART_Command : public A_Command { 
    public:
        virtual void Execute(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager); };

class MODE_Command : public A_Command { 
    public:
        virtual void Execute(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager); };

class TOPIC_Command : public A_Command { 
    public:
        virtual void Execute(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager); };

class NAMES_Command : public A_Command { 
    public:
        virtual void Execute(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager); };

class LIST_Command : public A_Command { 
    public:
        virtual void Execute(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager); };

class INVITE_Command : public A_Command { 
    public:
        virtual void Execute(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager); };

class KICK_Command : public A_Command { 
    public:
        virtual void Execute(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager); };

//=====================================Sending messages======================================

class PRIVMSG_Command : public A_Command { 
    public:
        virtual void Execute(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager); };

class NOTICE_Command : public A_Command { 
    public:
        virtual void Execute(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager); };

class AWAY_Command : public A_Command { 
    public:
        virtual void Execute(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager); };

#endif