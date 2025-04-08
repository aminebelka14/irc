/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:06:58 by amine             #+#    #+#             */
/*   Updated: 2022/11/21 17:29:00 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.hpp"
#include "User.hpp"

class Channel
{
	public:
		Channel();
		Channel(std::string chan);
		Channel(std::string chan, User *adm);
		~Channel();

		std::string				getName();
		User					*getAdmin();
		std::string				getTopic();
		std::vector<User *>		getUsers();
		User					*getUser(std::string);

		void					setName(std::string);
		void					setAdmin(User *);
		void					setTopic(std::string);
		void					addUser(User *);

		bool					checkName(std::string);
		bool					checkUser(User *);
		bool					checkUser(std::string);

		void					rmvUser(User *);

	private:
		std::string			_name;
		User				*_admin;
		std::string			_topic;
		std::vector<User *>	_users;
};