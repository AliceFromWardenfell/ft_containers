#include "vector.test.hpp"

static int constructors_test()
{
	timer perfomance;
	
	print_colored_caption("Constructors test:", CLR_YELLOW);

	return 0;
}

/*
static int relational_operators_test()
{

}
*/

int	vector_test()
{
	print_colored_caption("Vector test:", CLR_VIOLET);
	std::cout << std::endl;

	int result = 0;
	result = constructors_test();
	// ...
	
	std::cout << std::endl;

	return result;
}
