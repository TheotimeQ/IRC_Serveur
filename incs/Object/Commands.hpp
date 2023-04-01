/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:12:57 by tquere            #+#    #+#             */
/*   Updated: 2023/04/01 15:41:24 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "../../incs/Object/A_Command.hpp"

#define RPL_TOPIC       332
#define RPL_NAMREPLY    353
#define RPL_ENDOFNAMES  366

//=============================================TEST=================================================

class TEST_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

//=====================================Connection Registration======================================

class PASS_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

class NICK_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

class USER_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

class OPER_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

class QUIT_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

//=====================================Channel operations======================================

class JOIN_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

class PART_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

class MODE_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

class TOPIC_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

class NAMES_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

class LIST_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

class INVITE_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

class KICK_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

//=====================================Server queries and commands======================================

class VERSION_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

class STATS_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

class ADMIN_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

class INFO_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };


//=====================================Sending messages======================================

class PRIVMSG_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

class NOTICE_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };


//=====================================User-based queries======================================

class WHO_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

class WHOIS_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

class WHOWAS_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };


//=====================================Miscellaneous messages======================================

class KILL_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

class PING_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

class PONG_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };

class ERROR_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  std::map<std::string, Channel>  Channels); };


#endif