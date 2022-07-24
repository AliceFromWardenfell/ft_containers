#include "vector.test.hpp"

/* custom type for testing */
struct Human
{  
	int	age;
	const char* name;
	// add dynamic allocation
};

static int default_constructor_test()
{
	timer perfomance;

	print_colored_caption("Default constructor test:", CLR_YELLOW);

	{
		ft::vector<int> arr;
		std::cout << "size = " << arr.size() << std::endl;
	}
	std::cout << std::endl;
	{
		ft::vector<Human> arr;
	}

	return 0;
}

static int allocator_constructor_test()
{
	timer perfomance;

	print_colored_caption("Allocator constructor test:", CLR_YELLOW);

	{
		std::allocator<int> alloc;
		ft::vector<int, std::allocator<int> > arr(alloc);
	}
	std::cout << std::endl;
	{
		std::allocator<Human> alloc;
		ft::vector<Human, std::allocator<Human> > arr(alloc);
	}

	return 0;
}

static int size_and_val_constructor_test()
{
	timer perfomance;

	print_colored_caption("Size&value constructor test:", CLR_YELLOW);

	{
		Human greg;

		greg.age = 23;
		greg.name = "Greg";

		std::allocator<Human> alloc;
		ft::vector<Human, std::allocator<Human> > arr(20, greg, alloc);
		std::cout << "size = " << arr.size() << std::endl;
	}

	return 0;
}

// static int default_constructor_test()
// {
// 	timer perfomance;

// 	print_colored_caption("Constructors test:", CLR_YELLOW);

// 	return 0;
// }

static int iterators_test()
{
	timer perfomance;

	print_colored_caption("Iterators test:", CLR_YELLOW);

	return 0;
}

void	vector_test() // mb turn into class
{
	std::cout << std::endl;
	print_colored_caption("Vector test:", CLR_VIOLET);
	std::cout << std::endl;

	/* array of function pointers */
	int (*vector_test_func[])() =
	{
		default_constructor_test,
		allocator_constructor_test,
		size_and_val_constructor_test,
		iterators_test
	};
	const size_t amount_of_tests =	sizeof(vector_test_func) /
									sizeof(*vector_test_func);

	int score = 0;
	for (size_t i = 0; i < amount_of_tests; i++)
	{
		int result = vector_test_func[i]();
		
		if (result == OK)
			score++;
		handle_result(result);
		
		std::cout << std::endl;
	}

	print_score(score, amount_of_tests);
	std::cout << std::endl;
}
