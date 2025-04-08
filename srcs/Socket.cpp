/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:53:10 by amine             #+#    #+#             */
/*   Updated: 2022/11/15 21:33:57 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Socket.hpp"

Socket::Socket(): _sfd(0), _port(htons(PORT)), _pswrd()
{ memset(&this->_addrin, 0, sizeof(struct sockaddr)); }

Socket::~Socket() {}

Socket::Socket(Socket const &src) { *this = src; }

Socket	&Socket::operator=(Socket const &rhs)
{
	if (this == &rhs)
		return (*this);
	this->_sfd = rhs._sfd;
	this->_port = rhs._port;
	this->_addrin = rhs._addrin;
	return (*this);
}


int const					&Socket::getSfd() const { return this->_sfd; }
short const					&Socket::getPort() const { return this->_port; }
std::string const			&Socket::getPswrd() const { return this->_pswrd; }
struct sockaddr_in const	&Socket::getAddrin() const { return this->_addrin; }

void						Socket::setPswrd(std::string pswrd) { this->_pswrd = pswrd; }
void						Socket::setSfd(int sfd) { this->_sfd = sfd; }

void						Socket::initSock(short const &port, std::string const &pswrd)
{
	setPswrd(pswrd);
	_setSock(port);
}

#include <errno.h>

void						Socket::_setSock(short const &port)
{
	int	optval = 1; // for setsocketoption

	if ((this->_sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printexit("socket failed", 1);
	this->_addrin.sin_family = AF_INET;
	this->_addrin.sin_addr.s_addr = htonl(INADDR_ANY);
	this->_addrin.sin_port = htons(port);

	if (setsockopt(getSfd(), SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) < 0)
	{
		close(getSfd());
		printexit("setsockopt failed", 1);
	}
	if (fcntl(getSfd(), F_SETFL, O_NONBLOCK) < 0)
	{
		close(getSfd());
		printexit("fcntl failed", 1);
	}
	if (bind(getSfd(), (struct sockaddr *)&this->_addrin, sizeof(struct sockaddr)) < 0)
		printexit("bind failed", 1);
	if (listen(getSfd(), SOMAXCONN) < 0)
		printexit("listen failed", 1);
}
