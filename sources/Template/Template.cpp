/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Template.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:48:59 by mconreau          #+#    #+#             */
/*   Updated: 2024/06/16 21:19:08 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Template/Template.hpp"

Template::~Template()
{
}

string
Template::error(const int &status)
{
	static HttpStatus	HttpStatus;

	return (String::replace(String::replace("\
<html>\
	<head>\
		<title>%1 %2</title>\
	</head>\
	<body style=\"margin: 0; padding: 0; min-height: 500px; background-color: #eb4d4b; font-family: sans-serif; box-sizing: border-box;\">\
		<div style=\"top: 128px; left: 50%; transform: translateX(-50%); position: absolute; display: flex; align-items: center; flex-direction: column; gap: 16px;\">\
			<div style=\"color: #e3e3e3; font-size: 64px; font-weight: bold;\">%1</div>\
			<div style=\"color: #e3e3e3; font-size: 32px;\"><center>%2</center></div>\
		</div>\
		<div style=\"bottom: 32px; left: 50%; transform: translateX(-50%); font-size: 18px; font-weight: bold; color: #e3e3e3; position: absolute;\">WEBSERV 1.0.0</div>\
	</body>\
</html>",
	"%1", String::tostr(status)), "%2", HttpStatus.get(status)));
}

string
Template::index(const string &target)
{
	vector<string>	files(Filesystem::scandir(target[0] == '/' ? &target[1] : target));
	string			list, packet("\
<html>\
	<head>\
		<title>Index</title>\
	</head>\
	<body style=\"margin: 0; padding: 0; min-height: 500px; background-color: #3867d6; font-family: sans-serif; box-sizing: border-box;\">\
		<div style=\"padding: 16px; margin: 16px; width: auto; background-color: #e3e3e3; display: flex; flex-direction: column; gap: 6px;\">\
			%2\
		</div>\
		<div style=\"bottom: 32px; left: 50%; transform: translateX(-50%); font-size: 18px; font-weight: bold; color: #e3e3e3; position: absolute;\">WEBSERV 1.0.0</div>\
	</body>\
</html>");

	for (size_t i = 0; i < files.size(); i++)
		list += "<a href=\"/" + files[i] + "\">" + files[i] + (Filesystem::isDir(files[i]) ? "/" : "") + "</a>";
	return (String::replace(packet, "%2", list));
}
