#ifndef DEF_MAP_HPP
# define DEF_MAP_HPP

# include "Utils.hpp"
# include "Map_Iterator.hpp"
# include "Reverse_Iterator.hpp"
# include "TreeNode.hpp"

namespace ft 
{

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map 
	{
		public:

			typedef Key																key_type;
			typedef T																mapped_type;
			typedef ft::pair<key_type, mapped_type>							value_type;
			typedef Compare															key_compare;
			typedef Alloc															allocator_type;
			typedef typename allocator_type::reference								reference;
			typedef typename allocator_type::const_reference						const_reference;
			typedef typename allocator_type::pointer								pointer;
			typedef typename allocator_type::const_pointer							const_pointer;
			typedef ptrdiff_t														difference_type;
			typedef size_t															size_type;
			typedef ft::MapIterator<value_type, ft::TreeNode<value_type> >			iterator;
			typedef ft::MapIterator<const value_type, ft::TreeNode<value_type> >	const_iterator;
			typedef ft::reverse_iterator<iterator>									reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;

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

			typedef typename allocator_type::template rebind<ft::TreeNode<value_type> >::other	type_node_allocator;
			typedef typename type_node_allocator::pointer													node_pointer;
			type_node_allocator																				node_allocator;
			
			node_pointer																					m_root;
			key_compare																						m_compare;
			allocator_type																					m_allocator;
			size_type																						m_size;
			node_pointer																					m_ghost;

			void ft_init_tree(void)
			{
				this->m_ghost = node_allocator.allocate(1);
				node_allocator.construct(this->m_ghost, ft::TreeNode<value_type>());
				this->m_ghost->m_height = -1;
			};

			node_pointer ft_right_rotate(node_pointer y) 
			{

				node_pointer x = y->m_left;
				node_pointer T2 = x->m_right;

				x->m_right = y;
				x->m_parent = y->m_parent;
				y->m_parent = x;
				y->m_left = T2;
				if (T2)
					T2->m_parent = y;
				y->m_height = std::max(get_height(y->m_left), get_height(y->m_right)) + 1;
				x->m_height = std::max(get_height(x->m_left), get_height(x->m_right)) + 1;
				return (x);
			}

			node_pointer ft_left_rotate(node_pointer x) 
			{
				node_pointer y = x->m_right;
				node_pointer T2 = y->m_left;
				
				y->m_left = x;
				y->m_parent = x->m_parent;
				x->m_parent = y;
				x->m_right = T2;
				if (T2)
					T2->m_parent = x;
				x->m_height = std::max(get_height(x->m_left), get_height(x->m_right)) + 1;
				y->m_height = std::max(get_height(y->m_left), get_height(y->m_right)) + 1;
				return (y);
			}

			node_pointer ft_create_node(node_pointer node, node_pointer parent, const value_type & data)
			{
				node_pointer new_node;
				
				new_node = node_allocator.allocate(1);
				node_allocator.construct(new_node, ft::TreeNode<value_type>(data));
				new_node->m_parent = parent;
				this->m_size = this->m_size  + 1;
				if (node == this->m_ghost)
				{
					new_node->m_right = this->m_ghost;
					this->m_ghost->m_parent = new_node;
				}
				//std::cout << "new node " << new_node->m_data.first << " | " << new_node->m_data.second << " | " << new_node->m_height << std::endl;
				return (new_node);
			};

			node_pointer ft_insert_node(node_pointer node, node_pointer parent, value_type value)
			{
				int balance_factor;

				if (node == NULL || node == this->m_ghost)
					return (ft_create_node(node, parent, value));
				if (this->m_compare(value.first, node->m_data.first))
				{
					node->m_left = ft_insert_node(node->m_left, node, value);
				}
				else if (this->m_compare(node->m_data.first, value.first))
				{
					node->m_right = ft_insert_node(node->m_right, node, value);
				}
				else
					return (node);
				
				node->m_height = 1 + std::max(get_height(node->m_left), get_height(node->m_right));
				balance_factor = get_balance_factor(node);

				if (balance_factor > 1) 
				{
					if (this->m_compare(value.first, node->m_left->m_data.first))	
					{
						return (ft_right_rotate(node));
					} 
					else if (this->m_compare(node->m_left->m_data.first, value.first))	
					{
						node->m_left = ft_left_rotate(node->m_left);
						return (ft_right_rotate(node));
					}
				}
				else if (balance_factor < -1) 
				{
					if (this->m_compare(node->m_right->m_data.first, value.first))
					{
						return (ft_left_rotate(node));
					} 
					else if (this->m_compare(value.first, node->m_right->m_data.first))
					{
						node->m_right = ft_right_rotate(node->m_right);
						return (ft_left_rotate(node));
					}
				}
				//std::cout << "end" << node->m_data.first  << " " << value.first << std::endl;
				return (node);								
			};

			node_pointer nodeWithMimumValue(node_pointer node) 
			{
				node_pointer current;
				
				current = node;
				while (current->m_right != NULL)
					current = current->m_right;
				return (current);
			}

			node_pointer nodeWithMaxValue(node_pointer node) 
			{
				node_pointer current;
				
				current = node;
				while (current->m_left != NULL)
					current = current->m_left;
				return (current);
			}

			node_pointer ft_delete_node(node_pointer node, value_type value)
			{
				node_pointer 	tmp;
				int 			balance_factor;

				if (node == NULL || node == this->m_ghost)
    				return (node);
				if (this->m_compare(value.first, node->m_data.first))
				{
					node->m_left = ft_delete_node(node->m_left, value);
				}
				else if (this->m_compare(node->m_data.first, value.first))
				{
					node->m_right = ft_delete_node(node->m_right, value);
				}
				else
				{
					if (node->m_left != NULL && node->m_right != NULL)
					{
						tmp = nodeWithMaxValue(node->m_right);
						tmp->m_parent = node->m_parent;
						node->m_right->m_parent = tmp;
					}
					else if (node->m_right != NULL)
					{
						tmp = nodeWithMinValue(node->m_right);
						if(node->m_left == NULL && node->m_right == NULL)
						{
							tmp = node->m_parent;
						}
						else if(node->m_left == NULL)
						{
							tmp = node->m_right;
							tmp->m_parent = node->m_parent;
						}
						else if (node->m_right == NULL)
						{
							tmp = node->m_left;
							tmp->m_parent = node->m_parent;
						}
					}
					if(node == this->root)
						this->root = this->m_ghost;
					node_allocator.destroy(node);
					node_allocator.deallocate(node, 1);
					return (tmp);
				}

				if(node == NULL)
            		return (node);

				node->m_height = 1 + std::max(get_height(node->m_left), get_height(node->m_right));
				balance_factor = get_balance_factor(node);

				if (balance_factor > 1) 
				{
					if (this->m_compare(value.first, node->m_left->m_data.first))	
					{
						return (ft_right_rotate(node));
					} 
					else if (this->m_compare(node->m_left->m_data.first, value.first))	
					{
						node->m_left = ft_left_rotate(node->m_left);
						return (ft_right_rotate(node));
					}
				}
				else if (balance_factor < -1) 
				{
					if (this->m_compare(node->m_right->m_data.first, value.first))
					{
						return (ft_left_rotate(node));
					} 
					else if (this->m_compare(value.first, node->m_right->m_data.first))
					{
						node->m_right = ft_right_rotate(node->m_right);
						return (ft_left_rotate(node));
					}
				}
				
				return (node);
			};
		
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
					if (root->m_parent)
						std::cout << root->m_data.first << " | " << root->m_data.second << " | " << root->m_height << " << " << root->m_parent->m_data.first << std::endl;
					else
						std::cout << root->m_data.first << " | " << root->m_data.second << " | " << root->m_height << std::endl;
					ft_print_tree(root->m_left, indent, false);
					ft_print_tree(root->m_right, indent, true);
				}
			};

			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : m_root(), m_compare(comp), m_allocator(alloc), m_size(0) 
			{
				ft_init_tree();
				this->m_root = this->m_ghost;
			};

			template <class Ite>
			map(Ite first, Ite last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type(), typename ft::enable_if<!ft::is_integral_type<Ite>::value, Ite>::type* = NULL) : m_root(), m_compare(comp), m_allocator(alloc), m_size(0) 
			{
				ft_init_tree();
				this->m_root = this->m_ghost;
				this->insert(first, last);
			};

			map(const map &other) : m_root(), m_compare(key_compare()), m_allocator(allocator_type()), m_size(0) 
			{
				ft_init_tree();
				this->m_root = this->m_ghost;
				*this = other;
			};

			~map()
			{
				//this->clear();
			};

			map& operator=(map const &other) 
			{
				if (this == &other)
					return (*this);
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
				return (iterator(SeekLeft(this->m_root)));
			};

			const_iterator begin() const 
			{
				return (const_iterator(SeekLeft(this->m_root)));
			};

			iterator end() 
			{
				return (iterator(this->m_ghost));
			};

			const_iterator end() const 
			{
				return (const_iterator(this->m_ghost));
			};

			reverse_iterator rbegin() 
			{
				return (reverse_iterator(this->end()));
			};

			const_reverse_iterator rbegin() const 
			{
				return (const_reverse_iterator(this->end()));
			};

			reverse_iterator rend() 
			{
				return (reverse_iterator(this->begin()));
			};

			const_reverse_iterator rend() const 
			{
				return (const_reverse_iterator(this->begin()));
			};

			mapped_type & operator[](const key_type &key) 
			{
				return (this->insert(value_type(key, mapped_type())).first->second);
			};

			size_type size() const
			{
				return (this->m_size);
			};

			void clear()
			{
				if (this->m_size > 0)
					this->erase(this->begin(), this->end());
			};

			size_type max_size() const 
			{
				return (std::numeric_limits<size_type>::max() / (sizeof(TreeNode<value_type>)));
			};

			template <class Ite>
			void insert(Ite first, Ite last) 
			{
				bool is_valid;

				if (!(is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<Ite>::iterator_category>::value))
					throw (ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<Ite>::iterator_category >::type>());
				while (first != last)
				{
					this->insert(*first);
					first++;
				}
			};

			iterator insert(iterator position, const value_type &val) 
			{
				(void)(position);
				return (this->insert(val).first);
			};
			
			ft::pair<iterator, bool> insert(const value_type &value) 
			{
				ft::pair<iterator, bool> ret;

				ret.second = true;
				this->m_root = this->ft_insert_node(this->m_root, NULL, value);
				ret.first = iterator(this->m_root);
				return (ret);
			};

			void erase(iterator pos)
			{
				iterator tmp;

				tmp = pos;
				std::cout << "erase pos" << pos->first << " " << tmp->first << std::endl;
				this->m_root = this->ft_delete_node(pos.node(), *pos);
				std::cout << "erase pos" << pos->first << " " << this->m_root->m_data.first << std::endl;
				this->m_size--;
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
				iterator it;

				it = first;
				while (it != last)
				{
					print_tree();
					it = first;
					it++;
					std::cout << "erase" << first->first << " " << first.node()->m_right->m_data.first << std::endl;
					this->erase(first);
					print_tree();
					std::cout << "erase" << first->first << " " << first.node()->m_right->m_data.first << std::endl;
					first = it;
					std::cout << "erase" << first->first << std::endl;
				}
			}

			key_compare key_comp() const 
			{
				return (key_compare());
			};

			value_compare value_comp() const 
			{
				return (value_compare(key_compare()));
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


	
	};

} 

#endif