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
		std::cout << "size = " << arr.size() << std::endl;
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
		std::cout << "size = " << arr.size() << std::endl;
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

	/* array of function pointers */
	int (*vector_test_func[])() =
	{
		constructors_test,
		iterators_test
	};
	const size_t amount_of_tests =	sizeof(vector_test_func) /
									sizeof(*vector_test_func);

	int result = 0;
	int score = 0;
	for (size_t i = 0; i < amount_of_tests; i++)
	{
		if ((result = vector_test_func[i]()))
			return result;
		score++;

	}
	
	print_score(score, amount_of_tests);
	std::cout << std::endl;

	return result;
}
