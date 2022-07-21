#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#pragma once

#include <iterator>
#include <iostream> // debug

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

template<typename T>
struct iterator_traits<T*>
{
	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	//typedef ptrdiff_t						difference_type;
	typedef std::random_access_iterator_tag	iterator_category;

}; // struct iterator_traits<T*>

template<typename T>
struct iterator_traits<const T*>
{
	typedef T								value_type;
	typedef const T*						pointer;
	typedef const T&						reference;
	//typedef ptrdiff_t						difference_type;
	typedef std::random_access_iterator_tag	iterator_category;

}; // struct iterator_traits<const T*>

template<typename iterator, typename container>
class normal_iterator
{
	protected:

		iterator m_current_iterator;

		typedef iterator_traits<iterator>				traits_type;
		
	public:

		typedef iterator								iterator_type;
		typedef typename traits_type::value_type		value_type;
		typedef typename traits_type::pointer			pointer;
		typedef typename traits_type::reference			reference;
		typedef typename traits_type::difference_type	difference_type;
		typedef typename traits_type::iterator_category	iterator_category;
		
		normal_iterator()
		:	m_current_iterator(iterator_type())
		{
			std::cout << "normal_iterator: " << "default constructor" << std::endl; // debug
		}

		explicit normal_iterator(const iterator_type& it)
		:	m_current_iterator(it)
		{
			std::cout << "normal_iterator: " << "copy constructor" << std::endl; // debug	
		}

	public:

		// ...

		const iterator_type& get_iterator() const throw()
		{
			std::cout << "normal_iterator: " << "get_iterator()" << std::endl; // debug
			return m_current_iterator;
		}

}; // class normal_iterator

} // namespace ft

#endif
