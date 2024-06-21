/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:16:33 by mconreau          #+#    #+#             */
/*   Updated: 2024/05/10 17:59:25 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Logger/Logger.hpp"
#include "Server/Server.hpp"
#include "Support/Extends/Abortable.hpp"
#include "Support/Helpers/String.hpp"
#include <fstream>
#include <sys/epoll.h>
#include <vector>

class Configuration : public Abortable
{
	private  :
		vector<Server*>				_servers;

	public   :
									Configuration(const string &config, const int &epollfd);
									Configuration(const Configuration& src);
									~Configuration();

		Configuration&				operator=(const Configuration& rhs);
									operator vector<Server*>() const;
};
