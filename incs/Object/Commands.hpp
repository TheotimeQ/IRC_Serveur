/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:12:57 by tquere            #+#    #+#             */
/*   Updated: 2023/04/15 12:11:36 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "../../incs/Object/A_Command.hpp"

//=============================================TEST=================================================

class DEBUG_Command : public A_Command { 
    public:
        virtual void Execute(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager); };

class CAP_Command : public A_Command { 
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

class PART_Command : public A_Command 
{ 
    public:
        virtual void    Execute(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager);
        
	private:
		void		    leavingProcess(Client *Client, std::string const &channelName, ChannelManager &Channel_Manager, std::string &leavingMsg);
};

class MODE_Command : public A_Command 
{ 
    public:
        virtual void    Execute(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager);

	private :
		void			Exe_Channel_Info(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) const;
		void			Hub(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) const;
		void            Exe_Basic_Settings(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) const;
		void            Exe_Advanced_Settings(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) const;
		void            Exe_user_MODE(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) const;
		void            Exe_user_SET_MODE(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) const;
		void            Send_RPL_CHANNELMODEIS(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) const;
		void			Send_Solo_RPL_CHANNELMODEIS(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) const;
};

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
        virtual void Execute(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager); 
	private:
		void INVITE_user(Client *client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager);
		};

class KICK_Command : public A_Command { 
    public:
        virtual void Execute(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager); 
	private:
				void KICK_userList(Client *Client, ChannelManager &Channel_Manager, Client_Manager &Client_Manager, std::string const &channelName, std::vector<std::string> &users, std::string const &comment);
		};

class WHO_Command : public A_Command { 
    public:
        virtual void Execute(Client *Client, std::vector<std::string> Args,  ChannelManager &Channel_Manager, Client_Manager &Client_Manager); 
	private:
		void	Send_RPL_WHOREPLY(Client *client, Client const &who, std::vector<std::string> const &Args, ChannelManager &Channel_Manager);
};

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