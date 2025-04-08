/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:55:32 by amine             #+#    #+#             */
/*   Updated: 2022/11/21 21:34:26 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

#include "lib.hpp"

class User
{
	//	Constructor
	public:
		User(int fd);
		User(User const &src);
		User &operator=(User const &src);
		
	//	Destructor
		~User();

	//	GS
	void						setFd(int);
	void						setNickname(std::string);
	void						setUsername(std::string);
	void						setHostname(std::string);
	void						setPass(std::string);
	void						setPartial(bool);
	void						setJoin(bool);
	
	int const					&getFd();
	std::string const			&getNickname();
	std::string const			&getUsername();
	std::string const			&getHostname();
	std::string const			&getPass();
	bool						getJoin();
	bool						getPartial();
	std::string					getPrefix();
	std::vector<std::string>	getBanChans();

	//	Members
	void						findName(std::vector<std::string>);
	bool						checkBan(std::string chan);
	void						addBanChans(std::string name);
	void						rmvBanChans(std::string name);

	protected:
	//	Variables
		int							_fd;
		std::string					_nick;
		std::string					_nuser;
		std::string					_nhost;
		std::string					_pass;
		bool						_join;
		bool						_partial;
		std::vector<std::string>	_banChannels;
};

#endif