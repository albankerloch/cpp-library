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
			typedef T						value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, value_type>::iterator_category	iterator_category;
			typedef const value_type&		reference;
			typedef const value_type*		pointer;
			typedef RandomAccessIterator<value_type>		super;


		public:
			ConstVectorIterator(value_type *src) : RandomAccessIterator<value_type>(src) {};
			ConstVectorIterator(void) : RandomAccessIterator<value_type>() {};
			ConstVectorIterator(const RandomAccessIterator<value_type> &src) : RandomAccessIterator<value_type>(src) {};
			
			reference			operator*(void) const;
			pointer				operator->(void) const;
			ConstVectorIterator			&operator+=(difference_type n);
			ConstVectorIterator			&operator-=(difference_type n);
			reference			operator[](difference_type n) const;

			difference_type		operator-(const RandomAccessIterator<value_type> &n) const { return super::operator-(n); };
			ConstVectorIterator			operator-(difference_type n) const { return super::operator-(n); };
			ConstVectorIterator			operator+(difference_type n) const { return super::operator+(n); };
			friend ConstVectorIterator		operator+(difference_type n, const ConstVectorIterator &rhs) { return rhs.operator+(n); };

			ConstVectorIterator			&operator++(void) { super::operator++(); return *this; };
			ConstVectorIterator			operator++(int) { return super::operator++(0); };
			ConstVectorIterator			&operator--(void) { super::operator--(); return *this; };
			ConstVectorIterator			operator--(int) { return super::operator--(0); };

	};

	template <typename T>
	typename ConstVectorIterator<T>::reference ConstVectorIterator<T>::operator*(void) const {
		return (*this->_value);
	}

	template <typename T>
	typename ConstVectorIterator<T>::pointer ConstVectorIterator<T>::operator->(void) const {
		return (this->_value);
	}

	template <typename T>
	ConstVectorIterator<T> & ConstVectorIterator<T>::operator+=(difference_type n) 
	{
		this->_value += n; return *this;
	}

	template <typename T>
	ConstVectorIterator<T> & ConstVectorIterator<T>::operator-=(difference_type n) {
		this->_value -= n; return *this;
	}

	template <typename T>
	typename ConstVectorIterator<T>::reference ConstVectorIterator<T>::operator[](difference_type n) const {
		return (this->_value[n]);
	}
}

#endif
