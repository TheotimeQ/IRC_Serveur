/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:12:57 by tquere            #+#    #+#             */
/*   Updated: 2023/04/02 12:03:45 by zelinsta         ###   ########.fr       */
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
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

//=====================================Connection Registration======================================

class PASS_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

class NICK_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

class USER_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

class OPER_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

class QUIT_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

//=====================================Channel operations======================================

class JOIN_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

class PART_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

class MODE_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

class TOPIC_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

class NAMES_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

class LIST_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

class INVITE_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

class KICK_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

//=====================================Server queries and commands======================================

class VERSION_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

class STATS_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

class ADMIN_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

class INFO_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };


//=====================================Sending messages======================================

class PRIVMSG_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

class NOTICE_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };


//=====================================User-based queries======================================

class WHO_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

class WHOIS_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

class WHOWAS_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };


//=====================================Miscellaneous messages======================================

class KILL_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

class PING_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

class PONG_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };

class ERROR_Command : public A_Command { 
    public:
        virtual void Execute(Client &Client, std::vector<std::string> Args,  ChannelManager Channel_Manager); };


#endif