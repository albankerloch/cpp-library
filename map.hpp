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
			typedef ft::pair<const key_type, mapped_type>							value_type;
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

			typedef typename allocator_type::template rebind<ft::TreeNode<ft::pair<const Key,T> > >::other	type_node_allocator;
			typedef typename type_node_allocator::pointer													node_pointer;
			type_node_allocator																				node_allocator;
			
			node_pointer																					m_root;
			key_compare																						m_compare;
			allocator_type																					m_allocator;
			size_type																						m_size;
			node_pointer																					*m_storage;

		private:

			node_pointer ft_new_node(value_type value)
			{
				node_pointer tmp;

				this->m_storage = this->m_allocator.allocate(this->m_size + 1);
				tmp = this->m_allocator.construct(&this->m_storage[this->m_size + 1], value);
				return (tmp);				
			}

			void ft_insert_node(node_pointer newNode)
			{
				node_pointer	*parent;
				node_pointer	*node;
				node_pointer	ghost; 
				node_pointer	new_far_right;

				parent = &this->m_root;
				node = &this->m_root;
				ghost = SeekRight(this->m_root);
				this->m_size++;
				while (*node && *node != ghost)
				{
					parent = node;
					node = (this->m_compare(newNode->data.first, (*node)->data.first) ? &(*node)->left : &(*node)->right);
				}
				if (*node == NULL)
				{
					newNode->parent = (*parent);
					*node = newNode;
				}
				else
				{
					*node = newNode;
					newNode->parent = ghost->parent;
					new_far_right = SeekRight(newNode);
					ghost->parent = new_far_right;
					new_far_right->right = ghost;
				}
			};

			void ft_delete_node(node_pointer deleteNode)
			{
				node_pointer	replaceNode;
				node_pointer	*node;

				node = &this->m_root;
				this->m_size--;
				if (deleteNode->parent)
					node = (deleteNode->parent->left == deleteNode ? &deleteNode->parent->left : &deleteNode->parent->right);
				if (deleteNode->left == NULL && deleteNode->right == NULL)
					replaceNode = NULL;
				else if (deleteNode->left == NULL)
					replaceNode = deleteNode->right;
				else
				{
					replaceNode = SeekRight(deleteNode->left);
					if (replaceNode != deleteNode->left)
						if ((replaceNode->parent->right = replaceNode->left))
							replaceNode->left->parent = replaceNode->parent;
				}
				if (replaceNode)
				{
					replaceNode->parent = deleteNode->parent;
					if (deleteNode->left && deleteNode->left != replaceNode)
					{
						replaceNode->left = deleteNode->left;
						replaceNode->left->parent = replaceNode;
					}
					if (deleteNode->right && deleteNode->right != replaceNode)
					{
						replaceNode->right = deleteNode->right;
						replaceNode->right->parent = replaceNode;
					}
				}
				*node = replaceNode;
				delete deleteNode;
			};

			void ft_tree_clear(node_pointer node)
			{
				if (node == NULL)
					return;
				this->ft_tree_clear(node->left);
				this->ft_tree_clear(node->right);
				delete node;
			};

			bool ft_key_compare(const key_type &key1, const key_type &key2)  const 
			{
				return (!(this->m_compare(key1, key2)) && !(this->m_compare(key2, key1)));
			};

			void ft_copy(map &src) 
			{
				node_pointer tmp;

				this->clear();
				tmp = this->m_root;
				this->m_root = src.m_root;
				this->m_compare = src.m_compare;
				this->m_allocator = src.m_allocator;
				this->m_size = src.m_size;
				src.m_root = tmp; 
				src.m_size = 0;
				tmp = NULL;
			};

		public :

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
					std::cout << root->data.first << std::endl;
					ft_print_tree(root->left, indent, false);
					ft_print_tree(root->right, indent, true);
				}
			};

			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : m_root(), m_compare(comp), m_allocator(alloc), m_size(0) 
			{
				this->m_root = new ft::TreeNode<value_type>;
			};

			template <class Ite>
			map(Ite first, Ite last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type(), typename ft::enable_if<!ft::is_integral_type<Ite>::value, Ite>::type* = NULL) : m_root(), m_compare(comp), m_allocator(alloc), m_size(0) 
			{
				this->m_root = new ft::TreeNode<value_type>;
				this->insert(first, last);
			};

			map(const map &other) : m_root(), m_compare(key_compare()), m_allocator(allocator_type()), m_size(0) 
			{
				this->m_root = new ft::TreeNode<value_type>;
				*this = other;
			};

			~map()
			{
				this->clear();
				delete this->m_root;
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
				return (iterator(SeekRight(this->m_root)));
			};

			const_iterator end() const 
			{
				return (const_iterator(SeekRight(this->m_root)));
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
				iterator tmp;
				
				tmp = this->find(key);
				if (tmp != this->end())
					return (tmp->second);
				return (this->insert(value_type(key, mapped_type()))).first->second;
			};

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
				return (std::numeric_limits<size_type>::max() / (sizeof(TreeNode<value_type>)));
			};

			ft::pair<iterator, bool> insert(const value_type &value) 
			{
				ft::pair<iterator, bool> ret;

				ret.second = !this->count(value.first);
				if (ret.second)
					this->ft_insert_node(new ft::TreeNode<value_type>(value));
				ret.first = this->find(value.first);
				return (ret);
			};

			iterator insert(iterator position, const value_type &val) 
			{
				(void)(position);
				return (this->insert(val).first);
			};

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
				this->ft_delete_node(position.node());
			};

			size_type erase(const key_type &key) 
			{
				iterator element;
				
				element = this->find(key);
				if (element == this->end())
					return (0);
				this->ft_delete_node(element.node());
				return (1);
			};

			void erase(iterator first, iterator last) 
			{
				while (first != last)
					this->erase(first++);
			};

			void swap(map &x) 
			{
				map tmp;

				tmp.ft_copy(x);
				x.ft_copy(*this);
				this->ft_copy(tmp);
			};

			void clear() 
			{
				if (this->size() > 0)
					this->erase(this->begin(), this->end());
			};

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