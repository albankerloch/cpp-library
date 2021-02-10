#ifndef FT_CONTAINERS_QUEUE_HPP
#define FT_CONTAINERS_QUEUE_HPP

#include "../Vector/Vector.hpp"

namespace ft {
	template <class T, class Container = ft::Vector<T> >
	class Queue {
	public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;
	private:
		container_type ctnr_;
		template <class A, class B>
		friend bool	operator==(const Queue<A, B> &lhs, const Queue<A, B> &rhs);
		template <class A, class B>
		friend bool	operator!=(const Queue<A, B> &lhs, const Queue<A, B> &rhs);
		template <class A, class B>
		friend bool	operator<(const Queue<A, B> &lhs, const Queue<A, B> &rhs);
		template <class A, class B>
		friend bool	operator<=(const Queue<A, B> &lhs, const Queue<A, B> &rhs);
		template <class A, class B>
		friend bool	operator>(const Queue<A, B> &lhs, const Queue<A, B> &rhs);
		template <class A, class B>
		friend bool	operator>=(const Queue<A, B> &lhs, const Queue<A, B> &rhs);
	public:
		explicit Queue (const container_type& ctnr = container_type()): ctnr_(ctnr){}
		bool empty() const {
			return (ctnr_.empty());
		}

		size_type size() const {
			return (ctnr_.size());
		}
		value_type& front() {
			return (ctnr_.front());
		}

		const value_type& front() const {
			return (ctnr_.front());
		}

		value_type& back() {
			return (ctnr_.back());
		}

		const value_type& back() const {
			return (ctnr_.back());
		}

		void push (const value_type& val) {
			return (ctnr_.push_back(val));
		}

		void pop() {
			return (ctnr_.pop_front());
		}
	};
	template <class T, class Container>
	bool operator== (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {
		return (lhs.ctnr_ == rhs.ctnr_);
	}

	template <class T, class Container>
	bool operator!= (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {
		return (lhs.ctnr_ != rhs.ctnr_);
	}

	template <class T, class Container>
	bool operator<  (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {
		return (lhs.ctnr_ < rhs.ctnr_);
	}

	template <class T, class Container>
	bool operator<= (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {
		return (lhs.ctnr_ <= rhs.ctnr_);
	}

	template <class T, class Container>
	bool operator>  (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {
		return (lhs.ctnr_ > rhs.ctnr_);
	}

	template <class T, class Container>
	bool operator>=  (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {
		return (lhs.ctnr_ >= rhs.ctnr_);
	}
}

#endif //FT_CONTAINERS_QUEUE_HPP
