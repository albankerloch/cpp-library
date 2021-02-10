#ifndef FT_CONTAINERS_CONSTREVERSELISTITERATOR_HPP
#define FT_CONTAINERS_CONSTREVERSELISTITERATOR_HPP

#include "../Helpers/Node.hpp"

namespace ft {
	template <typename T>
	class ConstReverseListIterator {
	private:
		s_node<T> *ptr_;
	public:
		ConstReverseListIterator() {};
		ConstReverseListIterator(const ConstReverseListIterator &c) {
			*this = c;
		}
		ConstReverseListIterator (s_node<T> *p) : ptr_(p) {}
		virtual ~ConstReverseListIterator() {}
		const T &operator* () {
			return (ptr_->data);
		}
		const T *operator->() {
			return (ptr_->data);
		}
		ConstReverseListIterator &operator++ () {
			ptr_ = ptr_->prev;
			return *this;
		}
		ConstReverseListIterator operator++ (int) {
			ConstReverseListIterator tmp = *this;
			ptr_ = ptr_->prev;
			return tmp;
		}
		ConstReverseListIterator &operator-- () {
			ptr_ = ptr_->next;
			return *this;
		}
		ConstReverseListIterator operator-- (int) {
			ConstReverseListIterator tmp = *this;
			ptr_ = ptr_->next;
			return tmp;
		}
		ConstReverseListIterator &operator=(const ConstReverseListIterator &other){
			ptr_ = other.ptr_;
			return (*this);
		}
		bool operator== (const ConstReverseListIterator& other) const {
			return ptr_ == other.ptr_;
		}
		bool operator!= (const ConstReverseListIterator& other) const {
			return ptr_ != other.ptr_;
		}
		const s_node<T>	 *get_element() const{
			return (ptr_);
		}
	};
}

#endif //FT_CONTAINERS_REVERSELISTITERATOR_HPP
