#ifndef BASE_VECTOR_CLASS_HPP
#define BASE_VECTOR_CLASS_HPP

#pragma once

#include <memory>

namespace ft
{

template<typename T, typename Allocator = std::allocator<T> >
struct base_vector
{
		typedef Allocator	allocator_type;
		typedef T			value_type;
		typedef T*			pointer;
		typedef std::size_t	size_type;

	public:

		base_vector()
		:	m_ptr_start(NULL),
			m_ptr_finish(NULL),
			m_ptr_end_of_storage(NULL),
			m_allocator(std::allocator<value_type>()) { }

		base_vector(const allocator_type& allocator) throw()
		:	m_ptr_start(NULL),
			m_ptr_finish(NULL),
			m_ptr_end_of_storage(NULL),
			m_allocator(allocator) { }

		base_vector(size_type size)
		:	m_allocator(std::allocator<value_type>())
		{ m_create_storage(size); }

		base_vector(size_type size, const allocator_type& allocator)
		:	m_allocator(allocator)
		{ m_create_storage(size); }

		~base_vector() throw()
		{ m_deallocate(m_ptr_start, m_ptr_end_of_storage - m_ptr_start); }

		allocator_type	get_allocator() const throw()
		{ return m_allocator; }

	protected:

		pointer			m_ptr_start;
		pointer			m_ptr_finish;
		pointer			m_ptr_end_of_storage;
		allocator_type	m_allocator;

	protected:

		pointer	m_allocate(size_type size)
		{
			return m_allocator.allocate(size);
		}

		void	m_deallocate(pointer ptr, size_type size)
		{
			if (ptr)
			{
				m_allocator.deallocate(ptr, size);
			}
		}

		void	m_create_storage(size_type size)
		{
			m_ptr_start = m_allocate(size);
			m_ptr_finish = m_ptr_start;
			m_ptr_end_of_storage = m_ptr_start + size;
		}

}; // class base_vector

} // namespace ft

#endif
