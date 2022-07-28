#ifndef TRAITS_HPP
#define TRAITS_HPP

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

#endif
