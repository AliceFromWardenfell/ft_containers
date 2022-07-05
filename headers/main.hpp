#ifndef MAIN_HPP
#define MAIN_HPP

#pragma once

#include <iostream>
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

// colors
#define CLR_DEFAULT "\033[0;39m"
#define CLR_RED "\033[31m"
#define CLR_GREEN "\033[32m"
#define CLR_WHITE "\033[37m"

#endif
