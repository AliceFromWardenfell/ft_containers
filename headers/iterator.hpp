#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#pragma once

#include <iterator>

namespace ft
{

template<typename it>
struct iterator_traits
{
	typedef typename it::value_type			value_type;
	typedef typename it::pointer			pointer;
	typedef typename it::reference			reference;
	typedef typename it::difference_type	difference_type;
	typedef typename it::iterator_category	iterator_category;

}; // struct iterator_traits

template <typename T>
struct iterator_traits<T*>
{
	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	//typedef ptrdiff_t						difference_type;
	typedef std::random_access_iterator_tag	iterator_category;

}; // struct iterator_traits<T*>

template <typename T>
struct iterator_traits<const T*>
{
	typedef T								value_type;
	typedef const T*						pointer;
	typedef const T&						reference;
	//typedef ptrdiff_t						difference_type;
	typedef std::random_access_iterator_tag	iterator_category;

}; // struct iterator_traits<const T*>

} // namespace ft

#endif
