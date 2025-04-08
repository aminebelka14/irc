/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invoker.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 00:38:11 by amine             #+#    #+#             */
/*   Updated: 2022/11/23 19:32:31 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Invoker.hpp"
#include "../includes/Server.hpp"
#include "../includes/cmd/Join.hpp"
#include "../includes/cmd/Invite.hpp"
#include "../includes/cmd/Kick.hpp"
#include "../includes/cmd/Mode.hpp"
#include "../includes/cmd/Notice.hpp"
#include "../includes/cmd/Part.hpp"
#include "../includes/cmd/Pvmsg.hpp"
#include "../includes/cmd/Quit.hpp"
#include "../includes/cmd/Ping.hpp"

Invoker::Invoker()
{
	_cmds.push_back(new Ping());
	_cmds.push_back(new Part());
	_cmds.push_back(new Join());
	_cmds.push_back(new Notice());
	_cmds.push_back(new Pvmsg());
	_cmds.push_back(new Kick());
	_cmds.push_back(new Quit());
	_cmds.push_back(new Invite());
	_cmds.push_back(new Mode());
}

Invoker::~Invoker()
{
	std::vector<Command *>::iterator it = _cmds.begin();
	std::vector<Command *>::iterator ite = _cmds.end();

	for (; it != ite; ++it)
		delete *it;
}

std::string Invoker::parser(std::vector<std::string> warray, User *user, Server &server)
{
	std::vector<std::string>::iterator it = warray.begin();
	std::vector<std::string>::iterator ite = warray.end();
	std::vector<std::string> cmd;
	std::string reply;

	for (; it != ite; ++it)
	{
		cmd = str_to_warray(*it, " ");
		for (std::vector<Command *>::iterator i = _cmds.begin(); i != _cmds.end(); ++i)
		{
			if (cmd[0] == (*i)->getCmdName())
			{
				reply = ((*i)->execute(*it, user, server));
				return reply;
			}
		}
	}
	return reply;
}