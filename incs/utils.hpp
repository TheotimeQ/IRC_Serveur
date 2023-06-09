/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:22:17 by tquere            #+#    #+#             */
/*   Updated: 2023/05/02 11:51:35 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include <string>
#include <cstring>
#include <sys/time.h>
#include <string>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <cerrno>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

#include "../incs/Irc.hpp"
#include "../incs/Object/Client.hpp"

int				Send_Cmd(int client_sock, const std::string& message) ;
std::string		catVectString(std::vector<std::string> const &args, unsigned offset, std::string const &delim);
void			rmFromVectString(std::vector<std::string> &vs, std::string const &target);
void			addInVectString(std::vector<std::string> &vs, std::string const &target);
bool			findSetInString(std::string const &set, std::string const &string);
void			showVectStringPair(std::vector<std::pair<std::string, std::string> > const &list);

std::string     I_To_S(int num);
int             Check_Double(std::string NickName, std::string Args);
std::string     Join_End(int start, std::vector<std::string> Args);
int             Is_Valide_Nick(const std::string& str);

#endif
