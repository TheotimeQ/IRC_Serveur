/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:29:01 by tquere            #+#    #+#             */
/*   Updated: 2023/05/02 13:29:01 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/bot.hpp"

int check_port(const char *port)
{

    if (port == NULL) {
        return ERROR;
    }

    if (*port == '\0') {
        std::cerr << ERROR_PORT_EMPTY << port <<  std::endl;
        return ERROR;
    }

    errno = 0;
    long int num = strtol(port, NULL, 10);
	if (num < 0 || num > INT_MAX || errno == ERANGE) 
    {
		std::cerr << ERROR_PORT_MAX << std::endl;
		return ERROR;
	} 

    for (int i = 0; port[i] != '\0'; i++) {
        if (!isdigit(port[i])) 
        {
            std::cerr << ERROR_PORT_NO_DIGIT << ( port + i ) <<  std::endl;
            return ERROR;
        }
    }

	num = static_cast<int>(num); 
    if (num < 1 || num > 65535) {
        std::cerr << ERROR_PORT_RANGE << num << std::endl;
        return ERROR;
    }

    return GOOD;
}

int main(int argc, char** argv) 
{
    if (argc != 3) 
    {
        std::cout << ERROR_BOT_PARAM << std::endl;
        return ERROR;
    }

    if (check_port(argv[1])) 
        return 1;

    Bot bot = Bot(BOT_NAME, std::atoi(argv[1]), argv[2], IP);
    if (bot.Start_Bot())
        return ERROR;

    if (bot.Run())
        return ERROR;

    bot.Stop_Bot();

    return (GOOD);
}