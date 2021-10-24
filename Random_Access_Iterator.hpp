#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "Utils.hpp"

namespace ft {

	template <typename T>
	class RandomAccessIterator : ft::iterator<ft::random_access_iterator_tag, T>
	{
		protected:

		T									*_value;

		public:

		typedef T																						value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, value_type>::difference_type		difference_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, value_type>::iterator_category	iterator_category;


		RandomAccessIterator(void): _value(NULL) 
		{
		};

		RandomAccessIterator(T *src) : _value(src)
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
			this->_value = rhs._value;
			return (*this);
		};

		bool	operator==(const RandomAccessIterator &rhs) const
		{
			return (this->_value == rhs._value);
		};

		bool	operator!=(const RandomAccessIterator &rhs) const
		{
			return (this->_value != rhs._value);
		};

		bool	operator<(const RandomAccessIterator &rhs) const
		{
			std::cout << "---> test" << std::endl;
			return (this->_value < rhs._value);
		};

		bool	operator<=(const RandomAccessIterator &rhs) const
		{
			return (this->_value <= rhs._value);
		};

		bool	operator>(const RandomAccessIterator &rhs) const
		{
			return (this->_value > rhs._value);
		};

		bool	operator>=(const RandomAccessIterator &rhs) const
		{
			return (this->_value >= rhs._value);
		};

		RandomAccessIterator<T>	&operator++(void)
		{
			++this->_value;
			return (*this);
		};

		RandomAccessIterator<T>	operator++(int)
		{
			RandomAccessIterator<T>	tmp(*this);
			++this->_value;
			return (tmp);
		};

		RandomAccessIterator<T>	&operator--(void)
		{
			--this->_value;
			return (*this);
		};

		RandomAccessIterator<T>	operator--(int)
		{
			RandomAccessIterator<T>	tmp(*this);
			--this->_value;
			return (tmp);
		};

		difference_type				operator-(const RandomAccessIterator &rhs) const
		{
			return (this->_value - rhs._value);
		};

		RandomAccessIterator<T>			operator+(difference_type n) const
		{
			return (RandomAccessIterator(this->_value + n));
		};

		RandomAccessIterator<T>			operator-(difference_type n) const
		{
			return (RandomAccessIterator(this->_value - n));
		};

		friend RandomAccessIterator<T>	operator+(difference_type n, const RandomAccessIterator &rhs);

	};

}

#endif
