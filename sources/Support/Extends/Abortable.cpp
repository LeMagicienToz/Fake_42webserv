/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Abortable.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:35:03 by mconreau          #+#    #+#             */
/*   Updated: 2024/06/09 15:29:55 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Support/Extends/Abortable.hpp"

Abortable::Abortable() :
	_status(true)
{
}

Abortable::Abortable(const Abortable &src)
{
	*this = src;
}

Abortable::~Abortable()
{
}

bool
Abortable::abort(const string &message)
{
	if (message.size())
		Logger::fail("\001\33[1;31m\002ABORTING\001\33[0;37m\002: " + message);
	return (this->_status = false);
}

bool
Abortable::status() const
{
	return (this->_status);
}

Abortable&
Abortable::operator=(const Abortable &rhs)
{
	this->_status = rhs._status;
	return (*this);
}
