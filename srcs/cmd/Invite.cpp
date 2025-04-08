/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:09:07 by amine             #+#    #+#             */
/*   Updated: 2022/11/23 19:23:06 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cmd/Invite.hpp"

Invite::Invite() { _cname = "INVITE"; }

Invite::~Invite() {}

bool							Invite::_checkNick(std::string nick, Server &server)
{
	std::vector<User *>				users = server.getUsers();
	std::vector<User *>::iterator	it = users.begin();
	std::vector<User *>::iterator	ite = users.end();

	for (; it != ite; ++it)
		if ((*it)->getNickname() == nick)
			return true;
	return false;
}

bool							Invite::_checkUserChannel(Channel *chan, std::string name) { return chan->checkUser(name); }

int								Invite::_getFdName(std::string nick, Server &server)
{
	std::vector<User *>			users = server.getUsers();

	for (size_t i = 0; i < users.size(); ++i)
		if (users[i]->getNickname() == nick)
			return users[i]->getFd();
	return -1;
}

std::string						Invite::execute(std::string str, User *user, Server &server)
{
	std::vector<std::string>	cmd = str_to_warray(str, " ");
	std::string					name = cmd[1];
	std::string					chan = cmd[2];
	std::string					reply;
	Channel						*channel = server.getChannel(chan);
	int							fd = -1;

	if (_checkNick(name, server) == false)
	{
		reply = user->getPrefix() + ERR_NOSUCHNICK(user->getNickname(), name) + "\r\n";
		server.sendReply(reply, *user);
		return reply;
	}
	if (!channel)
	{
		reply = user->getPrefix() + ERR_NOSUCHCHANNEL(chan) + "\r\n";
		server.sendReply(reply, *user);
		return reply;
	}
	if (_checkUserChannel(channel, name) == true)
	{
		reply = user->getPrefix() + ERR_USERONCHANNEL(name, chan) + "\r\n";
		server.sendReply(reply, *user);
		return reply;
	}
	
	reply = user->getPrefix() + " INVITE " + name + " " + chan + "\r\n";
	server.sendReply(reply, *user);
	reply = user->getPrefix() + RPL_INVITING(user->getNickname(), name, chan) + "\r\n";
	server.sendReply(reply, *user);
	fd = _getFdName(name, server);
	reply = user->getNickname() + " invites you to " + chan + "\r\n";
	send(fd, reply.c_str(), reply.length(), 0);
	return reply;
}