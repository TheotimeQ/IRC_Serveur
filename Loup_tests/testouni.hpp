/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testouni.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelinsta <zelinsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 06:52:53 by loumarti          #+#    #+#             */
/*   Updated: 2023/04/03 14:56:48 by zelinsta         ###   ########.fr       */
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