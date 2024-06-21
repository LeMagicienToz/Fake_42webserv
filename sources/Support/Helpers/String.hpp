/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   String.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muteza <muteza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 22:30:54 by mconreau          #+#    #+#             */
/*   Updated: 2024/06/17 14:05:14 by muteza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sstream>
#include <string>
#include <vector>

using namespace std;

class String
{
	private  :
		virtual						~String() = 0;

	public   :
		static void					custom_strcpy(char* dest, const char* src);
		static int					count(const string &subject, const string &find);
		static string				replace(string subject, const string &from, const string &to);
		static bool					match(const string &pattern, const string &subject);
		static string				ltrim(string subject, const string &remove);
		static string				rtrim(string subject, const string &remove);
		static string				strim(const string &subject, const string &remove);
		static vector<string>		split(const string &subject, const string &delimiter);
		static string				join(const vector<string> &array, const string &delimiter);
		static string				lowercase(string subject);
		static string				uppercase(string subject);
		
		template<typename TYPE>
		static string				tostr(const TYPE &content);
};

#include "Support/Helpers/String.tpp"
