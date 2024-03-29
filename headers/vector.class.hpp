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
		using base_type::m_create_storage; // mb remove

	public:

		vector() { }

		explicit vector(const allocator_type& allocator) throw()
		:	base_type(allocator) { }

		explicit vector(size_type size, const value_type& value = value_type(),
			const allocator_type& allocator = allocator_type())
		:	base_type(check_init_len(size), allocator)
		{
			fill_value_size_times(m_ptr_start, size, value);
			m_ptr_finish += size;
		}

		template<typename iter>
		vector(iter first, iter last,
			typename ft::enable_if<!ft::is_integral<iter>::value, bool>::type* = NULL)
		{
			typedef typename ft::iterator_traits<iter>::iterator_category it_tag;
			range_init(first, last, it_tag());
		}

		vector(const vector& instance)
		:	base_type(instance.size(), instance.get_allocator())
		{
			copy_elements(instance.begin(), instance.end(), m_ptr_start);
			m_ptr_finish += instance.size();
		}

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

		size_type max_size() const throw()
		{ return potential_size(); }

		void resize(size_type new_size, value_type value = value_type())
		{
			if (new_size == size())
				return;
			if (new_size > size())
				insert_values_from_position(value, end(), new_size - size());
			if (new_size < size())
				excise_after_position(m_ptr_start + new_size);
		}

		size_type capacity() const throw()
		{ return (size_type)(m_ptr_end_of_storage - m_ptr_start); }

		bool empty() const throw()
		{ return begin() == end(); }

		void reserve(size_type size)
		{
			if (size > max_size())
				throw std::length_error("reserve(): max_size limit");
			if (capacity() < size)
				reallocate(size);
		}

	/* Element access */

		reference operator[](size_type index) throw()
		{ return *(m_ptr_start + index); }

		const_reference operator[](size_type index) const throw()
		{ return *(m_ptr_start + index); }

		reference at(size_type index)
		{
			if (index >= size())
				throw std::out_of_range("at(): out of vector range");
			return (*this)[index];
		}

		const_reference at(size_type index) const
		{
			if (index >= size())
				throw std::out_of_range("at(): out of vector range");
			return (*this)[index];
		}

		reference front() throw()
		{ return *begin(); }

		const_reference front() const throw()
		{ return *begin(); }

		reference back() throw()
		{ return *(end() - 1); }

		const_reference back() const throw()
		{ return *(end() - 1); }

	/* Modifiers */

		void assign(size_type new_size, const value_type& value)
		{
			value_type value_copy = value;
			if (new_size > capacity())
			{
				vector tmp(new_size, value, m_allocator);
				tmp.swap(*this);
			}
			else if (new_size > size())
			{
				pointer current_pos = m_ptr_start;
				while (current_pos < m_ptr_finish)
				{
					m_allocator.destroy(&(*current_pos));
					m_allocator.construct(&(*current_pos++), value_copy);
				}
				m_ptr_finish += new_size - size();
				while (current_pos < m_ptr_finish)
					m_allocator.construct(&(*current_pos++), value_copy);
			}
			else
			{
				pointer current_pos = m_ptr_start;
				pointer old_finish = m_ptr_finish;
				m_ptr_finish -= size() - new_size;
				while (current_pos < m_ptr_finish)
				{
					m_allocator.destroy(&(*current_pos));
					m_allocator.construct(&(*current_pos++), value_copy);
				}
				while (current_pos < old_finish)
					m_allocator.destroy(&(*current_pos++));
			}
		}

		template<typename iter>
		void assign(iter first, iter last,
			typename ft::enable_if<!ft::is_integral<iter>::value, bool>::type* = NULL)
		{
			const size_type range_size = std::distance(first, last);
			if (range_size > capacity())
			{
				vector tmp(first, last);
				tmp.swap(*this);
			}
			else if (size() >= range_size)
			{
				excise_after_position(m_ptr_start + range_size);
				pointer current_pos = m_ptr_start;
				while (current_pos != m_ptr_finish)
				{
					m_allocator.destroy(&(*current_pos));
					m_allocator.construct(&(*current_pos++), *first++);
				}
			}
			else
			{
				pointer current_pos = m_ptr_start;
				while (current_pos != m_ptr_finish)
				{
					m_allocator.destroy(&(*current_pos));
					m_allocator.construct(&(*current_pos++), *first++);
				}
				m_ptr_finish = m_ptr_start + range_size;
				while (current_pos != m_ptr_finish)
					m_allocator.construct(&(*current_pos++), *first++);
			}
		}

		void push_back(const value_type& value)
		{
			if (m_ptr_finish == m_ptr_end_of_storage)
				reallocate();
			m_allocator.construct(m_ptr_finish++, value);
		}
		
		void pop_back() throw()
		{
			m_ptr_finish--;
			m_allocator.destroy(&(*m_ptr_finish));
		}

		iterator insert(iterator position, const value_type& value)
		{
			insert_values_from_position(value, position, (size_type)1);
			return position;
		}

		void insert(iterator position, size_type amount, const value_type& value)
		{ insert_values_from_position(value, position, amount); }

		template<typename iter>
		void insert(iterator position, iter first, iter last,
			typename ft::enable_if<!ft::is_integral<iter>::value, bool>::type* = NULL)
		{ insert_range_from_position(position, first, last); }

		iterator erase(iterator position)
		{
			if (position + 1 != end())
				copy_elements(position + 1, end(), position);
			m_ptr_finish--;
			m_allocator.destroy(&(*m_ptr_finish));
			return position;
		}

		iterator erase(iterator first, iterator last)
		{
			if (first != last)
			{
				if (last != end())
					copy_elements(last, end(), first);
				excise_after_position(first.get_iterator() + (end() - last));
			}
			return first;
		}

		void swap(vector& instance) throw()
		{
			this_type tmp;
			tmp.copy_data(*this);
			copy_data(instance);
			instance.copy_data(tmp);

			tmp.m_ptr_start = NULL;
			tmp.m_ptr_finish = NULL;
			tmp.m_ptr_end_of_storage = NULL;

			// mb swap allocators
		}

		void clear() throw()
		{ excise_after_position(m_ptr_start); }

	/* Iterators */

		iterator begin() throw()
		{ return iterator(m_ptr_start); }

		const_iterator begin() const throw()
		{ return const_iterator(m_ptr_start); }

		iterator end() throw()
		{ return iterator(m_ptr_finish); }

		const_iterator end() const throw()
		{ return const_iterator(m_ptr_finish); }

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
				for (; n > 0; --n, (void)++current_pos)
					m_allocator.construct(&(*current_pos), val);
			}
			catch(...)
			{
				while (start++ != current_pos)
					m_allocator.destroy(&(*start));
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
					m_allocator.construct(&(*current_pos), *start);
			}
			catch(...)
			{
				while (result++ != current_pos)
					m_allocator.destroy(&(*result));
				throw;
			}
		}

		template<typename it_start, typename it_finish>
		void copy_elements_backward(it_start start, it_start finish, it_finish result)
		{
			it_finish current_pos = result;

			try
			{
				while (finish != start)
					m_allocator.construct(&(*--current_pos), *--finish);
			}
			catch(...)
			{
				while (result-- != current_pos)
					m_allocator.destroy(&(*result));
				throw;
			}
		}

		void copy_data(vector& instance) throw()
		{
			m_ptr_start = instance.m_ptr_start;
			m_ptr_finish = instance.m_ptr_finish;
			m_ptr_end_of_storage = instance.m_ptr_end_of_storage;
		}

		void excise_after_position(pointer position) throw()
		{
			size_type tale = m_ptr_finish - position;
			pointer new_finish = position;
			
			if (tale)
			{
				while (position++ != m_ptr_finish)
					m_allocator.destroy(&(*position));
				m_ptr_finish = new_finish;
			}
		}

		size_type check_new_vector_size(size_type size_to_insert) const
		{
			if (max_size() - size() < size_to_insert)
				throw std::length_error("insert_values_from_position(): max_size limit");
			const size_type updated_size = size() + ft::max(size(), size_to_insert);
			return updated_size > max_size() ? max_size() : updated_size;
		}

		void insert_values_from_position(const value_type& value, iterator position, size_type size_to_insert)
		{
			if (!size_to_insert)
				return;

			if (size_type(m_ptr_end_of_storage - m_ptr_finish) >= size_to_insert)
			{
				value_type value_copy = value;
				const size_type elements_amount_after_position = end() - position;
				pointer old_finish = m_ptr_finish;
				if (elements_amount_after_position > size_to_insert)
				{
					copy_elements(m_ptr_finish - size_to_insert, m_ptr_finish, m_ptr_finish);
					m_ptr_finish += size_to_insert;
					fill_value_size_times(position, size_to_insert, value_copy);
				}
				else
				{
					fill_value_size_times(m_ptr_finish, size_to_insert - elements_amount_after_position, value_copy);
					m_ptr_finish += size_to_insert - elements_amount_after_position;
					copy_elements(position.get_iterator(), old_finish, m_ptr_finish);
					m_ptr_finish += elements_amount_after_position;
					fill_value_size_times(position.get_iterator(), elements_amount_after_position, value_copy);
				}
			}
			else
			{
				const size_type new_vector_size = check_new_vector_size(size_to_insert);
				const size_type elements_amount_before_position = position - begin();
				const size_type elements_amount_after_position = end() - position;

				pointer new_start = m_allocate(new_vector_size);
				pointer new_finish = new_start;

				fill_value_size_times(new_start + elements_amount_before_position, size_to_insert, value);
				new_finish += elements_amount_before_position + size_to_insert;

				copy_elements(m_ptr_start, position.get_iterator(), new_start);
				copy_elements(position.get_iterator(), m_ptr_finish, new_finish);
				new_finish += elements_amount_after_position;

				base_type::~base_type();
				m_ptr_start = new_start;
				m_ptr_finish = new_finish;
				m_ptr_end_of_storage = new_start + new_vector_size;
			}
		}

		template<typename iter>
		void insert_range_from_position(iterator position, iter first, iter last)
		{
			if (first == last)
				return;

			const size_type range_size = ft::distance(first, last);
			if (size_type(m_ptr_end_of_storage - m_ptr_finish) >= range_size)
			{
				const size_type elements_amount_after_position = end() - position;
				pointer old_finish = m_ptr_finish;
				pointer middle = m_ptr_finish;
				middle += elements_amount_after_position + range_size;
				if (elements_amount_after_position > range_size)
				{
					copy_elements(m_ptr_finish - range_size, m_ptr_finish, m_ptr_finish);
					m_ptr_finish += range_size;
					copy_elements_backward(position.get_iterator(), old_finish - range_size, old_finish);
					copy_elements(first, last, position);
				}
				else
				{
					iter middle = first;
					middle += elements_amount_after_position;
					
					copy_elements(middle, last, m_ptr_finish);
					m_ptr_finish += range_size - elements_amount_after_position;
					copy_elements(position.get_iterator(), old_finish, m_ptr_finish);
					m_ptr_finish += elements_amount_after_position;
					copy_elements(first, middle, position.get_iterator());
				}
			}
			else
			{
				const size_type new_vector_size = check_new_vector_size(range_size);
				const size_type elements_amount_before_position = position - begin();
				const size_type elements_amount_after_position = end() - position;

				pointer new_start = m_allocate(new_vector_size);
				pointer new_finish = new_start;

				copy_elements(m_ptr_start, position.get_iterator(), new_start);
				new_finish += elements_amount_before_position;

				copy_elements(first, last, new_finish);
				new_finish += range_size;

				copy_elements(position.get_iterator(), m_ptr_finish, new_finish);
				new_finish += elements_amount_after_position;

				base_type::~base_type();
				m_ptr_start = new_start;
				m_ptr_finish = new_finish;
				m_ptr_end_of_storage = new_start + new_vector_size;
			}
		}

		void reallocate(size_type specific_capacity = 0)
		{
			size_type current_capacity = size_type(m_ptr_end_of_storage - m_ptr_start);
			size_type new_capacity;

			if (specific_capacity)
				new_capacity = specific_capacity;
			else
				new_capacity = current_capacity ? current_capacity * (size_type)MEM_REALLOC_FACTOR : 1;

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
	inline void swap(vector<T, Allocator>& lhs, vector<T, Allocator>& rhs)
	{ lhs.swap(rhs); }

	/* Relational operators */

	template<typename T, typename Allocator>
	inline bool operator==(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}

	template<typename T, typename Allocator>
	inline bool operator<(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

	template<typename T, typename Allocator>
	inline bool operator!=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{ return (!(lhs == rhs)); }

	template<typename T, typename Allocator>
	inline bool operator>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{ return rhs < lhs; }

	template<typename T, typename Allocator>
	inline bool operator<=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{ return !(rhs < lhs); }

	template<typename T, typename Allocator>
	inline bool operator>=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{ return !(lhs < rhs); }

} // namespace ft

#endif
