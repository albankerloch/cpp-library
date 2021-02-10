#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP
#include <memory>
#include <limits>
#include "ListIterator.hpp"
#include "ConstListIterator.hpp"
#include "ReverseListIterator.hpp"
#include "ConstReverseListIterator.hpp"
#include "../Helpers/Helpers.hpp"

namespace ft {
	template <typename T, typename Allocator_ = std::allocator<T> >
	class List {
	public:
		typedef T 										value_type;
		typedef Allocator_ 								allocator_type;
		typedef T 										&reference;
		typedef const T 								&const_reference;
		typedef T 										*pointer;
		typedef T const 								*const_pointer;
		typedef ListIterator<value_type>				iterator;
		typedef ConstListIterator<value_type>			const_iterator;
		typedef ReverseListIterator<value_type>			reverse_iterator;
		typedef ConstReverseListIterator<value_type>	const_reverse_iterator;
		typedef std::ptrdiff_t 							difference_type;
		typedef size_t									size_type;
	private:
		typedef s_node<T> node_type;
		allocator_type	allocator_;
		node_type 		*front_sentinel_;
		node_type		*back_sentinel_;
		size_t 			length_;

		node_type *new_node(T data, node_type *prev, node_type *next) {
			node_type *n = new node_type;
			n->data = data;
			n->prev = prev;
			n->next = next;
			return (n);
		};

		void create_sentinels_() {
			front_sentinel_ = new_node(T(), 0, 0);
			back_sentinel_ = new_node(T(), front_sentinel_, 0);
			front_sentinel_->next = back_sentinel_;
		};

		struct equal_ {
			bool operator()(T first, T second) {
				return (first == second);
			};
		};

		struct smaller_ {
			bool operator()(T first, T second) {
				return (first < second);
			};
		};

	public:
		explicit List (const allocator_type& alloc = allocator_type()): allocator_(alloc), length_(0) {
			create_sentinels_();
		};

		explicit List (size_type n, const value_type& val = value_type(),
		const allocator_type& alloc = allocator_type()): allocator_(alloc), length_(0) {
			create_sentinels_();
			for (size_type i = 0; i < n; i++) {
				push_back(val);
			}
		};

		template <class InputIterator>
		List(InputIterator first, InputIterator last, const allocator_type  &allocator=allocator_type()): allocator_(allocator), length_(0) {
			create_sentinels_();
			assign(first, last);
		};

		List(const List &x) {
			create_sentinels_();
			allocator_ = x.allocator_;
			assign(x.begin(), x.end());
		};

		~List() {
			clear();
			delete(front_sentinel_);
			delete(back_sentinel_);
		};

		List &operator=(const List &x){
			assign(x.begin(), x.end());
			return (*this);
		};

		iterator begin() {
			return (iterator(front_sentinel_->next));
		}

		const_iterator	begin() const {
			return (const_iterator(front_sentinel_->next));
		};

		iterator		end(){
			return (iterator(back_sentinel_));
		};

		const_iterator	end() const {
			return (const_iterator(back_sentinel_));
		};

		reverse_iterator rbegin() {
			return (reverse_iterator(back_sentinel_->prev));
		};

		const_reverse_iterator rbegin() const {
			return (const_reverse_iterator(back_sentinel_->prev));
		};

		reverse_iterator rend() {
			return (reverse_iterator(front_sentinel_));
		};

		const_reverse_iterator rend() const {
			return (const_reverse_iterator(front_sentinel_));
		};

		bool 			empty() const {
			if (length_ == 0)
				return (true);
			return (false);
		}

		size_type 			size() const {
			return (length_);
		}

		size_type 			max_size() const {
			return (ft::min(static_cast<size_type>(std::numeric_limits<difference_type>::max()), std::numeric_limits<size_type>::max() / sizeof(node_type)));
		}

		reference 			front() {
			return (front_sentinel_->next->data);
		}

		const_reference 	front() const {
			return (front_sentinel_->next->data);
		}

		reference back() {
			return (back_sentinel_->prev->data);
		}

		const_reference back() const {
			return (back_sentinel_->prev->data);
		}

		template <class InputIterator>
		void 				assign(InputIterator first, InputIterator last) {
			clear();
			while(first != last){
				push_back(*first);
				++first;
			}
		}

		void assign (size_type n, const value_type &val){
			clear();
			size_type i(0);

			while (i < n){
				push_front(val);
				i++;
			}
		}

		void push_front (const value_type &val) {
			node_type *n = new_node(val, front_sentinel_, front_sentinel_->next);
			front_sentinel_->next->prev = n;
			front_sentinel_->next = n;
			++length_;
		}

		void pop_front() {
			if (length_ == 0)
				return ;
			node_type *deleted = front_sentinel_->next;
			front_sentinel_->next = deleted->next;
			deleted->next->prev = front_sentinel_;
			delete(deleted);
			--length_;
		}

		void push_back (const value_type &val) {
			node_type *n = new_node(val, back_sentinel_->prev, back_sentinel_);
			back_sentinel_->prev->next = n;
			back_sentinel_->prev = n;
			++length_;
		}

		void pop_back () {
			if (length_ == 0)
				return ;
			node_type *deleted = back_sentinel_->prev;
			back_sentinel_->prev = deleted->prev;
			deleted->prev->next = back_sentinel_;
			delete  (deleted);
			--length_;
		}

		iterator insert (iterator position, const value_type &val){
			node_type *n;

			if (position == begin()) {
				push_front(val);
				return (begin());
			}
			if (position == end()) {
				push_back(val);
				return (end());
			}
			n = new_node(val, position.get_element()->prev, position.get_element());
			position.get_element()->prev->next = n;
			position.get_element()->prev = n;
			++length_;
			return (iterator(n));
		}

		void insert (iterator position, size_type n, const value_type& val) {
			while (n > 0) {
				position = insert(position, val);
				--n;
			}
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last) {
			while (first != last) {
				position = insert(position, *first);
				++first;
				if (position != end())
					position++;
			}
		}

		iterator erase (iterator position) {
			node_type *deleted = position.get_element();
			node_type *next = deleted->next;

			if (position == begin()){
				pop_front();
				return (begin());
			}
			if (position == end()){
				pop_back();
				return (end());
			}
			deleted->prev->next = deleted->next;
			deleted->next->prev = deleted->prev;
			delete(deleted);
			--length_;
			return (iterator(next));
		}

		iterator erase (iterator first, iterator last){
			while (first != last)
				first = erase(first);
			return (first);
		}

		void swap (List &x){
			ft::swap_element(length_, x.length_);
			ft::swap_element(front_sentinel_, x.front_sentinel_);
			ft::swap_element(back_sentinel_, x.back_sentinel_);
		}

		void resize (size_type n, value_type val = value_type()){
			while (n < length_){
				pop_back();
			}
			while (n > length_){
				push_back(val);
			}
		}

		void			clear() {
			node_type		*current;
			node_type		*next;

			length_ = 0;
			current = front_sentinel_->next;
			while(current != back_sentinel_){
				next = current->next;
				delete(current);
				current = next;
			}
			front_sentinel_->next = back_sentinel_;
			back_sentinel_->prev = front_sentinel_;
		}

		void splice(iterator position, List &x){
			splice(position, x, x.begin(), x.end());
		}

		void splice (iterator position, List& x, iterator i) {
			splice(position, x, i, ++i);
		}

		void splice (iterator position, List &x, iterator first, iterator last) {
			insert(position, first, last);
			x.erase(first, last);
		}

		void remove(const value_type &val) {
			iterator current = begin();

			while (current != end()) {
				if (*current == val)
					current = erase(current);
				else
					++current;
			}
		}

		template <class Predicate>
		void remove_if (Predicate pred) {
			iterator current = begin();

			while (current != end()) {
				if (pred(*current))
					current = erase(current);
				else
					++current;
			}
		}


		void unique() {
			unique(equal_());
		}

		template <class BinaryPredicate>
		void unique (BinaryPredicate binary_pred) {
			iterator previous = begin();
			iterator next = begin();

			while (++next != end()) {
				if (binary_pred(*previous, *next)) {
					erase(next);
					next = previous;
				}else{
					previous = next;
				}
			}
		}

		void merge (List &x) {
			merge(x, smaller_());
		}

		template <class Compare>
		void merge (List &x, Compare comp) {
			iterator xCurrent = x.begin();
			iterator thisCurrent = begin();

			if (&x == this)
				return ;
			while (xCurrent != x.end()) {
				while (thisCurrent != end()) {
					if (comp(*xCurrent, *thisCurrent)) {
						insert(thisCurrent, *xCurrent);
						break;
					}
					++thisCurrent;
				}
				++xCurrent;
			}
			x.clear();
		}

		void sort() {
			sort(smaller_());
		}

		template <class Compare>
		void sort (Compare comp) {
			for (iterator i = --end(); i != begin(); --i){
				for (iterator j = begin(); j != i; ++j) {
					if (comp(*i,*j))
						ft::swap_element(*i, *j);
				}
			}
		}

		void reverse() {
			ft::List<int> rev;
			iterator it = begin();

			while (it != end()){
				rev.push_front(*it);
				++it;
			}
			*this = rev;
		}
	};
	template <class T, class Alloc>
	bool operator== (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size()) {
			return false;
		}
		typename List<T>::const_iterator j = rhs.begin();
		for (typename List<T>::const_iterator i = lhs.begin(); i != lhs.end(); i++) {
			if (*i != *j)
				return (false);
			++j;
		}
		return (true);
	}

	template <typename T, class Alloc>
	bool operator!=(List <T, Alloc> const &lhs, List<T, Alloc> const &rhs) {
		if (&lhs == &rhs)
			return false;
		return true;
	}

	template <class T, class Alloc>
	bool operator<  (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
		if (lhs.size() < rhs.size())
			return (true);
		typename List<T>::const_iterator j = rhs.begin();
		for (typename List<T>::const_iterator i = lhs.begin(); i != lhs.end(); i++) {
			if (*i >= *j)
				return (false);
			++j;
		}
		return (true);
	}

	template <class T, class Alloc>
	bool operator<= (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>  (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
		return (rhs <= lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	void swap (List<T,Alloc> &x, List<T,Alloc> &y) {
		y.swap(x);
	}
}
#endif //FT_CONTAINERS_LIST_HPP
