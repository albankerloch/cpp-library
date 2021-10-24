#ifndef CONST_VECTOR_ITE_CLASS_HPP
# define CONST_VECTOR_ITE_CLASS_HPP

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
			typedef const value_type&																		reference;
			typedef const value_type*																		pointer;
			typedef RandomAccessIterator<value_type>														rai;


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

			friend ConstVectorIterator operator+(difference_type n, const ConstVectorIterator &rhs) 
			{ 
				return rhs.operator+(n); 
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
}

#endif
