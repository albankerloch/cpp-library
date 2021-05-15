#ifndef LIST_ITERATOR_HPP
# define LIST_ITERATOR_HPP

# include "Node.hpp"
# include "Algo.hpp"

namespace ft
{
	template<class InputIterator>
	typename std::ptrdiff_t  distance (InputIterator first, InputIterator last)
	{
		typename std::ptrdiff_t  rtn = 0;
		while (first != last)
		{
			first++;
			rtn++;
		}
		return (rtn);
	}

	template <typename T, typename N>
	class List_iterator : IteratorTrait
	{
		public:

			typedef T 					value_type;
			typedef value_type *  		pointer;
			typedef value_type const*   const_pointer;
			typedef value_type &		reference;
			typedef value_type const &	const_reference;
			typedef std::ptrdiff_t 		difference_type;
			typedef N 					node_type;
			typedef node_type* 			node_pointer;

			node_pointer _node;

			List_iterator() : _node(NULL) {}

			List_iterator(node_pointer init_node) : _node(init_node) {}

			List_iterator(List_iterator const & x) : _node(x._node) {}

			List_iterator &operator= (const List_iterator& x) 
			{
				if (&x == this)
					return (*this);
				this->_node = x._node;
				return (*this);
			}

			virtual ~List_iterator() {}

			reference operator*(void)
			{
				return (_node->data); 
			}

			pointer operator->(void) 
			{
				return &(this->operator*()); 
			}
	
			List_iterator& operator++(void)
			{
				this->_node = this->_node->m_next;
				return (*this);
			}

			List_iterator operator++(int)
			{
				List_iterator rtn(*this);
				operator++();
				return (rtn);
			}

			List_iterator& operator--(void)
			{
				this->_node = this->_node->m_previous;
				return (*this);
			}

			List_iterator operator--(int)
			{
				List_iterator rtn(*this);
				operator--();
				return (rtn);
			}

			bool operator==(List_iterator const &other) const 
			{
				return (this->_node  == other._node);
			}

			bool operator!=(List_iterator const &other) const 
			{
				return (this->_node != other._node);
			}
	};	
}

#endif