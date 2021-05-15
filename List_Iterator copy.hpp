#ifndef DEF_LIST_ITERATOR_HPP
# define DEF_LIST_ITERATOR_HPP

# include <iostream>
# include "Node.hpp"
# include <limits>

namespace ft 
{
    struct IteratorTrait {};

    template<typename T>
    class ListIterator: IteratorTrait
	{
		public:

			typedef T 					value_type;
			typedef value_type* 		pointer;
			typedef value_type const * 	const_pointer;
			typedef value_type& 		reference;
			typedef value_type const & 	const_reference;
			typedef std::ptrdiff_t 		difference_type;

		protected:

			pointer p;

		public:

			ListIterator(): p(NULL) {}
			ListIterator(pointer p): p(p) {}
			ListIterator(ListIterator const & other): p(other.p) {}
			virtual ~ListIterator() {}

			listIterator &operator=(listIterator const &src)
			{
				p = src.p;
				return (*this);
			};

			pointer &ptr(void) {
				return (this->p);
			}

			pointer as_node(void) const {
				return (this->p);
			}

			reference operator*() {
				return (this->p->value());
			}
			const_reference operator*() const {
				return (this->p->value());
			}
			pointer operator->() {
				return (&this->p->value());
			}
			const_pointer operator->() const {
				return (&this->p->value());
			}

			ListIterator &operator++() {
				this->p = this->p->next();
				return (*this);
			}
			ListIterator operator++(int) {
				ListIterator tmp(*this);
				this->p = this->p->next();
				return (tmp);
			}
			ListIterator &operator--() {
				this->p = this->p->previous();
				return (*this);
			}
			ListIterator operator--(int) {
				ListIterator tmp(*this);
				this->p = this->p->previous();
				return (tmp);
			}

			ListIterator &operator+=(int value) {
				if (value > 0) {
					for (int i = 0; i < value; i++)
						this->p = this->p->next();
				} else {
					for (int i = value; i > 0; i--)
						this->p = this->p->previous();
				}
			}
			ListIterator operator+(int value) const {
				ListIterator tmp(*this);
				return (tmp += value);
			}
			ListIterator &operator-=(int value) {
				operator+=(-value);
				return (*this);
			}
			ListIterator operator-(int value) const {
				ListIterator tmp(*this);
				return (tmp -= value);
			}

			bool operator==(ListIterator const &other) const {
				return (this->p == other.p);
			}
			bool operator!=(ListIterator const &other) const {
				return (this->p != other.p);
			}
			bool operator<(ListIterator const &other) const {
				return (this->p < other.p);
			}
			bool operator<=(ListIterator const &other) const {
				return (this->p <= other.p);
			}
			bool operator>(ListIterator const &other) const {
				return (this->p > other.p);
			}
			bool operator>=(ListIterator const &other) const {
				return (this->p >= other.p);
			}
		
	};
}

#endif