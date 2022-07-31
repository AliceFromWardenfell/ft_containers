#include "timer.class.hpp"

timer::timer()
{
	clock_gettime(CLOCK_MONOTONIC, &m_start);
}

timer::~timer()
{
	clock_gettime(CLOCK_MONOTONIC, &m_end);
	
	long lifetime = m_end.tv_nsec - m_start.tv_nsec;
	m_print_perfomance(lifetime, TIME_UNIT_US);
}

int timer::m_convert_to_microseconds(long nanoseconds) const
{
	return nanoseconds / 1000;
}

void timer::m_print_perfomance(long raw_result, int time_unit) const
{
	std::cout	<< "Execution time: " << CLR_WHITE;
				
	switch (time_unit)
	{
		case TIME_UNIT_NS:
			std::cout	<< raw_result
						<< CLR_DEFAULT
						<< " ns";	
			break;
		case TIME_UNIT_US:
			std::cout	<< m_convert_to_microseconds(raw_result)
						<< CLR_DEFAULT
						<< " us";
			break;
	}

	std::cout << std::endl;
}
