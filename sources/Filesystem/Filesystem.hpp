/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Filesystem.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:42:59 by mconreau          #+#    #+#             */
/*   Updated: 2024/06/12 22:05:38 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Filesystem/MimeType.hpp"
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

using namespace std;

class Filesystem
{
	private  :
		virtual						~Filesystem() = 0;

	public   :
		static bool					exist(const string &path);
		static string				extension(const string &path);
		static string				mimetype(const string &path);
		static string				get(const string &path);
		static void					set(const string &path, const string &data);
		static bool					isDir(const string &path);
		static bool					isLnk(const string &path);
		static bool					isReg(const string &path);
		static bool					isSck(const string &path);
		static bool					isReadable(const string &path);
		static bool					isWritable(const string &path);
		static bool					isXcutable(const string &path);
		static string				recv(const int &fd);
		static void					send(const int &fd, const string &data);
		static vector<string>		scandir(const string &path, const bool &hidden = false);
};
