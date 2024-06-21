/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 20:09:05 by mconreau          #+#    #+#             */
/*   Updated: 2024/06/16 13:15:46 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Support/Helpers/String.hpp"
#include <netdb.h>
#include <netinet/ip.h>
#include <stdexcept>
#include <string>
#include <unistd.h>

using namespace std;

class Socket
{
	private  :
		int							_afinet;
		pair<string,string>			_listen;
		int							_socket;

	public   :
									Socket(const pair<string,string> &target, const int &type = SOCK_STREAM | SOCK_NONBLOCK);
									Socket(const Socket &src);
									~Socket();

		void						close();

		Socket&						operator=(const Socket &rhs);
									operator int() const;

		class Exception : public runtime_error
		{
			public   :
									Exception(Socket &socket, const string &message);
		};
};
