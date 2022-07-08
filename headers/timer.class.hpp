#ifndef TIMER_CLASS_HPP
#define TIMER_CLASS_HPP

#pragma once

#include <time.h>
#include <iostream>

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

		int m_convert_to_microseconds(int nanoseconds) const;

}; // class timer

#endif
