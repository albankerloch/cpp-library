#ifndef FT_CONTAINERS_MAPITERATOR_HPP
#define FT_CONTAINERS_MAPITERATOR_HPP

#include <utility>
#include <iostream>
#include "../Helpers/RBNode.hpp"

namespace ft {
	template<class Key, class T, class Compare>
	class MapIterator {
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
		MapIterator() {};
		MapIterator(const MapIterator &c) {
			*this = c;
		}
		MapIterator (node root, node p) : root_(root), ptr_(p) {
			if (root_->parent == 0)
				sentinel_ = root_;
			else
				sentinel_ = root_->parent;

		}
		virtual ~MapIterator() {}
		MapIterator &operator++ () {
			if (ptr_ != sentinel_)
				ptr_ = successor_(ptr_);
			return *this;
		}
		MapIterator operator++ (int) {
			MapIterator tmp = *this;
			if (ptr_ != sentinel_)
				ptr_ = successor_(ptr_);
			return tmp;
		}
		MapIterator &operator-- () {
			if (ptr_ == sentinel_)
				ptr_ = highest_(root_);
			else
				ptr_ = predecessor_(ptr_);
			return *this;
		}
		MapIterator operator-- (int) {
			MapIterator tmp = *this;
			if (ptr_ == 0)
				ptr_ = highest_(root_);
			else
				ptr_ = predecessor_(ptr_);
			return tmp;
		}

		std::pair<Key, T> &operator* () {
			return (ptr_->data);
		}
		std::pair<Key, T> *operator->() {
			return (&ptr_->data);
		}
		bool operator== (const MapIterator& other) const {
			return ptr_ == other.ptr_;
		}
		bool operator!= (const MapIterator& other) const {
			return ptr_ != other.ptr_;
		}
		node get_element() {
			return ptr_;
		}
	};
}

#endif //FT_CONTAINERS_MAPITERATOR_HPP
