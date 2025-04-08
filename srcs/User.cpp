/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:02:48 by amine             #+#    #+#             */
/*   Updated: 2022/11/21 16:34:39 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"

User::User(int fd)
{
	_fd = fd;
	_join = false;
	_partial = true;
}

User		&User::operator=(User const &src)
{
	if (this == &src)
		return *this;
	this->_fd = src._fd;
	this->_nick = src._nick;
	this->_nhost = src._nhost;
	this->_nuser = src._nuser;
	return *this;
}

User::User(User const &src) { *this = src; }

User::~User() {}

void						User::setJoin(bool join) { _join = join; } // To change
void						User::setPartial(bool partial) { _partial = partial; } // To change
void						User::setFd(int fd) { _fd = fd; }
void						User::setNickname(std::string nick) { _nick = nick; }
void						User::setUsername(std::string nuser) { _nuser = nuser; }
void						User::setHostname(std::string nhost) { _nhost = nhost; }
void						User::setPass(std::string pass) { _pass = pass; }

bool						User::getJoin() { return _join; } // To change
bool						User::getPartial() { return _partial; } // To change
int const					&User::getFd() { return _fd; }
std::string const 			&User::getNickname() { return _nick; }
std::string const 			&User::getUsername() { return _nuser; }
std::string const 			&User::getHostname() { return _nhost; }
std::string const			&User::getPass() { return _pass; }
std::vector<std::string>	User::getBanChans() { return _banChannels; }

std::string					User::getPrefix()
{
	std::string		prefix;

	prefix += ":";
	prefix += _nick;
	prefix += "!";
	prefix += _nuser;
	prefix += "@";
	prefix += _nhost;
	return prefix;
}

bool						User::checkBan(std::string name)
{
	std::vector<std::string>::iterator it = _banChannels.begin();
	std::vector<std::string>::iterator ite = _banChannels.end();

	for (; it != ite; ++it)
		if (*it == name)
			return true;
	return false;
}

void						User::addBanChans(std::string name) { _banChannels.push_back(name); }

void						User::rmvBanChans(std::string name)
{
	std::vector<std::string>::iterator it = _banChannels.begin();
	std::vector<std::string>::iterator ite = _banChannels.end();

	for (; it != ite; ++it)
		if ((*it) == name)
			_banChannels.erase(it);
}

void						User::findName(std::vector<std::string> warray) 
{
	std::vector<std::string>::iterator it = warray.begin();
	std::vector<std::string>::iterator ite = warray.end();

	for (; it != ite; it++) {
		if ((*it).find("USER") != std::string::npos) 
		{
			std::string		temp = (*it).substr(5);
			int				end = temp.find(" ");
			this->setUsername(temp.substr(0, end));
		}
	}
}