#ifndef FT_CONTAINERS_CONSTLISTITERATOR_HPP
#define FT_CONTAINERS_CONSTLISTITERATOR_HPP

#include "../Helpers/Node.hpp"

namespace ft {
	template <typename T>
	class ConstListIterator {
	private:
		typedef const s_node<T> &const_node;
		s_node<T> *ptr_;
	public:
		ConstListIterator() {};
		ConstListIterator(const ConstListIterator &c) {
			*this = c;
		}
		ConstListIterator (s_node<T> *p) : ptr_(p) {}
		virtual ~ConstListIterator() {}
		const T &operator* (){
			return (ptr_->data);
		}
		const T *operator->() {
			return (ptr_->data);
		}
		ConstListIterator &operator++ () {
			ptr_ = ptr_->next;
			return *this;
		}
		ConstListIterator operator++ (int) {
			const ConstListIterator tmp = *this;
			ptr_ = ptr_->next;
			return tmp;
		}
		ConstListIterator &operator-- () {
			ptr_ = ptr_->prev;
			return *this;
		}
		ConstListIterator operator-- (int) {
			ConstListIterator tmp = *this;
			ptr_ = ptr_->prev;
			return tmp;
		}
		ConstListIterator &operator= (const ConstListIterator &other){
			ptr_ = other.ptr_;
			return (*this);
		}
		bool operator== (const ConstListIterator& other) const {
			return ptr_ == other.ptr_;
		}
		bool operator!= (const ConstListIterator& other) const {
			return ptr_ != other.ptr_;
		}
		const_node get_element() const{
			return (ptr_);
		}
	};
}

#endif //FT_CONTAINERS_CONSTLISTITERATOR_HPP
