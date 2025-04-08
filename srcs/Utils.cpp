/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:31:23 by amine             #+#    #+#             */
/*   Updated: 2022/11/15 17:18:19 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.hpp"

std::vector<std::string>	str_to_warray(std::string str, std::string sep)
{
	std::vector<std::string> words;
	size_t pos;

	while ((pos = str.find(sep)) != std::string::npos)
	{
		words.push_back(str.substr(0, pos));
		str.erase(0, pos + sep.length());
	}
	words.push_back(str);
	return words;
}

void						printexit(char const *str, int code)
{
	std::cerr << "Error : " << str << " with code : " << code << std::endl;
	exit(code);
}
