/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:12:57 by tquere            #+#    #+#             */
/*   Updated: 2023/04/01 10:43:24 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "../../incs/Object/A_Command.hpp"

class Join_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args);
};

class Kick_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args);
};

class Nick_Command : public A_Command 
{
    public:

        virtual void Execute(Client &Client, std::vector<std::string> Args);
};

class User_Command : public A_Command 
{
    public:
    
        virtual void Execute(Client &Client, std::vector<std::string> Args);
};

#endif