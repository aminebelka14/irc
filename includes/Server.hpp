/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:49:53 by amine             #+#    #+#             */
/*   Updated: 2022/11/22 14:01:49 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "lib.hpp"
#include "Socket.hpp"
#include "User.hpp"
#include "Channel.hpp"

class Server
{
	//	Constructor
	public:
		Server();
		Server(Server const &src);
		~Server();
		Server &operator=(Server const &rhs);

	//	GS
		Channel						*getChannel(std::string chan_name);
		std::vector<User *>			getUsers();
		std::vector<User *>			getChannelUsers(std::string chan_name);	
		std::vector<Channel *>		getChannels();
		User						*getUserByName(std::string);
	
	//	Checks
		bool						isWordInArray(std::vector<std::string> warray, std::string word);
		bool						checkRequestFormatFull(std::vector<std::string> warray);
		bool						checkRequestFormatIncomp(std::vector<std::string> warray);
		bool						ifJoinServer(int fd);
		bool						isIncomplete(int fd);
		bool						checkUser(std::string);
		bool						checkChannel(std::string);
	
	//	Members
		void						initServer(const short &port, const std::string &pswrd);
		void						addUser(std::vector<std::string> warray, int fd);
		void						addUserIncomplete(std::vector<std::string> warray, int fd, bool full);
		void						sendReply(std::string reply, User &user);
		void						addChannel(std::string chan_name);
		void						disconnectClient(int fd);
	
	
	private:
	//	_Members
		int				_fdMax();
		void			_connectClient();
		void			_manageRequest(int const fd);
		bool			_checkPassword(std::vector<std::string> warray);
		bool			_isNickAvailable(User *user, std::string nick);


	//	_Variables
		Socket					_socket;
		fd_set					_set;
		fd_set					_rset;
		std::vector<int>		_fdtab;
		std::vector<User *>		_users;
		std::vector<Channel *>	_channels;
		char					_buff[4096];
};

#endif