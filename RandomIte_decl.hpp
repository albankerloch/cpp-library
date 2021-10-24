#ifndef RANDOMITE_DECL_CLASS_HPP
# define RANDOMITE_DECL_CLASS_HPP

# include "Utils.hpp"

namespace ft {

	template <typename Spe>
	class RandIte : ft::iterator<ft::random_access_iterator_tag, Spe>
	{
		protected:
		Spe									*_value;

		public:
		typedef Spe						value_type;
		typedef ptrdiff_t				difference_type;

		RandIte(void): _value(NULL) 
		{
		};

		RandIte(Spe *src) : _value(src)
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

		bool	operator==(const RandIte &rhs) const;
		bool	operator!=(const RandIte &rhs) const;
		bool	operator<(const RandIte &rhs) const;
		bool	operator<=(const RandIte &rhs) const;
		bool	operator>(const RandIte &rhs) const;
		bool	operator>=(const RandIte &rhs) const;

		RandIte<Spe>	&operator++(void);
		RandIte<Spe>	operator++(int);
		RandIte<Spe>	&operator--(void);
		RandIte<Spe>	operator--(int);

		difference_type				operator-(const RandIte &rhs) const;
		RandIte<Spe>			operator+(difference_type n) const;
		RandIte<Spe>			operator-(difference_type n) const;
		friend RandIte<Spe>	operator+(difference_type n, const RandIte &rhs)
			{ return rhs.operator+(n); };
	};

}

#endif
