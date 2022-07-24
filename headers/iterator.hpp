#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#pragma once

#include <iterator>
#include <cstddef>
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
	typedef ptrdiff_t						difference_type;
	typedef std::random_access_iterator_tag	iterator_category;

}; // struct iterator_traits<T*>

template<typename T>
struct iterator_traits<const T*>
{
	typedef T								value_type;
	typedef const T*						pointer;
	typedef const T&						reference;
	typedef ptrdiff_t						difference_type;
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

		/* need special test
		template<typename iter>
		normal_iterator(const normal_iterator<it, typename enable_if<is_equal_types<it, typename container::pointer>(), container>::type>& it)
		:	m_current_iterator(it.get_iterator())
		{
			std::cout << "normal_iterator: " << "iter to const_iter conversion" << std::endl; // debug
		}
		*/

	public:

		const iterator_type& get_iterator() const throw()
		{ return m_current_iterator; }

		reference operator*() const throw()
		{ return *m_current_iterator; }

		pointer operator->() const throw()
		{ return m_current_iterator; }

		normal_iterator& operator++() throw()
		{ ++m_current_iterator; return *this; }

		normal_iterator operator++(int) throw()
		{ return normal_iterator(m_current_iterator++); }

		normal_iterator& operator--() throw()
		{ --m_current_iterator; return *this; }

		normal_iterator operator--(int) throw()
		{ return normal_iterator(m_current_iterator--); }

		reference operator[](difference_type n) const throw()
		{ return m_current_iterator[n]; } // change to address arithmetics

		normal_iterator& operator+=(difference_type n) throw()
		{ return m_current_iterator += n; return *this; }

		normal_iterator operator+(difference_type n) const throw()
		{ return normal_iterator(m_current_iterator + n); }

		normal_iterator& operator-=(difference_type n) throw ()
		{ m_current_iterator -= n; return *this; }

		normal_iterator operator-(difference_type n) const throw()
		{ return normal_iterator(m_current_iterator - n); }

	private:

		/* need special test
		template<typename type_1, typename type_2> // mb move in utils.cpp
		bool is_equal_types()
		{
			return typeid(type_1) == typeid(type_2);
		}
		*/

}; // class normal_iterator

		/* Additional overload with the same iterator-types needs because of the std::rel_ops */

		template<typename it_l, typename it_r, typename container>
		inline bool operator==(const normal_iterator<it_l, container>& lhs,
								const normal_iterator<it_r, container>& rhs) throw()
		{ return lhs.get_iterator() == rhs.get_iterator(); }

		template<typename iterator, typename container>
		inline bool operator==(const normal_iterator<iterator, container>& lhs,
								const normal_iterator<iterator, container>& rhs) throw()
		{ return lhs.get_iterator() == rhs.get_iterator(); }

		template<typename it_l, typename it_r, typename container>
		inline bool operator!=(const normal_iterator<it_l, container>& lhs,
								const normal_iterator<it_r, container>& rhs) throw()
		{ return lhs.get_iterator() != rhs.get_iterator(); }

		template<typename iterator, typename container>
		inline bool operator!=(const normal_iterator<iterator, container>& lhs,
								const normal_iterator<iterator, container>& rhs) throw()
		{ return lhs.get_iterator() != rhs.get_iterator(); }

		template<typename it_l, typename it_r, typename container>
		inline bool operator<(const normal_iterator<it_l, container>& lhs,
								const normal_iterator<it_r, container>& rhs) throw()
		{ return lhs.get_iterator() < rhs.get_iterator(); }

		template<typename iterator, typename container>
		inline bool operator<(const normal_iterator<iterator, container>& lhs,
								const normal_iterator<iterator, container>& rhs) throw()
		{ return lhs.get_iterator() < rhs.get_iterator(); }

		template<typename it_l, typename it_r, typename container>
		inline bool operator>(const normal_iterator<it_l, container>& lhs,
								const normal_iterator<it_r, container>& rhs) throw()
		{ return lhs.get_iterator() > rhs.get_iterator(); }

		template<typename iterator, typename container>
		inline bool operator>(const normal_iterator<iterator, container>& lhs,
								const normal_iterator<iterator, container>& rhs) throw()
		{ return lhs.get_iterator() > rhs.get_iterator(); }

		template<typename it_l, typename it_r, typename container>
		inline bool operator<=(const normal_iterator<it_l, container>& lhs,
								const normal_iterator<it_r, container>& rhs) throw()
		{ return lhs.get_iterator() <= rhs.get_iterator(); }

		template<typename iterator, typename container>
		inline bool operator<=(const normal_iterator<iterator, container>& lhs,
								const normal_iterator<iterator, container>& rhs) throw()
		{ return lhs.get_iterator() <= rhs.get_iterator(); }

		template<typename it_l, typename it_r, typename container>
		inline bool operator>=(const normal_iterator<it_l, container>& lhs,
								const normal_iterator<it_r, container>& rhs) throw()
		{ return lhs.get_iterator() >= rhs.get_iterator(); }

		template<typename iterator, typename container>
		inline bool operator>=(const normal_iterator<iterator, container>& lhs,
								const normal_iterator<iterator, container>& rhs) throw()
		{ return lhs.get_iterator() >= rhs.get_iterator(); }

template<typename iterator>
class reverse_iterator
{
	protected:

		iterator m_current_iterator;

		typedef iterator_traits<iterator>				traits_type;

	public:

		typedef iterator								iterator_type;
		typedef typename traits_type::pointer			pointer;
		typedef typename traits_type::reference			reference;
		typedef typename traits_type::difference_type	difference_type;

		reverse_iterator()
		:	m_current_iterator() { }

		explicit reverse_iterator(iterator_type it)
		:	m_current_iterator(it) { }

		reverse_iterator(const reverse_iterator& it)
		:	m_current_iterator(it.m_current_iterator) { }

		template<typename iter>
		reverse_iterator(const reverse_iterator<iter>& it)
		:	m_current_iterator(it.get_iterator()) { }

	public:

		iterator_type get_iterator() const
		{ return m_current_iterator; }

		reference operator*() const
		{ iterator tmp = m_current_iterator; return *--tmp; }

		pointer operator->() const
		{ iterator tmp = m_current_iterator; return --tmp; }

		reverse_iterator& operator++()
		{ --m_current_iterator; return *this; }

		reverse_iterator operator++(int)
		{ reverse_iterator tmp = *this; --m_current_iterator; return tmp; }

		reverse_iterator& operator--()
		{ ++m_current_iterator; return *this; }

		reverse_iterator operator--(int)
		{ reverse_iterator tmp = *this; ++m_current_iterator; return tmp; }

		reverse_iterator operator+(difference_type n) const
		{ return reverse_iterator(m_current_iterator - n); }

		reverse_iterator& operator+=(difference_type n)
		{ m_current_iterator -= n; return *this; }

		reverse_iterator operator-(difference_type n) const
		{ return reverse_iterator(m_current_iterator + n); }

		reverse_iterator& operator-=(difference_type n)
		{ m_current_iterator += n; return *this; }

		reference operator[](difference_type n) const
		{ return *(*this + n); }

}; // class reverse_iterator

		template<typename iterator>
		inline bool operator==(const reverse_iterator<iterator>& lhs,
								const reverse_iterator<iterator>& rhs)
		{ return lhs.get_iterator() == rhs.get_iterator(); }

		template<typename iterator>
		inline bool operator<(const reverse_iterator<iterator>& lhs,
								const reverse_iterator<iterator>& rhs)
		{ return rhs.get_iterator() < lhs.get_iterator(); }

		template<typename iterator>
		inline bool operator!=(const reverse_iterator<iterator>& lhs,
								const reverse_iterator<iterator>& rhs)
		{ return !(lhs == rhs); }

		template<typename iterator>
		inline bool operator>(const reverse_iterator<iterator>& lhs,
								const reverse_iterator<iterator>& rhs)
		{ return rhs < lhs; }

		template<typename iterator>
		inline bool operator<=(const reverse_iterator<iterator>& lhs,
								const reverse_iterator<iterator>& rhs)
		{ return !(rhs < lhs); }

		template<typename iterator>
		inline bool operator>=(const reverse_iterator<iterator>& lhs,
								const reverse_iterator<iterator>& rhs)
		{ return !(lhs < rhs); }

		template<typename iterator>
		inline typename reverse_iterator<iterator>::difference_type
		operator-(const reverse_iterator<iterator>& lhs, const reverse_iterator<iterator>& rhs)
		{ return rhs.get_iterator() - lhs.get_iterator(); }

		template<typename it_l, typename it_r>
		inline typename reverse_iterator<it_l>::difference_type
		operator-(const reverse_iterator<it_l>& lhs, const reverse_iterator<it_r>& rhs)
		{ return rhs.get_iterator() - lhs.get_iterator(); }

		template<typename iterator>
		inline reverse_iterator<iterator>
		operator+(typename reverse_iterator<iterator>::difference_type n,
					const reverse_iterator<iterator>& it)
		{ return reverse_iterator<iterator>(it.get_iterator() - n); }

} // namespace ft

#endif
