/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IO.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 11:55:14 by mconreau          #+#    #+#             */
/*   Updated: 2024/05/05 12:47:03 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Console/IO.hpp"

string
IO::ask(const string &prompt)
{
	string	content;

	IO::out(prompt);
	return (cin >> content, content);
}

void
IO::err(const string &output)
{
	cerr << output << flush;
}

void
IO::out(const string &output)
{
	cout << output << flush;
}
