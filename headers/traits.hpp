#ifndef TRAITS_HPP
#define TRAITS_HPP

#include <typeinfo>

namespace ft
{

struct true_type { };
struct false_type { };

template<bool>
struct truth_type
{ typedef false_type type; };

template<>
struct truth_type<true>
{ typedef true_type type; };

template<typename, typename>
struct are_same
{
	enum { value = 0 };
	typedef false_type type;
};

template<typename T>
struct are_same<T, T>
{
	enum { value = 1 };
	typedef true_type type;
};

template<bool, typename>
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

template<typename iter_1, typename iter_2>
bool lexicographical_compare(iter_1 first_1, iter_1 last_1, iter_2 first_2, iter_2 last_2)
{
	while (first_1 != last_1)
	{
		if (first_2 == last_2 || *first_2 < *first_1)
			return false;
		else if (*first_1 < *first_2)
			return true;
		++first_1;
		++first_2;
	}
	return (first_2 != last_2);
}

template<typename T>
inline const T& max(const T& x, const T& y)
{ return x > y ? x : y; }

} // namespace ft

#endif
