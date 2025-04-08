/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:26:28 by amine             #+#    #+#             */
/*   Updated: 2022/11/23 19:45:57 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_HPP
# define LIB_HPP

# define PORT 8080
# define BUFF_SIZE 4096

#include <sys/types.h> 
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <exception>
#include <cctype>

#include <iostream>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <fcntl.h>
#include <sstream>
#include <string>
#include <cstring>

extern bool running;

void						printexit(char const *str, int code);
std::vector<std::string>	str_to_warray(std::string str, std::string sep);

// Error messages
#define RPL_WELCOME(nick, user, host) " 001 " + nick + " :Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host

//Command PASS and USER
#define ERR_NEEDMOREPARAMS(command) " 461 * " + command +  " :Not enough parameters"
#define ERR_ALREADYREGISTRED()  " 462 * :Unauthorized command (a lready registered)"

//Command: NICK
#define ERR_NICKNAMEINUSE(nick) " 433 * " + nick + " :Nickname is already in use\r\n"

//Command: JOIN
#define ERR_BANNEDFROMCHAN(channel, ban)  " 474 " + ban + " " + channel + " :Cannot join channel (+b)"
#define ERR_NOSUCHCHANNEL(channel) " 403 * " + channel + ":No such channel"

//Command: PART 
//#define ERR_NOSUCHCHANNEL ()     
#define   ERR_NOTONCHANNEL(channel) " 442 * " + channel + ":You're not on that channel"

//Channel mode message
#define ERR_USERNOTINCHANNEL(nick, channel) " 441 * " + nick + " " + channel + ":They aren't on that channel"    
#define ERR_CHANOPRIVSNEEDED(channel) " 482 * " + channel + " :You're not channel operator"

//Command: INVITE
#define RPL_INVITING(from, to, channel) " 341 " + from + " " + to + " " + channel
#define ERR_NOSUCHNICK(from, to) " 401 " + from + " " + to + " :No such nick"
#define ERR_USERONCHANNEL(user, channel) " 443 * " + user + " " + channel + " :is already on channel"

//Command: PING
#define ERR_NOORIGIN() " 409 * :No origin specified" 

#endif