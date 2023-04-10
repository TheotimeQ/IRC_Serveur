/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Message.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/10 08:44:56 by loumarti         ###   ########lyon.fr   */
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

static int Check_Double(std::string NickName, std::string Args)
{
    std::stringstream Targets(Args); 
    std::string Target; 
    int nb = 0;

    while (std::getline(Targets, Target, ',')) 
    {
        if (NickName == Target)
            nb++;
    }
    if (nb > 1)
        return ERROR;
    return GOOD;
}

static std::string Join_End(int start, std::vector<std::string> Args)
{
    std::vector<Client>::iterator it;
    std::string Joined = ""; 

    for (int i = start; i < (int)Args.size(); ++i)
        Joined += Args[i] + " ";

    // "REMOVE LE \n"

    return Joined;
}

//=====================================Sending messages======================================

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

    //Concataine les args pour former le message
    std::string Message_to_send = Join_End(3, Args);

    //Mauvais format
    if (Args.size() != 3)
        return ;

    //Implementation des wildcard ? 

    std::stringstream Targets(Args[1]); 
    std::string Target; 

    while (std::getline(Targets, Target, ',')) 
    { 
        std::cout << Target << std::endl; 

        //Si c'est une channel
        if (Target[0] == '#')
        {  
            (void) Channel_Manager;
            
            //Check si la channel exist 

                //Check si l'user est pas dans la channel et que channel mode = +n
                
                //Check si pas chanop ou mode +v et la channel en mode +m

                std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_CANNOTSENDTOCHAN) + " " + From_Client->NickName + " :Cannot send to channel" + "\n";
                this->Send_Cmd(From_Client->Socket, Msg);
            
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
                this->Send_Cmd(From_Client->Socket, Msg);
                continue;
            }
            
            //Si client en double
            if (Check_Double(Target, Args[1]))
            {
                std::string Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(ERR_TOOMANYTARGETS) + " " + From_Client->NickName + " :Duplicate recipients. No message delivered" + "\n";
                this->Send_Cmd(From_Client->Socket, Msg);
                continue;
            }

            //Si le client est away
            if (To_Client->Away)
            {
                std::string Msg = ":" + std::string(To_Client->NickName) + " " + I_To_S(RPL_AWAY)  + " " + From_Client->NickName + To_Client->NickName + " :" + To_Client->Away_Str + "\n";
                this->Send_Cmd(From_Client->Socket, Msg);
                continue;
            }

            //Envoi le message
            std::string Msg = ":" + From_Client->NickName + "!" + From_Client->UserName + "@" + From_Client->HostName + " PRIVMSG " + To_Client->NickName + " :" + Message_to_send + "\n";
            this->Send_Cmd(To_Client->Socket, Msg);
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
    this->Send_Cmd(To_Client->Socket, Msg);
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
        this->Send_Cmd(From_Client->Socket, Msg);

        Msg = ":" + From_Client->NickName + "!" + From_Client->UserName + "@" + From_Client->HostName + " AWAY " +  "\n";
        this->Send_Cmd(From_Client->Socket, Msg);
    }

    if (Args.size() >= 2)
    {
        From_Client->Away = 1;
        
        //Concataine les args pour former le message
        std::string Message_to_send = Join_End(1, Args);
        From_Client->Away_Str = Message_to_send;

        Msg = ":" + std::string(SERVER_NAME) + " " + I_To_S(RPL_NOWAWAY)  + " " + From_Client->NickName + " :You have been marked as being away" + "\n";
        this->Send_Cmd(From_Client->Socket, Msg);
    }
}