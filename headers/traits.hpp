#ifndef TRAITS_HPP
#define TRAITS_HPP

#include "iterator.hpp"

template <typename iter>
inline typename ft::iterator_traits<iter>::difference_type
distance(iter start, iter finish)
{
	typename ft::iterator_traits<iter>::difference_type result = 0;

	while(start++ != finish)
		++result;

	return result;
}

template<bool statement, typename T = void>
struct enable_if { };

template<typename T>
struct enable_if<true, T>
{ typedef T type; };

template<typename>
struct is_integral
{ static const bool value = false; };

template<>
struct is_integral<char>
{ static const bool value = true; };

template<>
struct is_integral<signed char>
{ static const bool value = true; };

template<>
struct is_integral<unsigned char>
{ static const bool value = true; };

template<>
struct is_integral<wchar_t>
{ static const bool value = true; };

template<>
struct is_integral<char16_t>
{ static const bool value = true; };

template<>
struct is_integral<char32_t>
{ static const bool value = true; };

template<>
struct is_integral<short>
{ static const bool value = true; };

template<>
struct is_integral<unsigned short>
{ static const bool value = true; };

template<>
struct is_integral<int>
{ static const bool value = true; };

template<>
struct is_integral<unsigned int>
{ static const bool value = true; };

template<>
struct is_integral<long>
{ static const bool value = true; };

template<>
struct is_integral<unsigned long>
{ static const bool value = true; };

template<>
struct is_integral<long long>
{ static const bool value = true; };

template<>
struct is_integral<unsigned long long>
{ static const bool value = true; };

#endif
