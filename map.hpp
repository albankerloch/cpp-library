#ifndef DEF_MAP_HPP
# define DEF_MAP_HPP

# include "Utils.hpp"
# include "Map_Iterator.hpp"
# include "Reverse_Iterator.hpp"
# include "TreeNode.hpp"

namespace ft	
{

	template< 	class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< ft::TreeNode<ft::pair<const Key, T> > > >
	class map 
	{

		public:

			typedef Key																							key_type;
			typedef T																							mapped_type;
			typedef ft::pair<const key_type, mapped_type>														value_type;
			typedef size_t																						size_type;
			typedef std::ptrdiff_t																				difference_type;
			typedef	Compare																						key_compare;
			typedef Alloc																						allocator_type;
			typedef typename allocator_type::reference															reference;
			typedef typename allocator_type::const_reference													const_reference;
			typedef typename allocator_type::pointer															pointer;
			typedef typename allocator_type::const_pointer														const_pointer;
			typedef typename ft::bidirectional_iterator<value_type, Compare, ft::TreeNode<value_type> >			iterator;
			typedef typename ft::bidirectional_iterator<const value_type, Compare, ft::TreeNode<value_type> >	const_iterator;
            typedef typename ft::reverse_iterator<iterator> 													reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator>												const_reverse_iterator;

			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map;

				protected :

					Compare comp;

					value_compare (Compare compare) : comp(compare) 
					{
					};

				public:

					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					
					bool operator() (const value_type& value1, const value_type& value2) const
					{
						return (comp(value1.first, value2.first));
					};
			};

		private:

			typedef typename ft::TreeNode<value_type>															node_type;
			typedef typename allocator_type::template rebind<node_type>::other									type_node_allocator;
			typedef typename type_node_allocator::pointer														node_pointer;
			type_node_allocator																					m_node_allocator;
			node_pointer																						m_root;
			node_pointer																						m_ghost;
			size_type																							m_size;
			allocator_type		 																				m_allocator;
			Compare	const																						m_compare;

			node_pointer ft_create_node(node_pointer parent, value_type pair_value)	
			{
				node_pointer	newNode;
				
				newNode = this->m_node_allocator.allocate(1);
				m_node_allocator.construct(newNode, node_type(pair_value));
				newNode->parent = parent;
				return (newNode);
			}

			bool ft_key_compare(const key_type &key1, const key_type &key2)  const 
			{
				return (!(this->m_compare(key1, key2)) && !(this->m_compare(key2, key1)));
			};

			ft::pair<iterator, bool> ft_insert_node(node_pointer parent, node_pointer *node, value_type pair_value)	
			{
				node_pointer tmp;

				if (*node != NULL)	
				{
					tmp = *node;
					if (this->m_compare(pair_value.first, tmp->item.first))
						return (ft_insert_node(tmp, &tmp->left, pair_value));
					else if (!ft_key_compare(pair_value.first, tmp->item.first))
						return (ft_insert_node(tmp, &tmp->right, pair_value));
					else
						return (ft::pair<iterator, bool>(iterator(*node, this->m_ghost, this->m_compare), false));
				}
				else	
				{
					*node = ft_create_node(parent, pair_value);
					this->m_size++;
					if (this->empty() == true)	
					{
						this->m_ghost->left = this->m_root;
						this->m_ghost->right = this->m_root;
					}
					else	
					{
						this->m_ghost->left = seekFarLeft(this->m_root);
						this->m_ghost->right = seekFarRight(this->m_root);
					}
					return (ft::pair<iterator, bool>(iterator(*node, this->m_ghost, this->m_compare), true));
				}
			}

			void ft_detach_node(node_pointer node, node_pointer newChild = NULL)	
			{
				node_pointer parent;
				
				parent = node->parent;
				if (parent != NULL)	
				{
					if (parent->left == node)
						parent->left = newChild;
					else if (parent->right == node)
						parent->right = newChild;
				}
				else if (node == this->m_root)
					this->m_root = newChild;
				if (newChild != NULL)
					newChild->parent = parent;
				node->parent = NULL;
			};

			node_pointer ft_get_child(node_pointer node)	
			{
				if (node->right != NULL && node->left == NULL)
					return (node->right);
				else if (node->right == NULL && node->left != NULL)
					return (node->left);
				else
					return (NULL);
			};
	
			void ft_free_node( node_pointer node)	
			{
				if (node != NULL)	
				{
					m_node_allocator.destroy(node);
					m_node_allocator.deallocate(node, 1);
				}
			}

			void ft_clear_tree(node_pointer root)	
			{
				if (root == NULL)
					return;
				ft_clear_tree(root->left);
				ft_clear_tree(root->right);
				ft_free_node(root);
			}	
		
		public:

			void print_tree()
			{
				std::string indent;

				ft_print_tree(this->m_root, indent, true);
			};

			void ft_print_tree(node_pointer root, std::string indent, bool last) 
			{
				if (root != NULL) 
				{
					std::cout << indent;
					if (last) 
					{
						std::cout << "R---- ";
						indent += "   ";
					} 
					else 
					{
						std::cout << "L---- ";
						indent += "|  ";
					}
					if (root->parent)
						std::cout << root->item.first << " | " << root->item.second << " << " << root->parent->item.first << std::endl;
					else
						std::cout << root->item.first << " | " << root->item.second << std::endl;
					ft_print_tree(root->left, indent, false);
					ft_print_tree(root->right, indent, true);
				}
			};

			explicit map( const Compare& comp = key_compare(), const allocator_type & userAlloc = allocator_type())	: m_root(NULL), m_ghost(NULL), m_size(0), m_allocator(userAlloc), m_compare(comp)				
			{
				this->m_ghost = ft_create_node(NULL, value_type());
			};

			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),   const allocator_type& userAlloc = allocator_type() ) :	m_root(NULL), m_ghost(NULL), m_size(0), m_allocator(userAlloc), m_compare(comp)				
			{
				this->m_ghost = ft_create_node(NULL, value_type());
				this->insert(first, last);
			}

			map( map const & src ) : m_root(NULL), m_ghost(NULL), m_size(0), m_allocator(src.m_allocator), m_compare(src.m_compare)				
			{
				this->m_ghost = ft_create_node(NULL, value_type());
				this->insert(src.begin(), src.end());
			}

			~map()	
			{
				this->clear();
			}

			map& operator= (const map& src)	
			{
				if (this->m_root != src.m_root)	
				{

					this->clear();
					this->m_ghost = ft_create_node(NULL, value_type());
					if (src.empty() == false)	
						this->insert(src.begin(), src.end());
				}
				return (*this);
			};

			allocator_type get_allocator() const	
			{
				return (m_node_allocator());
			}

			mapped_type& at(const key_type& key)
			{
				iterator it;
				
				it = this->find(key);
				if (it == this->end())
					throw std::out_of_range("map::at:  key not found");
				return (it->second);
			};

			const mapped_type& at(const key_type& key) const
			{
				const_iterator it;
				
				it = this->find(key);
				if (it == this->end())
					throw std::out_of_range("map::at:  key not found");
				return (it->second);
			};

			mapped_type& operator[]( const key_type& key)
			{
				ft::pair<iterator, bool>	ret;
				
				ret = insert(value_type(key, mapped_type()));
				return (ret.first->second);
			};

			iterator begin()
			{
				if (empty() == false && m_ghost != NULL)
					return (iterator(m_ghost->left, m_ghost, m_compare));
				return (iterator(m_ghost, m_ghost, m_compare));
			};

			const_iterator begin() const		
			{
				if (empty() == false && m_ghost != NULL)
					return (const_iterator(m_ghost->left, m_ghost, m_compare));
				return (const_iterator(m_ghost, m_ghost, m_compare));
			};

			reverse_iterator rbegin()
			{	
				return (reverse_iterator(end())); 
			};

			const_reverse_iterator rbegin() const	
			{	
				return (const_reverse_iterator(end())); 
			};

			iterator end() 	 		
			{
				return (iterator(m_ghost, m_ghost, m_compare));
			};

			const_iterator end() const 
			{
				return (const_iterator(m_ghost, m_ghost, m_compare));
			};

			reverse_iterator rend()
			{	
				return (reverse_iterator(begin())); 
			};

			const_reverse_iterator rend() const	
			{	
				return (const_reverse_iterator(begin())); 
			};

			bool empty() const		
			{ 
				return (this->m_size == 0); 
			};

			size_type size() const 		
			{ 
				return (this->m_size); 
			};

			size_type max_size() const	
			{ 
				return (this->m_allocator.max_size()); 
			};

			void clear()			
			{
				ft_clear_tree(m_root);
				ft_free_node(m_ghost);
				m_size = 0;
				m_root = NULL;
				m_ghost = NULL;
			};

			ft::pair<iterator, bool> insert(const value_type& val)	
			{
				return(ft_insert_node(NULL, &m_root, val));
			}

			iterator insert (iterator position, const value_type& val)	
			{
				(void)(position);
				return (this->insert(val).first);
			}

			template <class Ite>
			void insert(Ite first, Ite last) 
			{
				bool is_valid;

				if (!(is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<Ite>::iterator_category>::value))
					throw (ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<Ite>::iterator_category >::type>());
				while (first != last)
					this->insert(*first++);
			};

			void erase(iterator position)	
			{

				node_pointer	deadNode = position.base();
				node_pointer	deadNodeLeft = deadNode->left;
				node_pointer	deadNodeRight = deadNode->right;
				node_pointer	singleChild = ft_get_child(deadNode);

				if (deadNode == NULL)
					return;
				if (isLeaf(deadNode) == true)
					ft_detach_node(deadNode);
				else if (singleChild != NULL)
					ft_detach_node(deadNode, singleChild);
				else	
				{
					ft_detach_node(deadNode, deadNodeLeft);
					node_pointer	farRight = seekFarRight(deadNodeLeft);
					deadNodeRight->parent = farRight;
					farRight->right = deadNodeRight;
				}
				this->m_size--;
				if (this->empty())	
				{
					m_ghost->left = m_root;
					m_ghost->right = m_root;
				}
				else	
				{
					m_ghost->left = seekFarLeft(m_root);
					m_ghost->right = seekFarRight(m_root);
				}
				ft_free_node(deadNode);
			};

			size_type erase(const key_type& key)	
			{
				iterator element;
				
				element = this->find(key);
				if (element == this->end())
					return (0);
				this->erase(iterator(element.base(), m_ghost, m_compare));
				return (1);
			};

			void erase (iterator first, iterator last)	
			{
				while (first != last)
					this->erase(first++);
			};

			void swap (map& src)	
			{
				if (this->m_root != src.m_root)	
				{
					node_pointer				tmpm_root;
					node_pointer				tmpm_ghost;
					size_t					tmpm_size;
					allocator_type 			tmpm_allocator;


					tmpm_root = src.m_root;
					tmpm_ghost = src.m_ghost;
					tmpm_size = src.m_size;
					tmpm_allocator = src.m_allocator;

					src.m_root = this->m_root;
					src.m_ghost = this->m_ghost;
					src.m_size = this->m_size;
					src.m_allocator = this->m_allocator;

					this->m_root = tmpm_root;
					this->m_ghost = tmpm_ghost;
					this->m_size = tmpm_size;
					this->m_allocator = tmpm_allocator;
				}
			};

			iterator find(const key_type &key) 
			{
				iterator it;
				iterator ite;
				
				it = this->begin();
				ite = this->end();
				while (it != ite)
				{
					if (this->ft_key_compare(it->first, key))
						break;
					it++;
				}
				return (it);
			};

			const_iterator find(const key_type &key) const 
			{
				const_iterator it;
				const_iterator ite;
				
				it = this->begin();
				ite = this->end();
				while (it != ite)
				{
					if (this->ft_key_compare(it->first, key))
						break;
					it++;
				}
				return (it);
			};

			size_type count(const key_type &key) const 
			{
				size_type		ret;
				const_iterator it;
				const_iterator ite;
			
				it = this->begin();
				ite = this->end();
				ret = 0;
				while (it != ite)
				{
					if (this->ft_key_compare((it++)->first, key))
					{
						ret++;
						break;
					}
				}
				return (ret);
			};

			iterator lower_bound(const key_type &key) 
			{
				iterator it;
				iterator ite;
				
				it = this->begin();
				ite = this->end();
				while (it != ite)
				{
					if (!this->m_compare(it->first, key))
						break;
					it++;
				}
				return (it);
			};

			const_iterator lower_bound(const key_type &key) const 
			{
				const_iterator it;
				const_iterator ite;
			
				it = this->begin();
				ite = this->end();
				while (it != ite)
				{
					if (!this->m_compare(it->first, key))
						break;
					it++;
				}
				return (it);
			};

			iterator upper_bound(const key_type &key) 
			{
				iterator it;
				iterator ite;
				
				it = this->begin();
				ite = this->end();
				while (it != ite)
				{
					if (this->m_compare(key, it->first))
						break;
					it++;
				}
				return (it);
			};

			const_iterator upper_bound(const key_type &key) const 
			{
				const_iterator it;
				const_iterator ite;
			
				it = this->begin();
				ite = this->end();
				while (it != ite)
				{
					if (this->m_compare(key, it->first))
						break;
					it++;
				}
				return (it);
			};

			ft::pair<const_iterator,const_iterator> equal_range(const key_type &key) const 
			{
				ft::pair<const_iterator, const_iterator> ret;

				ret.first = this->lower_bound(key);
				ret.second = this->upper_bound(key);
				return (ret);
			};

			ft::pair<iterator,iterator>	equal_range(const key_type &key) 
			{
				ft::pair<iterator, iterator> ret;

				ret.first = this->lower_bound(key);
				ret.second = this->upper_bound(key);
				return (ret);
			};

            value_compare value_comp() const	
			{
				return value_compare(m_compare); 
			};

            key_compare key_comp() const		
			{ 
				return key_compare(m_compare); 
			};

	};

	template <class Key, class T, class Compare, class Alloc>
	bool	operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) 
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) 
	{
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator< (const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) 
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) 
	{
		return (!(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator> (const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) 
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) 
	{
		return (!(lhs < rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	void	swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y) 
	{
		x.swap(y);
	}

}

#endif
