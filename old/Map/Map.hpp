#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <memory>
#include <functional>
#include <utility>
#include <limits>
#include <stack>
#include "MapIterator.hpp"
#include "ConstMapIterator.hpp"
#include "ReverseMapIterator.hpp"
#include "ConstReverseMapIterator.hpp"
#include "../Helpers/Helpers.hpp"

namespace ft {
	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
	class Map {
	public:
		typedef Key			 							key_type;
		typedef T 										mapped_type;
		typedef std::pair<const key_type , mapped_type> value_type;
		typedef Compare 								key_compare;
		typedef Allocator								allocator_type;
		typedef T&										reference;
		typedef const T&								const_reference;
		typedef T*										pointer;
		typedef const T*								const_pointer;
		typedef ReverseMapIterator<key_type, mapped_type, key_compare>	reverse_iterator;
		typedef ConstReverseMapIterator<key_type, mapped_type, key_compare>	const_reverse_iterator;
		typedef MapIterator<key_type, mapped_type, key_compare>		iterator;
		typedef ConstMapIterator<key_type, mapped_type, key_compare>	const_iterator;
		typedef std::ptrdiff_t 							difference_type;
		typedef size_t 									size_type;
		class value_compare
		{
			friend class Map;
		protected:
			Compare comp;
			value_compare (Compare c) : comp(c) {}
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};
	private:
		value_compare				value_compare_;
		typedef s_br_node<key_type , mapped_type>		*node;
		key_compare					cmp_;
		Allocator					alloc_;
		node						root_;
		node						sentinel_;
		size_type 					size_;

		node						new_node(key_type key, mapped_type  val, node parent, e_br_color color) {
			node n;
			n = new s_br_node<key_type, mapped_type>();
			n->parent = parent;
			n->left = sentinel_;
			n->right = sentinel_;
			n->color = color;
			n->data.first = key;
			n->data.second = val;
			return (n);
		}

		std::pair<iterator,bool> insert_at_(node root, const value_type& val) {
			node y = sentinel_;
			node x = root;
			while (x != sentinel_) {
				y = x;
				if (val.first == x->data.first)
					return std::make_pair(iterator(root_, y), false);
				else if (cmp_(val.first, x->data.first))
					x = x->left;
				else
					x = x->right;
			}
			node n = new_node(val.first, val.second, y, RED);
			if (y == sentinel_)
				root_ = n;
			else if (cmp_(val.first, y->data.first))
				y->left = n;
			else
				y->right = n;
			++size_;
			rb_insert_fixup(n);
			return std::make_pair(iterator(root_, n), true);

		}

		void new_sentinel_() {
			sentinel_ = new s_br_node<key_type, mapped_type>();
			sentinel_->parent = 0;
			sentinel_->left = 0;
			sentinel_->right = 0;
			sentinel_->color = BLACK;
			root_ = sentinel_;
		}

		void rotate_left_(node x) {
			node y;
			y = x->right;
			x->right = y->left;
			if (y->left != sentinel_){
				y->left->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == sentinel_)
				root_ = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		void rotate_right_(node x) {
			node y;
			y = x->left;
			x->left = y->right;
			if (y->right != sentinel_) {
				y->right->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == sentinel_)
				root_ = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}

		void rb_insert_fixup(node z) {
			node y;
			while (z->parent->color == RED) {
				if (z->parent == z->parent->parent->left) {
					y = z->parent->parent->right;
					if (y->color == RED) {
						z->parent->color = BLACK;
						y->color = BLACK;
						z->parent->parent->color = RED;
						z = z->parent->parent;
					}else{
						if (z == z->parent->right) {
							z = z->parent;
							rotate_left_(z);
						}
						z->parent->color = BLACK;
						z->parent->parent->color = RED;
						rotate_right_(z->parent->parent);
					}
				}else{
					y = z->parent->parent->left;
					if (y->color == RED) {
						z->parent->color = BLACK;
						y->color = BLACK;
						z->parent->parent->color = RED;
						z = z->parent->parent;
					}else {
						if (z == z->parent->left) {
							z = z->parent;
							rotate_right_(z);
						}
						z->parent->color = BLACK;
						z->parent->parent->color = RED;
						rotate_left_(z->parent->parent);
					}
				}
			}
			root_->color = BLACK;
		}

		void rb_delete_fixup(node n){
			node x = n;
			node w;
			while (x != root_ && x->color == BLACK){
				if (x == x->parent->left) {
					w = x->parent->right;
					if (w->color == RED) {
						w->color = BLACK;
						x->parent->color = RED;
						rotate_left_(x->parent);
						w = x->parent->right;
					}
					if (w->left->color == BLACK && w->right->color == BLACK) {
						w->color = RED;
						x = x->parent;
					} else {
						if (w->right->color == BLACK) {
							w->left->color = BLACK;
							w->color = RED;
							rotate_right_(w);
							w = x->parent->right;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->right->color = BLACK;
						rotate_left_(x->parent);
						x = root_;
					}
				}else{
					w = x->parent->left;
					if (w->color == RED) {
						w->color = BLACK;
						x->parent->color = RED;
						rotate_right_(x->parent);
						w = x->parent->left;
					}
					if (w->right->color == BLACK && w->left->color == BLACK) {
						w->color = RED;
						x = x->parent;
					} else {
						if (w->left->color == BLACK) {
							w->right->color = BLACK;
							w->color = RED;
							rotate_left_(w);
							w = x->parent->left;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->left->color = BLACK;
						rotate_right_(x->parent);
						x = root_;
					}
				}
			}
			x->color = BLACK;
		}

		void transplant_(node gone, node substitute) {
			if (gone->parent == sentinel_)
				root_ = substitute;
			else if (gone == gone->parent->left)
				gone->parent->left = substitute;
			else
				gone->parent->right = substitute;
			substitute->parent = gone->parent;
		}

		void delete_tree_(node current) {
			if (current->left != sentinel_)
				delete_tree_(current->left);
			if (current->right != sentinel_)
				delete_tree_(current->right);
			delete current;
		}

		node lowest_(node root) const {
			while (root->left != sentinel_){
				root = root->left;
			}
			return root;
		}

		node highest_(node root) const {
			while (root->right != sentinel_)
				root = root->right;
			return root;
		}

		node successor_(node root, Key key, bool equal) {
			node succ = sentinel_;
			while (1) {
				if (cmp_(key,root->data.first)) {
					succ = root;
					root = root->left;
				} else if (cmp_(root->data.first, key))
					root = root->right;
				else {
					if (equal)
						return (root);
					if (root->right != sentinel_)
						succ = lowest_(root->right);
					break;
				}
				if (root == sentinel_){
					if (succ && cmp_(key, succ->data.first))
						return succ;
					return sentinel_;
				}
			}
			return succ;
		}
	public:
		explicit Map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
		value_compare_(comp),
		cmp_(comp),
		alloc_(alloc),
		size_(0) {
			new_sentinel_();
		}
		template <class InputIterator>
		Map (InputIterator first, InputIterator last,
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type()):
		value_compare_(comp),
		cmp_(comp),
		alloc_(alloc),
		size_(0){
			new_sentinel_();
			while (first != last){
				insert(*first);
				first++;
			}
		}

		Map (const Map& x):
		value_compare_(x.cmp_),
		cmp_(x.cmp_),
		alloc_(x.alloc_),
		size_(0){
			new_sentinel_();
			insert(x.begin(), x.end());
		}

		~Map() {
			if (size_ > 0)
				delete_tree_(root_);
			delete sentinel_;
		}

		Map& operator= (const Map& x) {
			clear();
			cmp_ = x.key_comp();
			value_compare_ = x.value_comp();
			size_ = 0;
			insert(x.begin(), x.end());
			return *this;
		}

		iterator begin() {
			if (root_ == sentinel_)
				return (iterator(root_, sentinel_));
			return (iterator(root_, lowest_(root_)));
		}

		const_iterator begin() const {
			if (root_ == sentinel_)
				return (const_iterator(root_, sentinel_));
			return (const_iterator(root_, lowest_(root_)));
		}
		iterator end() {
			return (iterator(root_, sentinel_));
		}
		const_iterator end() const {
			return (const_iterator(root_, sentinel_));
		}

		reverse_iterator rbegin() {
			if (root_ == sentinel_)
				return (reverse_iterator(root_, sentinel_));
			return (reverse_iterator(root_, highest_(root_)));
		}

		const_reverse_iterator rbegin() const {
			if (root_ == sentinel_)
				return (const_reverse_iterator(root_, sentinel_));
			return (const_reverse_iterator(root_, highest_(root_)));

		}
		reverse_iterator rend() {
			return (reverse_iterator(root_, sentinel_));
		}

		const_reverse_iterator rend() const {
			return (const_reverse_iterator(root_, sentinel_));
		}

		bool empty() const {
			return (size_ == 0);
		}

		size_type size() const {
			return (size_);
		}

		size_type max_size() const {
			return (ft::min(static_cast<size_type>(std::numeric_limits<difference_type>::max()),
				   std::numeric_limits<size_type>::max() / sizeof(s_br_node<key_type, mapped_type>)));
		}

		mapped_type& operator[] (const key_type& k) {
			iterator it = find(k);
			if (it == end())
			{
				value_type p = std::make_pair(k, mapped_type());
				return (*(insert(p).first)).second;
			}
			return (*it).second;
		}

		std::pair<iterator,bool> insert (const value_type& val) {
			return insert_at_(root_, val);
		}

		iterator insert (iterator position, const value_type& val) {
			node current = position.get_element();
			while (current) {
				if (current->data.first == val.first)
					return (iterator(root_, current));
				if ((val.first >= lowest_(current)->data.first) && val.first <= highest_(current)->data.first) {
					std::pair<iterator, bool> ret = insert_at_(current, val);
					return (ret.first);
				}
				current = current->parent;
			}
			return (position);
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last) {
			while (first != last) {
				insert_at_(root_, *first);
				++first;
			}
		}

		iterator find (const key_type& k) {
			node x = root_;
			while (x != sentinel_) {
				if (k == x->data.first)
					return iterator(root_, x);
				else if (cmp_(k, x->data.first))
					x = x->left;
				else
					x = x->right;
			}
			if (x == root_)
				return end();
			return iterator(root_, x);
		}

		const_iterator find (const key_type& k) const {
			node x = root_;
			while (x != sentinel_) {
				if (k == x->data.first)
					return const_iterator(root_, x);
				else if (cmp_(k, x->data.first))
					x = x->left;
				else
					x = x->right;
			}
			if (x == root_)
				return end();
			return const_iterator(root_, x);
		}

		void erase (iterator position) {
			node z = position.get_element();
			node y;
			e_br_color original_color = z->color;
			node x;
			if (z->left == sentinel_){
				x = z->right;
				transplant_(z, z->right);
			}else if (z->right == sentinel_){
				x = z->left;
				transplant_(z, z->left);
			}else{
				y = lowest_(z->right);
				original_color = y->color;
				x = y->right;
				if (y->parent == z) {
					x->parent = y;
				}else{
					transplant_(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				transplant_(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			if (original_color == BLACK)
				rb_delete_fixup(x);
			delete z;
			--size_;
		}

		size_type erase (const key_type& k)	{
			erase(find(k));
			return (1);
		}

		void erase (iterator first, iterator last) {
			iterator current;
			while (first != last) {
				current = first++;
				erase(current);
			}
		}

		void swap (Map& x) {
			ft::swap_element(sentinel_, x.sentinel_);
			ft::swap_element(size_, x.size_);
			ft::swap_element(root_, x.root_);
		}

		void clear() {
			if (size_ > 0)
				delete_tree_(root_);
			root_ = sentinel_;
			size_ = 0;
		}

		key_compare key_comp() const {
			return cmp_;
		}

		value_compare value_comp() const {
			return (value_compare_);
		}

		size_type count (const key_type& k) const {
			const_iterator it = find(k);

			if (it == end())
				return 0;
			return 1;
		}

		iterator lower_bound (const key_type& k) {
			if (size_ == 0)
				return (end());
			node succ = successor_(root_, k, true);
			if (succ == sentinel_)
				return end();
			return iterator(root_, succ);
		}

		const_iterator lower_bound (const key_type& k) const {
			if (size_ == 0)
				return (end());
			node succ = successor_(root_, k, true);
			if (succ == sentinel_)
				return end();
			return const_iterator(root_, succ);
		}

		iterator upper_bound (const key_type& k) {
			if (size_ == 0)
				return (end());
			node succ = successor_(root_, k, false);
			if (succ == sentinel_)
				return end();
			return iterator(root_, succ);
		}

		const_iterator upper_bound (const key_type& k) const {
			if (size_ == 0)
				return (end());
			node succ = successor_(root_, k, false);
			if (succ == sentinel_)
				return end();
			return const_iterator(root_, succ);
		}

		std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
			return std::make_pair(lower_bound(k), upper_bound(k));
		}

		std::pair<iterator,iterator>             equal_range (const key_type& k) {
			return std::make_pair(lower_bound(k), upper_bound(k));
		}
	};
}

#endif //FT_CONTAINERS_MAP_HPP
