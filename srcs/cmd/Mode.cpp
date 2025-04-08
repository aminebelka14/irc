/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:09:58 by amine             #+#    #+#             */
/*   Updated: 2022/11/23 23:17:25 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cmd/Mode.hpp"

Mode::Mode() { _cname = "MODE"; }

Mode::~Mode() {}

Channel							*Mode::getChannel(std::string cname, Server &server)
{
	std::vector<Channel *>				channels = server.getChannels();
	std::vector<Channel *>::iterator	it = channels.begin();
	std::vector<Channel *>::iterator	ite = channels.end();

	for (; it != ite; ++it)
		if ((*it)->getName() == cname)
			return *it;
	return NULL;
}

bool							Mode::checkAdmin(std::string uname, std::string cname, Server &server)
{
	Channel						*chan = getChannel(cname, server);
	std::vector<User *>			users = chan->getUsers();

	if ((users.front())->getNickname() == uname)
		return true;
	return false;
}

std::string						Mode::execute(std::string str, User *user, Server &server)
{
	std::string					reply;
	std::vector<std::string>	cmd = str_to_warray(str, " ");
	std::string					banned;
	std::string					channel;
	std::vector<std::string>	line;
	std::vector<User *>			users;
	

	if (cmd.size() == 4)
	{
		channel = cmd[1];
		banned = cmd[3];
		line = str_to_warray(banned, "@");
		banned = line[0] + "@" + user->getHostname();
		if (!getChannel(channel, server))
			return (reply = "Channel does not exist\r\n");
		if (checkAdmin(user->getNickname(), channel, server) == false)
		{
			reply += user->getPrefix() + ERR_CHANOPRIVSNEEDED(channel) + "\r\n";
			server.sendReply(reply, *user);
			return reply;
		}
		User *uban = server.getUserByName(cmd[3]);
		if (cmd[2] == "-b")
		{
			if (uban && checkAdmin(user->getNickname(), channel, server) == true)
			{
				uban->rmvBanChans(channel);
				server.sendReply(reply, *uban);
			}
		}
		if (cmd[2] == "+b")
		{
			if (uban && uban->checkBan(channel) == true)
			{
				reply += user->getPrefix() + " 697 " + user->getNickname() + " " + channel + " " + banned + " b  :";
				reply += "Channel " + channel + " list already contains " + banned + "\r\n";
				server.sendReply(reply, *user);
				return reply;
			}
			users = server.getChannelUsers(channel);
			for (std::vector<User *>::iterator it = users.begin(); it != users.end(); ++it)
			{
				reply = user->getPrefix() + " " + cmd[0] + " " + cmd[1] + " " + cmd[2] + " " + banned + "\r\n";
				server.sendReply(reply, *(*it));
			}
			if (uban && checkAdmin(banned, channel, server) == false)
			{
				uban->addBanChans(channel);
				server.sendReply(reply, *uban);
			}
		}
	}
	return reply;
}