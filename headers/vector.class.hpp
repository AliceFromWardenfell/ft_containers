#ifndef VECTOR_CLASS_HPP
#define VECTOR_CLASS_HPP

#pragma once

#include <stdint.h> // for PTRDIFF_MAX

#include "base_vector.class.hpp"
#include "iterator.hpp"
#include "traits.hpp"

#define MEM_REALLOC_FACTOR 2

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
		using base_type::m_allocator;
		using base_type::m_allocate;
		using base_type::m_deallocate;
		using base_type::m_create_storage;

	public:

		vector() { }

		explicit vector(const allocator_type& allocator) throw()
		:	base_type(allocator) { }

		explicit vector(size_type size, const value_type& value = value_type(),
			const allocator_type& allocator = allocator_type())
		:	base_type(check_init_len(size), allocator)
		{ fill_value_size_times(m_ptr_start, size, value); }

		template<typename iter>
		vector(iter first, iter last,
			typename ft::enable_if<!ft::is_integral<iter>::value, bool>::type* = NULL)
		{
			typedef typename ft::iterator_traits<iter>::iterator_category it_tag;
			range_init(first, last, it_tag());
		}

		vector(const vector& instance)
		:	base_type(instance.size(), instance.get_allocator())
		{ copy_elements(instance.begin(), instance.end(), m_ptr_start); }

		vector& operator=(const vector& instance)
		{
			if (&instance == this) return *this;

			base_type::~base_type();
			range_init(instance.begin(), instance.end(), std::forward_iterator_tag()); // Think how to send actual iterator tag
			
			return *this;
		}

		~vector() throw() { }

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

		reference operator[](size_type index) throw()
		{ return *(m_ptr_start + index); }

		const_reference operator[](size_type index) const throw();

		reference at(size_type index);

		const_reference at(size_type index) const;

		reference front() throw();

		const_reference front() const throw();

		reference back() throw();

		const_reference back() const throw();

	/* Modifiers */

		void assign(size_type size, const value_type& value);

		template<typename iter>
		void assign(iter first, iter last);

		void push_back(const value_type& value)
		{
			if (m_ptr_finish == m_ptr_end_of_storage)
				reallocate();
			m_allocator.construct(m_ptr_finish++, value);
		}
		
		void pop_back() throw();

		iterator insert(iterator position, const value_type& value);

		void insert(iterator position, size_type amount, const value_type& value);

		template<typename iter>
		void insert(iterator position, iter first, iter last);

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

		size_type check_init_len(size_type size) const
		{
			if (size > potential_size())
				throw std::length_error("cannot create ft::vector larger than max_size()");
			return size;
		}

		size_type potential_size() const throw()
		{
			const size_t ptrdiff_max = PTRDIFF_MAX / sizeof(value_type);
			const size_type allocator_max = m_allocator.max_size(); 
			return ptrdiff_max < allocator_max ? ptrdiff_max : allocator_max;
		}

		template <typename iter, typename size, typename V>
		void fill_value_size_times(iter start, size n, const V& val)
		{
			iter current_pos = start;

			try
			{
				for (; n > 0; --n, ++current_pos)
					m_allocator.construct(current_pos, val);
				m_ptr_finish = current_pos;
			}
			catch(...)
			{
				while (start++ != current_pos)
					m_allocator.destroy(start);
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
					m_allocator.construct(current_pos, *start);
				m_ptr_finish = current_pos;
			}
			catch(...)
			{
				while (result++ != current_pos)
					m_allocator.destroy(result);
				throw;
			}
		}

		void reallocate()
		{
			size_type current_capacity = size_type(m_ptr_end_of_storage - m_ptr_start);
			size_type new_capacity = current_capacity ? current_capacity * (size_type)MEM_REALLOC_FACTOR : 1;
			
			pointer new_start = m_allocate(new_capacity);
			
			for (size_type i = 0; i < size(); ++i)
				m_allocator.construct(&new_start[i], m_ptr_start[i]);

			m_ptr_finish = new_start + size();
			m_deallocate(m_ptr_start, size());
			m_ptr_start = new_start;
			m_ptr_end_of_storage = m_ptr_start + new_capacity;
		}

		template <typename iter>
		inline void range_init(iter start, iter finish, std::input_iterator_tag)
		{
			for(; start != finish; ++start)
				push_back(*start);
		}

		template <typename iter>
		inline void range_init(iter start, iter finish, std::forward_iterator_tag)
		{
			const size_type size = (size_type)ft::distance(start, finish);
			m_ptr_start = m_allocate(check_init_len(size));
			m_ptr_end_of_storage = m_ptr_start + size;
			m_ptr_finish = m_ptr_end_of_storage;

			copy_elements(start, finish, m_ptr_start); // mb need to remove const from m_ptr_start
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
