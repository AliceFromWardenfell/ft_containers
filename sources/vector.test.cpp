#include "vector.test.hpp"

/* custom type for testing */
struct Human
{  
	int	age;
	const char* name;
};

static int default_constructor_test()
{
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
	print_colored_caption("Size&value constructor test:", CLR_YELLOW);

	{
		Human greg;

		greg.name = "Greg";
		greg.age = 23;
		
		std::allocator<Human> alloc;
		ft::vector<Human, std::allocator<Human> > arr(20, greg, alloc);
		std::cout << "size = " << arr.size() << std::endl;
	}

	return 0;
}

static int copy_constructor_test()
{
	print_colored_caption("Copy constructor test:", CLR_YELLOW);

	{
		Human bob;

		bob.name = "Bob";
		bob.age = 35;

		ft::vector<Human> bunch_of_bobs(10, bob);
		std::cout	<< bunch_of_bobs[3].name
					<< "'s age is "
					<< bunch_of_bobs[3].age
					<< std::endl;

		ft::vector<Human> bunch_of_copies(bunch_of_bobs);
		std::cout	<< bunch_of_copies[3].name
					<< "'s age is still "
					<< bunch_of_copies[3].age
					<< std::endl;
	}

	return 0;
}

static int size_test()
{
	print_colored_caption("Size test:", CLR_YELLOW);

	//ft::vector<int> arr(125, 0);
	//std::cout << "Size = " << arr.size() << std::endl;

	return 0;
}

// static int default_constructor_test()
// {
// 	print_colored_caption("Constructors test:", CLR_YELLOW);

// 	return 0;
// }

static int iterators_test()
{
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
		copy_constructor_test,
		iterators_test,
		size_test
	};
	const size_t amount_of_tests =	sizeof(vector_test_func) /
									sizeof(*vector_test_func);

	int result;
	int score = 0;
	for (size_t i = 0; i < amount_of_tests; i++)
	{
		{
			timer perfomance;
			result = vector_test_func[i]();
		}
		if (result == OK)
			score++;
		handle_result(result);
		
		std::cout << std::endl;
	}

	print_score(score, amount_of_tests);
	std::cout << std::endl;
}
