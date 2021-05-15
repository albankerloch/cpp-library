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

			node_pointer p;

			List_iterator() : p(NULL) {}

			List_iterator(node_pointer initp) : p(initp) {}

			List_iterator(List_iterator const & x) : p(x.p) {}

			List_iterator &operator= (const List_iterator& x) 
			{
				if (&x == this)
					return (*this);
				this->p = x.p;
				return (*this);
			}

			virtual ~List_iterator() {}

			reference operator*(void)
			{
				return (p->data); 
			}

			pointer operator->(void) 
			{
				return &(this->operator*()); 
			}
	
			List_iterator& operator++(void)
			{
				this->p = this->p->m_next;
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
				this->p = this->p->m_previous;
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
				return (this->p  == other.p);
			}

			bool operator!=(List_iterator const &other) const 
			{
				return (this->p != other.p);
			}
	};	
}

#endif