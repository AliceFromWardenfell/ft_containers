#include "utils.hpp"

void	print_colored_caption(const char* caption, const char* color)
{
	std::cout	<< color
				<< caption
				<< CLR_DEFAULT
				<< std::endl;
}
