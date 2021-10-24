#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "Utils.hpp"

namespace ft {

	template <typename T>
	class RandIte : ft::iterator<ft::random_access_iterator_tag, T>
	{
		protected:

		T									*_value;

		public:

		typedef T																						value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;


		RandIte(void): _value(NULL) 
		{
		};

		RandIte(T *src) : _value(src)
		{
		};

		RandIte(const RandIte &src)
		{
			*this = src;
		};

		virtual ~RandIte(void)
		{
		};

		RandIte	&operator=(RandIte const &rhs)
		{
			if (this == &rhs)
				return (*this);
			this->_value = rhs._value;
			return (*this);
		};

		bool	operator==(const RandIte &rhs) const
		{
			return (this->_value == rhs._value);
		};

		bool	operator!=(const RandIte &rhs) const
		{
			return (this->_value != rhs._value);
		};

		bool	operator<(const RandIte &rhs) const
		{
			return (this->_value < rhs._value);
		};

		bool	operator<=(const RandIte &rhs) const
		{
			return (this->_value <= rhs._value);
		};

		bool	operator>(const RandIte &rhs) const
		{
			return (this->_value > rhs._value);
		};

		bool	operator>=(const RandIte &rhs) const
		{
			return (this->_value >= rhs._value);
		};

		RandIte<T>	&operator++(void)
		{
			++this->_value;
			return (*this);
		};

		RandIte<T>	operator++(int)
		{
			RandIte<T>	tmp(*this);
			++this->_value;
			return (tmp);
		};

		RandIte<T>	&operator--(void)
		{
			--this->_value;
			return (*this);
		};

		RandIte<T>	operator--(int)
		{
			RandIte<T>	tmp(*this);
			--this->_value;
			return (tmp);
		};

		difference_type				operator-(const RandIte &rhs) const
		{
			return (this->_value - rhs._value);
		};

		RandIte<T>			operator+(difference_type n) const
		{
			return (RandIte(this->_value + n));
		};

		RandIte<T>			operator-(difference_type n) const
		{
			return (RandIte(this->_value - n));
		};

		friend RandIte<T>	operator+(difference_type n, const RandIte &rhs);

	};

}

#endif
