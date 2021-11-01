#ifndef DEF_MAP_HPP
# define DEF_MAP_HPP

# include "Utils.hpp"
# include "Map_Iterator.hpp"
# include "Reverse_Iterator.hpp"
# include "TreeNode.hpp"

# include <iostream>
# include <limits>
# include <cstddef>

namespace ft	
{

	template< 	class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator< ft::TreeNode<ft::pair<const Key, T> > > >
	class map 
	{

		public:

			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair<const key_type, mapped_type>	value_type;
			typedef	Compare									key_compare;
			typedef size_t									size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef Allocator								allocator_type;
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			typedef typename ft::bidirectional_iterator<value_type, Compare, ft::TreeNode<value_type> >	iterator;
			typedef typename ft::bidirectional_iterator<const value_type, Compare, ft::TreeNode<value_type> >	const_iterator;
            typedef typename ft::reverse_iterator<bidirectional_iterator<value_type, Compare, ft::TreeNode<value_type> > > reverse_iterator;
            typedef typename ft::reverse_iterator<bidirectional_iterator<const value_type, Compare, ft::TreeNode<value_type> > >  const_reverse_iterator;

			class value_compare	
			{

				friend class map<Key, T, Compare, Allocator>;

				public:
					typedef	bool		result_type;
					typedef	value_type	first_argument_type;
					typedef	value_type	second_argument_type;

					bool
					operator()( const value_type& lhs, const value_type& rhs ) const {
						return (m_compare(lhs.first, rhs.first));
					}

				protected:
					value_compare( Compare c ) : m_compare(c) {}

					Compare				m_compare;
			};


		private:

			typedef typename ft::TreeNode<value_type>		node_type;

		protected:
				node_type*				_head;
				node_type*				_dumbNode;
				size_type				_size;
				allocator_type		 	_allocNode;
				Compare	const			m_compare;

		public:

		void print_tree()
			{
				std::string indent;

				ft_print_tree(this->_head, indent, true);
			};

			void ft_print_tree(node_type *root, std::string indent, bool last) 
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


			explicit map( const Compare& comp = key_compare(), const allocator_type & userAlloc = allocator_type())	: _head(NULL), _dumbNode(NULL), _size(0), _allocNode(userAlloc), m_compare(comp)				
			{
				btree_init_dumbNode();
			};

			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),   const allocator_type& userAlloc = allocator_type() ) :	_head(NULL), _dumbNode(NULL), _size(0), _allocNode(userAlloc), m_compare(comp)				
			{
				insert(first, last);
			}

			map( map const & src ) : _head(NULL), _dumbNode(NULL), _size(0), _allocNode(src._allocNode), m_compare(src.m_compare)				
			{
				insert(src.begin(), src.end());
			}

			~map()	
			{
				clear();
			}

			bool empty() const		
			{ 
				return (_size == 0); 
			};

			size_type size() const 		
			{ 
				return (_size); 
			};

			size_type max_size() const	
			{ 
				return this->_allocNode.max_size(); 
			};

			iterator begin()
			{
				if (empty() == false && _dumbNode != NULL)
					return (iterator(_dumbNode->left, _dumbNode, m_compare));
				return (iterator(_dumbNode, _dumbNode, m_compare));
			};

			const_iterator begin() const		
			{
				if (empty() == false && _dumbNode != NULL)
					return (const_iterator(_dumbNode->left, _dumbNode, m_compare));
				return (const_iterator(_dumbNode, _dumbNode, m_compare));
			};

			iterator end() 	 		
			{
				return (iterator(_dumbNode, _dumbNode, m_compare));
			};

			const_iterator end() const 
			{
				return (const_iterator(_dumbNode, _dumbNode, m_compare));
			};

			reverse_iterator rbegin()
			{	
				return reverse_iterator(end()); 
			};

			const_reverse_iterator rbegin() const	
			{	
				return const_reverse_iterator(end()); 
			};

			reverse_iterator rend()
			{	
				return reverse_iterator(begin()); 
			};

			const_reverse_iterator rend() const	
			{	
				return const_reverse_iterator(begin()); 
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

			ft::pair<iterator, bool> insert(const value_type& val)	
			{
				return(btree_insert_data(NULL, &_head, val));
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

				node_type*	deadNode = position.base();
				node_type*	deadNodeLeft = deadNode->left;
				node_type*	deadNodeRight = deadNode->right;
				node_type*	singleChild = getSingleChild(deadNode);

				if (deadNode == NULL)
					return;
				if (isLeaf(deadNode) == true)
					detachFromParent(deadNode);
				else if (singleChild != NULL)
					detachFromParent(deadNode, singleChild);
				else	{
					detachFromParent(deadNode, deadNodeLeft);
					node_type*	farRight = getFarRight(deadNodeLeft);
					deadNodeRight->parent = farRight;
					farRight->right = deadNodeRight;
				}
				decSize();
				btree_update_dumbNode();
				freeNode(deadNode);
			};

			size_type erase( const key_type& k )	
			{

				node_type*	target = btree_search_key(_head, k);
				if (target == NULL)
					return 0;
				else	{
					erase(iterator(target, _dumbNode, m_compare));
					return 1;
				}
			};

			void erase (iterator first, iterator last)	
			{
				while (first != last)
					this->erase(first++);
			}

			void
			swap (map& src)	{

				if (this->_head != src._head)	{
					node_type*				tmp_head = src._head;
					node_type*				tmp_dumbNode = src._dumbNode;
					size_t					tmp_size = src._size;
					allocator_type 			tmp_allocNode = src._allocNode;

					src._head = this->_head;
					src._dumbNode = this->_dumbNode;
					src._size = this->_size;
					src._allocNode = this->_allocNode;

					this->_head = tmp_head;
					this->_dumbNode = tmp_dumbNode;
					this->_size = tmp_size;
					this->_allocNode = tmp_allocNode;
				}
			}

			map&
			operator= (const map& src)	{

				if (this->_head != src._head)	{

					clear();

					if (src.empty() == false)	{
						if (src.size() > 2)	{
							const_iterator	half = src.begin();
							for (size_t i = 0; i < src.size() / 2; i++)
								half++;
							insert(*half);
						}
						insert(src.begin(), src.end());
					}
				}
				return *this;
			}

			mapped_type&
			operator[]( const key_type& key )	{

				value_type					insertValue(key, mapped_type());
				ft::pair<iterator, bool>	ret = insert(insertValue);
				return (ret.first->second);
			}

			void
			clear()			{

				freeAllNodes(_head);
				freeNode(_dumbNode);
				_size = 0;
				_head = NULL;
				_dumbNode = NULL;
			}

            value_compare	value_comp() const	{ return value_compare(m_compare); }
            key_compare		key_comp() const		{ return key_compare(m_compare); }


 		private:

		 	bool ft_key_compare(const key_type &key1, const key_type &key2)  const 
			{
				return (!(this->m_compare(key1, key2)) && !(this->m_compare(key2, key1)));
			};

			void
			detachFromParent( node_type* node, node_type* newChild = NULL )	{
				node_type* parent = node->parent;
				if (parent != NULL)	{
					if (parent->left == node)
						parent->left = newChild;
					else if (parent->right == node)
						parent->right = newChild;
				}
				else if (node == _head)
					_head = newChild;
				if (newChild != NULL)
					newChild->parent = parent;
				node->parent = NULL;
			}

			static node_type*
			getSingleChild( node_type* node )	{

				if (node->right != NULL && node->left == NULL)
					return (node->right);
				else if (node->right == NULL && node->left != NULL)
					return (node->left);
				else
					return (NULL);
			}

			node_type*
			locateBound( node_type* root, const key_type& key, bool (*isBound)(node_type*, const key_type&) ) const	{

				if (root == _head && isBound(_dumbNode->left, key) == true)
					return (_dumbNode->left);
				else if (root == _head && isBound(_dumbNode->right, key) == false)
					return (NULL);

				node_type* candidate = root;
				node_type* bestCandidate = NULL;
				while (candidate != NULL)	{
					if (isBound(candidate, key) == true)	{
						bestCandidate = candidate;
						candidate = candidate->left;
					}
					else
						candidate = candidate->right;
				}
				return (bestCandidate);
			}

			node_type*
			locateNode( node_type* root, const key_type& key ) const	{

				if (root != NULL)	{
					if (m_compare(key, root->item.first) == true)
						return (locateNode(root->left, key));
					else if (isEqualKey(key, root->item.first) == false)
						return (locateNode(root->right, key));
					else
						return (root);
				}
				else
					return (NULL);
			}

			static bool
			isLowerBoundNode( node_type* node, const key_type& key ) {

			typename ft::map<Key, T, Compare> tmpObj;
			typename ft::map<Key, T, Compare>::key_compare cmpFunc = tmpObj.keym_compare();

				return (node != NULL
					&& (cmpFunc(node->item.first, key) == false
						|| isEqualKey(node->item.first, key) == true));
			}

			static bool
			isUpperBoundNode( node_type* node, const key_type& key ) {
				typename ft::map<Key, T, Compare> tmpObj;
				typename ft::map<Key, T, Compare>::key_compare cmpFunc = tmpObj.keym_compare();
				return (node != NULL && cmpFunc(key, node->item.first) == true);
			}

			void
			btree_update_dumbNode()	{
				if (_dumbNode == NULL)
					btree_init_dumbNode();
				if (empty() == true)	{
					_dumbNode->left = _head;
					_dumbNode->right = _head;
				}
				else	{
					_dumbNode->left = getFarLeft(_head);
					_dumbNode->right = getFarRight(_head);
				}
			}

			void
			btree_init_dumbNode()	{

				if (_dumbNode == NULL)	{
					_dumbNode = _allocNode.allocate(1);
					_allocNode.construct(_dumbNode, node_type(value_type()));
					_dumbNode->left = _head;
					_dumbNode->right = _head;
				}
			}

			node_type*
			btree_create_node(node_type* parent, key_type k, mapped_type val)	{

				node_type*	newNode = _allocNode.allocate(1);
				_allocNode.construct(newNode, node_type(value_type(k ,val)));
				newNode->parent = parent;
				return (newNode);
			}

				/**
				 * @brief Actual function inserting new data in the tree.
				 * @param parent shall be NULL to insert anywhere from the head.
				 * @param root starting point in the tree to look for a suitable potision.
				 * @param pairSrc pair to be inserted.
				*/

			ft::pair<iterator, bool>
			btree_insert_data(node_type* parent, node_type **root, value_type pairSrc)	{

				if (*root != NULL)	{
					node_type* tree = *root;
					if (m_compare(pairSrc.first, tree->item.first) == true)
						return (btree_insert_data(tree, &tree->left, pairSrc));
					else if (isEqualKey(pairSrc.first, tree->item.first) == false)
						return (btree_insert_data(tree, &tree->right, pairSrc));
					else
						return (ft::pair<iterator, bool>(iterator(*root, _dumbNode, m_compare), false));
				}
				else	{
					*root = btree_create_node(parent, pairSrc.first, pairSrc.second);
					incSize();
					btree_update_dumbNode();
					return (ft::pair<iterator, bool>(iterator(*root, _dumbNode, m_compare), true));
				}
			}

			node_type*
			btree_search_key(node_type* root, const key_type& targetKey)	{

				if (root != NULL)	{
					if (m_compare(targetKey, root->item.first) == true)
						return (btree_search_key(root->left, targetKey));
					else if (m_compare(root->item.first, targetKey) == true)
						return (btree_search_key(root->right, targetKey));
				}
				return (root);
			}

			static node_type*
			getFarLeft( node_type* cursor )  {

				while (cursor != NULL && cursor->left != NULL)
					cursor = cursor->left;
				return (cursor);
			}

			static node_type*
			getFarRight( node_type* cursor )  {

				while (cursor != NULL && cursor->right != NULL)
					cursor = cursor->right;
				return (cursor);
			}

			static bool
			isLeaf(node_type* node)  {
				return (node->left == NULL && node->right == NULL);
			}

			static bool
			isEqualKey(const Key& existingKey, const Key& newKey) {
				typename ft::map<Key, T, Compare> tmpObj;
				typename ft::map<Key, T, Compare>::key_compare cmpFunc = tmpObj.key_comp();
				return (cmpFunc(existingKey, newKey) == false
				&& cmpFunc(newKey, existingKey) == false);
			}

			size_t
			incSize( size_t inc = 1 ) { _size += inc; return(_size); }

			size_t
			decSize( size_t inc = 1 ) { _size -= inc; return(_size); }

			void
			freeNode( node_type* node)	{
				if (node != NULL)	{
					_allocNode.destroy(node);
					_allocNode.deallocate(node, 1);
				}
			}

			void
			freeAllNodes( node_type* root )	{

				if (root == NULL)
					return;
				freeAllNodes(root->left);
				freeAllNodes(root->right);
				freeNode(root);
			}

			allocator_type
			get_allocator() const	{
				return _allocNode();
			}

		}; // -------------------------------------------------------- Class map

/******************************************************************************.
.******************************************************************************.
.*********** PUBLIC NON MEMBER FUNCTIONS     **********************************.
.******************************************************************************.
.******************************************************************************/

		template <class Key, class T, class Compare, class Alloc>
		void
		swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)	{

			x.swap(y);
		};

		template< class Key, class T, class Compare, class Alloc >
		bool operator==( const map<Key,T,Compare,Alloc>& lhs,
						const map<Key,T,Compare,Alloc>& rhs )	{

			if (lhs.size() != rhs.size())
				return false;

			typename ft::map<Key,T,Compare,Alloc>::const_iterator lhs_it = lhs.begin();
			typename ft::map<Key,T,Compare,Alloc>::const_iterator rhs_it = rhs.begin();

			for (;lhs_it != lhs.end() && rhs_it != rhs.end(); lhs_it++, rhs_it++)	{
				if (lhs_it->first != rhs_it->first || lhs_it->second != rhs_it->second)
					return false;
			}
			if (lhs_it != lhs.end() || rhs_it != rhs.end())
				return false;
			return true;

		}

		template< class Key, class T, class Compare, class Alloc >
		bool operator!=( const map<Key,T,Compare,Alloc>& lhs,
						const map<Key,T,Compare,Alloc>& rhs )	{
			return !(lhs == rhs);
		}

		template< class Key, class T, class Compare, class Alloc >
		bool operator<( const map<Key,T,Compare,Alloc>& lhs,
						const map<Key,T,Compare,Alloc>& rhs )	{

			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		template< class Key, class T, class Compare, class Alloc >
		bool operator>=( const map<Key,T,Compare,Alloc>& lhs,
						const map<Key,T,Compare,Alloc>& rhs )	{

			return !(lhs < rhs);
		}

		template< class Key, class T, class Compare, class Alloc >
		bool operator<=( const map<Key,T,Compare,Alloc>& lhs,
						const map<Key,T,Compare,Alloc>& rhs )	{
			return (lhs < rhs || lhs == rhs);
		}

		template< class Key, class T, class Compare, class Alloc >
		bool operator>( const map<Key,T,Compare,Alloc>& lhs,
						const map<Key,T,Compare,Alloc>& rhs )	{

			return !(lhs <= rhs);

		}



} // -------------------------------------------------------------- ft namespace

#endif /* *****BVALETTE****** MAP_HPP */
