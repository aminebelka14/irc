/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:10:38 by amine             #+#    #+#             */
/*   Updated: 2022/11/22 13:50:11 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cmd/Notice.hpp"

Notice::Notice() { _cname = "NOTICE"; }

Notice::~Notice() {}

std::string			Notice::execute(std::string str, User *user, Server &server)
{
	std::vector<std::string>		cmd = str_to_warray(str, " ");
	std::string						name = cmd[1];
	std::vector<User *>				users = server.getUsers();
	std::vector<User *>::iterator	it = users.begin();
	std::vector<User *>::iterator	ite = users.end();
	std::string						reply;

	reply = user->getPrefix() + " " + str + "\r\n";
	for (; it != ite; ++it)
		if ((*it)->getNickname() == name)
			if (send((*it)->getFd(), reply.c_str(), reply.length(), 0) < 0)
			{
				std::cout << "[Send response failed]" << std::endl;
				server.disconnectClient((*it)->getFd());
				return NULL;
			}
	return reply;
}