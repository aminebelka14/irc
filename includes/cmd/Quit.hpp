/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:27:11 by amine             #+#    #+#             */
/*   Updated: 2022/11/15 17:37:48 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUIT_HPP
# define QUIT_HPP

#include "../lib.hpp"
#include "../Command.hpp"

class Quit : public Command
{
	public:
		Quit();
		virtual ~Quit();

		std::string execute(std::string str, User *user, Server &server);
};

#endif