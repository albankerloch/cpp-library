#ifndef DEF_RANDOM_ACCESS_ITERATOR_HPP
# define DEF_RANDOM_ACCESS_ITERATOR_HPP

# include "Utils.hpp"

namespace ft {

	template <typename T>
	class RandomAccessIterator : ft::iterator<ft::random_access_iterator_tag, T>
	{
		protected:

			T	*m_value;

		public:

			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type 					value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, value_type>::iterator_category	iterator_category;


			RandomAccessIterator(void): m_value(NULL) 
			{
			};

			RandomAccessIterator(T *src) : m_value(src)
			{
			};

			RandomAccessIterator(const RandomAccessIterator &src)
			{
				*this = src;
			};

			virtual ~RandomAccessIterator(void)
			{
			};

			RandomAccessIterator	&operator=(RandomAccessIterator const &rhs)
			{
				if (this == &rhs)
					return (*this);
				this->m_value = rhs.m_value;
				return (*this);
			};

			bool	operator==(const RandomAccessIterator &rhs) const
			{
				return (this->m_value == rhs.m_value);
			};

			bool	operator!=(const RandomAccessIterator &rhs) const
			{
				return (this->m_value != rhs.m_value);
			};

			bool	operator<(const RandomAccessIterator &rhs) const
			{
				return (this->m_value < rhs.m_value);
			};

			bool	operator<=(const RandomAccessIterator &rhs) const
			{
				return (this->m_value <= rhs.m_value);
			};

			bool	operator>(const RandomAccessIterator &rhs) const
			{
				return (this->m_value > rhs.m_value);
			};

			bool	operator>=(const RandomAccessIterator &rhs) const
			{
				return (this->m_value >= rhs.m_value);
			};

			RandomAccessIterator<T>	&operator++(void)
			{
				++this->m_value;
				return (*this);
			};

			RandomAccessIterator<T>	operator++(int)
			{
				RandomAccessIterator<T>	tmp(*this);
				++this->m_value;
				return (tmp);
			};

			RandomAccessIterator<T>	&operator--(void)
			{
				--this->m_value;
				return (*this);
			};

			RandomAccessIterator<T>	operator--(int)
			{
				RandomAccessIterator<T>	tmp(*this);
				--this->m_value;
				return (tmp);
			};

			difference_type				operator-(const RandomAccessIterator &rhs) const
			{
				return (this->m_value - rhs.m_value);
			};

			RandomAccessIterator<T>			operator+(difference_type n) const
			{
				return (RandomAccessIterator(this->m_value + n));
			};

			RandomAccessIterator<T>			operator-(difference_type n) const
			{
				return (RandomAccessIterator(this->m_value - n));
			};

	};

}

#endif
