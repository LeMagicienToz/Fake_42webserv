/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 21:47:17 by mconreau          #+#    #+#             */
/*   Updated: 2024/06/16 21:31:14 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Http/Request.hpp"
#include <string>
#include <vector>

using namespace std;

class Route
{
	public   :
		vector<string>				_method;
		string						_target;
		string						_upload;

	public   :
									Route();
									Route(const Route &src);
									~Route();

		bool						match(Request &request) const;

		Route&						operator=(const Route &rhs);
};
