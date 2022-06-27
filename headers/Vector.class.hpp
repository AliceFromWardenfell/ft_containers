#ifndef VECTOR_CLASS_HPP
# define VECTOR_CLASS_HPP

#pragma once

#include <memory>
#include "BaseVector.class.hpp"

namespace ft
{

template< typename T, typename Allocator = std::allocator<T> >
class vector : protected BaseVector<T, Allocator>
{
		typedef BaseVector<T, Allocator>			base_type;
		typedef vector<T, Allocator>				this_type;

	public:

		typedef T									value_type;
		typedef T*									pointer;
		typedef const T*							const_pointer;
		typedef T&									reference;
		typedef const T&							const_reference;
		typedef Allocator							allocator_type;
		typedef typename base_type::size_type		size_type;
		typedef T*									iterator; // tmp typedef

		using base_type::ptrStart;
		using base_type::ptrFinish;
		using base_type::ptrEndOfStorage;
		using base_type::Allocate;
		using base_type::Deallocate;
		using base_type::CreateStorage;

	public:

		vector()
		{
			std::cout << "vector: " << "default constructor" << std::endl; // debug
		}

		explicit vector(const allocator_type& allocator)
		:	base_type(allocator)
		{
			std::cout << "vector: " << "allocator constructor" << std::endl; // debug
		}

		explicit vector(size_type size, const value_type& value = value_type(),
			const allocator_type& allocator = allocator_type());

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last,
			const allocator_type& allocator = allocator_type());

		vector(const vector& instance);

		vector& operator=(const vector& instance);

		~vector();

	public:

	/* Capacity */

		size_type size() const throw();

		size_type max_size() const throw();

		void resize(size_type new_size, value_type value = value_type());

		size_type capacity() const throw();

		bool empty() const throw();

		void reserve (size_type size);

	/* Element access */

		reference operator[] (size_type index) throw();

		const_reference operator[] (size_type index) const throw();

		reference at (size_type index);

		const_reference at (size_type index) const;

		reference front() throw();

		const_reference front() const throw();

		reference back() throw();

		const_reference back() const throw();

	/* Modifiers */

		void assign(size_type size, const value_type& value);

		template<typename InputIterator>
		void assign(InputIterator first, InputIterator last);

		void push_back (const value_type& value);

		void pop_back() throw();

		iterator insert (iterator position, const value_type& value);

		void insert (iterator position, size_type amount, const value_type& value);

		template <typename InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last);

		iterator erase (iterator position);

		iterator erase (iterator first, iterator last);

		void swap (vector& instance) throw();

		void clear() throw();

	/* Iterators */

		// Place for iterators

	protected:

		void CheckRange(size_type size) const;

}; // class vector

	template <typename T, typename Allocator>
	inline void swap(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) throw();

	/* Relational operators */

	template <typename T, typename Allocator>
	inline bool operator==(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);

	template <typename T, typename Allocator>
	inline bool operator<(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);

	template <typename T, typename Allocator>
	inline bool operator!=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);

	template <typename T, typename Allocator>
	inline bool operator>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);

	template <typename T, typename Allocator>
	inline bool operator<=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);

	template <typename T, typename Allocator>
	inline bool operator>=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);

} // namespace ft

#endif
