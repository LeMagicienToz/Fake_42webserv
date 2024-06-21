/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MimeType.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:05:21 by mconreau          #+#    #+#             */
/*   Updated: 2024/06/09 19:11:17 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Filesystem/MimeType.hpp"

MimeType::MimeType()
{
	this->_mimetype[".css"] 	= "text/css";
	this->_mimetype[".html"] 	= "text/html";
	this->_mimetype[".txt"] 	= "text/plain";
	this->_mimetype[".xml"] 	= "text/xml";

	this->_mimetype[".bmp"] 	= "image/x-ms-bmp";
	this->_mimetype[".gif"] 	= "image/gif";
	this->_mimetype[".ico"] 	= "image/x-icon";
	this->_mimetype[".jpeg"] 	= "image/jpeg";
	this->_mimetype[".jpg"] 	= "image/jpeg";
	this->_mimetype[".png"] 	= "image/png";
	this->_mimetype[".svg"] 	= "image/svg+xml";
	this->_mimetype[".webp"] 	= "image/webp";

	this->_mimetype[".7z"] 		= "application/x-7z-compressed";
	this->_mimetype[".doc"] 	= "application/msword";
	this->_mimetype[".eot"] 	= "application/vnd.ms-fontobject";
	this->_mimetype[".jar"] 	= "application/java-archive";
	this->_mimetype[".js"] 		= "application/javascript";
	this->_mimetype[".json"] 	= "application/json";
	this->_mimetype[".pdf"] 	= "application/pdf";
	this->_mimetype[".ppt"] 	= "application/vnd.ms-powerpoint";
	this->_mimetype[".rar"] 	= "x-rar-compressed";
	this->_mimetype[".xls"] 	= "application/vnd.ms-excel";
	this->_mimetype[".zip"] 	= "application/zip";

	this->_mimetype[".mid"] 	= "audio/midi";
	this->_mimetype[".midi"] 	= "audio/midi";
	this->_mimetype[".mp3"] 	= "audio/mpeg";
	this->_mimetype[".ogg"] 	= "audio/ogg";

	this->_mimetype[".avi"] 	= "video/x-msvideo";
	this->_mimetype[".flv"] 	= "video/x-flv";
	this->_mimetype[".mov"] 	= "video/quicktime";
	this->_mimetype[".mp4"] 	= "video/mp4";
	this->_mimetype[".mpeg"] 	= "video/mpeg";
	this->_mimetype[".mpg"] 	= "video/mpeg";
	this->_mimetype[".webm"] 	= "video/webm";

	this->_mimetype[".woff"] 	= "font/woff";
}

MimeType::MimeType(const MimeType &src)
{
	*this = src;
}

MimeType::~MimeType()
{
}

string
MimeType::get(const string &extension)
{
	return (this->_mimetype.find(extension) != this->_mimetype.end() ? this->_mimetype[extension] : "application/octet-stream");
}

MimeType&
MimeType::operator=(const MimeType &rhs)
{
	this->_mimetype = rhs._mimetype;
	return (*this);
}
