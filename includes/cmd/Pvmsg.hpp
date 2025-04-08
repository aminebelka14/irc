/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pvmsg.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:26:44 by amine             #+#    #+#             */
/*   Updated: 2022/11/15 17:37:56 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PVMSG_HPP
# define PVMSG_HPP

#include "../lib.hpp"
#include "../Command.hpp"

class Pvmsg : public Command
{
	public:
		Pvmsg();
		virtual ~Pvmsg();

		std::string execute(std::string str, User *user, Server &server);

};

#endif