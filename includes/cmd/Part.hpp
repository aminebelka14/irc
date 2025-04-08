/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:25:45 by amine             #+#    #+#             */
/*   Updated: 2022/11/15 17:38:06 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PART_HPP
# define PART_HPP

#include "../lib.hpp"
#include "../Command.hpp"

class Part : public Command
{
	public:
		Part();
		virtual ~Part();

		std::string execute(std::string str, User *user, Server &server);

};

#endif