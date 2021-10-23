#ifndef VECTOR_ITE_CLASS_HPP
# define VECTOR_ITE_CLASS_HPP

# include "Utils.hpp"
# include "RandomIte.hpp"

namespace ft 
{

	template <typename T>
	class VectorIterator : public RandIte<T> 
	{
		public:
			typedef T						value_type;
			typedef ptrdiff_t				difference_type;
			typedef value_type&				reference;
			typedef value_type*				pointer;
			typedef RandIte<value_type> 	super;

		private:

			VectorIterator(const RandIte<value_type> &src) : RandIte<value_type>(src) {};

		public:

			VectorIterator(void) : RandIte<value_type>() {};
			VectorIterator(const VectorIterator &src) : RandIte<value_type>(src) {};
			VectorIterator(value_type *src) : RandIte<value_type>(src) {};
			
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

	template <typename T>
	typename VectorIterator<T>::reference VectorIterator<T>::operator*(void) const {
		return (*this->_value);
	}

	template <typename T>
	typename VectorIterator<T>::pointer VectorIterator<T>::operator->(void) const {
		return (this->_value);
	}

	template <typename T>
	VectorIterator<T> & VectorIterator<T>::operator+=(difference_type n) 
	{
		this->_value += n; return *this;
	}

	template <typename T>
	VectorIterator<T> & VectorIterator<T>::operator-=(difference_type n) {
		this->_value -= n; return *this;
	}

	template <typename T>
	typename VectorIterator<T>::reference VectorIterator<T>::operator[](difference_type n) const {
		return (this->_value[n]);
	}
}

#endif
