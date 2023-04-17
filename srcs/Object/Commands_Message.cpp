/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Message.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/12 15:10:43 by zelinsta         ###   ########.fr       */
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

    // std::cout << "MESSAGE à ENVOYER : " << Args[2] << std::endl;


    //ENLEVER LE : au debut du message

    //Enelever le /n à la fin

    //Concataine les args pour former le message
    std::string Message_to_send = Join_End(2, Args);

    std::cout << "MESSAGE à ENVOYER : " << Message_to_send << std::endl;

    //Mauvais format
    // if (Args.size() != 3)
    //     return ;

    //Implementation des wildcard ? 

    std::stringstream Targets(Args[1]); 
    std::string Target; 

    while (std::getline(Targets, Target, ',')) 
    { 
        // std::cout << Target << std::endl; 

        //Si c'est une channel
        if (Target[0] == '#')
        {  
            (void) Channel_Manager;
            
            //Check si la channel exist 

                //Check si l'user est pas dans la channel et que channel mode = +n
                
                //Check si pas chanop ou mode +v(voice) et la channel en mode +m (modere)

                std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_CANNOTSENDTOCHAN) + " " + From_Client->NickName + " :Cannot send to channel" + "\n";
                Send_Cmd(From_Client->Socket, Msg);
            
                //Announce de la channel

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
            
            //Si client en double
            if (Check_Double(Target, Args[1]))
            {
                std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_TOOMANYTARGETS) + " " + From_Client->NickName + " :Duplicate recipients. No message delivered" + "\n";
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
        
        //Concataine les args pour former le message
        std::string Message_to_send = Join_End(1, Args);
        From_Client->Away_Str = Message_to_send;

        Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(RPL_NOWAWAY)  + " " + From_Client->NickName + " :You have been marked as being away" + "\n";
        Send_Cmd(From_Client->Socket, Msg);
    }
}