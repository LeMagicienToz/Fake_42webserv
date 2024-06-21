/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 11:55:14 by mconreau          #+#    #+#             */
/*   Updated: 2024/05/10 19:27:26 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger/Logger.hpp"

void
Logger::dump(const string &message)
{
	Logger::write("\001\33[1;35m\002DUMP\001\33[0;37m\002", message);
}

void
Logger::fail(const string &message)
{
	Logger::write("\001\33[1;31m\002FAIL\001\33[0;37m\002", message);
}

void
Logger::logs(const string &message)
{
	Logger::write("\001\33[1;37m\002LOGS\001\33[0;37m\002", message);
}

void
Logger::info(const string &message)
{
	Logger::write("\001\33[1;34m\002INFO\001\33[0;37m\002", message);
}

void
Logger::warn(const string &message)
{
	Logger::write("\001\33[1;33m\002WARN\001\33[0;37m\002", message);
}

void
Logger::write(const string &level, const string &message)
{
	IO::out("[" + Datetime() + "][" + level + "] " + message + "\n");
}
