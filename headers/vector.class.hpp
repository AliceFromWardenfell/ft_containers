#ifndef VECTOR_CLASS_HPP
#define VECTOR_CLASS_HPP

#pragma once

#include <memory>
#include <algorithm> // for std::min, mb create own
#include <stdint.h> // for PTRDIFF_MAX

#include "base_vector.class.hpp"
#include "iterator.hpp"

namespace ft
{

template<typename T, typename Allocator = std::allocator<T> >
class vector : protected base_vector<T, Allocator>
{
		typedef base_vector<T, Allocator>					base_type;
		typedef vector<T, Allocator>						this_type;

	public:

		typedef T											value_type;
		typedef T*											pointer;
		typedef const T*									const_pointer;
		typedef T&											reference;
		typedef const T&									const_reference;
		typedef Allocator									allocator_type;
		typedef ptrdiff_t									difference_type;
		typedef typename base_type::size_type				size_type;
		typedef ft::normal_iterator<pointer, vector>		iterator;
		typedef ft::normal_iterator<const_pointer, vector>	const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		using base_type::m_ptr_start;
		using base_type::m_ptr_finish;
		using base_type::m_ptr_end_of_storage;
		using base_type::m_allocate;
		using base_type::m_deallocate;
		using base_type::m_create_storage;

	public:

		vector()
		{
			std::cout << "vector: " << "default constructor" << std::endl; // debug
		}

		explicit vector(const allocator_type& allocator) throw()
		:	base_type(allocator)
		{
			std::cout << "vector: " << "allocator constructor" << std::endl; // debug
		}

		explicit vector(size_type size, const value_type& value = value_type(),
			const allocator_type& allocator = allocator_type())
		:	base_type(check_init_len(size), allocator)
		{
			std::cout << "vector: " << "size&val&alloc constructor" << std::endl; // debug
			fill_value_size_times(m_ptr_start, size, value);
		}

		template<typename InputIterator>
		vector(InputIterator first, InputIterator last,
			const allocator_type& allocator = allocator_type());

		vector(const vector& instance)
		:	base_type(instance.size(), instance.get_allocator())
		{
			copy_elements(instance.begin(), instance.end(), m_ptr_start);
		}

		vector& operator=(const vector& instance);

		~vector() { }

	public:

	/* Capacity */

		size_type size() const throw()
		{ return size_type(m_ptr_finish - m_ptr_start); }

		size_type max_size() const throw();

		void resize(size_type new_size, value_type value = value_type());

		size_type capacity() const throw();

		bool empty() const throw();

		void reserve(size_type size);

	/* Element access */

		reference operator[](size_type index) throw();

		const_reference operator[](size_type index) const throw();

		reference at(size_type index);

		const_reference at(size_type index) const;

		reference front() throw();

		const_reference front() const throw();

		reference back() throw();

		const_reference back() const throw();

	/* Modifiers */

		void assign(size_type size, const value_type& value);

		template<typename InputIterator>
		void assign(InputIterator first, InputIterator last);

		void push_back(const value_type& value);

		void pop_back() throw();

		iterator insert(iterator position, const value_type& value);

		void insert(iterator position, size_type amount, const value_type& value);

		template<typename InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);

		iterator erase(iterator position);

		iterator erase(iterator first, iterator last);

		void swap(vector& instance) throw();

		void clear() throw();

	/* Iterators */

		iterator begin() throw()
		{ return iterator(this->m_ptr_start); }

		const_iterator begin() const throw()
		{ return const_iterator(this->m_ptr_start); }

		iterator end() throw()
		{ return iterator(this->m_ptr_finish); }

		const_iterator end() const throw()
		{ return const_iterator(this->m_ptr_finish); }

		reverse_iterator rbegin() throw()
		{ return reverse_iterator(end()); }

		const_reverse_iterator rbegin() const throw()
		{ return const_reverse_iterator(end()); }

		reverse_iterator rend() throw()
		{ return reverse_iterator(begin()); }

		const_reverse_iterator rend() const throw()
		{ return const_reverse_iterator(begin()); }

	protected:

		void check_range(size_type size) const;

		size_type check_init_len(size_type size) const
		{
			if (size > potential_size())
				throw std::length_error("cannot create ft::vector larger than max_size()");
			return size;
		}

		size_type potential_size() const throw()
		{
			const size_t ptrdiff_max = PTRDIFF_MAX / sizeof(value_type);
			// const size_t allocator_max = allocator_type::max_size();
			// return std::min(ptrdiff_max, allocator_max); // mb replace on ? operator to get rid of <algorithm>
			return ptrdiff_max;
		}

		template <typename iter, typename size, typename V>
		void fill_value_size_times(iter start, size n, const V& val)
		{
			iter current_pos = start;

			try
			{
				for(; n > 0; --n, ++current_pos)
				{
					std::_Construct(std::__addressof(*current_pos), val);
				}
				m_ptr_finish = current_pos;
			}
			catch(...)
			{
				std::_Destroy(start, current_pos);
				throw;
			}
		}

		template<typename it_start, typename it_finish>
		void copy_elements(it_start start, it_start finish, it_finish result)
		{
			it_finish current_pos = result;

			try
			{
				for (; start != finish; ++start, (void)++current_pos)
				std::_Construct(std::__addressof(*current_pos), *start);
				m_ptr_finish = current_pos;
			}
			catch(...)
			{
				std::_Destroy(result, current_pos);
				throw;
			}
		}

}; // class vector

	template<typename T, typename Allocator>
	inline void swap(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) throw();

	/* Relational operators */

	template<typename T, typename Allocator>
	inline bool operator==(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);

	template<typename T, typename Allocator>
	inline bool operator<(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);

	template<typename T, typename Allocator>
	inline bool operator!=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);

	template<typename T, typename Allocator>
	inline bool operator>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);

	template<typename T, typename Allocator>
	inline bool operator<=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);

	template<typename T, typename Allocator>
	inline bool operator>=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);

} // namespace ft

#endif
