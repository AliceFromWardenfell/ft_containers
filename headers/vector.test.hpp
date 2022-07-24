#ifndef VECTOR_TEST_HPP
#define VECTOR_TEST_HPP

#pragma once

#include <iostream>
#include "utils.hpp"
#include "colors.hpp"
#include "timer.class.hpp"

#ifdef STL_TEST
	namespace ft = std;
	#include <vector>
#else
	#include "vector.class.hpp"
#endif

int vector_test();

#endif
