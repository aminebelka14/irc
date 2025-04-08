/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:52:57 by amine             #+#    #+#             */
/*   Updated: 2022/11/23 20:20:15 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include "../includes/Invoker.hpp"

Server::Server(): _socket()
{ 
	FD_ZERO(&_set);
}

Server::Server(Server const &src) { *this = src; }

Server::~Server()
{
	for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); ++it)
		delete(*it);
	_users.clear();
	for (std::vector<Channel *>::iterator it2 = _channels.begin(); it2 != _channels.end(); ++it2)
		delete(*it2);
	_channels.clear();

}

Server	&Server::operator=(Server const &rhs)
{
	if (this == &rhs)
		return (*this);
	this->_socket = rhs._socket;
	this->_channels = rhs._channels;
	this->_fdtab = rhs._fdtab;
	this->_rset = rhs._rset;
	this->_set = rhs._set;
	this->_fdtab = rhs._fdtab;
	return (*this);
}

void			Server::addUser(std::vector<std::string> warray, int fd)
{
	bool								free = true;
	User								*user = NULL;
	std::vector<std::string>::iterator	it = warray.begin();
	std::vector<std::string>::iterator	ite = warray.end();
	std::vector<User *>::iterator		uit = _users.begin();
	std::vector<User *>::iterator		uite = _users.end();

	for (; uit != uite; ++uit)
	{
		if ((*uit)->getFd() == fd)
		{
			user = (*uit);
			break;
		}
	}

	std::string							nick;

	for (; it != ite; ++it)
		if ((*it).find("NICK") != std::string::npos)
		{
			nick = (*it).substr(5);
			for (; uit != uite; uit++)
			{
				if ((*uit)->getNickname() == nick)
				{
					std::string msg = ":";
					msg += ERR_NICKNAMEINUSE(nick);
					send(fd, msg.c_str(), msg.length(), 0);
					free = false;
				}
			}
			if (free)
				user->setNickname(nick);
		}

	std::string							reply;

	user->findName(warray);
	if (user->getNickname() != "" && user->getUsername() != "")
	{
		user->setPartial(false);
		reply = user->getPrefix();
		reply += RPL_WELCOME(user->getNickname(), user->getUsername(), user->getHostname());
		reply += "\r\n";
		sendReply(reply, *user);
		user->setJoin(true);
	}
}

void							Server::addUserIncomplete(std::vector<std::string> warray, int fd, bool full)
{
	User								*user = NULL;
	std::vector<std::string>::iterator	it = warray.begin();

	for (std::vector<User *>::iterator uit = _users.begin(); uit != _users.end(); uit++) {
		if ((*uit)->getFd() == fd) {
			user = *uit;
			break ;
		}
	}

	std::string 						reply = user->getPrefix();
	std::string							nick;
	bool								free = true;

	if (user != NULL)
	{
		for (; it != warray.end(); it++)
		{
			if ((*it).find("NICK") != std::string::npos)
			{
				nick = (*it).substr(5);
				if (full == false)
				{
					for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); it++)
					{
						if ((*it)->getNickname() == nick)
						{
							std::string msg = ":";
							msg += ERR_NICKNAMEINUSE(nick);
							send(fd, msg.c_str(), msg.length(), 0);
							free = false;
						}
					}
					if (free)
						user->setNickname(nick);
				}
			}
			if (it->find("PASS") != std::string::npos)
				user->setPass(it->substr(5));
			if (it->find("USER") != std::string::npos)
				user->findName(warray);
		}
		if (user->getNickname() != "" && user->getPass() != "" && user->getUsername() != "" && user->getPass() == this->_socket.getPswrd())
		{
			user->setPartial(false);
			reply += RPL_WELCOME(user->getNickname(), user->getUsername(), user->getHostname());
			reply += "\r\n";
			this->sendReply(reply, *user);
			user->setJoin(true);
		}
	}
}

void							Server::_manageRequest(int const fd)
{
	bzero(this->_buff, sizeof(this->_buff));
	if (recv(fd, this->_buff, BUFF_SIZE, 0) <= 0)
	{
		disconnectClient(fd);
		return;
	}

	std::cout << "\n		CLIENT :\n" << _buff << std::endl;

	std::vector<std::string>	warray = str_to_warray(_buff, "\r\n");
	bool						cmd = true;
	bool						full = false;

	if (checkRequestFormatFull(warray) == true && _checkPassword(warray) == true && ifJoinServer(fd) == false) // Full user connect
	{
		addUser(warray, fd);
		cmd = false;
		full = true;
	}
	if (checkRequestFormatIncomp(warray) && isIncomplete(fd) && ifJoinServer(fd) == false)
	{
		addUserIncomplete(warray, fd, full);
		cmd = false;
	}
	if (cmd == true && ifJoinServer(fd) == true)
	{
		Invoker					inv;
		std::string				tmp;
		for (size_t i = 0; i < _users.size(); ++i)
			if (_users[i]->getFd() == fd)
			{
				tmp = inv.parser(warray, _users[i], *this);
				std::cout << "\n		SERVER :\n" << tmp << std::endl;
			}
	}
}

void					Server::_connectClient()
{
	int					c_fd;
	struct sockaddr_in 	c_addr;
	socklen_t			len = sizeof(c_addr);

	if ((c_fd = accept(_socket.getSfd(), (struct sockaddr *)&c_addr, &len)) < 0)
		printexit("accept failed", 1);
	if (fcntl(c_fd, F_SETFL, O_NONBLOCK) < 0)
		printexit("fcntl failed", 1);

	User	*user = new User(c_fd);
	
	user->setNickname("");
	user->setHostname(std::string(inet_ntoa(c_addr.sin_addr)));
	_users.push_back(user);
	_fdtab.push_back(c_fd);
	FD_SET(c_fd, &_set);
}

void					Server::disconnectClient(int fd)
{
	close(fd);
	FD_CLR(fd, &_set);
	for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if ((*(*it)).getFd() == fd)
		{
			delete (*it);
			_users.erase(it);
			break ;
		}
	}
	for (std::vector<int>::iterator it = _fdtab.begin(); it != _fdtab.end(); it++)
	{
		if (*it == fd)
		{
			_fdtab.erase(it);
			break ;
		}
	}
}

void					Server::initServer(const short &port, const std::string &pswrd)
{
	int		rval;

 	_socket.initSock(port, pswrd);
	FD_ZERO(&_set);
	FD_SET(_socket.getSfd(), &_set);
	
	while (running == true) // Add switch later
	{
		_rset = _set;
		if ((rval = select(_fdMax() + 1, &_rset, NULL, NULL, NULL)) < 0)
			continue;
		for (int fd = 0; fd <= _fdMax(); ++fd)
		{
			if (FD_ISSET(fd, &_rset))
			{
				if (fd == _socket.getSfd())
				{
					_connectClient();
					break;
				}
				else
				{
					_manageRequest(fd);
					continue;
				}
			}
		}
	}
}
