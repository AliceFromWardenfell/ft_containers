#ifndef TIMER_CLASS_HPP
#define TIMER_CLASS_HPP

#pragma once

#include <time.h>
#include <iostream>
#include "colors.hpp"

#define TIME_UNIT_NS 1
#define TIME_UNIT_US 2

class timer
{
	public:

		timer();
		~timer();

	private:

		timer(const timer& instance);

	protected:

		struct timespec	m_start;
		struct timespec	m_end;
	
	protected:

		int m_convert_to_microseconds(long nanoseconds) const;
		void m_print_perfomance(long raw_result, int time_unit) const;

}; // class timer

#endif
