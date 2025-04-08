/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:19:18 by amine             #+#    #+#             */
/*   Updated: 2022/11/15 17:38:23 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOIN_HPP
# define JOIN_HPP

#include "../lib.hpp"
#include "../Command.hpp"

class Join : public Command
{
	public:
		Join();
		virtual ~Join();

		std::string execute(std::string str, User *user, Server &server);

};

#endif