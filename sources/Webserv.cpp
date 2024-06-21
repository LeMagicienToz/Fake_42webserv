/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:56:03 by mconreau          #+#    #+#             */
/*   Updated: 2024/06/16 17:55:50 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Foundation/Application.hpp"
#include "Logger/Logger.hpp"

int
main(const int agc, const char **agv)
{
	Logger::logs("Launching Webserv...");
	return(!Application(agc > 1 ? agv[1] : "").run());
}


/*
#include "Filesystem/Filesystem.hpp"
#include <chrono>
#include <iostream>

int
main()
{
	using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	vector<string>	v = Filesystem::scandir("..");
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << endl;

	return (0);
}
*/
