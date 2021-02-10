#ifndef FT_CONTAINERS_REVERSELISTITERATOR_HPP
#define FT_CONTAINERS_REVERSELISTITERATOR_HPP

#include "../Helpers/Node.hpp"

namespace ft {
	template <typename T>
	class ReverseListIterator {
	private:
		s_node<T> *ptr_;
	public:
		ReverseListIterator() {};
		ReverseListIterator(const ReverseListIterator &c) {
			*this = c;
		}
		ReverseListIterator (s_node<T> *p) : ptr_(p) {}
		virtual ~ReverseListIterator() {}
		T &operator* () {
			return (ptr_->data);
		}
		T *operator->() {
			return (ptr_->data);
		}
		ReverseListIterator &operator++ () {
			ptr_ = ptr_->prev;
			return *this;
		}
		ReverseListIterator operator++ (int) {
			ReverseListIterator tmp = *this;
			ptr_ = ptr_->prev;
			return tmp;
		}
		ReverseListIterator &operator-- () {
			ptr_ = ptr_->next;
			return *this;
		}
		ReverseListIterator operator-- (int) {
			ReverseListIterator tmp = *this;
			ptr_ = ptr_->next;
			return tmp;
		}
		ReverseListIterator &operator= (const ReverseListIterator &other){
			ptr_ = other.ptr_;
			return (*this);
		}
		bool operator== (const ReverseListIterator& other) const {
			return ptr_ == other.ptr_;
		}
		bool operator!= (const ReverseListIterator& other) const {
			return ptr_ != other.ptr_;
		}
		s_node<T>	 *get_element() const{
			return (ptr_);
		}
	};
}

#endif //FT_CONTAINERS_REVERSELISTITERATOR_HPP
