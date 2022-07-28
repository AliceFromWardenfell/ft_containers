#ifndef UTILS_HPP
#define UTILS_HPP

#pragma once

#include <iostream>
#include "colors.hpp"

// handle_result codes
#define OK 0
#define CONT_ERR 1
#define TESTER_ERR 2

void	print_colored_caption(const char* caption, const char* color);
void	print_score(int passed_tests, int num_of_tests);
void	handle_result(int code);

#endif
