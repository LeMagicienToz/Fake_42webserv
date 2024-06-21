/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muteza <muteza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 20:09:26 by mconreau          #+#    #+#             */
/*   Updated: 2024/06/21 16:22:50 by muteza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Http/Request.hpp"

Request::Request(const int &socket) :
	_socket(socket),
	_status(200)
{
}

Request::Request(const Request &src) :
	Abortable(src)
{
	*this = src;
}

Request::~Request()
{
}

void
Request::recv()
{
	const string	packet(Filesystem::recv(this->_socket));
	// std::cout << packet << std::endl;

	size_t 			p = packet.find("\r\n\r\n");
	const string 	h(packet.substr(0, p));
	stringstream	stream(h.substr(0, (p = h.find("\r\n", 0) + 2) - 2));

	if (!(stream >> this->_method >> this->_target >> this->_version))
		this->abort();
	else
	{
		size_t	m;
		if ((m = this->_target.find('?')) != string::npos)
		{
			this->_params = this->_target.substr(m + 1);
			this->_target = this->_target.substr(0, m);
		}

		size_t	e, f;
		this->_packet = packet.substr(packet.find("\r\n\r\n") + 4);
		this->_length = this->_packet.size();
		
		while ((e = h.find("\r\n", p)) != string::npos)
		{
			string	lne(h.substr(p, e - p));
			string 	key(lne.substr(0, f = lne.find(':')));
			string	val(lne.substr(f + 1));

			this->_header[String::lowercase(String::strim(key, " "))] = String::strim(val, " \r\n");
			p = e + 2;
		}
	}
}

string
Request::getHeader(const string &key, const string &other)
{
	return (this->_header.find(key) != this->_header.end() ? this->_header[key] : other);
}

size_t
Request::getLength() const
{
	return (this->_length);
}


string
Request::getVersion() const
{
	return (this->_version);
}


string
Request::getMethod() const
{
	return (this->_method);
}

string
Request::getPacket() const
{
	return (this->_packet);
}

string
Request::getParams() const
{
	return (this->_params);
}

size_t
Request::getStatus() const
{
	return (this->_status);
}

string
Request::getTarget() const
{
	return (this->_target);
}

Request&
Request::operator=(const Request &rhs)
{
	Abortable::operator=(rhs);
	this->_header = rhs._header;
	this->_length = rhs._length;
	this->_method = rhs._method;
	this->_packet = rhs._packet;
	this->_params = rhs._params;
	this->_socket = rhs._socket;
	this->_target = rhs._target;
	return (*this);
}
