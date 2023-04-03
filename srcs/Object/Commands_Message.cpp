/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Message.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:09:32 by tquere            #+#    #+#             */
/*   Updated: 2023/04/03 16:26:15 by zelinsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Object/Commands.hpp"

    // std::cout << "Args : " << std::endl;;
    // for (unsigned i = 0; i < Args.size(); ++i) {
    //     std::cout << "|" << Args[i].c_str() << "|" << std::endl;
    // }
    // std::cout << std::endl;
    
//=====================================Sending messages======================================

// https://www.rfc-editor.org/rfc/rfc1459#section-4.4.1
void  PRIVMSG_Command::Execute(Client *From_Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    //Verif Args
    if (Args.size() < 3)
        return ;

    //Implementation des wildcard ? 

    //Recupere le Client/Channel qui recoit le message

    //Decoupe args[1] sur les ","

    //Pour chaque client/channel
        //Si c'est un channel (start with #)
            //Invoque announce de la channel
            // ERR_CANNOTSENDTOCHAN

        //Si c'est un client
            //Envoie le message au client
            //ERR_NOSUCHNICK

        //Sinon
           

    Client *To_Client = Client_Manager.Get_Client(Args[1]);
    if (To_Client == NULL)
    {
        std::cout << "Client not found" << std::endl;
        //Si le client n'existe pas, on verifie si c'est un channel ?

        //Si pas de client avec ce nick name -> Envoi erreur no suchnickname

        //Creer le message : ":Zel!~a@localhost PRIVMSG Zel :yes I'm receiving it !receiving it ! \n"
        // std::string Msg = ":" + From_Client.NickName + "!" + From_Client.UserName + "@" + From_Client.HostName + " PRIVMSG " + To_Client->NickName + " :" + Args[2] + "\n";

        //Envoie le message au client
        // this->Send_Cmd(To_Client->Socket, Msg);
        return ;
    }

    //Creer le message : ":Zel!~a@localhost PRIVMSG Zel :yes I'm receiving it !receiving it ! \n"
    std::string Msg = ":" + From_Client->NickName + "!" + From_Client->UserName + "@" + From_Client->HostName + " PRIVMSG " + To_Client->NickName + " :" + Args[2] + "\n";
    this->Send_Cmd(To_Client->Socket, Msg);

    (void)Channel_Manager;
    (void)From_Client;
    (void)Client_Manager;
}

// https://www.rfc-editor.org/rfc/rfc1459#section-4.4.2
void  NOTICE_Command::Execute(Client *From_Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
{
    (void)Channel_Manager;

    Client *To_Client = Client_Manager.Get_Client(Args[1]);
    if (To_Client == NULL)
        return ;

    std::string Msg = ":" + From_Client->NickName + "!" + From_Client->UserName + "@" + From_Client->HostName + " NOTICE " + To_Client->NickName + " :" + Args[2] + "\n";
    this->Send_Cmd(To_Client->Socket, Msg);
}
