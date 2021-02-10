#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP
#include <memory>
#include <limits>
#include <iostream>
#include "VectorIterator.hpp"
#include "ConstVectorIterator.hpp"
#include "ReverseVectorIterator.hpp"
#include "ConstReverseVectorIterator.hpp"
#include "../Helpers/Helpers.hpp"

namespace ft {
	template <typename T, typename Allocator_ = std::allocator<T> >
	class Vector {
	public:
		typedef T										value_type;
		typedef Allocator_								allocator_type;
		typedef T										&reference;
		typedef const T 								&const_reference;
		typedef T 										*pointer;
		typedef const T									*const_pointer;
		typedef VectorIterator<value_type>				iterator;
		typedef ConstVectorIterator<value_type>			const_iterator;
		typedef ReverseVectorIterator<value_type>		reverse_iterator;
		typedef ConstReverseVectorIterator<value_type>	const_reverse_iterator;
		typedef std::ptrdiff_t							difference_type;
		typedef size_t 									size_type;
	private:
		allocator_type	allocator_;
		pointer 		vec_;
		size_type		capacity_;
		size_type		size_;
		size_type 		new_capacity_(size_type n) {
			size_type cap(capacity_);
			if (cap == 0)
				cap++;
			while (cap < size_ + n + 1)
				cap *= 2;
			return cap;
		}
		void 			extend_(size_type n) {
			reserve(new_capacity_(n));
		}
		void move_down_(iterator position) {
			iterator current = end();
			while (current != position) {
				*current = *(current - 1);
				current--;
			}
		}
		void move_up_(iterator position) {
			while (position + 1 != end()){
				*position = *(position + 1);
				position++;
			}
			*end() = 0;
		}
	public:
		explicit Vector (const allocator_type& alloc = allocator_type()): allocator_(alloc), capacity_(0), size_(0){
			vec_ = new value_type [0];
		};
		explicit Vector (size_type n, const value_type& val = value_type(),
		const allocator_type& alloc = allocator_type()): allocator_(alloc), capacity_(0), size_(0){
			vec_ = new value_type [0];
			assign(n, val);
		}
		template <class InputIterator>
		Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()): allocator_(alloc), capacity_(0), size_(0) {
			vec_ = new value_type [0];
			assign(first, last);
		}

		Vector (const Vector& x): allocator_(x.allocator_), capacity_(x.capacity_), size_(0) {
			vec_ = new value_type [0];
			assign(x.begin(), x.end());
		}

		~Vector() {
			delete [] vec_;
		}

		Vector &operator=(const Vector &x){
			delete [] vec_;
			vec_ = new value_type [0];
			size_ = 0;
			capacity_ = 0;
			assign(x.begin(), x.end());
			return (*this);
		}

		iterator begin() {
			return (iterator(vec_));
		}

		const_iterator begin() const {
			return (const_iterator(vec_));
		}

		iterator end() {
			return (iterator(vec_ + size_));
		}

		const_iterator end() const {
			return (const_iterator(vec_ + size_));
		}

		reverse_iterator rbegin() {
			return (reverse_iterator(vec_ + size_ - 1));
		}

		const_reverse_iterator rbegin() const {
			return (const_reverse_iterator(vec_ + size_ - 1));
		}

		reverse_iterator rend() {
			return (reverse_iterator(vec_ - 1));
		}

		const_reverse_iterator rend() const {
			return (const_reverse_iterator(vec_ - 1));
		}

		size_type size() const {
			return (size_);
		}

		size_type max_size() const {
			return (ft::min(static_cast<size_type>(std::numeric_limits<difference_type>::max()),
				   std::numeric_limits<size_type>::max() / sizeof(T)));
		}

		void resize (size_type n, value_type val = value_type()) {
			while (size_ > n)
				--size_;
			while (size_ < n)
				push_back(val);
		}

		size_type capacity() const {
			return (capacity_);
		}

		bool empty() const {
			return (capacity_ == 0);
		}

		void reserve (size_type n) {
			if (capacity_ > n)
				return ;
			pointer tmp = new value_type [n];
			capacity_ = n;
			for (size_type i = 0; i < size_; i++)
				tmp[i] = vec_[i];
			delete [] vec_;
			vec_ = tmp;

		}

		reference operator[] (size_type n) {
			return vec_[n];
		}

		const_reference operator[] (size_type n) const {
			return vec_[n];
		}

		reference at (size_type n) {
			if (n >= size_)
				throw std::out_of_range("out-of-range");
			return (vec_[n]);
		}

		const_reference at (size_type n) const {
			if (n >= size_)
				throw std::out_of_range("out-of-range");
			return (vec_[n]);
		}

		reference front() {
			return (vec_[0]);
		}

		const_reference front() const {
			return (vec_[0]);
		}

		reference back() {
			if (size_ > 0)
				return (vec_[size_ - 1]);
			else
				return (vec_[0]);
		}

		const_reference back() const {
			if (size_ > 0)
				return (vec_[size_ - 1]);
			else
				return (vec_[0]);
		}

		template <class InputIterator>
		void assign (InputIterator first, InputIterator last) {
			clear();
			InputIterator 	current = first;
			size_type 		i = 0;

			while (current++ != last)
				i++;
			extend_(i);
			while (first != last){
				push_back(*first);
				++first;
			}
		}

		void assign (size_type n, const value_type& val) {
			clear();
			extend_(n);
			for (size_type i = 0; i < n; i++ )
				vec_[size_++] = val;
		}

		void push_back (const value_type& val) {
			extend_(1);
			vec_[size_++] = val;
		}

		void pop_back() {
			if (size_ > 0)
				--size_;
		}

		iterator insert (iterator position, const value_type& val) {
			iterator  pos;
			if (size_ + 1 >= capacity_){
				capacity_ = new_capacity_(1);
				pointer tmp = new value_type [capacity_];
				iterator it = begin();
				iterator e = end();
				ft::swap_element(tmp, vec_);
				size_ = 0;
				while (it != position)
					push_back(*it++);
				size_type i = size_;
				push_back(val);
				while (it != e)
					push_back(*it++);
				delete [] tmp;
				return (iterator(&vec_[i]));
			} else {
				move_down_(position);
				*position = val;
				size_++;
				return (position);
			}
		}

		void insert (iterator position, size_type n, const value_type& val) {
			while(n-- > 0){
				position = insert(position, val);
			}
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last) {
			while (first != last){
				position = insert(position, *first);
				position++;
				first++;
			}
		}

		iterator erase (iterator position) {
			if (position == end() - 1) {
				pop_back();
				return (end());
			}
			move_up_(position);
			--size_;
			return (position);
		}

		iterator erase (iterator first, iterator last) {
			while (last != first)
				last = erase(--last);
			return (iterator(first));
		}

		void swap (Vector& x) {
			ft::swap_element(this->vec_, x.vec_);
			ft::swap_element(this->size_, x.size_);
			ft::swap_element(this->capacity_, x.capacity_);
		}

		void clear() {
			while(size_ > 0)
				--size_;
		}
	};

	template <class T, class Alloc>
	bool operator== (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		for (typename Vector<T>::size_type i = 0; i < lhs.size(); i++){
			if (lhs[i] != rhs[i])
				return false;
		}
		return true;
	}

	template <class T, class Alloc>
	bool operator!= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
		if (&lhs == &rhs)
			return false;
		return true;
	}

	template <class T, class Alloc>
	bool operator<  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
		if (lhs.size() < rhs.size())
			return true;
		for (typename Vector<T>::size_type i = 0; i < lhs.size(); i++){
			if (lhs[i] >= rhs[i])
				return false;
		}
		return true;
	}

	template <class T, class Alloc>
	bool operator<= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
		return (rhs <= lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	void swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y) {
		x.swap(y);
	}
}

#endif //FT_CONTAINERS_VECTOR_HPP
