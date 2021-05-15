#ifndef DEF_NODE_HPP
# define DEF_NODE_HPP

# include <iostream>

namespace ft 
{
    template<typename T >
    class Node
    {
		public:

			Node				*m_previous;
			Node				*m_next;
			T					data;

			Node(): m_previous(0), m_next(0) {}
			
			Node(T const & elem): m_previous(0), m_next(0), data(elem) {}

			Node(T const & elem, Node *previous, Node *m_next): m_previous(previous), m_next(m_next), data(elem) {}

			Node(Node const & Node_to_Copy)
			{
				*this = Node_to_Copy;
			}

			Node &operator=(Node const & Node_to_Copy)
			{
				this->data = Node_to_Copy.data;
				this->m_next = Node_to_Copy.m_next;
				this->m_previous = Node_to_Copy.m_previous;
				return (*this);
			};
			
			virtual ~Node() {}
	};
}

#endif