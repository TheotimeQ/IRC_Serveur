/* JE GARDE CECI POUR LE MOMENT*/
// void  JOIN_Command::Execute(Client *Client, std::vector<std::string> Args, ChannelManager &Channel_Manager, Client_Manager &Client_Manager) 
// {
//     (void )Args;
//     (void )Channel_Manager;
//     (void )Client_Manager;


//     //Regarde si tu peux join

//     //Si c'est bon
//         this->Send_Cmd(Client.Socket,":Zel!~a@localhost JOIN #test \n");

//         this->Send_Cmd(Client.Socket,":IRC 332 Zel #test :This is my cool channel! \n");

//         this->Send_Cmd(Client.Socket,":IRC 353 Zel = #test :@Zel Tristan\n");
//         this->Send_Cmd(Client.Socket,":IRC 366 Zel #test :End of /NAMES list \n");

//     //Si tu peux pas message d'erreur


//     this->Send_Cmd(Client.Socket,":IRC 332 Zel #test Rien a dire \n");
//     this->Send_Cmd(Client.Socket,":IRC 333 Zel #test dan!~d@localhost 1547691506 \n"); //set topic
//     this->Send_Cmd(Client.Socket,":IRC MODE #test +nt \n");
//     this->Send_Cmd(Client.Socket,":IRC 475 Zel #test :Cannot join channel (+k) - bad key \n");
// }