/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2023/05/02 11:22:50 by tquere            #+#    #+#             */
/*   Updated: 2023/05/02 11:51:35 by tquere           ###   ########.fr       */
=======
/*   Created: 2023/05/02 11:22:50 by zelinsta          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/02 11:37:15 by zelinsta         ###   ########.fr       */
>>>>>>> 3d7fd407bf79231ca2508ae96fd4e24c11ef3985
=======
/*   Updated: 2023/05/02 13:02:54 by zelinsta         ###   ########.fr       */
>>>>>>> b35a07df25f9b12b899510cd6b3e3ab1f34cde54
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Irc.hpp"
#include "../incs/Object/Server.hpp"
#include "../incs/Object/Client.hpp"

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

void signal_callback_handler(int signum) {
    std::cout << "Caught signal " << signum << std::endl;
    std::cout << " ----STOPPING SERVER---- " << signum << std::endl;
    Stop = 1;
}

int main(int argc, char **argv)
{
    Stop = 0;
    signal(SIGINT, signal_callback_handler);
    
    if (argc != 3) {
        std::cerr << ERROR_SERVER_PARAM <<  std::endl;
        return 1;
    }

    if (check_port(argv[1])) 
        return 1;

    Server Serv = Server(SERVER_NAME, std::atoi(argv[1]), argv[2]);
    if (Serv.Start_Server())
        return ERROR;

    if (Serv.Run())
        return ERROR;

    Serv.Stop_Server();

    return (GOOD);
}
