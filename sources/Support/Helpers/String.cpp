/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   String.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muteza <muteza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:06:15 by mconreau          #+#    #+#             */
/*   Updated: 2024/06/17 14:04:33 by muteza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Support/Helpers/String.hpp"

String::~String()
{
}

int
String::count(const string &subject, const string &find)
{
	const int	len = find.size();
	int			i = 0;

	for (size_t pos = 0; (pos = subject.find(find, pos)) != string::npos; ++i, pos += len);
	return (i);
}

string
String::replace(string subject, const string &from, const string &to)
{
	const int	len = from.size();

	for (size_t pos = 0; (pos = subject.find(from, pos)) != string::npos; pos += len)
		subject.replace(pos, len, to);
	return (subject);
}

bool
String::match(const string &pattern, const string &subject)
{
	const int 	n = subject.length(), m = pattern.length();
	int			i = 0, j = 0, last = -1, match = 0;

	while (i < n)
	{
		if (j < m && (pattern[j] == '?' || pattern[j] == subject[i]))
			++i, ++j;
		else if (j < m && pattern[j] == '*')
		{
			last = j++;
			match = i;
		}
		else if (last != -1)
		{
			j = last + 1;
			i = ++match;
		}
		else
			return (false);
	}
	while (j < m && pattern[j++] == '*');
	return (j == m);
}

string
String::ltrim(string subject, const string &remove)
{
	return (subject.erase(0, subject.find_first_not_of(remove)));
}

string
String::rtrim(string subject, const string &remove)
{
	return (subject.erase(subject.find_last_not_of(remove) + 1));
}

string
String::strim(const string &subject, const string &remove)
{
	return (String::rtrim(String::ltrim(subject, remove), remove));
}

vector<string>
String::split(const string &subject, const string &delimiter)
{
	vector<string>	array;
	size_t			end = 0, start = 0, len = delimiter.length();
	string			sub;

	while ((end = subject.find(delimiter, start)) != string::npos)
	{
		if ((sub = subject.substr(start, end - start)).size())
			array.push_back(sub);
		start = end + len;
	}
	if ((sub = subject.substr(start, end - start)).size())
			array.push_back(sub);
	return (array);
}

string
String::join(const vector<string> &array, const string &delimiter)
{
	string	content;

	for (vector<string>::const_iterator it = array.begin(), end = array.end(); it != end; it++)
	{
		content += *it;
		if (it + 1 != end)
			content += delimiter;
	}
	return (content);
}

string
String::lowercase(string subject)
{
	for (int i = 0, j = subject.size(); i < j; i++)
		subject[i] = ::tolower(subject[i]);
	return (subject);
}

string
String::uppercase(string subject)
{
	for (int i = 0, j = subject.size(); i < j; i++)
		subject[i] = ::toupper(subject[i]);
	return (subject);
}

void String::custom_strcpy(char* dest, const char* src) 
{
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}
