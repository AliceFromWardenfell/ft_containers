#include "timer.class.hpp"

timer::timer()
{
	clock_gettime(CLOCK_MONOTONIC, &m_start);
}

timer::~timer()
{
	clock_gettime(CLOCK_MONOTONIC, &m_end);
	
	int lifetime = m_end.tv_nsec - m_start.tv_nsec;

	std::cout	<< "Execution time: "
				<< CLR_WHITE
				<< m_convert_to_microseconds(lifetime)
				<< CLR_DEFAULT
				<< " us"
				<< std::endl;
}

int timer::m_convert_to_microseconds(int nanoseconds) const
{
	return nanoseconds / 1000;
}
