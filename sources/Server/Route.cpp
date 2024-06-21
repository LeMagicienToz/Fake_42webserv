/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 21:47:19 by mconreau          #+#    #+#             */
/*   Updated: 2024/06/16 21:23:26 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Route.hpp"

Route::Route() 
{
}

Route::Route(const Route &src)
{
	*this = src;
}

Route::~Route()
{
}

bool
Route::match(Request &request) const
{
	if (this->_target == request.getTarget())
		return (true);
	return (false);
}

Route&
Route::operator=(const Route &rhs)
{
	(void) rhs;
	return (*this);
}
