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
			
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type 					value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, value_type>::iterator_category	iterator_category;
			typedef value_type&																				reference;
			typedef value_type*																				pointer;

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
				return (*this->m_value);
			};
 
			pointer operator->(void) const
			{
				return (this->m_value);
			};

			VectorIterator &operator+=(difference_type n)
			{
				this->m_value += n; return *this;
			};

			VectorIterator &operator-=(difference_type n)
			{
				this->m_value -= n; return *this;
			};

			reference operator[](difference_type n) const
			{
				return (this->m_value[n]);
			};

			difference_type operator-(const RandomAccessIterator<value_type> &n) const 
			{
				return RandomAccessIterator<value_type>::operator-(n);
			};

			VectorIterator operator-(difference_type n) const 
			{
				return RandomAccessIterator<value_type>::operator-(n);
			};

			VectorIterator operator+(difference_type n) const 
			{
				return RandomAccessIterator<value_type>::operator+(n); 
			};

			VectorIterator &operator++(void) 
			{
				RandomAccessIterator<value_type>::operator++(); return *this;
			};
			VectorIterator operator++(int)
			{ 
				return RandomAccessIterator<value_type>::operator++(0); 
			};

			VectorIterator &operator--(void)
			{
				RandomAccessIterator<value_type>::operator--(); return *this; 
			};

			VectorIterator operator--(int) 
			{ 
				return RandomAccessIterator<value_type>::operator--(0); 
			};

	};

	template<typename T>
    ft::VectorIterator<T> operator+(typename ft::VectorIterator<T>::difference_type n, typename ft::VectorIterator<T>& rhs)
	{
		return (rhs.operator+(n));
	}	
}

#endif
