#include "main.hpp"

static void	test_containers()
{
	std::cout << std::endl;
	
	#ifdef STL_TEST
		print_colored_caption("STL containers test:", CLR_GREEN);
	#else
		print_colored_caption("FT containers test:", CLR_GREEN);
	#endif

	vector_test();
	// map_test();
	// stack_test();
	// ...

}

int	main()
{
	/*
	 *	Try to catch serious internal problems.
	 *	Ordinary test errors are handled in corresponding test functions.
	 */
	try
	{
		test_containers();
	}
	catch(...)
	{
		// handle exceptions
	}
	
	return 0;
}
