#include <iostream>
#include <vector>
#include "../headers/BaseVector.class.hpp"

int	main()
{
	std::cout << "Hello, STL!" << std::endl;

	std::allocator<char> myAllocator;

	std::vector< int, std::allocator<int> > Arr(myAllocator);

	ft::BaseVector< int, std::allocator<int> > baseArr(myAllocator);
}
