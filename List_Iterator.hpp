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
			typedef value_type* 		pointer;
			typedef value_type const	*const_pointer;
			typedef value_type&			reference;
			typedef value_type const &	const_reference;
			typedef std::ptrdiff_t 		difference_type;
			typedef N 					node_type;
			typedef node_type* 			node_pointer;

			Node<T> *_node;

			List_iterator() : _node(NULL) {}

			List_iterator(Node<T> *init_node) : _node(init_node) {}

			List_iterator(const List_iterator& x) : _node(x._node) {}

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
				return (this->_node != other._node );
			}

	};	

	template <typename T>
	class List_const_iterator : IteratorTrait
	{
		public:
			typedef T 					value_type;
			typedef value_type* 		pointer;
			typedef value_type const	*const_pointer;
			typedef value_type&			reference;
			typedef value_type const &	const_reference;
			typedef std::ptrdiff_t 		difference_type;

			List_const_iterator()
			:
				_node(NULL)
			{}

			List_const_iterator(Node<T> *init_node)
			:
				_node(init_node)
			{}

			List_const_iterator(const List_const_iterator& x)
			:
				_node(x._node)
			{}

			List_const_iterator(const List_iterator<T, Node<T> >& x)
			:
				_node(x._node)
			{}

			List_const_iterator &operator= (const List_const_iterator& x)
			{
				if (&x == this)
					return (*this);
				this->_node = x._node;
				return (*this);
			}

			virtual ~List_const_iterator() {}

			reference operator* (void) { return (_node->data); }

			pointer operator->(void) { return &(this->operator*()); }
	
			List_const_iterator& operator++(void)
			{
				this->_node = this->_node->m_next;
				return (*this);
			}

			List_const_iterator operator++(int)
			{
				List_const_iterator rtn(*this);
				operator++();
				return (rtn);
			}

			List_const_iterator& operator--(void)
			{
				this->_node = this->_node->prev;
				return (*this);
			}

			List_const_iterator operator--(int)
			{
				List_const_iterator rtn(*this);
				operator--();
				return (rtn);
			}

			friend bool operator==(const List_const_iterator<T>& lhs, const List_const_iterator<T>& rhs)
			{ return (lhs._node == rhs._node); }

			friend bool operator!=(const List_const_iterator<T>& lhs, const List_const_iterator<T>& rhs)
			{ return (lhs._node != rhs._node); }

			Node<T> *_node;
	};
}

#endif