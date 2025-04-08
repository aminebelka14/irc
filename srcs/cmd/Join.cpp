/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:02:34 by amine             #+#    #+#             */
/*   Updated: 2022/11/23 18:56:59 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd/Join.hpp"

Join::Join() { _cname = "JOIN"; }

Join::~Join() {}

std::string			Join::execute(std::string cmd, User *user, Server &server)
{
	std::vector<std::string>	cmd_tab = str_to_warray(cmd, " ");
	std::string					chan = cmd_tab[1];
	std::string					reply;
	
	if (!cmd_tab[1].size())
		return (reply + "\r\n");
	if (user->checkBan(chan) == true)
	{
		reply = user->getPrefix() + ERR_BANNEDFROMCHAN(chan, user->getNickname()) + "\r\n";
		server.sendReply(reply, *user);
		return reply;
	}
	if (chan[0] != '#')
	{
		reply = user->getPrefix() + " Invalid channel name\r\n";
		server.sendReply(reply, *user);
		return reply;
	}

	std::vector<Channel *>		channels = server.getChannels();

	if (server.getChannel(chan) == NULL)
		server.addChannel(chan);
	channels = server.getChannels();
	
	std::string							names;
	std::vector<User *>					users;
	std::vector<Channel *>::iterator	it = channels.begin();
	std::vector<Channel *>::iterator	ite = channels.end();

	for (; it != ite; ++it)
		if ((*it)->getName() == chan)
		{
			if (!(*it)->getUser(user->getNickname()))
				(*it)->addUser(user);
			users = (*it)->getUsers();
			for (std::vector<User *>::iterator uit = users.begin(); uit < users.end(); ++uit)
			{
				names += (*uit)->getNickname();
				if (uit == users.end() - 1)
					break;
				names += " ";
			}
		}
	reply = ":" + user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname() + " " + cmd + "\r\n";
	std::string reply2 = ":" + user->getNickname() + "!" + user->getUsername()+ "@" +user->getHostname() + " 353 " + user->getNickname() +" = "+ chan + " : @" + names + "\r\n";
	std::string reply3 = ":" + user->getNickname() + "!" + user->getUsername()+ "@" +user->getHostname() + " 366 " + user->getNickname() +" "+ chan + " :End of /NAMES list"+"\r\n";
	for (std::vector<User *>::iterator uit = users.begin(); uit != users.end(); ++uit)
	{
		if ((*uit)->getFd() != user->getFd())
			server.sendReply(reply, *(*uit));
		else
		{
			server.sendReply(reply, *(*uit));
			server.sendReply(reply2, *(*uit));
			server.sendReply(reply3, *(*uit));
		}
	}
	return reply;
}