#ifndef FT_CONTAINERS_REVERSEMAPITERATOR_HPP
#define FT_CONTAINERS_REVERSEMAPITERATOR_HPP

#include <utility>
#include "../Helpers/RBNode.hpp"

namespace ft {
	template<class Key, class T, class Compare>
	class ReverseMapIterator {
	private:
		typedef Compare 							key_compare;
		typedef s_br_node<Key, T> 					*node;
		node 										root_;
		node 										ptr_;
		node 										sentinel_;
		node lowest_(node current) {
			while (current->left != sentinel_)
				current = current->left;
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
		ReverseMapIterator() {};
		ReverseMapIterator(const ReverseMapIterator &c) {
			*this = c;
		}
		ReverseMapIterator (node root, node p) : root_(root), ptr_(p) {
			if (root_->parent == 0)
				sentinel_ = root_;
			else
				sentinel_ = root_->parent;
		}
		virtual ~ReverseMapIterator() {}
		ReverseMapIterator &operator-- () {
			if (ptr_ == sentinel_)
				ptr_ = lowest_(root_);
			else
				ptr_ = successor_(ptr_);
			return *this;
		}
		ReverseMapIterator operator-- (int) {
			ReverseMapIterator tmp = *this;
			if (ptr_ == sentinel_)
				ptr_ = lowest_(root_);
			else
				ptr_ = successor_(ptr_);
			return tmp;
		}
		ReverseMapIterator &operator++ () {
			if (ptr_ != sentinel_)
				ptr_ = predecessor_(ptr_);
			return *this;
		}
		ReverseMapIterator operator++ (int) {
			ReverseMapIterator tmp = *this;
			if (ptr_ != sentinel_)
				ptr_ = predecessor_(ptr_);
			return tmp;
		}

		std::pair<Key, T> &operator* () {
			return (ptr_->data);
		}
		std::pair<Key, T> *operator->() {
			return (&ptr_->data);
		}
		bool operator== (const ReverseMapIterator& other) const {
			return ptr_ == other.ptr_;
		}
		bool operator!= (const ReverseMapIterator& other) const {
			return ptr_ != other.ptr_;
		}
		node get_element() {
			return ptr_;
		}
	};
}

#endif //FT_CONTAINERS_MAPITERATOR_HPP
