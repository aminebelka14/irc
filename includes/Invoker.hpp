/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invoker.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 00:28:02 by amine             #+#    #+#             */
/*   Updated: 2022/11/15 17:49:35 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVOKER_HPP
# define INVOKER_HPP

#include "lib.hpp"
#include "Server.hpp"
#include "Command.hpp"

class Invoker
{
	public:
		Invoker();
		virtual	~Invoker();
		std::string		parser(std::vector<std::string> buffer, User *user, Server &server);
		
	private:
		std::vector<Command *>		_cmds;
};

#endif