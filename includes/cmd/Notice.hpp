/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Notice.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:25:16 by amine             #+#    #+#             */
/*   Updated: 2022/11/15 17:38:09 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOTICE_HPP
# define NOTICE_HPP

#include "../lib.hpp"
#include "../Command.hpp"

class Notice : public Command
{
	public:
		Notice();
		virtual ~Notice();

		std::string execute(std::string str, User *user, Server &server);

};

#endif