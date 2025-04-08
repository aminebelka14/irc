/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:12:12 by amine             #+#    #+#             */
/*   Updated: 2022/11/21 16:53:44 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cmd/Quit.hpp"

Quit::Quit() { _cname = "QUIT"; }

Quit::~Quit() {}

std::string			Quit::execute(std::string str, User *user, Server &server)
{
	std::vector<std::string>	cmd = str_to_warray(str, " ");
	std::vector<User *>			users;
	std::string					c_name;
	std::string					reply;

	(void)user;
	if (cmd.size() < 2)
		return "QUIT: Need channel name as argument\r\n";
	c_name = cmd[1];
	users = server.getChannelUsers(c_name);
	reply = user->getPrefix() + " QUIT :Quit: leaving\r\n";
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); ++it)
		server.sendReply(reply, *(*it));
	server.disconnectClient(user->getFd());
	return reply;
}