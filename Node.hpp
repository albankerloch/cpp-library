#ifndef DEF_NODE_HPP
# define DEF_NODE_HPP

# include <iostream>

namespace ft 
{
    template<typename T >
    class Node
    {
		public:

			T					data;
			Node				*prev;
			Node				*next;

			Node(): data(0), prev(0), next(0) {}
			
			Node(T const & elem): prev(0), data(elem), next(0) {}

			Node(T const & elem, Node *previous, Node *next):  data(elem), prev(previous), next(next) {}

			/*Node(Node const & Node_to_Copy)
			{
				*this = src;
			}

			Node &operator=(Node const & Node_to_Copy)
			{
				this->data = Node_to_Copy.data;
				this->next = Node_to_Copy.next;
				this->prev = Node_to_Copy.prev;

				return (*this);
			};*/
			
			virtual ~Node() {}
	};
}

#endif