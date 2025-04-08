/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:37:03 by amine             #+#    #+#             */
/*   Updated: 2022/11/22 14:41:16 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include "../includes/Invoker.hpp"

//							GENERAL

void						Server::sendReply(std::string reply, User &user)
{
	if (send(user.getFd(), reply.c_str(), reply.length(), 0) < 0)
		disconnectClient(user.getFd());
}

int							Server::_fdMax()
{
	std::vector<int>::iterator it = _fdtab.begin();
	std::vector<int>::iterator ite = _fdtab.end();
	int		i = _socket.getSfd();

	if (_fdtab.empty())
		return i;
	for (; it != ite; ++it)
		if (*it > i)
			i = *it;
	return i;
}

//							CHANNELS

std::vector<Channel *>		Server::getChannels() { return _channels; }

std::vector<User *>			Server::getUsers() { return _users; }

void						Server::addChannel(std::string chan_name) { _channels.push_back(new Channel(chan_name)); }

Channel						*Server::getChannel(std::string chan_name)
{
	std::vector<Channel *>::iterator it = _channels.begin();
	std::vector<Channel *>::iterator ite = _channels.end();

	for (; it != ite; ++it)
		if ((*it)->getName() == chan_name)
			return *it;
	return NULL;
}

std::vector<User *>			Server::getChannelUsers(std::string chan_name)
{
	std::vector<Channel *>::iterator	it = _channels.begin();
	std::vector<Channel *>::iterator	ite = _channels.end();
	std::vector<User *>					users;

	for (; it != ite; ++it)
		if ((*it)->getName() == chan_name)
			return ((*it)->getUsers());
	return users;
}

//							CHECKS

bool						Server::checkUser(std::string nick)
{
	std::vector<User *>::iterator it = _users.begin();
	std::vector<User *>::iterator ite = _users.end();

	for (; it != ite; ++it)
		if ((*it)->getNickname() == nick)
			return true;
	return false;
}

bool						Server::ifJoinServer(int fd)
{
	std::vector<User *>::iterator it = _users.begin();
	std::vector<User *>::iterator ite = _users.end();

	for(; it != ite; it++)
	{
		if ((*it)->getFd() == fd && (*it)->getJoin())
			return true;
	}
	return false;
}

bool						Server::isIncomplete(int fd)
{
	if (_users.size() == 0)
		return false;
	for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); ++it)
		if ((*it)->getFd() == fd && (*it)->getPartial() == true)
			return true;
	return false;
}

bool						Server::_isNickAvailable(User *user, std::string nick)
{
	std::vector<User *>::iterator 	it = _users.begin();
	std::vector<User *>::iterator 	ite = _users.end();
	std::string						err = ":";

	for (; it != ite; ++it)
	{
		if ((*it)->getNickname() == nick)
		{
			err += ERR_NICKNAMEINUSE(nick);
			send(user->getFd(), err.c_str(), err.length(), 0);
			return false;
		}
	}
	return true;
}

bool						Server::checkRequestFormatFull(std::vector<std::string> warray)
{
	if (this->isWordInArray(warray, "CAP")
		&& this->isWordInArray(warray, "NICK")
		&& this->isWordInArray(warray, "USER")
		&& this->isWordInArray(warray, "PASS"))
		return true;
	return false;
}

bool						Server::checkRequestFormatIncomp(std::vector<std::string> warray)
{
	if (this->isWordInArray(warray, "CAP")
		|| this->isWordInArray(warray, "NICK")
		|| this->isWordInArray(warray, "USER")
		|| this->isWordInArray(warray, "PASS"))
		return true;
	return false;
}

bool						Server::_checkPassword(std::vector<std::string> warray)
{
//	size_t pos = 0;
	std::vector<std::string>::iterator it = warray.begin();
	std::vector<std::string>::iterator ite = warray.end();

	for(; it != ite; it++)
		if ((*it).find("PASS") != std::string::npos)
		{
//			pos = (*it).find("PASS");
			std::string pswrd = (*it).substr(5);
			if (pswrd == _socket.getPswrd())
				return true;
		}
	return false;
}

bool						Server::isWordInArray(std::vector<std::string> warray, std::string word)
{
	std::vector<std::string>::iterator it = warray.begin();
	std::vector<std::string>::iterator ite = warray.end();

	for(; it != ite; it++)
	{
		if ((*it).find(word) != std::string::npos) 
				return true;
	}
	return false;
}

bool								Server::checkChannel(std::string cname)
{
	std::vector<Channel *>				_channels = getChannels();
	std::vector<Channel *>::iterator	it = _channels.begin();
	std::vector<Channel *>::iterator	ite = _channels.end();

	for (; it != ite; ++it)
	{
		std::cout << (*it)->getName() << std::endl;

		if ((*it)->getName() == cname)
			return true;
	}
	return false;
}

//							USERS

User						*Server::getUserByName(std::string name)
{
	if (_users.size() == 0)
		return NULL;
	std::vector<User *>::iterator it = _users.begin();
	std::vector<User *>::iterator ite = _users.end();

	for (; it != ite; ++it)
		if ((*it)->getNickname() == name)
			return *it;
	return NULL;
}