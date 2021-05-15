#ifndef DEF_NODE_HPP
# define DEF_NODE_HPP

# include <iostream>

namespace ft 
{
    template<typename T, class allocator = std::allocator<T> >
    class Node
    {
		public :

			typedef allocator	allocator_type;

		private:

			Node				*m_previous;
			Node				*m_next;
			T					*m_pointer;
			allocator_type		m_allocator;

		public:

			Node(const allocator_type& alloc = allocator_type()): m_previous(0), m_pointer(0), m_next(0), m_allocator(alloc) {}
			
			Node(T const & elem, const allocator_type& alloc = allocator_type()): m_previous(0), m_pointer(0), m_next(0), m_allocator(alloc) 
			{
				this->m_pointer = m_allocatorator.allocate(1);
				this->m_allocator.construct(m_pointer, elem);
			}

			Node(T const & elem, Node *previous, Node *next, const allocator_type & alloc = allocator_type()): m_previous(previous), m_pointer(0), m_next(next), m_allocator(alloc) 
			{
				this->m_pointer = m_allocatorator.allocate(1);
				this->m_allocator.construct(m_pointer, elem);
			}

			Node(Node const & Node_to_Copy)
			{
				*this = src;
			}

			Node &operator=(Node const & Node_to_Copy)
			{
				this->m_pointer = Node_to_Copy.m_pointer;
				this->m_next = Node_to_Copy.m_next;
				this->m_previous = Node_to_Copy.m_previous;
				this->m_allocator = Node_to_Copy.m_allocator;

				return (*this);
			};
			
			virtual ~Node() 
			{
				if (this->m_pointer)
				{
					this->m_allocator.destroy(this->m_pointer);
					this->m_allocator.deallocate(this->m_pointer, 1);
				}
			}
	};
}

#endif