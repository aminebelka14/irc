/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:26:14 by amine             #+#    #+#             */
/*   Updated: 2022/11/15 17:38:02 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PING_HPP
# define PING_HPP

#include "../lib.hpp"
#include "../Command.hpp"

class Ping : public Command
{
	public:
		Ping();
		virtual ~Ping();

		std::string execute(std::string str, User *user, Server &server);

};

#endif