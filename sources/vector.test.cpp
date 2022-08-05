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
		std::cout << "Size = " << arr.size() << std::endl;
	}
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

static int iterator_constructor_test()
{
	print_colored_caption("Iterator constructor test:", CLR_YELLOW);

	{
		ft::vector<int> arr;
		std::cout << "Base array: ";
		for (size_t i = 0; i < 9; i++)
		{
			arr.push_back((i + 1) * 11);
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;
		
		typedef ft::vector<int>::iterator vector_it;
		vector_it it_first(&arr[2]);
		vector_it it_last(&arr[7]);

		ft::vector<int> range_arr(it_first, it_last);
		std::cout << "Range array: ";
		for (size_t i = 0; i < range_arr.size(); i++)
			std::cout << range_arr[i] << " ";
		std::cout << std::endl;
	}
	{
		ft::vector<Human> arr;
		std::cout << "Base ages array: ";
		for (size_t i = 0; i < 9; i++)
		{
			arr.push_back(Human());
			arr[i].age = rand() % 70 + 1;
			std::cout << arr[i].age << " ";
		}
		std::cout << std::endl;
		
		typedef ft::vector<Human>::iterator vector_it;
		vector_it it_first(&arr[2]);
		vector_it it_last(&arr[7]);

		ft::vector<Human> range_arr(it_first, it_last);
		std::cout << "Range ages array: ";
		for (size_t i = 0; i < range_arr.size(); i++)
			std::cout << range_arr[i].age << " ";
		std::cout << std::endl;
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

static int assignment_operator_test()
{
	print_colored_caption("Assignment operator test:", CLR_YELLOW);

	{
		Human stan;

		stan.name = "Stan";
		stan.age = 35;

		ft::vector<Human> bunch_of_stans(10, stan);
		std::cout	<< bunch_of_stans[3].name
					<< "'s age is "
					<< bunch_of_stans[3].age
					<< std::endl;

		Human lee;

		lee.name = "Lee";
		lee.age = 55;

		ft::vector<Human> bunch_of_lees(10, lee);
		std::cout	<< bunch_of_lees[3].name
					<< "'s age is "
					<< bunch_of_lees[3].age
					<< std::endl;

		bunch_of_lees = bunch_of_stans;
		std::cout	<< bunch_of_lees[3].name
					<< "'s age is "
					<< bunch_of_lees[3].age
					<< " (Lee: \"Help, I was consumed\")"
					<< std::endl;
	}

	return 0;
}

static int destructor_test()
{
	print_colored_caption("Destructor test:", CLR_YELLOW);

	// { /* memory leaks test */
	// 	ft::vector<char*> arr(10, NULL);
	// 	for (size_t i = 0; i < arr.size(); i++)
	// 	{
	// 		arr[i] = ::new char[i];
	// 		size_t j = i;
	// 		arr[i][j] = '\0';
	// 		while (j--)
	// 			arr[i][j] = '*';
	// 		std::cout << arr[i] << std::endl;
	// 	}
	// }
	// std::cout << "Have to be memory leaks in 10 blocks" << std::endl;

	return 0;
}

static int iterators_test()
{
	print_colored_caption("Iterators test:", CLR_YELLOW);

	ft::vector<int> arr;
	std::cout << "Base array: ";
	for (size_t i = 0; i < 9; i++)
	{
		arr.push_back((i + 1) * 11);
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
	{ /* normal iterator */
		typedef ft::vector<int>::iterator normal_it;
		normal_it it_begin(arr.begin());

		std::cout	<< "begin: "
					<< *it_begin
					<< std::endl;
		
		std::cout << "Normal array: ";
		while (it_begin != arr.end())
			std::cout << *it_begin++ << " ";
		std::cout << std::endl;
	} /* normal const iterator */
	{
		typedef ft::vector<int>::const_iterator const_normal_it;
		const_normal_it it_begin(arr.begin());

		std::cout	<< "begin: "
					<< *it_begin
					<< std::endl;
		
		std::cout << "Const normal array: ";
		while (it_begin != arr.end())
			std::cout << *it_begin++ << " ";
		std::cout << std::endl;
	}
	{ /* reverse iterator */
		typedef ft::vector<int>::reverse_iterator reverse_it;
		reverse_it it_begin(arr.rbegin());

		std::cout	<< "begin: "
					<< *it_begin
					<< std::endl;

		std::cout << "Reverse array: ";
		while (it_begin != arr.rend())
			std::cout << *it_begin++ << " ";
		std::cout << std::endl;
	}
	{ /* reverse const iterator */
		typedef ft::vector<int>::const_reverse_iterator const_reverse_it;
		const_reverse_it it_begin(arr.rbegin());

		std::cout	<< "begin: "
					<< *it_begin
					<< std::endl;

		std::cout << "Const reverse array: ";
		while (it_begin != arr.rend())
			std::cout << *it_begin++ << " ";
		std::cout << std::endl;
	}
	{ /* Comparison between normal and const iterator */
		typedef ft::vector<int>::iterator normal_it;
		typedef ft::vector<int>::const_iterator const_normal_it;

		normal_it it(arr.begin());
		const_normal_it const_it(arr.begin());

		if (it == const_it)
			std::cout << "Different iterators are indeed comparable" << std::endl;
	}

	return 0;
}

static int size_test()
{
	print_colored_caption("Size() test:", CLR_YELLOW);

	ft::vector<int> arr(125, 0);
	std::cout << "Size = " << arr.size() << std::endl;

	return 0;
}

static int max_size_test()
{
	print_colored_caption("Max_size() test:", CLR_YELLOW);

	ft::vector<int> arr(125, 0);
	std::cout << "Max size = " << arr.max_size() << std::endl;

	return 0;
}

static int resize_test()
{
	print_colored_caption("Resize() test:", CLR_YELLOW);

	ft::vector<int> arr(8, 1);
	size_t new_size = arr.size() + 4;
	int	value = 0;

	std::cout << "Array before resize: " << std::endl;
	for (size_t i = 0; i < arr.size(); i++)
		std::cout << arr[i] << " ";
	
	arr.resize(new_size, value);

	std::cout << std::endl << "Array after resize: " << std::endl;
	for (size_t i = 0; i < arr.size(); i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;

	return 0;
}

static int capacity_test()
{
	print_colored_caption("Capacity() test:", CLR_YELLOW);

	{
		ft::vector<int> arr;
		std::cout << "Capacity: " << arr.capacity() << std::endl;
	}
	{
		ft::vector<int> arr(128, 0);
		std::cout << "Capacity: " << arr.capacity() << std::endl;
	}

	return 0;
}

static int reserve_test()
{
	print_colored_caption("Reserve() test:", CLR_YELLOW);

	ft::vector<int> arr(128, 0);
	std::cout << "Capacity: " << arr.capacity() << std::endl;
	arr.reserve(256);
	std::cout << "Capacity: " << arr.capacity() << std::endl;

	return 0;
}

static int push_back_test()
{
	print_colored_caption("Push_back() test:", CLR_YELLOW);

	ft::vector<int> arr;
	
	std::cout	<< "Size = "
				<< arr.size()
				<< std::endl;
	
	arr.push_back(3);
	arr.push_back(88);
	arr.push_back(0);
	arr.push_back(-6);

	std::cout	<< "Size = "
				<< arr.size()
				<< std::endl;

	std::cout << "Array: ";
	for(size_t i = 0; i < arr.size(); i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;

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
		iterator_constructor_test,
		copy_constructor_test,
		assignment_operator_test,
		destructor_test,
		iterators_test,
		size_test,
		max_size_test,
		resize_test,
		capacity_test,
		reserve_test,
		push_back_test
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
