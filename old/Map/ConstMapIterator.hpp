#ifndef FT_CONTAINERS_CONSTMAPITERATOR_HPP
#define FT_CONTAINERS_CONSTMAPITERATOR_HPP

#include <utility>
#include <iostream>
#include "../Helpers/RBNode.hpp"

namespace ft {
	template<class Key, class T, class Compare>
	class ConstMapIterator {
	private:
		typedef s_br_node<Key, T> 					*node;
		node 										root_;
		node 										sentinel_;
		node 										ptr_;

		node highest_(node current) {
			while (current->right != sentinel_)
				current = current->right;
			return current;
		}

		node successor_(node x) {
			if (x->right != sentinel_){
				x = x->right;
				while (x->left != sentinel_)
					x = x->left;
			}else{
				node y = x->parent;
				if (y == sentinel_){
					return sentinel_;
				}
				while (x == y->right){
					x = y;
					y = y->parent;
				}
				if (x->right != y)
					x = y;
			}
			return x;
		}

		node predecessor_(node x) {
			if (x->left != sentinel_){
				x = x->left;
				while (x->right != sentinel_)
					x = x->right;
			}else{
				node y = x->parent;
				if (y == sentinel_){
					return sentinel_;
				}
				while (x == y->left){
					x = y;
					y = y->parent;
				}
				if (x->left != y)
					x = y;
			}
			return x;
		}

	public:
		ConstMapIterator() {};
		ConstMapIterator(const ConstMapIterator &c) {
			*this = c;
		}
		ConstMapIterator (node root, node p) : root_(root), ptr_(p) {
			if (root_->parent == 0)
				sentinel_ = root_;
			else
				sentinel_ = root_->parent;

		}
		virtual ~ConstMapIterator() {}
		ConstMapIterator &operator++ () {
			if (ptr_ != sentinel_)
				ptr_ = successor_(ptr_);
			return *this;
		}
		ConstMapIterator operator++ (int) {
			ConstMapIterator tmp = *this;
			if (ptr_ != sentinel_)
				ptr_ = successor_(ptr_);
			return tmp;
		}
		ConstMapIterator &operator-- () {
			if (ptr_ == sentinel_)
				ptr_ = highest_(root_);
			else
				ptr_ = predecessor_(ptr_);
			return *this;
		}
		ConstMapIterator operator-- (int) {
			ConstMapIterator tmp = *this;
			if (ptr_ == 0)
				ptr_ = highest_(root_);
			else
				ptr_ = predecessor_(ptr_);
			return tmp;
		}

		const std::pair<Key, T> &operator* () {
			return (ptr_->data);
		}
		const std::pair<Key, T> *operator->() {
			return (&ptr_->data);
		}
		bool operator== (const ConstMapIterator& other) const {
			return ptr_ == other.ptr_;
		}
		bool operator!= (const ConstMapIterator& other) const {
			return ptr_ != other.ptr_;
		}
		const node get_element() {
			return ptr_;
		}
	};
}

#endif //FT_CONTAINERS_MAPITERATOR_HPP
