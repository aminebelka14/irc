/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:41:48 by amine             #+#    #+#             */
/*   Updated: 2022/11/23 19:44:47 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lib.hpp"
#include "includes/Server.hpp"
#include "includes/Socket.hpp"
#include <signal.h>

bool	running = true;

void	handler(int sig)
{
	std::cout << std::endl << "[Quit]" << std::endl;
	if (SIGINT == sig)
	{
		running = false;
	}
}

int		main(int ac, char **av)
{
	Server	serv;

	signal(SIGINT, handler);
	if (ac != 3)
		printexit("Argument must be port and password\n", 1);
	for (int i = 0; av[1][i]; ++i)
		if (!isdigit(av[1][i]))
			printexit("Port must be only numerical\n", 1);
	serv.initServer(atoi(av[1]), av[2]);
}