/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:10:58 by amine             #+#    #+#             */
/*   Updated: 2022/11/23 19:15:17 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cmd/Part.hpp"

Part::Part() { _cname = "PART"; }

Part::~Part() {}

std::string						Part::execute(std::string str, User *user, Server &server)
{
	std::vector<std::string>	cmd = str_to_warray(str, " ");
	std::vector<User *>			users;
	std::string					reply;
	std::string					chan;

	chan = cmd[1];
	reply = user->getPrefix() + " " + str + " " + ":" + user->getNickname();
	if (server.checkChannel(chan) == false)
	{
		reply = user->getPrefix() + ERR_NOSUCHCHANNEL(chan) + "\r\n";
		server.sendReply(reply, *user);
		return reply;
	}
	users = server.getChannelUsers(chan);
	if (users.size() == 0)
	{
		reply = user->getPrefix() + ERR_NOTONCHANNEL(chan) + "\r\n";
		server.sendReply(reply, *user);
		return reply;
	}
	reply += "\r\n";
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); ++it)
		if (send((*it)->getFd(), reply.c_str(), reply.length(), 0) < 0)
		{
			std::cout << "[Send response failed]" << std::endl;
			server.disconnectClient((*it)->getFd());
			return reply;
		}
	server.getChannel(chan)->rmvUser(user);
	return reply;
}
