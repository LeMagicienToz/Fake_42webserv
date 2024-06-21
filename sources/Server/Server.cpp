/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 21:47:19 by mconreau          #+#    #+#             */
/*   Updated: 2024/06/16 20:38:23 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Server.hpp"

Server::Server() :
	socket(-1)
{
}

Server::Server(const Server &src)
{
	*this = src;
}

Server::~Server()
{
	Logger::logs("Closing server: " + this->listen.first + ":" + this->listen.second);
	Vector::free(this->routes);
	this->routes.clear();
	::close(this->socket);
}

void
Server::run()
{
	this->socket = Socket(this->listen);
}

bool
Server::match(Request &request) const
{
	const int		i = this->snames.size();
	const string	host(request.getHeader("host", ""));

	for (int j = 0; j < i; j++)
	{
		if (String::match(this->snames[j], host))
			return (true);
	}
	return (false);
}

Server&
Server::operator=(const Server &rhs)
{
	this->errors = rhs.errors;
	this->listen = rhs.listen;
	this->routes = rhs.routes;
	this->snames = rhs.snames;
	this->socket = rhs.socket;
	return (*this);
}
