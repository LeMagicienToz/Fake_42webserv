/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Template.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:48:31 by mconreau          #+#    #+#             */
/*   Updated: 2024/06/15 21:29:12 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Filesystem/Filesystem.hpp"
#include "Http/HttpStatus.hpp"
#include "Support/Helpers/String.hpp"
#include <string>
#include <vector>

using namespace std;

class Template
{
	private  :
		virtual						~Template() = 0;
	
	public   :
		static string				error(const int &status);
		static string				index(const string &target);
};
