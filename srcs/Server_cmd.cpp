#include "../incs/Irc.hpp"
#include "../incs/Server.hpp"
#include "../incs/Client.hpp"

void Tokenize(std::string const &str, const char delim, std::vector<std::string> &out) 
{ 
    // construct a stream from the string 
    std::stringstream ss(str); 
 
    std::string s; 
    while (std::getline(ss, s, delim)) { 
        out.push_back(s); 
    } 
} 

int	Server::Interpret_Data(std::vector<std::string>& Data, Client &Client)
{
    for (std::vector<std::string>::const_iterator it = Data.begin(); it != Data.end(); ++it) 
    {
        std::cout << Client.Get_UserName() << " -> " << *it << std::endl;
        
        //Interpretation des données
        std::vector<std::string> arg; 
        Tokenize(*it, ' ', arg); 

        //POUR CHAQUE COMMANDE , VERIFIER QUE ON A ASSEZ D'ARGUMENT

        // CAP
        // PASS

        // NICK
        if (strncmp(arg[0].c_str(),"NICK",4) == 0)
        {
            Client.Set_NickName(arg[1]);
        }
        // USER
        if (strncmp(arg[0].c_str(),"USER",4) == 0)
        {
            Client.Set_UserName(arg[1]);
        }
        if (strncmp(arg[0].c_str(),"PASS",4) == 0)
        {
            Client.Set_Password(arg[1]);
            this->Send_Message(Client._Client_Socket,":IRC 001 Zel :BIENVENU SUR LE Server IRC\n ");
        }
        // QUIT
        // JOIN
        if (strncmp(arg[0].c_str(),"JOIN",4) == 0)
        {
            //Creer une instance de join (args , client , channel) 
            //Join.exececute()

            //
            // Client.Set_Password(arg[1]);





            // this->Add_Client_To_Channel(Client, Channel);
            // this->Rmv_Client_To_Channel(Client, Channel);





            // this->Send_Message(Client._Client_Socket,":IRC 403 Zel 5 :No such channel\n");
            // this->Send_Message(Client._Client_Socket,":IRC 403 Zel 5 :No such channel\n");
            // this->Send_Message(Client._Client_Socket,":IRC 403 Zel 5 :No such channel\n");

        }
        // Channel.add client



    }
    return GOOD;
}