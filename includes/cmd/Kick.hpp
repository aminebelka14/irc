/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:22:25 by amine             #+#    #+#             */
/*   Updated: 2022/11/21 19:23:55 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KICK_HPP
# define KICK_HPP

#include "../lib.hpp"
#include "../Command.hpp"

class Kick : public Command
{
	public:
		Kick();
		virtual ~Kick();

		bool				checkChannel(std::string cname, Server &server);
		bool				checkUserInChannel(std::string name, std::string chan, Server &server);

		std::string			execute(std::string str, User *user, Server &server);

};

#endif