/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MimeType.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:05:30 by mconreau          #+#    #+#             */
/*   Updated: 2024/06/09 18:52:29 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>

using namespace std;

class MimeType
{
	public   :
		map<string,string>			_mimetype;

	public   :
									MimeType();
									MimeType(const MimeType &src);
									~MimeType();

		string						get(const string &extension);

		MimeType&					operator=(const MimeType &rhs);
};
