/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:09:33 by amine             #+#    #+#             */
/*   Updated: 2022/11/21 20:40:03 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cmd/Kick.hpp"

Kick::Kick() { _cname = "KICK"; }

Kick::~Kick() {}

bool							Kick::checkChannel(std::string cname, Server &server)
{
	std::vector<Channel *>				tmp = server.getChannels();
	std::vector<Channel *>::iterator	it = tmp.begin();
	std::vector<Channel *>::iterator	ite = tmp.end();

	for (; it != ite; ++it)
		if ((*it)->getName() == cname)
			return true;
	return false;
}

bool							Kick::checkUserInChannel(std::string name, std::string chan, Server &server)
{
	Channel						*Channel = server.getChannel(chan);

	if (Channel)
		if (Channel->checkUser(name) == true)
			return true;
	return false;
}

std::string						Kick::execute(std::string str, User *user, Server &server)
{
	std::vector<std::string>	cmd = str_to_warray(str, " ");
	std::string					reply = user->getPrefix();
	std::string					chan = cmd[1];
	std::string					name = cmd[2];
	Channel						*channel;
	User						*kicked;


	if (cmd.size() != 4)
	{
		std::string cmd = "KICK";
		reply = ERR_NEEDMOREPARAMS(cmd) + "\r\n";
		server.sendReply(reply, *user);
		return reply;
	}
	if (server.checkUser(name) == false)
	{
		reply = ERR_NOSUCHNICK(user->getNickname(), name) + "\r\n";
		server.sendReply(reply, *user);
		return reply;
	}
	if (checkChannel(chan, server) == false)
	{
		reply = ERR_NOSUCHCHANNEL(chan) + "\r\n";
		server.sendReply(reply, *user);
		return reply;
	}
	if (checkUserInChannel(name, chan, server) == false)
	{
		reply = ERR_USERNOTINCHANNEL(name, chan) + "\r\n";
		server.sendReply(reply, *user);
		return reply;
	}
	channel = server.getChannel(chan);
	if (channel->getUsers().front()->getNickname() != user->getNickname())
	{
		reply = ERR_CHANOPRIVSNEEDED(chan) + "\r\n";
		server.sendReply(reply, *user);
		return reply;
	}
	kicked = channel->getUser(name);
	reply += " KICK " + chan + " " + name + " " + user->getNickname() + "\r\n";
	if (kicked)
		server.sendReply(reply, *kicked);
	if (kicked != user)
		server.sendReply(reply, *user);
	channel->rmvUser(kicked);
	return reply;
}