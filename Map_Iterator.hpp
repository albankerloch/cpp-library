#ifndef DEF_MAP_ITERATOR_HPP
# define DEF_MAP_ITERATOR_HPP

# include "Utils.hpp"

namespace ft	{

	template< class T, class Compare, typename node_type>
	class map_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T > 
	{

		template< typename _k, typename _t, typename _c, typename _a>
		friend class map;

		public:

			typedef	Compare																			key_compare;
			typedef typename iterator<ft::bidirectional_iterator_tag, T >::value_type				value_type;
			typedef typename iterator<ft::bidirectional_iterator_tag, T >::difference_type			difference_type;
			typedef typename iterator<ft::bidirectional_iterator_tag, T >::reference				reference;
            typedef typename iterator<ft::bidirectional_iterator_tag, T >::pointer					pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T >::iterator_category	iterator;

		private:

			node_type*																				_ptr;
			node_type*																				_btreeDumdNode;
			Compare																					_comp;

		public:

			map_iterator( node_type* ptr = NULL, node_type* dumbNode = NULL, const key_compare& comp = key_compare()) : _ptr(ptr),  _btreeDumdNode(dumbNode), _comp(comp)
			{
			};

			map_iterator(const map_iterator<T, Compare, node_type> & itSrc) : _ptr(itSrc.base()), _btreeDumdNode(itSrc.getDumbNode()),_comp(itSrc.getComp())		
			{
			};

			~map_iterator()
			{
			};

			operator map_iterator<const T, Compare, node_type>(void) const 
			{
				return (map_iterator<const T, Compare, node_type>(this->_ptr, this->_btreeDumdNode , this->_comp));
			};

			map_iterator& operator=( const map_iterator &src)	
			{
				if (*this != src)	
				{
					_ptr = src.base();
					_btreeDumdNode = src.getDumbNode();
					_comp = src.getComp();
				}
				return (*this);
			}

			map_iterator& operator++() 
			{
				if (_ptr == _btreeDumdNode)
					_ptr = _btreeDumdNode->left;
				else if (isLastNode(_ptr) == true)
					_ptr = _btreeDumdNode;
				else if (isLeaf(_ptr) == true)	
				{
					if (_ptr == _ptr->parent->left)
						_ptr = _ptr->parent;
					else
						getNextBranch();
				}
				else	
				{
					if (_ptr->right != NULL)
						_ptr = getFarLeft(_ptr->right);
					else
						getNextBranch();
				}
				return (*this);
			}

			map_iterator operator++( int ) 
			{
				map_iterator tmp(*this);

				operator++();
				return tmp;
			}

			map_iterator &operator--( void ) 
			{
				if (_ptr == _btreeDumdNode)
					_ptr = _btreeDumdNode->right;
				else if (isFirstNode(_ptr) == true)
					_ptr = _btreeDumdNode;
				else if (isLeaf(_ptr) == true)	
				{
					if (_ptr == _ptr->parent->right)
						_ptr = _ptr->parent;
					else
						getPreviousBranch();
				}
				else	
				{
					if (_ptr->left != NULL)
						_ptr = getFarRight(_ptr->left);
					else
						getPreviousBranch();
				}
				return (*this);
			}

			map_iterator operator--(int) 
			{
				map_iterator tmp(*this);

				operator--();
				return (tmp);
			}
 
			pointer	operator->() const		
			{ 
				return (&_ptr->item); 
			};

			node_type *base() const
			{
				return (this->_ptr); 
			};

			reference
			operator*()	const			{ return (_ptr->item); }


		private:

			node_type*			getDumbNode(void) const { return (_btreeDumdNode);	}
			Compare				getComp(void) const 	{ return (_comp);	}

			node_type*			getPosParent(void) const	
			{

				if (_ptr != NULL)
					return (_ptr->parent);
				return (NULL);
			}


			void
			getNextBranch( void )	{

				node_type*		cursor = _ptr->parent;

				while (cursor != NULL && _comp(cursor->item.first, _ptr->item.first) == true)
					cursor = cursor->parent;
				_ptr = cursor;
			}

			void
			getPreviousBranch( void )	{

				node_type*		cursor = _ptr->parent;

				while (cursor != NULL && _comp(_ptr->item.first, cursor->item.first) == true)
					cursor = cursor->parent;
				_ptr = cursor;
			}

			static	node_type*
			getFarLeft( node_type* cursor )	{

				while (cursor != NULL && cursor->left != NULL)
					cursor = cursor->left;
				return (cursor);
			}

			static	node_type*
			getFarRight( node_type* cursor )	{

				while (cursor != NULL && cursor->right != NULL)
					cursor = cursor->right;
				return (cursor);
			}

			bool
			isFirstNode( node_type* p )	{
				return (p == _btreeDumdNode->left);
			}

			bool
			isLastNode( node_type* p )	{
				return (p == _btreeDumdNode->right);
			}

			static	bool
			isLeaf(node_type* node)	{
				return (node->left == NULL && node->right == NULL);
			}


		}; //----------------- Class map_iterator

		template <typename T, typename T2, typename Compare, typename node_type> 
		bool operator==(const map_iterator<T, Compare, node_type>& rhs, const map_iterator<T2, Compare, node_type>& lhs)	
		{ 
			return (lhs.base() == rhs.base());
		};

		template <typename T, typename T2, typename Compare, typename node_type> 
		bool operator!=(const map_iterator<T, Compare, node_type>& rhs, const map_iterator<T2, Compare, node_type>& lhs)		
		{ 
			return (lhs.base() != rhs.base());
		};


} // ----------------- ft namespace


#endif
