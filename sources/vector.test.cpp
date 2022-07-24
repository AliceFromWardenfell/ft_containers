#include "vector.test.hpp"

struct Human // add dynamic allocation
{  
	int	age;
	const char* name;
};

static int constructors_test()
{
	timer perfomance;
	
	print_colored_caption("Constructors test:", CLR_YELLOW);
	
	{
		ft::vector<int> arr;
	}
	std::cout << std::endl;
	{
		ft::vector<Human> arr;
	}
	std::cout << std::endl;
	{
		std::allocator<int> alloc;
		ft::vector<int, std::allocator<int> > arr(alloc);
	}
	std::cout << std::endl;
	{
		std::allocator<Human> alloc;
		ft::vector<Human, std::allocator<Human> > arr(alloc);
	}
	std::cout << std::endl;
	{
		Human greg;

		greg.age = 23;
		greg.name = "Greg";

		std::allocator<Human> alloc;
		ft::vector<Human, std::allocator<Human> > arr(20, greg, alloc);
	}
	std::cout << std::endl;

	return 0;
}

static int iterators_test()
{
	timer perfomance;

	print_colored_caption("Iterators test:", CLR_YELLOW);

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
	result = iterators_test();
	// ...
	
	std::cout << std::endl;

	return result;
}
