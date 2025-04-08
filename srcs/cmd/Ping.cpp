/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:11:17 by amine             #+#    #+#             */
/*   Updated: 2022/11/21 16:52:42 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cmd/Ping.hpp"

Ping::Ping() { _cname = "PING"; }

Ping::~Ping() {}

std::string							Ping::execute(std::string str, User *user, Server &server)
{
	std::string						reply;
	std::vector<std::string>		cmd = str_to_warray(str, " ");

	if (cmd.size() < 2)
	{
		reply = user->getPrefix() + ERR_NOORIGIN() + "\r\n";
		server.sendReply(reply, *user);
		return reply;
	}
	reply = user->getPrefix() + " PONG " + cmd[1] + "\r\n";
	server.sendReply(reply, *user);
	return reply;
}