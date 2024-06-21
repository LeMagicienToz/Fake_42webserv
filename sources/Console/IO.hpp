/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IO.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:12:58 by mconreau          #+#    #+#             */
/*   Updated: 2024/05/05 12:47:07 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

using namespace std;

class IO
{
	public   :
		static string				ask(const string &prompt = "");
		static void					err(const string &output);
		static void					out(const string &output);
};
