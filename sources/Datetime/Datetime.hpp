/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Datetime.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 21:24:13 by mconreau          #+#    #+#             */
/*   Updated: 2024/05/19 10:35:10 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Support/Helpers/String.hpp"
#include <ctime>
#include <string>

using namespace std;



class Datetime
{
	
	public   :
		static const char*			DEFAULT;
		static const char*			RFC0850;
		static const char*			RFC7231;

	private  :
		static const char*			M_SHRT_NAME[];
		static const char*			M_LONG_NAME[];
		static const char*			W_SHRT_NAME[];
		static const char*			W_LONG_NAME[];
	
	private  :
		time_t						_timestamp;
		string						_formatted;

	public   :
									Datetime(const string &format = Datetime::DEFAULT, const time_t time = ::time(0));
									Datetime(const Datetime &src);
									~Datetime();

		string						getFormatted() const;
		time_t						getTimestamp() const;

	public   :
		Datetime&					operator=(const Datetime &rhs);
		string 						operator+(const string &rhs) const;
									operator string() const;
};

ostream&	operator<<(ostream &ostream, const Datetime &rhs);
string 		operator+(const string &lhs, const Datetime &rhs);
