#ifndef MAP_HPP
# define MAP_HPP

#include "Map_Iterator.hpp"
#include <iostream>
#include <cmath>
#include <limits>

namespace ft
{

	template <typename T>
	void	swap(T &a, T &b)
	{
		T c;

		c = a;
		a = b;
		b = c;
	}

	template <class Key, class T, class Compare=std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key 																		key_type;
			typedef T 																			mapped_type;
			typedef std::pair<const key_type, mapped_type> 										value_type;
			typedef Compare 																	key_compare;
			typedef Alloc 																		allocator_type;

			typedef T& 																			reference;
			typedef const T& 																	const_reference;
			typedef T* 																			pointer;
			typedef const T* 																	const_pointer;
			typedef BNode<key_type, mapped_type>* 												node;
			typedef MapIterator<key_type, mapped_type, pointer, reference> 						iterator;
			typedef ReverseMapIterator<key_type, mapped_type, pointer, reference> 				reverse_iterator;
			typedef MapIterator<key_type, mapped_type, const_pointer, const_reference> 			const_iterator;
			typedef ReverseMapIterator<key_type, mapped_type, const_pointer, const_reference>	const_reverse_iterator;

			typedef size_t 																		size_type;

			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map<key_type, mapped_type, key_compare, Alloc>;

				protected:

					Compare m_compare;
					value_compare (Compare compare) : m_compare(compare) 
					{
					};

				public:

					bool operator() (const value_type& value1, const value_type& value2) const
					{
						return (m_compare(value1.first, value2.first));
					}
			};

		private:

			allocator_type m_allocator;
			key_compare m_compare;
			node m_root;
			size_type m_length;

			void ft_tree_initialization(void)
			{
				m_root = ft_new_node(key_type(), mapped_type(), 0);
				m_root->right  = ft_new_node(key_type(), mapped_type(), m_root, true);
				m_length = 0;
			};

			node ft_new_node(key_type key, mapped_type value, node parent, bool end = false)
			{
				node tmp;
				
				tmp = new BNode<key_type, mapped_type>();
				tmp->pair = std::make_pair(key, value);
				tmp->right = 0;
				tmp->left = 0;
				tmp->parent = parent;
				tmp->end = end;

				return (tmp);
			};

			node ft_find(node n, key_type key) const
			{
				node tmp;

				if (!n->end && n->pair.first == key && n->parent)
					return (n);
				if (n->right)
				{
					if ((tmp = ft_find(n->right, key)))
						return (tmp);
				}
				if (n->left)
				{
					if ((tmp = ft_find(n->left, key)))
						return (tmp);
				}

				return (0);
			};

			node ft_insert_node(node n, key_type key, mapped_type value, bool end = false)
			{
				if (n->end)
				{
					if (!n->left)
					{
						n->left = ft_new_node(key, value, n, end);
						return (n->left);
					}
					return (ft_insert_node(n->left, key, value));
				}
				if (key < n->pair.first && !end)
				{
					if (!n->left)
					{
						n->left = ft_new_node(key, value, n, end);
						return (n->left);
					}
					else
						return (ft_insert_node(n->left, key, value));
				}
				else
				{
					if (!n->right)
					{
						n->right = ft_new_node(key, value, n, end);
						return (n->right);
					}
					else
						return(ft_insert_node(n->right, key, value));
				}
			};

			void ft_delete_node(node n)
			{
				node parent;
				node next;
				
				parent = n->parent;
				if (!n->left && !n->right)
				{
					if (parent->right == n)
						parent->right = 0;
					else
						parent->left = 0;
					delete n;
					return ;
				}
				if (n->right && !n->left)
				{
					if (parent->right == n)
						parent->right = n->right;
					else
						parent->left = n->right;
					n->right->parent = parent;
					delete n;
					return ;
				}
				if (n->left && !n->right)
				{
					if (parent->right == n)
						parent->right = n->left;
					else
						parent->left = n->left;
					n->left->parent = parent;
					delete n;
					return ;
				}
				next = (iterator(n)++).node();
				if (!next)
					next = (iterator(n)--).node();
				ft::swap(next->pair, n->pair);
				ft_delete_node(next);
			}

			void ft_free_tree(node n)
			{
				if (n->right)
					ft_free_tree(n->right);
				if (n->left)
					ft_free_tree(n->left);
				delete (n);
			}

		public:

			explicit map(const key_compare &comp = key_compare(), const allocator_type alloc = allocator_type())
			{
				this->m_allocator = alloc;
				this->m_compare = comp;
				this->ft_tree_initialization();
			};

			template< class InputIt >
			map(InputIt first, InputIt last, const key_compare &comp = key_compare(), const allocator_type alloc = allocator_type())
			{
				this->m_allocator = alloc;
				this->m_compare = comp;
				this->ft_tree_initialization();
				this->insert(first, last);
			};

			map(const map<Key, T> &other)
			{
				this->ft_tree_initialization();
				*this = other;
			};

			map &operator=(const map<Key, T> &other)
			{
				this->clear();
				this->insert(other.begin(), other.end());
				return (*this);
			};

			~map()
			{
				this->ft_free_tree(this->m_root);	
			};

			iterator begin()
			{
				node tmp;
				
				tmp = this->m_root;
				if (!tmp->left && !tmp->right)
					return (this->end());
				if (!tmp->left && tmp->right)
					tmp = tmp->right;
				while (tmp->left)
					tmp = tmp->left;
				return (iterator(tmp));
			}

			const_iterator begin() const
			{
				node tmp;
				
				tmp = this->m_root;
				if (!tmp->left && !tmp->right)
					return (this->end());
				if (!tmp->left && tmp->right)
					tmp = tmp->right;
				while (tmp->left)
					tmp = tmp->left;
				return (const_iterator(tmp));
			}

			iterator end()		
			{
				return (iterator(this->m_root->right));
			};

			const_iterator end() const	
			{ 
				return (const_iterator(this->m_root->right));
			};

			void erase(iterator pos)
			{
				this->ft_delete_node(pos.node());
				this->_length--;
			}

			size_type erase(const key_type &value)
			{
				size_type i;
				iterator it;

				i = 0;
				while ((it = this->find(value)) != this->end())
				{
					this->erase(it);
					i++;
				}
				return (i);
			}

			void erase(iterator first, iterator last)
			{
				while (first != last)
					this->erase(first++);
			}

			void clear()
			{
				this->erase(this->begin(), this->end());
			};

			bool empty() const		
			{ 
				return (this->m_length == 0);
			};

			iterator find(const key_type &value)
			{
				node tmp;

				if (this->empty())
					return (this->end());
				tmp = this->ft_find(this->m_root, value);
				if (tmp)
					return (iterator(tmp));
				return (this->end());
			}

			const_iterator find(const key_type &value) const
			{
				node tmp;

				if (this->empty())
					return (this->end());
				tmp = this->ft_find(this->m_root, value);
				if (tmp)
					return (const_iterator(tmp));
				return (this->end());
			}

			iterator insert(const value_type &value)
			{
				iterator tmp;

				tmp = this->find(value.first);
				if (tmp != this->m_root->right)
					return (std::make_pair(tmp, false));
				else
					this->m_length++;
				return (std::make_pair(iterator(this->ft_insert_node(this->_root, value.first, value.second)), true));
			};

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					this->insert(*first);
					first++;
				}
			}
	};

}

#endif