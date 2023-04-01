/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command_Manager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 08:32:08 by tquere            #+#    #+#             */
/*   Updated: 2023/04/01 09:55:23 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Manager/Command_Manager.hpp"

Command_Manager::Command_Manager()
{
    Cmd_List["JOIN"] = A_Command();
    Cmd_List["KICK"] = A_Command();
    Cmd_List["NICK"] = A_Command();
    Cmd_List["USER"] = A_Command();

    return;
}

Command_Manager::~Command_Manager()
{
	return;
}

void Command_Manager::Tokenize(std::string const &str, const char delim, std::vector<std::string> &out) 
{ 
    // construct a stream from the string 
    std::stringstream ss(str); 
 
    std::string s; 
    while (std::getline(ss, s, delim)) { 
        out.push_back(s); 
    } 
} 

int	Command_Manager::Interpret_Data(std::vector<std::string>& Data, Client &Client)
{
    for (std::vector<std::string>::const_iterator it = Data.begin(); it != Data.end(); ++it) 
    {
        std::cout << Client.Get_UserName() << " -> " << *it << std::endl;
        
        //Interpretation des données
        std::vector<std::string> arg; 
        Tokenize(*it, ' ', arg); 

        //Parcours la liste de commande
        //Liste d'instance

        //Compare les data avec la lise des commande

        //Instentie la commande

        //Execute la commande


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
            // this->Send_Message(Client._Client_Socket,":IRC 001 Zel :BIENVENU SUR LE Server IRC\n ");
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


//Parcours le tableau de commande

//Parcours 































// class MyClass1 {
// public:
//     void doSomething() {
//         std::cout << "MyClass1::doSomething() called." << std::endl;
//     }
// };

// class MyClass2 {
// public:
//     void doSomething() {
//         std::cout << "MyClass2::doSomething() called." << std::endl;
//     }
// };

// class MyClass3 {
// public:
//     void doSomething() {
//         std::cout << "MyClass3::doSomething() called." << std::endl;
//     }
// };

// class MyClass4 {
// public:
//     void doSomething() {
//         std::cout << "MyClass4::doSomething() called." << std::endl;
//     }
// };


// std::map<std::string, A_Command> = 

//     std::map<std::string, int> m{{"CPU", 10}, {"GPU", 15}, {"RAM", 20}};
 
//     print_map("1) Initial map: ", m);
 
//     m["CPU"] =

// // Define a map of string to class constructors
// std::map<std::string, std::function<void*()>> Class_Constructors = 
// {
//     {"MyClass1", [](){return new MyClass1();}},
//     {"MyClass2", [](){return new MyClass2();}},
//     {"MyClass3", [](){return new MyClass3();}},
//     {"MyClass4", [](){return new MyClass4();}}
// };


// // Define a function that creates an instance of the specified class
// void* createInstance(const std::string& className) {
//     auto constructor = classConstructors[className];
//     if (constructor) {
//         return constructor();
//     }
//     return nullptr;
// }

// // Define the main function that uses the createInstance function
// void processInput(const std::vector<std::string>& classNames, const std::vector<std::string>& inputs) {
//     for (auto input : inputs) {
//         auto instance = createInstance(input);
//         if (instance) {
//             auto className = classNames[std::distance(inputs.begin(), std::find(inputs.begin(), inputs.end(), input))];
//             auto typedInstance = static_cast<decltype(&className)>(instance);
//             typedInstance->doSomething();
//             delete instance;
//         } else {
//             std::cout << "Unknown class: " << input << std::endl;
//         }
//     }
// }

// int main() {
//     std::vector<std::string> classNames = {"MyClass1", "MyClass2", "MyClass3", "MyClass4"};
//     std::vector<std::string> inputs = {"MyClass1", "MyClass2", "MyClass3", "MyClass4", "UnknownClass"};

//     processInput(classNames, inputs);

//     return 0;
// }
