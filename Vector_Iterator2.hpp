#ifndef DEF_VECTOR_VectorIterator2_HPP
# define DEF_VECTOR_VectorIterator2_HPP

# include <iostream>
# include "Algo.hpp"
# include "RandomIte.hpp"
# include "ReverseIte.hpp"

namespace ft 
{
	template<typename T>
	class VectorIterator : public RandIte<T> {
		public:
		typedef T value_type;
		typedef ptrdiff_t difference_type;

		protected:
		typedef RandIte<value_type> super;

		private:
		VectorIterator(const RandIte<value_type> &src) : RandIte<value_type>(src) {};

		public:
		VectorIterator(value_type *src) : RandIte<value_type>(src) {};
		VectorIterator(void) : RandIte<value_type>() {};
		VectorIterator(const VectorIterator &src) : RandIte<value_type>(src) {};

		typedef value_type&			reference;
		typedef value_type*			pointer;

		reference			operator*(void) const;
		pointer				operator->(void) const;
		VectorIterator			&operator+=(difference_type n);
		VectorIterator			&operator-=(difference_type n);
		reference			operator[](difference_type n) const;

		difference_type		operator-(const RandIte<value_type> &n) const { return super::operator-(n); };
		VectorIterator			operator-(difference_type n) const { return super::operator-(n); };
		VectorIterator			operator+(difference_type n) const { return super::operator+(n); };
		friend VectorIterator		operator+(difference_type n, const VectorIterator &rhs) { return rhs.operator+(n); };

		VectorIterator			&operator++(void) { super::operator++(); return *this; };
		VectorIterator			operator++(int) { return super::operator++(0); };
		VectorIterator			&operator--(void) { super::operator--(); return *this; };
		VectorIterator			operator--(int) { return super::operator--(0); };

	};

	template<typename T>
	class VectorConstIterator : public RandIte<T> {
		public:
		typedef T value_type;
		typedef ptrdiff_t difference_type;

		protected:
		typedef RandIte<value_type> super;

		public:
		VectorConstIterator(value_type *src) : RandIte<value_type>(src) {};
		VectorConstIterator(void) : RandIte<value_type>() {};
		VectorConstIterator(const RandIte<value_type> &src) : RandIte<value_type>(src) {};

		typedef const value_type&		reference;
		typedef const value_type*		pointer;

		reference			operator*(void) const;
		pointer				operator->(void) const;
		VectorConstIterator		&operator+=(difference_type n);
		VectorConstIterator		&operator-=(difference_type n);
		reference			operator[](difference_type n) const;

		difference_type		operator-(const RandIte<value_type> &n) const { return super::operator-(n); };
		VectorConstIterator		operator-(difference_type n) const { return super::operator-(n); };
		VectorConstIterator		operator+(difference_type n) const { return super::operator+(n); };
		friend VectorConstIterator	operator+(difference_type n, const VectorConstIterator &rhs) { return rhs.operator+(n); };

		VectorConstIterator		&operator++(void) { super::operator++(); return *this; };
		VectorConstIterator		operator++(int) { return super::operator++(0); };
		VectorConstIterator		&operator--(void) { super::operator--(); return *this; };
		VectorConstIterator		operator--(int) { return super::operator--(0); };

	};
}

#endif