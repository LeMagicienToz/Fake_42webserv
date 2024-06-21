/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 20:09:26 by mconreau          #+#    #+#             */
/*   Updated: 2024/06/16 13:17:52 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Network/Socket.hpp"


Socket::Socket(const pair<string,string> &listen, const int &type) :
	_afinet(String::match("*.*.*.*", listen.first) ? AF_INET : (String::match("*:*:*:*:*:*:*:*", listen.first) ? AF_INET6 : -1)),
	_listen(listen),
	_socket(-1)
{
	const int	opt = 1;

	if (this->_afinet  == -1)
		throw Exception(*this, "Wrong ip address format: " + listen.first + ":" + listen.second);
	if ((this->_socket = ::socket(this->_afinet, type, IPPROTO_TCP)) == -1)
		throw Exception(*this, "Failed to create socket for " + listen.first + ":" + listen.second);
	if (::setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1)
		throw Exception(*this, "Failed to set option to socket for " + listen.first + ":" + listen.second);

	addrinfo	h = {}, *r;

	h.ai_family = this->_afinet;
	h.ai_flags = AI_NUMERICHOST | AI_PASSIVE;
	h.ai_socktype = SOCK_STREAM;
	h.ai_protocol = IPPROTO_TCP;

	if (::getaddrinfo(this->_listen.first.c_str(), this->_listen.second.c_str(), &h, &r) != 0)
		throw Exception(*this, "Failed to get addrinfo for " + this->_listen.first + ":" + this->_listen.second);
	else
	{
		if (::bind(this->_socket, r->ai_addr, r->ai_addrlen) == -1)
		{
			::freeaddrinfo(r);
			throw Exception(*this, "Failed to bind socket on " + this->_listen.first + ":" + this->_listen.second);
		}
		::freeaddrinfo(r);
	}

	if (::listen(this->_socket, SOMAXCONN) == -1)
		throw Exception(*this, "Failed to listen socket on " + this->_listen.first + ":" + this->_listen.second);
}

Socket::Socket(const Socket &src)
{
	*this = src;
}

Socket::~Socket()
{
}

void
Socket::close()
{
	::close(this->_socket);
}

Socket&
Socket::operator=(const Socket &rhs)
{
	this->_afinet = rhs._afinet;
	this->_listen = rhs._listen;
	this->_socket = rhs._socket;
	return (*this);
}

Socket::operator int() const
{
	return (this->_socket);
}

Socket::Exception::Exception(Socket &socket, const string &message) :
	runtime_error(message)
{
	socket.close();
}
