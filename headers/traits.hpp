#ifndef TRAITS_HPP
#define TRAITS_HPP

#include <typeinfo>

namespace ft
{

template<typename type_1, typename type_2>
bool is_equal_types()
{
	return typeid(type_1) == typeid(type_2);
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

} // namespace ft

#endif
