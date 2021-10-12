
#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "TreeNode.hpp"
# include "Algo.hpp"

namespace ft
{
	template <typename K, typename T, typename Pointer, typename Reference>
		class MapIterator : IteratorTrait
		{
			public:
				typedef std::pair<K, T> 	value_type;
				typedef TreeNode<K, T>* 	pointer;
				typedef value_type const*   const_pointer;
				typedef value_type &		reference;
				typedef value_type const &	const_reference;
				typedef std::ptrdiff_t 		difference_type;
				typedef MapIterator<K, T, Pointer, Reference>		curr_class;
				typedef MapIterator<K, T, T*, T&>              		iterator;
				pointer p;

			private:
				pointer ptr_next(pointer ptr)
				{
					pointer next;
					if (!ptr->right)
					{
						next = ptr;
						while (next->parent && next == next->parent->right)
							next = next->parent;
						next = next->parent;
					}
					else
					{
						next = ptr->right;
						while (next->left)
							next = next->left;
					}
					return (next);
				};
				pointer ptr_prev(pointer ptr)
				{
					pointer next;

					if (!ptr->left)
					{
						next = ptr;
						while (next->parent && next == next->parent->left)
							next = next->parent;
						next = next->parent;
					}
					else
					{
						next = ptr->left;
						while (next->right)
							next = next->right;
					}
					return (next);
				};
			public:
				MapIterator(void): p(0) {}
				MapIterator(const pointer ptr): p(ptr) {}
				MapIterator(const MapIterator &other) { *this = other;}
				
				MapIterator &operator=(const MapIterator &other)
				{
					p = other.p;
					return (*this);
				};
				
				pointer node(void) { return (p);}
				
				value_type &operator*(void) { return (p->pair);}
				
				value_type *operator->(void) { return (&p->pair);}
				
				bool operator==(const MapIterator &other) { return (p == other.p);}
				bool operator!=(const MapIterator &other) { return (!(*this == other));}
				
				MapIterator &operator++(void)
				{
					p = ptr_next(p);
					return (*this);
				}

				MapIterator &operator--(void)
				{
					p = ptr_prev(p);
					return (*this);
				}

				MapIterator operator++(int)
				{
					MapIterator tmp(*this);
					this->operator++();
					return (tmp);
				}

				MapIterator operator--(int)
				{
					MapIterator tmp(*this);
					this->operator--();
					return (tmp);
				}

		};
		template <typename K, typename T, typename Pointer, typename Reference>
		class ReverseMapIterator
		{
			public:
				typedef std::pair<K, T> value_type;
				typedef std::pair<K, T>& reference;
				typedef TreeNode<K, T>* pointer;
				typedef ReverseMapIterator<K, T, Pointer, Reference>		curr_class;
				typedef ReverseMapIterator<K, T, T*, T&>              		iterator;
				pointer p;
			private:
				pointer ptr_next(pointer ptr)
				{
					pointer next;
					if (!ptr->right)
					{
						next = ptr;
						while (next->parent && next == next->parent->right)
							next = next->parent;
						next = next->parent;
					}
					else
					{
						next = ptr->right;
						while (next->left)
							next = next->left;
					}
					return (next);
				};
				pointer ptr_prev(pointer ptr)
				{
					pointer next;

					if (!ptr->left)
					{
						next = ptr;
						while (next->parent && next == next->parent->left)
							next = next->parent;
						next = next->parent;
					}
					else
					{
						next = ptr->left;
						while (next->right)
							next = next->right;
					}
					return (next);
				};
			public:
				ReverseMapIterator(): p(0) {}
				ReverseMapIterator(const pointer ptr): p(ptr) {}
				ReverseMapIterator(const iterator &other) {	*this = other;}

				ReverseMapIterator &operator=(const iterator &other)
				{
					p = other.p;
					return (*this);
				};
				
				pointer node() { return (p);}
				
				value_type &operator*(void) { return (p->pair);}

				value_type *operator->(void) { return (&p->pair);}

				bool operator==(const curr_class &other) { return (p == other.p);}
				bool operator!=(const curr_class &other) { return (!(*this == other));}
				
				ReverseMapIterator &operator++(void)
				{
					p = ptr_prev(p);
					return (*this);
				}

				ReverseMapIterator &operator--(void)
				{
					p = ptr_next(p);
					return (*this);
				}

				ReverseMapIterator operator++(int)
				{
					ReverseMapIterator tmp(*this);
					this->operator++();
					return (tmp);
				}

				ReverseMapIterator operator--(int)
				{
					ReverseMapIterator tmp(*this);
					this->operator--();
					return (tmp);
				}

		};
}
#endif
	