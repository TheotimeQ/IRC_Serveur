/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testouni.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumarti <loumarti@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 06:52:53 by loumarti          #+#    #+#             */
/*   Updated: 2023/03/25 09:59:34 by loumarti         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTOUNI_HPP
# define TESTOUNI_HPP

# include <iostream>

# include <sys/socket.h> // socket()
# include <netinet/in.h> // struct sockaddr_in6	
# include <arpa/inet.h> // htons (marche sans ce header)
# include <poll.h> // poll()

# include <cerrno> 
# include <cstring> // strerror() bzero()
# include <cstdlib> // exit()
# include <unistd.h> // close()


using namespace std;

# define MAX_CLIENTS 10
# define BUFFER_SIZE 1024

#endif