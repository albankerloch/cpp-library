#ifndef DEF_REVERSE_ITERATOR_HPP
# define DEF_REVERSE_ITERATOR_HPP

# include <iostream>

namespace ft 
{
    template<typename Iterator>
	class ReverseIterator:	public Iterator
	{
		public:

			using typename Iterator::value_type;
			using typename Iterator::pointer;
			using typename Iterator::const_pointer;
			using typename Iterator::reference;
			using typename Iterator::const_reference;
			using typename Iterator::difference_type;

		public:
			ReverseIterator(): Iterator() {}

			ReverseIterator(Iterator const &it): Iterator(it) {}

			ReverseIterator(ReverseIterator const &other): Iterator(other.p) {}

			ReverseIterator &operator=(ReverseIterator const &other) 
			{
				this->p = other.p;
				return (*this);
			}

			reference operator*() 
			{
				Iterator tmp(*this);
				return (*--tmp);
			}

			const_reference operator*() const 
			{
				Iterator tmp(*this);
				return (*--tmp);
			}

			pointer operator->() 
			{
				Iterator tmp(*this);
				return (&*--tmp);
			}

			const_pointer operator->() const 
			{
				Iterator tmp(*this);
				return (&*--tmp);
			}

			ReverseIterator operator++(int) 
			{
				ReverseIterator tmp(*this);
				operator++();
				return (tmp);
			}

			Iterator &operator++() 
			{
				return (this->Iterator::operator--());
			}
			
			ReverseIterator operator--(int) 
			{
				ReverseIterator tmp(*this);
				operator--();
				return (tmp);
			}

			Iterator &operator--() 
			{
				return (this->Iterator::operator++());
			}
	};
}

#endif