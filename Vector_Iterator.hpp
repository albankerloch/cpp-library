#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include "Utils.hpp"
# include "Random_Access_Iterator.hpp"

namespace ft 
{

	template <typename T>
	class VectorIterator : public RandomAccessIterator<T> 
	{
		public:

			typedef T																						value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, value_type>::iterator_category	iterator_category;
			typedef value_type&																				reference;
			typedef value_type*																				pointer;
			typedef RandomAccessIterator<value_type> 														rai;

		private:

			VectorIterator(const RandomAccessIterator<value_type> &src) : RandomAccessIterator<value_type>(src)
			{
			};

		public:

			VectorIterator(void) : RandomAccessIterator<value_type>() 
			{
			};

			VectorIterator(const VectorIterator &src) : RandomAccessIterator<value_type>(src)
			{
			};
			
			VectorIterator(value_type *src) : RandomAccessIterator<value_type>(src)
			{
			};
			
			reference operator*(void) const
			{
				return (*this->_value);
			};
 
			pointer operator->(void) const
			{
				return (this->_value);
			};

			VectorIterator &operator+=(difference_type n)
			{
				this->_value += n; return *this;
			};

			VectorIterator &operator-=(difference_type n)
			{
				this->_value -= n; return *this;
			};

			reference operator[](difference_type n) const
			{
				return (this->_value[n]);
			};

			difference_type operator-(const RandomAccessIterator<value_type> &n) const 
			{
				return rai::operator-(n);
			};

			VectorIterator operator-(difference_type n) const 
			{
				return rai::operator-(n);
			};

			VectorIterator operator+(difference_type n) const 
			{
				return rai::operator+(n); 
			};

			VectorIterator &operator++(void) 
			{
				rai::operator++(); return *this;
			};
			VectorIterator operator++(int)
			{ 
				return rai::operator++(0); 
			};

			VectorIterator &operator--(void)
			{
				rai::operator--(); return *this; 
			};

			VectorIterator operator--(int) 
			{ 
				return rai::operator--(0); 
			};
/*
			friend VectorIterator operator+(difference_type n, const VectorIterator &rhs) 
			{
				return rhs.operator+(n);
			};*/

	};

	template<typename T>
    ft::VectorIterator<T> operator+(
        typename ft::VectorIterator<T>::difference_type n,
        typename ft::VectorIterator<T>& rai)
        {
            return (&(*rai) + n);
        }


	
}

#endif
