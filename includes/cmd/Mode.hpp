/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:23:47 by amine             #+#    #+#             */
/*   Updated: 2022/11/18 19:07:00 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_HPP
# define MODE_HPP

#include "../lib.hpp"
#include "../Command.hpp"

class Mode : public Command
{
	public:
		Mode();
		virtual ~Mode();

		std::string		execute(std::string str, User *user, Server &server);

	private:
		Channel			*getChannel(std::string cname, Server &server);
		bool			checkAdmin(std::string uname, std::string cname, Server &server);
};

#endif