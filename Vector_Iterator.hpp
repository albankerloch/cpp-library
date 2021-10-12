#ifndef DEF_VECTOR_ITERATOR_HPP
# define DEF_VECTOR_ITERATOR_HPP

# include <iostream>
# include "Algo.hpp"

namespace ft 
{
    template<typename T>
    class VectorIterator: IteratorTrait
    {
		public:

			typedef T 					value_type;
			typedef value_type* 		pointer;
			typedef value_type const	*const_pointer;
			typedef value_type&			reference;
			typedef value_type const &	const_reference;
			typedef std::ptrdiff_t 		difference_type;

		protected:
		
			pointer p;

		public:

			VectorIterator(): p(0) {}

			VectorIterator(pointer p): p(p) {}

			VectorIterator(VectorIterator const &other): p(other.p) {}

			virtual ~VectorIterator() {}

			VectorIterator &operator=(VectorIterator const &other) 
			{
				this->p = other.p;
				return (*this);
			}

			reference operator*() 
			{
				return (*this->p);
			}

			const_reference operator*() const 
			{
				return (*this->p);
			}

			pointer operator->() 
			{
				return (this->p);
			}

			const_pointer operator->() const 
			{
				return (this->p);
			}

			reference operator[](int val) 
			{
				return (*(this->p + val));
			}

			const_reference operator[](int val) const 
			{
				return (*(this->p + val));
			}

			VectorIterator operator++(int) 
			{
				VectorIterator tmp(*this);
				++this->p;
				return (tmp);
			}
			
			VectorIterator &operator++() 
			{
				++this->p;
				return (*this);
			}

			VectorIterator operator--(int) 
			{
				VectorIterator tmp(*this);
				--this->p;
				return (tmp);
			}

			VectorIterator &operator--() 
			{
				--this->p;
				return (*this);
			}

			VectorIterator &operator+=(int value) 
			{
				this->p += value;
				return (*this);
			}

			VectorIterator operator+(int value) const 
			{
				VectorIterator tmp(*this);
				return (tmp += value);
			}

			VectorIterator &operator-=(int value) 
			{
				this->p -= value;
				return (*this);
			}

			VectorIterator operator-(int value) const 
			{
				VectorIterator tmp(*this);
				return (tmp -= value);
			}

			difference_type operator-(VectorIterator const &other) const 
			{
				return (this->p - other.p);
			}

			bool operator==(VectorIterator const &other) const 
			{
				return (this->p == other.p);
			}

			bool operator!=(VectorIterator const &other) const 
			{
				return (this->p != other.p);
			}

			bool operator<(VectorIterator const &other) const 
			{
				return (this->p < other.p);
			}

			bool operator<=(VectorIterator const &other) const 
			{
				return (this->p <= other.p);
			}

			bool operator>(VectorIterator const &other) const
			{
				return (this->p > other.p);
			}
			
			bool operator>=(VectorIterator const &other) const 
			{
				return (this->p >= other.p);
			}
    };
}

#endif