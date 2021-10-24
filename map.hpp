#ifndef DEF_MAP_HPP
# define DEF_MAP_HPP

# include "Utils.hpp"
# include "Map_Iterator.hpp"
# include "Reverse_Iterator.hpp"
# include "TreeNode.hpp"

namespace ft 
{

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map 
	{
		public:

			typedef Key												key_type;
			typedef T												mapped_type;
			typedef ft::pair<const key_type, mapped_type>			value_type;
			typedef Compare											key_compare;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef ft::TreeNode<value_type>						node_type;
			typedef node_type*										node_pointer;
			typedef ptrdiff_t										difference_type;
			typedef size_t											size_type;
			typedef ft::MapIterator<value_type, node_type>			iterator;
			typedef ft::MapIterator<const value_type, node_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

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

			node_pointer			m_root;
			key_compare				m_compare;
			allocator_type			m_allocator;
			size_type				m_size;

		private:

			void ft_insertm_node(node_pointer newNode)
			{
				node_pointer	*parent = &this->m_root;
				node_pointer	*node = &this->m_root;
				node_pointer	ghost = farRight(this->m_root);
				bool			side_left = -1;

				++this->m_size;
				while (*node && *node != ghost)
				{
					parent = node;
					side_left = this->m_compare(newNode->data.first, (*node)->data.first);
					node = (side_left ? &(*node)->left : &(*node)->right);
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
					ghost->parent = farRight(newNode);
					farRight(newNode)->right = ghost;
				}
			};

			void ft_deletem_node(node_pointer rmNode)
			{
				node_pointer	replaceNode = NULL;
				node_pointer	*rmPlace = &this->m_root;

				--this->m_size;
				if (rmNode->parent)
					rmPlace = (rmNode->parent->left == rmNode ? &rmNode->parent->left : &rmNode->parent->right);
				if (rmNode->left == NULL && rmNode->right == NULL)
					;
				else if (rmNode->left == NULL)
					replaceNode = rmNode->right;
				else
				{
					replaceNode = farRight(rmNode->left);
					if (replaceNode != rmNode->left)
						if ((replaceNode->parent->right = replaceNode->left))
							replaceNode->left->parent = replaceNode->parent;
				}
				if (replaceNode)
				{
					replaceNode->parent = rmNode->parent;
					if (rmNode->left && rmNode->left != replaceNode)
					{
						replaceNode->left = rmNode->left;
						replaceNode->left->parent = replaceNode;
					}
					if (rmNode->right && rmNode->right != replaceNode)
					{
						replaceNode->right = rmNode->right;
						replaceNode->right->parent = replaceNode;
					}
				}
				*rmPlace = replaceNode;
				delete rmNode;
			};

			void ft_tree_clear(node_pointer node)
			{
				if (node == NULL)
					return ;
				this->ft_tree_clear(node->left);
				this->ft_tree_clear(node->right);
				delete node;
			};

			bool ft_key_compare(const key_type &k1, const key_type &k2)  const 
			{
				return (!this->m_compare(k1, k2) && !this->m_compare(k2, k1));
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
				src.m_root = tmp; src.m_size = 0;
				tmp = NULL;
			};

		public :

			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : m_root(), m_compare(comp), m_allocator(alloc), m_size(0) 
			{
				this->m_root = new node_type;
			};

			template <class Ite>
			map(Ite first, Ite last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type(), typename ft::enable_if<!ft::is_integral_type<Ite>::value, Ite>::type* = NULL) : m_root(), m_compare(comp), m_allocator(alloc), m_size(0) 
			{
				this->m_root = new node_type;
				this->insert(first, last);
			};

			map(const map &other) : m_root(), m_compare(key_compare()), m_allocator(allocator_type()), m_size(0) 
			{
				this->m_root = new node_type;
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
				return iterator(farLeft(this->m_root));
			};

			const_iterator begin() const 
			{
				return const_iterator(farLeft(this->m_root));
			};

			iterator end() 
			{
				return iterator(farRight(this->m_root));
			};

			const_iterator end() const 
			{
				return const_iterator(farRight(this->m_root));
			};

			reverse_iterator rbegin() 
			{
				return reverse_iterator(this->end());
			};

			const_reverse_iterator rbegin() const 
			{
				return const_reverse_iterator(this->end());
			};

			reverse_iterator rend() 
			{
				return reverse_iterator(this->begin());
			};

			const_reverse_iterator rend() const 
			{
				return const_reverse_iterator(this->begin());
			};

			mapped_type & operator[](const key_type &key) 
			{
				iterator tmp;
				
				tmp = this->find(key);
				if (tmp != this->end())
					return (tmp->second);
				return (this->insert(value_type(key, mapped_type()))).first->second;
			};

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
				ft::pair<iterator, bool> res;

				res.second = !this->count(value.first);
				if (!this->count(value.first))
					this->ft_insertm_node(new node_type(value));
				res.first = this->find(value.first);
				return (res);
			};

			iterator insert(iterator position, const value_type &val) 
			{
				(void)(position);
				return this->insert(val).first;
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

			void erase(iterator pos) 
			{
				this->ft_deletem_node(pos.node());
			};

			size_type erase(const key_type &k) 
			{
				iterator element;
				
				
				element = this->find(k);
				if (element == this->end())
					return (0);
				this->ft_deletem_node(element.node());
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

			iterator find(const key_type &k) 
			{
				iterator it;
				iterator ite;
				
				it = this->begin();
				ite = this->end();
				while (it != ite)
				{
					if (this->ft_key_compare(it->first, k))
						break ;
					++it;
				}
				return (it);
			};

			const_iterator find(const key_type &k) const 
			{
				const_iterator it;
				const_iterator ite;
				
				it = this->begin();
				ite = this->end();
				while (it != ite)
				{
					if (this->ft_key_compare(it->first, k))
						break ;
					++it;
				}
				return (it);
			};

			size_type count(const key_type &k) const 
			{
				size_type		ret;
				const_iterator it;
				const_iterator ite;
			
				it = this->begin();
				ite = this->end();
				ret = 0;
				while (it != ite)
				{
					if (this->ft_key_compare((it++)->first, k))
					{
						++ret;
						break ;
					}
				}
				return (ret);
			};

			iterator lower_bound(const key_type &k) 
			{
				iterator it;
				iterator ite;
				
				it = this->begin();
				ite = this->end();
				while (it != ite)
				{
					if (!this->m_compare(it->first, k))
						break;
					++it;
				}
				return (it);
			};

			const_iterator lower_bound(const key_type &k) const 
			{
				const_iterator it;
				const_iterator ite;
			
				it = this->begin();
				ite = this->end();
				while (it != ite)
				{
					if (!this->m_compare(it->first, k))
						break;
					++it;
				}
				return (it);
			};

			iterator upper_bound(const key_type &k) 
			{
				iterator it;
				iterator ite;
				
				it = this->begin();
				ite = this->end();
				while (it != ite)
				{
					if (this->m_compare(k, it->first))
						break;
					++it;
				}
				return (it);
			};

			const_iterator upper_bound(const key_type &k) const 
			{
				const_iterator it;
				const_iterator ite;
			
				it = this->begin();
				ite = this->end();
				while (it != ite)
				{
					if (this->m_compare(k, it->first))
						break;
					++it;
				}
				return (it);
			};

			ft::pair<const_iterator,const_iterator> equal_range(const key_type &k) const 
			{
				ft::pair<const_iterator, const_iterator> res;

				res.first = this->lower_bound(k);
				res.second = this->upper_bound(k);
				return (res);
			};

			ft::pair<iterator,iterator>	equal_range(const key_type &k) 
			{
				ft::pair<iterator, iterator> res;

				res.first = this->lower_bound(k);
				res.second = this->upper_bound(k);
				return (res);
			};

	}; 

	template <class Key, class T, class Compare, class Alloc>
	bool	operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) 
	{
		if (lhs.size() != rhs.size())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) 
	{
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator< (const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) 
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) 
	{
		return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator> (const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) 
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) 
	{
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void	swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y) 
	{
		x.swap(y);
	}

} 

#endif
