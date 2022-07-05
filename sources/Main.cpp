#include "Main.hpp"

int	main()
{
	std::cout << "Hello, STL!" << std::endl;

// temp test if two executables work correctly
#ifdef STL_TEST
	std::cout << "STL_TEST" << std::endl;
#else
	std::cout << "FT_TEST" << std::endl;
#endif

}
