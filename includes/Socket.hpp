/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:59:27 by amine             #+#    #+#             */
/*   Updated: 2022/11/14 20:59:45 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

#include "lib.hpp"

class Socket
{
	public:
	//	Constructor
		Socket();
		Socket(Socket const &src);
		Socket &operator=(Socket const &src);

	//	Destructor
		~Socket();


	//	GS
		int const					&getSfd() const;
		short const					&getPort() const;
		std::string const			&getPswrd() const;
		struct sockaddr_in const	&getAddrin() const;

		void						setSfd(int sfd);
		void						setPswrd(std::string const pswrd);


	//	Members
		void						initSock(short const &port, std::string const &pswrd);


	private:
	//	_Members
		void						_setSock(const short &port);


	//	_Variables
		int					_sfd;
		short				_port;
		std::string			_pswrd;
		struct sockaddr_in	_addrin;
};

#endif