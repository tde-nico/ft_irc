#ifndef UTILS_HPP
#define UTILS_HPP

#pragma once

#include <iostream>
#include <time.h>


#define MAX_CONNECTIONS 200


inline void	console_log(std::string const &msg)
{
	time_t		raw_time;
	struct tm	*time_info;
	char		buffer[80];

	time(&raw_time);
	time_info = localtime(&raw_time);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", time_info);
	std::string now(buffer);
	std::cout << "[" << now << "] " << msg << "\n";
}

#endif
