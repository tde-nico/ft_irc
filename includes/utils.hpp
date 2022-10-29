#ifndef UTILS_HPP
#define UTILS_HPP

#pragma once

#include <iostream>
#include <time.h>
#include <signal.h>
#include <cstring>
#include <cstdio>
#include <vector>
#include <map>

#define MAC_OS 0

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


const class nullptr_t
{
	public:
		template<class T>
		operator T*() const { return (0); }

		template<class C, class T>
			operator T C::*() const { return (0); }	

	private:
		void operator&() const;

} nullp = {};


#endif
