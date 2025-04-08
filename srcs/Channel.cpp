/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:10:18 by amine             #+#    #+#             */
/*   Updated: 2022/11/23 20:21:01 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"


Channel::Channel() {}

Channel::Channel(std::string chan) : _name(chan), _admin(NULL) {}

Channel::~Channel() {}

Channel::Channel(std::string chan, User *adm) : _name(chan), _admin(adm) {}

void				Channel::setName(std::string name) { _name = name; }
void				Channel::setAdmin(User *admin) { _admin = admin; }
void				Channel::setTopic(std::string topic) { _topic = topic; }
void				Channel::addUser(User *user) { _users.push_back(user); }

std::string			Channel::getName() { return _name; }
User				*Channel::getAdmin() { return _admin; }
std::string			Channel::getTopic() { return _topic; }
std::vector<User *>	Channel::getUsers() { return _users; }

User				*Channel::getUser(std::string uname)
{
	std::vector<User *>::iterator it = _users.begin();
	std::vector<User *>::iterator ite = _users.end();

	for (; it != ite; ++it)
		if ((*it)->getNickname() == uname)
			return *it;
	return NULL;
}

bool				Channel::checkUser(User *user)
{
	std::vector<User *>::iterator it = _users.begin();
	std::vector<User *>::iterator ite = _users.end();

	for (; it != ite; ++it)
		if (*it == user)
			return true;
	return false;
}

bool				Channel::checkUser(std::string name)
{
	std::vector<User *>::iterator it = _users.begin();
	std::vector<User *>::iterator ite = _users.end();

	for (; it != ite; ++it)
		if ((*it)->getNickname() == name)
			return true;
	return false;
}

bool					Channel::checkName(std::string name)
{
	if (name.empty() || name.size() > 50 || (name[0] != '#' && name[0] != '&')) 
		return false;
	for (size_t i = 0; i < name.size(); i++)
		if (name[i] == ' ' || name[i] == '\a' || name[i] == ',')
			return false;
	return true;
}

void					Channel::rmvUser(User *user)
{
	std::vector<User *>::iterator it = _users.begin();
	std::vector<User *>::iterator ite = _users.end();

	for (; it != ite; ++it)
		if ((*it)->getFd() == user->getFd())
		{
			_users.erase(it);
			return;
		}
}