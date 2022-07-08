#ifndef MAIN_HPP
#define MAIN_HPP

#pragma once

#include <iostream>
#include "utils.hpp"
#include "colors.hpp"

#include "vector.test.hpp"

#ifdef STL_TEST
	namespace ft = std;
	#include <vector>
#else
	#include "vector.class.hpp"
#endif

// handle_result codes
#define OK 0
#define CONT_ERR 1
#define TESTER_ERR 2

#endif
