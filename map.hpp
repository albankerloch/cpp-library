/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_decl.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:56:50 by mli               #+#    #+#             */
/*   Updated: 2021/03/06 12:37:40 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_DECL_CLASS_HPP
# define MAP_DECL_CLASS_HPP

# include "base.hpp"
# include "mapIte.hpp"
# include "ReverseIte.hpp"
# include "TreeNode.hpp"

namespace ft {

template <typename T>
void	swap(T *a, T *b)
{
	T *c;

	c = a;
	a = b;
	b = c;
}

template < class Key,                                     // map::key_type
		 class T,                                         // map::mapped_type
		 class Compare = std::less<Key>,                  // map::key_compare
		 class Alloc = std::allocator<pair<const Key,T> > // map::allocator_type
		 >
class map {
	public:

	typedef Key											key_type;
	typedef T											mapped_type;
	typedef ft::pair<const key_type, mapped_type>		value_type;
	typedef Compare										key_compare;
	class												value_compare;

	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef ft::TreeNode<key_type, mapped_type>			node_type;
	typedef node_type*									node;

	typedef ptrdiff_t									difference_type;
	typedef size_t										size_type;

	typedef ft::mapIte<value_type, node_type>			iterator;
	typedef ft::mapIte<const value_type, node_type>		const_iterator;
	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

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
				
				tmp = new TreeNode<key_type, mapped_type>(key, value, parent, end);
				/*+
				tmp->pair = ft::make_pair(key, value);
				tmp->right = 0;
				tmp->left = 0;
				tmp->parent = parent;
				tmp->end = end;*/

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
				}
				else if (n->right && !n->left)
				{
					if (parent->right == n)
						parent->right = n->right;
					else
						parent->left = n->right;
					n->right->parent = parent;
					delete n;
				}
				else if (n->left && !n->right)
				{
					if (parent->right == n)
						parent->right = n->left;
					else
						parent->left = n->left;
					n->left->parent = parent;
					delete n;
				}
				else
				{
					next = (iterator(n)++).node();
					if (!next)
						next = (iterator(n)--).node();
					ft::swap(&(next->pair), &(n->pair));
					ft_delete_node(next);
				}
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
			
			~map()
			{
				this->clear();	
			};

			map &operator=(const map<Key, T> &other)
			{
				this->clear();
				this->insert(other.begin(), other.end());
				return (*this);
			};

			allocator_type get_allocator() const
			{
				return (this->m_allocator);
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

			reverse_iterator rbegin()
			{
				iterator i = this->end();
				i--;
				return (reverse_iterator(i.node()));
			}

			const_reverse_iterator rbegin() const
			{
				iterator i = this->end();
				i--;
				return (const_reverse_iterator(i.node()));
			}

			iterator end()		
			{
				return (iterator(this->m_root->right));
			};

			const_iterator end() const	
			{ 
				return (const_iterator(this->m_root->right));
			};

			reverse_iterator rend()			
			{
				return (reverse_iterator(this->m_root));
			};

			const_reverse_iterator rend() const	
			{ 
				return (const_reverse_iterator(this->m_root));
			};

			mapped_type &operator[](const key_type& key)
			{
				iterator tmp;
				
				tmp = this->find(key);
				if (tmp != this->end())
					return (tmp->second);
				return (this->insert(ft::make_pair(key, mapped_type())).first->second);
			}
			
			mapped_type& at(const key_type& k)
			{
				iterator it;
				
				it = this->find(k);
				if (it == this->end())
					throw std::out_of_range("map::at:  key not found");
				return it->second;
			};	

			const mapped_type& at(const key_type& k) const 
			{
				const_iterator it;
				
				it = this->find(k);
				if (it == this->end())
					throw std::out_of_range("map::at:  key not found");
				return it->second;
			};	
			
			bool empty() const		
			{ 
				return (this->m_length == 0);
			};

			size_type	size() const		
			{ 
				return (this->m_length);
			};

			size_type	max_size() const	
			{ 
				return (std::numeric_limits<size_type>::max() / (sizeof(TreeNode<key_type, mapped_type>)));
			};

			ft::pair<iterator, bool> insert(const value_type &value)
			{
				iterator tmp;

				tmp = this->find(value.first);
				if (tmp != this->end())
					return (ft::make_pair(tmp, false));
				this->m_length++;
				return (ft::make_pair(iterator(this->ft_insert_node(this->m_root, value.first, value.second)), true));
			};

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					this->insert(*first);
					++first;
				}
			}

			iterator  insert(iterator pos, const value_type &value)
			{
				iterator tmp;

				if ((tmp = this->find(value.first)) != this->end())
					return (tmp);
				this->m_length++;
				return (iterator(ft_insert_node(pos.node(), value.first, value.second)));
			}

			void erase(iterator pos)
			{
				this->ft_delete_node(pos.node());
				this->m_length--;
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

			void swap(map &x)
			{
				map<Key, T, Compare, Alloc> tmp;

				tmp = *this;
				*this = x;
				x = tmp;
			};

			void clear()
			{
				if (this->size() > 0)
					this->erase(this->begin(), this->end());
			};

			size_type count(const key_type &value) const
			{
				const_iterator it_begin = this->begin();
				const_iterator it_end = this->end();

				while (it_begin != it_end)
				{
					if (it_begin->first == value)
						return (1);
					++it_begin;
				}
				return (0);
			}

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
			};

			ft::pair<iterator, iterator> equal_range(const key_type &k)
			{
				return (ft::pair<iterator, iterator>(this->lower_bound(k), this->upper_bound(k)));
			};

			ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
			{
				return (ft::pair<const_iterator, const_iterator>(this->lower_bound(k), this->upper_bound(k)));
			};

			iterator lower_bound(const key_type &key)
			{
				iterator it_begin; 
				iterator it_end;
				
				it_begin= this->begin();
				it_end = this->end();
				while (it_begin != it_end)
				{
					if (this->m_compare(it_begin->first, key) <= 0)
						return (it_begin);
					it_begin++;
				}
				return (it_end);
			};

			const_iterator lower_bound(const key_type &key) const
			{
				const_iterator it_begin; 
				const_iterator it_end;
				
				it_begin= this->begin();
				it_end = this->end();
				while (it_begin != it_end)
				{
					if (this->m_compare(it_begin->first, key) <= 0)
						return (it_begin);
					it_begin++;
				}
				return (it_end);
			};

			iterator upper_bound(const key_type &key)
			{
				iterator it_begin; 
				iterator it_end;
				
				it_begin= this->begin();
				it_end = this->end();
				while (it_begin != it_end)
				{
					if (it_begin->first != key && this->m_compare(it_begin->first, key) <= 0)
						return (it_begin);
					it_begin++;
				}
				return (it_end);
			};

			const_iterator upper_bound(const key_type &key) const
			{
				const_iterator it_begin; 
				const_iterator it_end;
				
				it_begin= this->begin();
				it_end = this->end();
				while (it_begin != it_end)
				{
					if (it_begin->first != key && this->m_compare(it_begin->first, key) <= 0)
						return (it_begin);
					it_begin++;
				}
				return (it_end);
			};

			key_compare		key_comp(void) const	
			{ 
				return (this->m_compare);
			};

			value_compare	value_comp(void) const	
			{ 
				return (value_compare(this->m_compare));
			};

	};

} // ******************************************************* ft namespace end //

#endif // ******************************************** MAP_DECL_CLASS_HPP end //
