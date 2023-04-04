/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Message.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/04 09:48:07 by zelinsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

    // std::cout << "Args : " << std::endl;;
    // for (unsigned i = 0; i < Args.size(); ++i) {
    //     std::cout << "|" << Args[i].c_str() << "|" << std::endl;
    // }
    // std::cout << std::endl;
    
static std::string I_To_S(int num)
{
    std::stringstream ss;
    ss << num;
    return (ss.str());
}

//=====================================Sending messages======================================


// #define ERR_NORECIPIENT         411     
//":No recipient given (<command>)"

// #define ERR_NOTEXTTOSEND        412     
// ":No text to send"

// #define ERR_CANNOTSENDTOCHAN    404
//"<channel name> :Cannot send to channel"

// - Sent to a user who is either (a) not on a channel
//     which is mode +n or (b) not a chanop (or mode +v) on
//     a channel which has mode +m set and is trying to send
//     a PRIVMSG message to that channel.

// #define ERR_TOOMANYTARGETS      407
//"<target> :Duplicate recipients. No message delivered"

// - Returned to a client which is attempting to send a
//     PRIVMSG/NOTICE using the user@host destination format
//     and for a user@host which has several occurrences.

// #define ERR_WASNOSUCHNICK       406
//"<nickname> :There was no such nickname"

// #define RPL_AWAY                301
//"<nick> :<away message>"

// https://www.rfc-editor.org/rfc/rfc1459#section-4.4.1
void  PRIVMSG_Command::Execute(Client *From_Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    //Pas de destinataire
    if (Args.size() == 1)
    {
        std::string Msg = ":" + std::string(SERVER_NAME) + " "  + I_To_S(ERR_NORECIPIENT) + " " + From_Client->NickName + " " + ":No recipient given " + Args[0] + "\n";
        this->Send_Cmd(From_Client->Socket, Msg);
        return ;
    }
    
    //Pas de message
    if (Args.size() == 2)
    {
        std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_NOTEXTTOSEND) + " " + From_Client->NickName + " " + ":No text to send" + "\n";
        this->Send_Cmd(From_Client->Socket, Msg);
        return ;
    }

    //Mauvais format
    if (Args.size() != 3)
        return ;

    std::stringstream ss(Args[1]); 
    std::string Targets; 

    while (std::getline(ss, Targets, ',')) 
    { 
        std::cout << Targets << std::endl; 

        //Si c'est une channel
        if (Targets[0] == '#')
        {
            //Pour chaque client/channel
                //Si c'est un channel (start with #)

                    //Announce de la channel

                    //Si impossible d'envoyer le message
                    // std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_CANNOTSENDTOCHAN) + " " + From_Client->NickName + " :Cannot send to channel" + "\n";
            continue;
        }

        //Si c'est un client
        else
        {
            //Si client en double
            // std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_TOOMANYTARGETS) + " " + From_Client->NickName + " :Duplicate recipients. No message delivered" + "\n";

            //Si le client est away 
            //std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(RPL_AWAY)  + " " + From_Client->NickName + ":" + "<away message>" + "\n";

            //Si pas de client avec ce nickname
            // std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_WASNOSUCHNICK) + " " + From_Client->NickName + " :There was no such nickname" + "\n";

            //Si pas de client avec ce nickname
            Client *To_Client = Client_Manager.Get_Client(Targets);
            if (To_Client == NULL)
            {
                std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_WASNOSUCHNICK) + " " + From_Client->NickName + " :There was no such nickname" + "\n";
                this->Send_Cmd(From_Client->Socket, Msg);
                continue;
            }

            //Envoi le message
            std::string Msg = ":" + From_Client->NickName + "!" + From_Client->UserName + "@" + From_Client->HostName + " PRIVMSG " + To_Client->NickName + " :" + Args[2] + "\n";
            this->Send_Cmd(To_Client->Socket, Msg);
        }

    } 

    //Implementation des wildcard ? 

    //Recupere le Client/Channel qui recoit le message
    //Decoupe args[1] sur les ","

           
    (void)Channel_Manager;
    (void)From_Client;
    (void)Client_Manager;
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
    this->Send_Cmd(To_Client->Socket, Msg);
}
