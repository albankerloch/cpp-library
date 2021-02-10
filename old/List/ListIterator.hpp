#ifndef FT_CONTAINERS_LISTITERATOR_HPP
#define FT_CONTAINERS_LISTITERATOR_HPP

#include "../Helpers/Node.hpp"

namespace ft {
	template <typename T>
	class ListIterator {
	private:
		s_node<T> *ptr_;
	public:
		ListIterator() {};
		ListIterator(const ListIterator &c) {
			*this = c;
		}
		ListIterator (s_node<T> *p) : ptr_(p) {}
		virtual ~ListIterator() {}
		T &operator* () {
			return (ptr_->data);
		}
		T *operator->() {
			return (ptr_->data);
		}
		ListIterator &operator++ () {
			ptr_ = ptr_->next;
			return *this;
		}
		ListIterator operator++ (int) {
			ListIterator tmp = *this;
			ptr_ = ptr_->next;
			return tmp;
		}
		ListIterator &operator-- () {
			ptr_ = ptr_->prev;
			return *this;
		}
		ListIterator operator-- (int) {
			ListIterator tmp = *this;
			ptr_ = ptr_->prev;
			return tmp;
		}
		ListIterator &operator= (const ListIterator &other){
			ptr_ = other.ptr_;
			return (*this);
		}
		bool operator== (const ListIterator& other) const {
			return ptr_ == other.ptr_;
		}
		bool operator!= (const ListIterator& other) const {
			return ptr_ != other.ptr_;
		}
		s_node<T>	 *get_element() const{
			return (ptr_);
		}
	};
}

#endif //FT_CONTAINERS_LISTITERATOR_HPP
