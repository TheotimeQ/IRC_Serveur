/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Registration.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/14 11:22:50 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//=====================================Connection Registration======================================

// https://www.rfc-editor.org/rfc/rfc1459#section-4.1.1
void  PASS_Command::Execute(Client *Clt, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{        
    
    (void )Channel_Manager;
    (void )Client_Manager;

    // ERR_NEEDMOREPARAMS              
    if (Args.size() < 2 || Args[1] == "")
    {
        Log("PASS",ERROR_BAD_FORMAT);
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_NEEDMOREPARAM) + " " + Clt->NickName + " " + Args[0] + " :Not enough parameters" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }
    
    // ERR_ALREADYREGISTRED
    if (Clt->Logged == 1)
    {
        Log("PASS",ERROR_PASS_ALREADY_SET);
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_ALREADYREGISTRED) + " " + Clt->NickName + " :You may not reregister" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }

    Clt->Password = Args[1];
}

//https://www.rfc-editor.org/rfc/rfc1459#section-4.1.2
void  NICK_Command::Execute(Client *Clt, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{

    (void) Channel_Manager;
    (void) Client_Manager;
       
    // ERR_NONICKNAMEGIVEN      
    if (Args.size() < 2 || Args[1] == "")
    {
        Log("NICK",ERROR_BAD_FORMAT);
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_NONICKNAMEGIVEN) + " " + Clt->NickName + " :No nickname given   " + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }

    // ERR_NICKNAMEINUSE
    if (Client_Manager.Get_Client(Args[1]) != NULL)
    {
        Log("NICK",ERROR_NICKNAME_ALREADY_USED);
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_NICKNAMEINUSE) + " " + Clt->NickName + " " + Args[1] + " :Nickname is already in use" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }

    // ERR_ERRONEUSNICKNAME
    if (Is_Valide_Nick(Args[1]))
    {
        Log("NICK",ERROR_NICKNAME_BAD_FORMAT);
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_NICKNAMEINUSE) + " " + Clt->NickName + " " + Args[1] + " :Erroneus nickname" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;      
    }

    //NOT USED -> Its for server to server communication
    // ERR_NICKCOLLISION
    // "<nick> :Nickname collision KILL"

    Log("NICK","changing nickname from " + Clt->NickName + " to " + Args[1]);
    std::string Msg = ":"+ Clt->NickName + " NICK " + Args[1] + "\n";
    Clt->NickName = Args[1];
    Client_Manager.Send_To_All(Msg);
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.1.3
void  USER_Command::Execute(Client *Clt, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    
    (void )Channel_Manager;
    (void )Client_Manager;

    // ERR_NEEDMOREPARAMS              
    if (Args.size() < 2 || Args[1] == "")
    {
        Log("USER",ERROR_BAD_FORMAT);
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_NEEDMOREPARAM) + " " + Clt->NickName + " " + Args[0] + " :Not enough parameters" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }

    // ERR_ALREADYREGISTRED
    if (Clt->Logged == 1)
    {
        Log("USER",ERROR_USER_ALREADY_SET);
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_ALREADYREGISTRED) + " " + Clt->NickName + " :You may not reregister" + "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }
    
    Log("NICK","changing username from " + Clt->UserName + " to " + Args[1]);
    Clt->UserName = Args[1];
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.1.5
void  OPER_Command::Execute(Client *Clt, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{              

    (void )Channel_Manager;
    (void )Client_Manager;

    // ERR_NEEDMOREPARAMS              
    if (Args.size() < 2 || Args[1] == "")
    {
        Log("OPER",ERROR_BAD_FORMAT);
        std::string Msg = "\n";
        Send_Cmd(Clt->Socket, Msg);
        return ;
    }

    //Si deja operateur 
    // RPL_YOUREOPER
    if (Clt->Oper == 1)
    {
        Log("OPER",ERROR_BAD_FORMAT);
        std::string Msg = "\n";
        Send_Cmd(Clt->Socket, Msg);
    }

    //Si wrong password 
    // ERR_PASSWDMISMATCH

    //Si pas d'user set 
    // ERR_NOOPERHOST       






    //    Command: OPER
    //    Parameters: <user> <password>

    //    OPER message is used by a normal user to obtain operator privileges.
    //    The combination of <user> and <password> are required to gain
    //    Operator privileges.

    //    If the client sending the OPER command supplies the correct password
    //    for the given user, the server then informs the rest of the network
    //    of the new operator by issuing a "MODE +o" for the clients nickname.

    //    The OPER message is client-server only.

    //    Numeric Replies:

    //            ERR_NEEDMOREPARAMS              RPL_YOUREOPER
    //            ERR_NOOPERHOST                  ERR_PASSWDMISMATCH

    //    Example:

    //    OPER foo bar                    ; Attempt to register as an operator
    //                                    using a username of "foo" and "bar" as
    //                                    the password.

}

void  CAP_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void )Args;
    (void )Channel_Manager;
    (void )Client_Manager;

    if (Args.size() >= 2)
    {
        if (Args[1] == "LS")
        {
            Log("CAP ","Sending cap response");
            std::string Msg = ":" + std::string(SERVER_NAME) + " " + Client->NickName + " CAP * LS : None " "\n";
            Send_Cmd(Client->Socket, Msg);
            Client->Cap_End = 0;
        }
        if (Args[1] == "END")
        {
            Log("CAP ","Ended cap exchange");
            Client->Cap_End = 1;
        }
    }
}


