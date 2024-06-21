/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muteza <muteza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:00:14 by mconreau          #+#    #+#             */
/*   Updated: 2024/06/19 14:50:34 by muteza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Foundation/Application.hpp"
#include "Gateway/Gateway.hpp"

Application::Application(const string &config) :
	_epollfd(epoll_create(1)),
	_servers(this->_epollfd != -1 ? Configuration(config.size() ? config : "config/default.cfg", this->_epollfd) : vector<Server*>())
{
	if (this->_epollfd == -1)
		this->abort("Failed to create epoll instance.");
	else if (!this->_servers.size())
		this->abort("No server to listen on.");
	else if (!config.size())
		Logger::warn("Default configuration file used.");
}

Application::Application(const Application &src) :
	Abortable(src)
{
	*this = src;
}

Application::~Application()
{
	Map<const int,time_t>::iterKey(this->_clients, &::close);
	Vector::free(this->_servers);
	this->_chunked.clear();
	this->_clients.clear();
	this->_servers.clear();
	::close(this->_epollfd);
}

bool
Application::run()
{
	const int		hfd = this->_servers.size() ? this->_servers.back()->socket : 0;
	epoll_event		events[32];

	for (int e, fd; this->_status;) // While _status == true (may be set to false by Ctrl-C)
	{
		if ((e = ::epoll_wait(this->_epollfd, events, 32, 2000)) == -1) // Wait until epoll trigger event or until 2000ms (for timeout check)
			return (this->abort("Failed to wait on epoll"));
		for (int i = 0; i < e; i++) // For each triggered event from epoll (number of trigerred events is in "e")
		{
			if ((fd = events[i].data.fd) <= hfd) // If the "fd" triggered by epoll is one of the servers socket (<= "hfd"), it's a first connection from a new client
				this->add(fd);
			else // Handle the data receveid on the socket "fd"
			{
				Request		req(fd);
				Response	res(fd);
				Gateway		cgi;
				std::string response;

				req.recv();
				std::cout << "reponse before" << std::endl;
				response = cgi.cgirun(req);
				std::cout << "reponse after" << std::endl;
				// std::cout << req.getParams() << std::endl;
				send(fd, response.c_str(), response.size(), 0); //Je te laisse le mettre la ou tu veut ! : )
				res.setStatus(200);
				res.addPacket("<h1>Hello there!</h1>");
				//res.addPacket(Template::index("."));
				//res.addPacket(Template::error(431));
				// res.send(); // Send the data to the socket
				std::cout << "send after" << std::endl;

				// if (String::lowercase(req.getHeader("connection", "keep-alive")) != "close") // <= Use this for "keep-alive" by default with HTTP/1.1, commented for testing purpose only
				if (String::lowercase(req.getHeader("connection", "")) == "keep-alive") // <= Used for testing purpose only, use the above one in production
					this->_clients[fd] = ::time(0); // Create or update the keep-alive fd timestamp...
				else
					::close(fd); // Or close the fd
			}
		}
		this->timeout();
	}
	return (true);
}

void
Application::add(const int &fd)
{
	static epoll_event 	event = {EPOLLIN, {0}};
	static sockaddr_in	remote;
	static socklen_t	len;

	if ((event.data.fd = ::accept(fd, (sockaddr*) &remote, &len)) > -1)
		if (::epoll_ctl(this->_epollfd, EPOLL_CTL_ADD, event.data.fd, &event) == -1)
			::close(event.data.fd);
}

void
Application::timeout()
{
	const time_t	now = ::time(0);

	for (map<const int,time_t>::iterator it = this->_clients.begin(); it != this->_clients.end();)
	{
		if (now - (it->second) > 2)
		{
			::close(it->first);
			this->_clients.erase(it++);
		}
		else
			++it;
	}
}

Application&
Application::operator=(const Application &rhs)
{
	Abortable::operator=(rhs);
	this->_clients = rhs._clients;
	this->_epollfd = rhs._epollfd;
	this->_servers = rhs._servers;
	return (*this);
}
