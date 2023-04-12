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

//[!]

#include "../incs/Irc.hpp"
#include "../incs/Object/Client.hpp"

#define ERROR_SEND_MSG 		"Error: Can't send message : \n"
#define EVENT_NEW_MSG 		"Log: Message sent : "

int             Send_Cmd(int client_sock, const std::string& message) ;

std::string     I_To_S(int num);
int             Check_Double(std::string NickName, std::string Args);
std::string     Join_End(int start, std::vector<std::string> Args);
int             Is_Valide_Nick(const std::string& str);

#endif
