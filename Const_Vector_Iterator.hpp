#ifndef DEF_CONST_VECTOR_ITERATOR_CLASS_HPP
# define DEF_CONST_VECTOR_ITERATOR_CLASS_HPP

# include "Utils.hpp"
# include "Random_Access_Iterator.hpp"

namespace ft 
{

	template <typename T>
	class ConstVectorIterator : public RandomAccessIterator<T> 
	{
		public:

			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type					value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, value_type>::iterator_category	iterator_category;
			typedef const value_type&																		reference;
			typedef const value_type*																		pointer;


		public:

			ConstVectorIterator(value_type *src) : RandomAccessIterator<value_type>(src)
			{
			};

			ConstVectorIterator(void) : RandomAccessIterator<value_type>()
			{
			};
			
			ConstVectorIterator(const RandomAccessIterator<value_type> &src) : RandomAccessIterator<value_type>(src)
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

			ConstVectorIterator &operator+=(difference_type n)
			{
				this->m_value += n; return *this;
			};

			ConstVectorIterator &operator-=(difference_type n)
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

			ConstVectorIterator operator-(difference_type n) const 
			{ 
				return RandomAccessIterator<value_type>::operator-(n); 
			};

			ConstVectorIterator operator+(difference_type n) const 
			{ 
				return RandomAccessIterator<value_type>::operator+(n); 
			};

			ConstVectorIterator &operator++(void) 
			{ 
				RandomAccessIterator<value_type>::operator++(); return *this; 
			};

			ConstVectorIterator operator++(int) 
			{ 
				return RandomAccessIterator<value_type>::operator++(0); 
			};

			ConstVectorIterator &operator--(void) 
			{ 
				RandomAccessIterator<value_type>::operator--(); return *this; 
			};

			ConstVectorIterator operator--(int) 
			{ 
				return RandomAccessIterator<value_type>::operator--(0); 
			};

	};

	template<typename T>
    ft::ConstVectorIterator<T> operator+(typename ft::ConstVectorIterator<T>::difference_type n, typename ft::ConstVectorIterator<T>& rhs)
	{
		return (rhs.operator+(n));
	}	
}

#endif
