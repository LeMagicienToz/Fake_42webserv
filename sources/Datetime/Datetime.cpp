/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Datetime.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 21:49:14 by mconreau          #+#    #+#             */
/*   Updated: 2024/05/19 10:35:21 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Datetime/Datetime.hpp"

const char*	Datetime::DEFAULT 		= "%y-%m-%d %h:%i:%s";
const char*	Datetime::RFC0850 		= "%l, %d-%M-%y %h:%i:%s %e";
const char*	Datetime::RFC7231 		= "%D, %d %M %y %h:%i:%s GMT";

const char*	Datetime::M_SHRT_NAME[]	= {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
	};

const char*	Datetime::M_LONG_NAME[] = {
	"January", "February", "March", "April", "May", "June", "July", "August", "September",
	"October", "November", "December"
	};

const char*	Datetime::W_SHRT_NAME[] = {
	"Sun", "Mon", "Tues", "Wed", "Thurs", "Fri", "Sat"
	};

const char*	Datetime::W_LONG_NAME[] = {
	"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
	};


Datetime::Datetime(const string &format, const time_t time) :
	_timestamp(time),
	_formatted(format)
{
	const tm*	tm = ::localtime(&this->_timestamp);

	this->_formatted = String::replace(this->_formatted, "%y", String::tostr(tm->tm_year + 1900));
	this->_formatted = String::replace(this->_formatted, "%m", (tm->tm_mon  < 9  ? "0" : "") + String::tostr(tm->tm_mon + 1));
	this->_formatted = String::replace(this->_formatted, "%F", Datetime::M_LONG_NAME[tm->tm_mon]);
	this->_formatted = String::replace(this->_formatted, "%M", Datetime::M_SHRT_NAME[tm->tm_mon]);
	this->_formatted = String::replace(this->_formatted, "%d", (tm->tm_mday < 10 ? "0" : "") + String::tostr(tm->tm_mday));
	this->_formatted = String::replace(this->_formatted, "%l", Datetime::W_LONG_NAME[tm->tm_wday]);
	this->_formatted = String::replace(this->_formatted, "%D", Datetime::W_SHRT_NAME[tm->tm_wday]);
	this->_formatted = String::replace(this->_formatted, "%h", (tm->tm_hour < 10 ? "0" : "") + String::tostr(tm->tm_hour));
	this->_formatted = String::replace(this->_formatted, "%i", (tm->tm_min  < 10 ? "0" : "") + String::tostr(tm->tm_min));
	this->_formatted = String::replace(this->_formatted, "%s", (tm->tm_sec  < 10 ? "0" : "") + String::tostr(tm->tm_sec));
	this->_formatted = String::replace(this->_formatted, "%e", tm->tm_zone);
}

Datetime::Datetime(const Datetime &src)
{
	*this = src;
}

Datetime::~Datetime()
{
}

string
Datetime::getFormatted() const
{
	return (this->_formatted);
}

time_t
Datetime::getTimestamp() const
{
	return (this->_timestamp);
}

Datetime&
Datetime::operator=(const Datetime &rhs)
{
	this->_formatted = rhs._formatted;
	this->_timestamp = rhs._timestamp;
	return (*this);
}

string
Datetime::operator+(const string &rhs) const
{
	return (this->_formatted + rhs);
}

Datetime::operator string() const
{
	return (this->_formatted);
}

ostream&
operator<<(ostream &ostream, const Datetime &rhs)
{
	return (ostream << rhs.getFormatted());
}

string
operator+(const string &lhs, const Datetime &rhs)
{
	return (lhs + rhs.getFormatted());
}
