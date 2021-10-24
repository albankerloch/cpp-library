#ifndef CONST_VECTOR_ITERATOR_HPP
# define CONST_VECTOR_ITERATOR_HPP

# include "Utils.hpp"
# include "Random_Access_Iterator.hpp"

namespace ft 
{

	template <typename T>
	class ConstVectorIterator : public RandomAccessIterator<T> 
	{
		public:

			typedef T																						value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, value_type>::iterator_category	iterator_category;
			typedef const value_type&																				reference;
			typedef const value_type*																				pointer;
			typedef RandomAccessIterator<value_type> 														rai;


		public:

			ConstVectorIterator(void) : RandomAccessIterator<value_type>() 
			{
			};

			ConstVectorIterator(const ConstVectorIterator &src) : RandomAccessIterator<value_type>(src)
			{
			};
			
			ConstVectorIterator(value_type *src) : RandomAccessIterator<value_type>(src)
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

			ConstVectorIterator &operator+=(difference_type n)
			{
				this->_value += n; return *this;
			};

			ConstVectorIterator &operator-=(difference_type n)
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

			ConstVectorIterator operator-(difference_type n) const 
			{
				return rai::operator-(n);
			};

			ConstVectorIterator operator+(difference_type n) const 
			{
				return rai::operator+(n); 
			};

			ConstVectorIterator &operator++(void) 
			{
				rai::operator++(); return *this;
			};
			ConstVectorIterator operator++(int)
			{ 
				return rai::operator++(0); 
			};

			ConstVectorIterator &operator--(void)
			{
				rai::operator--(); return *this; 
			};

			ConstVectorIterator operator--(int) 
			{ 
				return rai::operator--(0); 
			};
	};

	template<typename T>
    ft::ConstVectorIterator<T> operator+(typename ft::ConstVectorIterator<T>::difference_type n, typename ft::ConstVectorIterator<T>& rhs)
	{
		return (rhs.operator+(n));
	}	
}

#endif
