#ifndef DEF_MAP_HPP
# define DEF_MAP_HPP

# include "base.hpp"
# include "Map_Iterator.hpp"
# include "ReverseIte.hpp"
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
			class													value_compare;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef ft::TreeNode<value_type>						node_type;
			typedef node_type*										node_ptr;
			typedef ptrdiff_t										difference_type;
			typedef size_t											size_type;
			typedef ft::MapIterator<value_type, node_type>			iterator;
			typedef ft::MapIterator<const value_type, node_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		private:

			node_ptr				m_root;
			key_compare				m_compare;
			allocator_type			m_allocator;
			size_type				m_size;


		public:


	// ******************************* Operations ******************************* //

		iterator		find(const key_type &k);
		const_iterator	find(const key_type &k) const;
		size_type		count(const key_type &k) const;

		iterator		lower_bound(const key_type &k);
		const_iterator	lower_bound(const key_type &k) const;
		iterator		upper_bound(const key_type &k);
		const_iterator	upper_bound(const key_type &k) const;
		pair<const_iterator,const_iterator>	equal_range(const key_type &k) const;
		pair<iterator,iterator>				equal_range(const key_type &k);

	// ******************************* Non-public ******************************* //

		private:

			void ft_insert_node(node_ptr newNode)
			{
				node_ptr	*parent = &this->m_root;
				node_ptr	*node = &this->m_root;
				node_ptr	ghost = farRight(this->m_root);
				bool		side_left = -1;

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

			void ft_delete_node(node_ptr rmNode)
			{
				node_ptr	replaceNode = NULL;
				node_ptr	*rmPlace = &this->m_root;

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

			void ft_tree_clear(node_ptr node)
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
				node_ptr tmp;

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
				return ;
			};

			template <class Ite>
			map(typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type first, Ite last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : m_root(), m_compare(comp), m_allocator(alloc), m_size(0) 
			{
				this->m_root = new node_type;
				this->insert(first, last);
			};

			map(const map &src) : m_root(), m_compare(key_compare()), m_allocator(allocator_type()), m_size(0) 
			{
				this->m_root = new node_type;
				*this = src;
			};

			~map(void)
			{
				this->clear();
				delete this->m_root;
			};

			map& operator=(map const &rhs) 
			{
				if (this == &rhs)
					return (*this);
				this->clear();
				this->insert(rhs.begin(), rhs.end());
				return (*this);
			};

			iterator begin(void) 
			{
				return iterator(farLeft(this->m_root));
			};

			const_iterator begin(void) const 
			{
				return const_iterator(farLeft(this->m_root));
			};

			iterator end(void) 
			{
				return iterator(farRight(this->m_root));
			};

			const_iterator end(void) const 
			{
				return const_iterator(farRight(this->m_root));
			};

			reverse_iterator rbegin(void) 
			{
				return reverse_iterator(this->end());
			};

			const_reverse_iterator rbegin(void) const 
			{
				return const_reverse_iterator(this->end());
			};

			reverse_iterator rend(void) 
			{
				return reverse_iterator(this->begin());
			};

			const_reverse_iterator rend(void) const 
			{
				return const_reverse_iterator(this->begin());
			};

			size_type size(void) const 
			{
				return (this->m_size);
			};

			size_type max_size(void) const 
			{
				return (std::numeric_limits<difference_type>::max() / (sizeof(node_type) / 2 ?: 1));
			};

			bool empty(void) const 
			{
				return (this->m_size == 0 ? true : false);
			};

			mapped_type & operator[](const key_type &k) 
			{
				return (this->insert(value_type(k, mapped_type()))).first->second;
			};

			ft::pair<iterator, bool> insert(const value_type &val) 
			{
				ft::pair<iterator, bool> res;

				res.second = !this->count(val.first);
				if (res.second == true)
					this->ft_insert_node(new node_type(val));
				res.first = this->find(val.first);
				return (res);
			};

			iterator insert(iterator position, const value_type &val) 
			{
				static_cast<void>(position);
				return this->insert(val).first;
			};

			template <class Ite>
			void insert(Ite first, Ite last) 
			{
				while (first != last)
					this->insert(*first++);
			};

			void erase(iterator position) 
			{
				this->erase(position++, position);
			};

			size_type erase(const key_type &k) 
			{
				iterator element = this->find(k);

				if (element == this->end())
					return (0);
				this->ft_delete_node(element._node);
				return (1);
			};

			void erase(iterator first, iterator last) 
			{
				while (first != last)
					this->ft_delete_node((first++)._node);
			};

			void swap(map &x) 
			{
				map tmp;

				tmp.ft_copy(x);
				x.ft_copy(*this);
				this->ft_copy(tmp);
			};

			void clear(void) 
			{
				node_ptr ghost = this->end()._node;

				if (this->m_size == 0)
					return ;
				ghost->parent->right = NULL;
				this->ft_tree_clear(this->m_root);
				this->m_root = ghost;
				this->m_size = 0;
			};

			key_compare key_comp(void) const 
			{
				return (key_compare());
			};

			value_compare value_comp(void) const 
			{
				return (value_compare(key_compare()));
			};


	}; // ***************************************************** class ft::map end //

	
	

	// ******************************* Observers ******************************** //

	
	// ******************************* Operations ******************************* //

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator
	map<Key, T, Compare, Alloc>::find(const key_type &k) {
		iterator it = this->begin(), ite = this->end();

		while (it != ite)
		{
			if (this->ft_key_compare(it->first, k))
				break ;
			++it;
		}
		return (it);
	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator
	map<Key, T, Compare, Alloc>::find(const key_type &k) const {
		const_iterator it = this->begin(), ite = this->end();

		while (it != ite)
		{
			if (this->ft_key_compare(it->first, k))
				break ;
			++it;
		}
		return (it);
	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type
	map<Key, T, Compare, Alloc>::count(const key_type &k) const {
		const_iterator	it = this->begin(), ite = this->end();
		size_type		res = 0;

		while (it != ite)
		{
			if (this->ft_key_compare((it++)->first, k))
			{
				++res;
				break ; // Because map can't have the same key twice (or more)
			}
		}
		return (res);
	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator
	map<Key, T, Compare, Alloc>::lower_bound(const key_type &k) {
		iterator it = this->begin(), ite = this->end();

		while (it != ite)
		{
			if (!this->m_compare(it->first, k))
				break;
			++it;
		}
		return (it);
	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator
	map<Key, T, Compare, Alloc>::lower_bound(const key_type &k) const {
		const_iterator it = this->begin(), ite = this->end();

		while (it != ite)
		{
			if (!this->m_compare(it->first, k))
				break;
			++it;
		}
		return (it);
	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator
	map<Key, T, Compare, Alloc>::upper_bound(const key_type &k) {
		iterator it = this->begin(), ite = this->end();

		while (it != ite)
		{
			if (this->m_compare(k, it->first))
				break;
			++it;
		}
		return (it);
	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator
	map<Key, T, Compare, Alloc>::upper_bound(const key_type &k) const {
		const_iterator it = this->begin(), ite = this->end();

		while (it != ite)
		{
			if (this->m_compare(k, it->first))
				break;
			++it;
		}
		return (it);
	}

	template<class Key, class T, class Compare, class Alloc>
	ft::pair<typename map<Key, T, Compare, Alloc>::const_iterator, typename map<Key, T, Compare, Alloc>::const_iterator>
	map<Key, T, Compare, Alloc>::equal_range(const key_type &k) const {
		pair<const_iterator, const_iterator> res;

		res.first = this->lower_bound(k);
		res.second = this->upper_bound(k);
		return (res);
	}

	template<class Key, class T, class Compare, class Alloc>
	ft::pair<typename map<Key, T, Compare, Alloc>::iterator, typename map<Key, T, Compare, Alloc>::iterator>
	map<Key, T, Compare, Alloc>::equal_range(const key_type &k) {
		pair<iterator, iterator> res;

		res.first = this->lower_bound(k);
		res.second = this->upper_bound(k);
		return (res);
	}

	// ####################### Non-member function overloads #######################

	template <class Key, class T, class Compare, class Alloc>
	bool	operator==(const map<Key, T, Compare, Alloc> &lhs,
						const map<Key, T, Compare, Alloc> &rhs) {
		if (lhs.size() != rhs.size())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator!=(const map<Key, T, Compare, Alloc> &lhs,
						const map<Key, T, Compare, Alloc> &rhs) {
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator< (const map<Key, T, Compare, Alloc> &lhs,
						const map<Key, T, Compare, Alloc> &rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<=(const map<Key, T, Compare, Alloc> &lhs,
						const map<Key, T, Compare, Alloc> &rhs) {
		return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator> (const map<Key, T, Compare, Alloc> &lhs,
						const map<Key, T, Compare, Alloc> &rhs) {
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const map<Key, T, Compare, Alloc> &lhs,
						const map<Key, T, Compare, Alloc> &rhs) {
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void	swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y) {
		x.swap(y);
	}

	template <class Key, class T, class Compare, class Alloc>
	class	map<Key, T, Compare, Alloc>::value_compare {
		public:
		Compare comp;
		value_compare(Compare c) : comp(c) { };

		typedef bool		result_type;
		typedef value_type	first_argument_type;
		typedef value_type	second_argument_type;
		bool	operator()(const value_type &x, const value_type &y) const {
			return comp(x.first, y.first);
		}
	};

} 

#endif
