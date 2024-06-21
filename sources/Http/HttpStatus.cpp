/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpStatus.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:05:21 by mconreau          #+#    #+#             */
/*   Updated: 2024/06/13 14:36:34 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Http/HttpStatus.hpp"

HttpStatus::HttpStatus()
{
	this->_status[200] 		= "OK";
	this->_status[201] 		= "Created";
	this->_status[202] 		= "Accepted";
	this->_status[203] 		= "Non-Authoritative Information";
	this->_status[204] 		= "No Content";
	this->_status[205] 		= "Reset Content";
	this->_status[206] 		= "Partial Content";
	this->_status[207] 		= "Multi-Status";
	this->_status[208] 		= "Already Reported";

	this->_status[300] 		= "Multiple Choices";
	this->_status[301] 		= "Moved Permanently";
	this->_status[302] 		= "Found";
	this->_status[303] 		= "See Other";
	this->_status[304] 		= "Not Modified";
	this->_status[305] 		= "Use Proxy";
	this->_status[306] 		= "Switch Proxy";
	this->_status[307] 		= "Temporary Redirect";
	this->_status[308] 		= "Permanent Redirect";

	this->_status[400] 		= "Bad Request";
	this->_status[401] 		= "Unauthorized";
	this->_status[402] 		= "Payment Required";
	this->_status[403] 		= "Forbidden";
	this->_status[404] 		= "Not Found";
	this->_status[405] 		= "Method Not Allowed";
	this->_status[406] 		= "Not Acceptable";
	this->_status[407] 		= "Proxy Authentication Required";
	this->_status[408] 		= "Request Timeout";
	this->_status[409] 		= "Conflict";
	this->_status[410] 		= "Gone";
	this->_status[411] 		= "Length Required";
	this->_status[412] 		= "Precondition Failed";
	this->_status[413] 		= "Payload Too Large";
	this->_status[414] 		= "URI Too Long";
	this->_status[415] 		= "Unsupported Media Type";
	this->_status[416] 		= "Range Not Satisfiable";
	this->_status[417] 		= "Expectation Failed";
	this->_status[418] 		= "I'm a teapot";
	this->_status[421] 		= "Misdirected Request";
	this->_status[422] 		= "Unprocessable Content";
	this->_status[423] 		= "Locked";
	this->_status[424] 		= "Failed Dependency";
	this->_status[425] 		= "Too Early";
	this->_status[426] 		= "Upgrade Required";
	this->_status[428] 		= "Precondition Required";
	this->_status[429] 		= "Too Many Requests";
	this->_status[431] 		= "Request Header Fields Too Large";
	this->_status[451] 		= "Unavailable For Legal Reasons";

	this->_status[500] 		= "Internal Server Error";
	this->_status[501] 		= "Not Implemented";
	this->_status[502] 		= "Bad Gateway";
	this->_status[503] 		= "Service Unavailable";
	this->_status[504] 		= "Gateway Timeout";
	this->_status[505] 		= "HTTP Version Not Supported";
	this->_status[506] 		= "Variant Also Negotiates";
	this->_status[507] 		= "Insufficient Storage";
	this->_status[508] 		= "Loop Detected";
	this->_status[510] 		= "Not Extended";
	this->_status[511] 		= "Network Authentication Required";
}

HttpStatus::HttpStatus(const HttpStatus &src)
{
	*this = src;
}

HttpStatus::~HttpStatus()
{
}

string
HttpStatus::get(const size_t &status)
{
	return (this->_status.find(status) != this->_status.end() ? this->_status[status] : "");
}

HttpStatus&
HttpStatus::operator=(const HttpStatus &rhs)
{
	this->_status = rhs._status;
	return (*this);
}
