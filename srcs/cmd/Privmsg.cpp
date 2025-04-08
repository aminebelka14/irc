/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:11:46 by amine             #+#    #+#             */
/*   Updated: 2022/11/23 19:01:50 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cmd/Pvmsg.hpp"

Pvmsg::Pvmsg() { _cname = "PRIVMSG"; }

Pvmsg::~Pvmsg() {}

std::string						Pvmsg::execute(std::string str, User *user, Server &server)
{
	std::vector<std::string>		cmd = str_to_warray(str, " ");
	std::string						chan = cmd[1];
	std::vector<User *>				users = server.getChannelUsers(chan);
	std::vector<User *>::iterator	it = users.begin();
	std::vector<User *>::iterator	ite = users.end();
	std::string						reply;

	reply = ":" + user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname() + " " + str + "\r\n";
	for (; it != ite; ++it)
		if ((*it)->getFd() != user->getFd())
		{
			if (send((*it)->getFd(), reply.c_str(), reply.length(), 0) < 0)
			{
				std::cout << "[Send response failed]\n";
				server.disconnectClient((*it)->getFd());
				return NULL;
			}
		}
	return reply;
}