/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 00:31:36 by amine             #+#    #+#             */
/*   Updated: 2022/11/15 17:53:08 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

#include "lib.hpp"
#include "User.hpp"
#include "Server.hpp"

class Command
{
	public:
		Command() {};
		virtual	~Command() {};

		std::string				getCmdName() const { return _cname; };
		virtual std::string		execute(std::string str, User *user, Server &server) = 0;
		
	protected:
		User				*_from;
		std::string			_cname;
		std::string			_args;
		std::string			_desc;
};

#endif