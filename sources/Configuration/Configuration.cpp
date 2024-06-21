/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:16:33 by mconreau          #+#    #+#             */
/*   Updated: 2024/06/16 22:01:42 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Configuration/Configuration.hpp"

Configuration::Configuration(const string &config, const int &epollfd)
{
	ifstream	stream(config.c_str());
	size_t		context = 0, y = 0; // "context": 0 = none, 1 = server, 2 = route; "y": number of the line, can be used for error message if needed
	string		line;

	if (!stream.is_open())
		this->abort("Failed to open the configuration file: " + config); // Aborting (set "_status" to false et print message to stderr)
	else
	{
		Logger::info("Reading configuration: " + config);
		while (this->_status && getline(stream, line, '\n') && ++y) // While "_status" == true and there is a line
		{
			line = String::strim(line, " \f\r\t\v"); // Trim the line
			if (context == 0 && line == "{") // If context = none and line == "{"
			{
				// Open server.
				Logger::dump("Entering server #" + String::tostr(this->_servers.size() + 1));
				++context;
			}
			else if (context == 1 && String::match("location ** {", line)) // If context == server and line match the pattern "location ** {"
			{
				// Open route.
				Logger::dump("Open route: " + line);
				++context;
			}
			else if (context == 2 && line == "}") // If context == location and line == "}"
			{
				// Close route.
				Logger::dump("Close route: " + line);
				--context;
			}
			else if (context == 1 && line == "}") // If context == server and line == "}"
			{
				// Close server.
				Logger::dump("Closing server #" + String::tostr(this->_servers.size() + 1));
				--context;
			}
			else if (line.size()) // Otherwise, and if line is not empty
			{
				if (context == 1)
				{
					// Server directive.
					Logger::dump("Directive S: " + line);
				}
				if (context == 2)
				{
					// Location directive.
					Logger::dump("Directive L: " + line);
				}
			}
		}
		stream.close();

		// TEMP: Add one listener manually to 0.0.0.0:3000, must be created with parsing
		this->_servers.push_back(new Server());
		this->_servers[0]->listen.first = "0.0.0.0";
		this->_servers[0]->listen.second = "3000";
		this->_servers[0]->snames.push_back("*");
		this->_servers[0]->routes.push_back(new Route());
		this->_servers[0]->routes[0]->_target = "/get";
		this->_servers[0]->routes[0]->_method.push_back("GET");
		this->_servers[0]->routes.push_back(new Route());
		this->_servers[0]->routes[1]->_target = "/post";
		this->_servers[0]->routes[1]->_method.push_back("POST");

		// TEMP: Add a second listener manually to 0.0.0.0:3001, must be created with parsing
		this->_servers.push_back(new Server());
		this->_servers[1]->listen.first = "0.0.0.0";
		this->_servers[1]->listen.second = "3001";

		// ==============================================
		// Add all servers to epoll
		// ==============================================

		epoll_event	event;
		event.events = EPOLLIN; // Setup event to trigger epoll only when data is received, not when data is sended

		for (size_t i = 0; i < this->_servers.size(); i++) // For each servers created by parsing...
		{
			try
			{
				this->_servers[i]->run(); // Open the server socket
				Logger::info("Server #" + String::tostr(i) + " running on socket: " + String::tostr(this->_servers[i]->socket));

				event.data.fd = this->_servers[i]->socket;
				if (epoll_ctl(epollfd, EPOLL_CTL_ADD, event.data.fd, &event) == -1) // Add server socket to epoll
				{
					// Remove from vector<Server*> if fail
					Logger::fail("Failed to add socket to epoll");
					delete this->_servers[i];
					this->_servers.erase(this->_servers.begin() + i--);
				}
			}
			catch(const Socket::Exception &e) // Handle Socket creation exception
			{
				// Remove from vector<Server*> if fail
				Logger::fail(e.what());
				delete this->_servers[i];
				this->_servers.erase(this->_servers.begin() + i--);
			}
		}
	}
}

Configuration::Configuration(const Configuration &src) :
	Abortable(src)
{
	*this = src;
}

Configuration::~Configuration()
{
}


Configuration&
Configuration::operator=(const Configuration &rhs)
{
	Abortable::operator=(rhs);
	this->_servers = rhs._servers;
	return (*this);
}

Configuration::operator vector<Server*>() const
{
	return (this->_servers);
}
