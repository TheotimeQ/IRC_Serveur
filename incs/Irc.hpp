/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquere <tquere@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:22:13 by tquere            #+#    #+#             */
/*   Updated: 2023/05/02 13:29:32 by tquere           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

#define GOOD  0
#define ERROR 1
#define QUIT  2

//Quelques variable de configuration du serveur

#define SERVER_NAME             "IRC"
#define MSG_BIENVENU 		    "Wellcoooommmeee on 'Y AIR C' by Loumarti & Tquere"

const int MAX_CLIENTS = 10;
const int BUFFER_SIZE = 4096;

//Code numeric associé à la doc IRC
#define RPL_WELCOME             001
#define RPL_AWAY                301
#define RPL_UNAWAY              305
#define RPL_NOWAWAY             306
#define RPL_ENDOFWHO            315
#define RPL_TOPIC               332
#define RPL_WHOREPLY            352
#define RPL_NAMREPLY            353
#define RPL_ENDOFNAMES          366
#define RPL_YOUREOPER           381
#define ERR_CANNOTSENDTOCHAN    404
#define ERR_WASNOSUCHNICK       406
#define ERR_TOOMANYTARGETS      407
#define ERR_NORECIPIENT         411
#define ERR_NOTEXTTOSEND        412
#define ERR_NONICKNAMEGIVEN     431
#define ERR_ERRONEUSNICKNAME    432
#define ERR_NICKNAMEINUSE       433
#define ERR_NICKCOLLISION       436
#define ERR_NOSUCHSERVER        402
#define ERR_NEEDMOREPARAM       461
#define ERR_ALREADYREGISTRED    462
#define ERR_PASSWDMISMATCH      464
#define ERR_NOOPERHOST          491

//Message d'erreur à envoyer au client ( issue de la doc )
#define SRPL_LISTEND				":End of LIST"					// 323
#define SERR_NOSUCHNICK 			"No such nickname"				// 401
#define SERR_NOSUCHCHANNEL			"No such channel"				// 403
#define SERR_USERNOTINCHANNEL		"They aren't on that channel"	// 441
#define SERR_USERONCHANNEL			"Is already on channel"			// 443
#define SERR_NEEDMOREPARAMS			"Not enough parameters"			// 461
#define SERR_CHANNELISFULL			"Cannot join channel (+l)"		// 471
#define SERR_UNKNOWNMODE			"unknown mode asked"			// 472
#define SERR_INVITEONLYCHAN			"Cannot join channel (+i)"		// 473
#define SERR_BANNEDFROMCHAN			"Cannot join channel (+b)"		// 474
#define SERR_BADCHANNELKEY			"Cannot join channel (+k)"		// 475
#define SERR_CHANOPRIVSNEEDED		"You're not channel operator"	// 482

//Message d'erreur à envoyer au client ( custom )
#define SERR_NOSUCHCHANNEL_KC		"No such channel, kicking process canceled"

//Message d'erreur sur le serveur
#define ERROR_SERVER_PARAM 	        "Usage: ircserv <port> <password>"
#define ERROR_PORT_EMPTY 	        "Error: port empty : "
#define ERROR_PORT_NO_DIGIT         "Error: port contain no digit caractere : "
#define ERROR_PORT_MAX		        "Error: wtf bro? What are those test.. folow the correction sheet :D"
#define ERROR_PORT_RANGE 	        "Error: 1 <= port <= 65535 : "
#define ERROR_SOCKET 		        "Error: Can't create socket"
#define ERROR_CONF_SOCKET 	        "Error: Can't configure socket "
#define ERROR_BIND 			        "Error: Can't bind socket"
#define ERROR_LISTEN 		        "Error: Can't listen on socket"
#define ERROR_POLL 			        "Error: Can't get poll event"
#define ERROR_CONNECTION 	        "Error: Can't while accept new client"
#define ERROR_DATA 			        "Error: Can't while getting data from client"
#define ERROR_BAD_FORMAT 	        "Error: Bad format"
#define ERROR_PASS_ALREADY_SET      "Error: Password already set"
#define ERROR_USER_ALREADY_SET      "Error: Username already set"
#define ERROR_NICKNAME_BAD_FORMAT   "Error: Nickname bad format"
#define ERROR_MAX_CLIENT			"Error: Can't add new client , max reached"
#define ERROR_RTN_CLIENT			"Error: Can't return client , wrong index"
#define ERROR_DEL_CLIENT			"Error: Can't add remove client , no such client"
#define ERROR_FID_CLIENT			"Error: Can't find client , no such : "
#define ERROR_NICKNAME_ALREADY_USED	"Error: Can't change nickname , already used"
#define ERROR_CMDNOTFOUND 	        "Error: Command not found : "
#define ERROR_OPER_UNKOW            "Error: Operator unkown : "
#define ERROR_SEND_MSG 		        "Error: Can't send message : \n"

//Channel error
# define CHERR_FORMAT			    "channel name format : <#name>"
# define CHERR_FORMAT_PRE		    "channel name must start with # or !"
# define CHERR_FORMAT_TOOLONG	    "channel name can't exceed 200 character long"
# define CHERR_FORMAT_FCHAR		    "channel name can't have spaces, coma or semicolon"

// errors while maping into _users
# define CHERR_USERNAME_NOTFOUND	"can't find the user : "

//Message d'event sur le serveur
#define EVENT_NEW_CLIENT 	        "New connection    "
#define EVENT_DECONNECTED 	        "Client deconnected : "
#define EVENT_NEW_DATA 		        "Data received : \n"
#define EVENT_LOGGED				"Client logged : "
#define EVENT_CMDFOUND		        "Executing : "
#define EVENT_NEW_MSG 		        "Message sent : "

// Channel errors
# define ERRCHAN_CREATION	        "channel creation error : "
# define ERRCHAN_WRONGNAME	        "[!] Channel Manager can't find : "
# define LOGCHAN_NOTOPICPERM	    " : has no topic set permission in channel : "





#endif
