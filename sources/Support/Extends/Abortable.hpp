/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Abortable.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:35:04 by mconreau          #+#    #+#             */
/*   Updated: 2024/06/09 15:30:02 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Console/IO.hpp"
#include "Logger/Logger.hpp"
#include <iostream>
#include <string>

using namespace std;

class Abortable
{
	protected:
		bool							_status;

	protected:
										Abortable();
										Abortable(const Abortable &src);
		virtual							~Abortable() = 0;

		Abortable&						operator=(const Abortable &rhs);
	
	public   :
		bool							abort(const string &message = "");
		bool							status() const;
};
