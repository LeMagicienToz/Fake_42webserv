/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:12:58 by mconreau          #+#    #+#             */
/*   Updated: 2024/05/10 18:36:53 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Console/IO.hpp"
#include "Datetime/Datetime.hpp"
#include <iostream>
#include <string>

using namespace std;

class Logger
{
	private  :
		virtual						~Logger() = 0;

	public   :
		static void					dump(const string &message);
		static void					fail(const string &message);
		static void					logs(const string &message);
		static void					info(const string &message);
		static void					warn(const string &message);

	private  :
		static void					write(const string &level, const string &message);
};
