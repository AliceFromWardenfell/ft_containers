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
	std::cout << CLR_YELLOW << "Score: ";

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

static void	print_code_synopsis(const char* synopsis, int code, const char* color)
{
	std::cout	<< color
				<< "#"
				<< code
				<< ": "
				<< CLR_YELLOW
				<< synopsis
				<< CLR_DEFAULT
				<< std::endl;
}

void	handle_result(int code)
{
	switch (code)
	{
		case OK:
			print_code_synopsis("No errors", code, CLR_GREEN);
			break;
		case CONT_ERR:
			print_code_synopsis("Error in container", code, CLR_RED);
			break;
		case TESTER_ERR:
			print_code_synopsis("Error in tester", code, CLR_RED);
			break;
		// ...
	}
}
