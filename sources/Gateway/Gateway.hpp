/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Gateway.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muteza <muteza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:27:09 by mconreau          #+#    #+#             */
/*   Updated: 2024/06/21 16:41:59 by muteza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Http/Request.hpp"
#include <string>

class Gateway
{
	public   :
		Gateway();
		Gateway(const Gateway &src);
		~Gateway();
		Gateway&	operator=(const Gateway &rhs);

		
		const char *getAbsolutePathOfFile(const char *fileName);
		void	 addenv(const std::string& key, const std::string& value);
		char	**put_to_env();
		std::string	cgirun(Request& req);
	public   :
		std::vector<std::string> v;
};

