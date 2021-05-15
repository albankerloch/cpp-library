#ifndef LIST_ITERATOR_HPP
# define LIST_ITERATOR_HPP

# include "utils.hpp"
# include "Node.hpp"

namespace ft
{
	template <typename T>
	class List_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category     iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type            value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type       difference_type;
			typedef T*  pointer;
			typedef T&  reference;

			List_iterator()
			:
				_node(u_nullptr)
			{}

			List_iterator(Node<T> *init_node)
			:
				_node(init_node)
			{}

			List_iterator(const List_iterator& x)
			:
				_node(x._node)
			{}

			List_iterator &operator= (const List_iterator& x)
			{
				if (&x == this)
					return (*this);
				this->_node = x._node;
				return (*this);
			}

			virtual ~List_iterator() {}

			reference operator* (void) { return (_node->data); }

			pointer operator->(void) { return &(this->operator*()); }
	
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

			friend bool operator==(const List_iterator<T>& lhs, const List_iterator<T>& rhs)
			{ return (lhs._node == rhs._node); }

			friend bool operator!=(const List_iterator<T>& lhs, const List_iterator<T>& rhs)
			{ return (lhs._node != rhs._node); }

			Node<T> *_node;
	};
	
	template <typename T>
	class List_const_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category     iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type            value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type       difference_type;
			typedef const T*  pointer;
			typedef const T&  reference;

			List_const_iterator()
			:
				_node(u_nullptr)
			{}

			List_const_iterator(Node<T> *init_node)
			:
				_node(init_node)
			{}

			List_const_iterator(const List_const_iterator& x)
			:
				_node(x._node)
			{}

			List_const_iterator(const List_iterator<T>& x)
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