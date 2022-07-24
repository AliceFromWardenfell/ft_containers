#include "utils.hpp"

void	print_colored_caption(const char* caption, const char* color)
{
	std::cout	<< color
				<< caption
				<< CLR_DEFAULT
				<< std::endl;
}

void	print_score(int passed_tests, int num_of_tests)
{
	std::cout << CLR_WHITE << "Score: ";

	if (passed_tests < num_of_tests)
		std::cout << CLR_RED;
	else
		std::cout << CLR_GREEN;
	
	std::cout 	<< passed_tests
				<< "/"
				<< num_of_tests
				<< CLR_DEFAULT
				<< std::endl;
}
