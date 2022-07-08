#include "main.hpp"

// mb move to utils.cpp
static void	print_code_synopsis(const char* synopsis, int code, const char* color)
{
	std::cout	<< color
				<< "#"
				<< code
				<< ": "
				<< CLR_WHITE
				<< synopsis
				<< CLR_DEFAULT
				<< std::endl;
}

static void	handle_result(int code)
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

static int	test_containers()
{
	int result = 0;

	print_colored_caption("Containers test:", CLR_GREEN);

	result = vector_test();
	// error_code = map_test();
	// error_code = stack_test();
	// ...

	return result;
}

int	main()
{
	int result = 0;

	result = test_containers();
	handle_result(result);

	return result;
}
