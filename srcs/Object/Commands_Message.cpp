/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Message.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/13 14:23:04 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

//=====================================Sending messages======================================

// https://www.rfc-editor.org/rfc/rfc1459#section-4.4.1
void  PRIVMSG_Command::Execute(Client *From_Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    //Pas de destinataire
    if (Args.size() == 1)
    {
        std::string Msg = ":" + std::string(SERVER_NAME) + " "  + I_To_S(ERR_NORECIPIENT) + " " + From_Client->NickName + " " + ":No recipient given " + Args[0] + "\n";
        Send_Cmd(From_Client->Socket, Msg);
        return ;
    }
    
    //Pas de message
    if (Args.size() == 2)
    {
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_NOTEXTTOSEND) + " " + From_Client->NickName + " " + ":No text to send" + "\n";
        Send_Cmd(From_Client->Socket, Msg);
        return ;
    }

    //Concataine les args pour former le message
    std::string Message_to_send = Join_End(2, Args);

    std::stringstream Targets(Args[1]); 
    std::string Target; 

    while (std::getline(Targets, Target, ',')) 
    { 
        //Si Target en double
        if (Check_Double(Target, Args[1]))
        {
            std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_TOOMANYTARGETS) + " " + From_Client->NickName + " :Duplicate recipients. No message delivered" + "\n";
            Send_Cmd(From_Client->Socket, Msg);
            continue;
        }

        //Si c'est une channel
        if (Target[0] == '#')
        {  
            //PRIVMSG #*.edu
            if (Target == "#.localhost")
            {
                //Pour faire ca il faut avoir ?
                //Annonce 2 tout les client sur localhost
            }

            //Check si la channel exist 
            Channel *Chn = Channel_Manager.Get_Channel(Target);
            if (Chn == NULL)
            {
                std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_CANNOTSENDTOCHAN) + " " + From_Client->NickName + " :Cannot send to channel" + "\n";
                Send_Cmd(From_Client->Socket, Msg);
                continue;
            }
            
            //Check si l'user est pas dans la channel et que channel mode = +n

//Fonction pour check si un client est dans une channel
//Fonction pour tester si une channel a un mode 
                
            //Check si pas chanop ou mode +v(voice) et la channel en mode +m (modere)
            
//Fonction pour check si un client est chanop d'une channel
                                                                                    //Fonction pour chekcer le mode d'un client 

            //Announce de la channel
            std::string Msg = ":" + From_Client->NickName + "!" + From_Client->UserName + "@" + From_Client->HostName + " PRIVMSG " + Target + " :" + Message_to_send + "\n";
            Channel_Manager.channelSend(From_Client->NickName ,Target, Msg, false);
            
            continue;
        }

        //Si c'est un client
        else
        {
            //Si pas de client avec ce nickname
            Client *To_Client = Client_Manager.Get_Client(Target);
            if (To_Client == NULL)
            {
                std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_WASNOSUCHNICK) + " " + From_Client->NickName + " :There was no such nickname" + "\n";
                Send_Cmd(From_Client->Socket, Msg);
                continue;
            }

            //Si le client est away
            if (To_Client->Away)
            {
                std::string Msg = ":" + std::string(To_Client->NickName) + " " + I_To_S(RPL_AWAY)  + " " + From_Client->NickName + To_Client->NickName + " :" + To_Client->Away_Str + "\n";
                Send_Cmd(From_Client->Socket, Msg);
                continue;
            }

            //Envoi le message
            std::string Msg = ":" + From_Client->NickName + "!" + From_Client->UserName + "@" + From_Client->HostName + " PRIVMSG " + To_Client->NickName + " :" + Message_to_send + "\n";
            Send_Cmd(To_Client->Socket, Msg);
        }

    } 
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.4.2
void  NOTICE_Command::Execute(Client *From_Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void)Channel_Manager;

    if (Args.size() != 3)
        return ;

    Client *To_Client = Client_Manager.Get_Client(Args[1]);
    if (To_Client == NULL)
        return ;

    std::string Msg = ":" + From_Client->NickName + "!" + From_Client->UserName + "@" + From_Client->HostName + " NOTICE " + To_Client->NickName + " :" + Args[2] + "\n";
    Send_Cmd(To_Client->Socket, Msg);
}

// https://www.rfc-editor.org/rfc/rfc1459#section-5.1
void  AWAY_Command::Execute(Client *From_Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void)Channel_Manager;
    (void)Client_Manager;

    std::string Msg = "";


    if (Args.size() == 1)
    {
        From_Client->Away = 0;
        Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(RPL_UNAWAY)  + " " + From_Client->NickName + " :You are no longer marked as being away" + "\n";
        Send_Cmd(From_Client->Socket, Msg);

        Msg = ":" + From_Client->NickName + "!" + From_Client->UserName + "@" + From_Client->HostName + " AWAY " +  "\n";
        Send_Cmd(From_Client->Socket, Msg);
    }

    if (Args.size() >= 2)
    {
        From_Client->Away = 1;
        
        std::string Message_to_send = Join_End(1, Args);
        From_Client->Away_Str = Message_to_send;

        Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(RPL_NOWAWAY)  + " " + From_Client->NickName + " :You have been marked as being away" + "\n";
        Send_Cmd(From_Client->Socket, Msg);
    }
}