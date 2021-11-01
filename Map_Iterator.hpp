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

			node_type*																				m_pointer;
			node_type*																				m_ghost;
			Compare																					m_compare;

		public:

			map_iterator( node_type* ptr = NULL, node_type* dumbNode = NULL, const key_compare& comp = key_compare()) : m_pointer(ptr),  m_ghost(dumbNode), m_compare(comp)
			{
			};

			map_iterator(const map_iterator<T, Compare, node_type> & itSrc) : m_pointer(itSrc.base()), m_ghost(itSrc.getGhostNode()),m_compare(itSrc.getCompare())		
			{
			};

			~map_iterator()
			{
			};

			operator map_iterator<const T, Compare, node_type>() const 
			{
				return (map_iterator<const T, Compare, node_type>(this->m_pointer, this->m_ghost , this->m_compare));
			};

			map_iterator& operator=( const map_iterator &src)	
			{
				if (*this != src)	
				{
					m_pointer = src.base();
					m_ghost = src.getGhostNode();
					m_compare = src.getCompare();
				}
				return (*this);
			}

			map_iterator& operator++() 
			{
				if (m_pointer == m_ghost)
					m_pointer = m_ghost->left;
				else if (isLastNode(m_pointer) == true)
					m_pointer = m_ghost;
				else if (isLeaf(m_pointer) == true)	
				{
					if (m_pointer == m_pointer->parent->left)
						m_pointer = m_pointer->parent;
					else
						getNextBranch();
				}
				else	
				{
					if (m_pointer->right != NULL)
						m_pointer = getFarLeft(m_pointer->right);
					else
						getNextBranch();
				}
				return (*this);
			}

			map_iterator operator++(int) 
			{
				map_iterator tmp(*this);

				operator++();
				return tmp;
			}

			map_iterator &operator--() 
			{
				if (m_pointer == m_ghost)
					m_pointer = m_ghost->right;
				else if (isFirstNode(m_pointer) == true)
					m_pointer = m_ghost;
				else if (isLeaf(m_pointer) == true)	
				{
					if (m_pointer == m_pointer->parent->right)
						m_pointer = m_pointer->parent;
					else
						getPreviousBranch();
				}
				else	
				{
					if (m_pointer->left != NULL)
						m_pointer = getFarRight(m_pointer->left);
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
				return (&m_pointer->item); 
			};

			node_type *base() const
			{
				return (this->m_pointer); 
			};

			reference operator*() const			
			{ 
				return (m_pointer->item); 
			};


		private:

			node_type* getGhostNode() const 
			{ 
				return (m_ghost);	
			};

			Compare getCompare() const 	
			{ 
				return (m_compare);	
			};

			node_type* getPosParent() const	
			{

				if (m_pointer != NULL)
					return (m_pointer->parent);
				return (NULL);
			};

			void getNextBranch()	
			{
				node_type*		cursor;
				
				cursor = m_pointer->parent;
				while (cursor != NULL && m_compare(cursor->item.first, m_pointer->item.first) == true)
					cursor = cursor->parent;
				m_pointer = cursor;
			};

			void
			getPreviousBranch()	
			{
				node_type*		cursor;
				
				cursor = m_pointer->parent;
				while (cursor != NULL && m_compare(m_pointer->item.first, cursor->item.first) == true)
					cursor = cursor->parent;
				m_pointer = cursor;
			};

			node_type* getFarLeft( node_type* cursor )	
			{

				while (cursor != NULL && cursor->left != NULL)
					cursor = cursor->left;
				return (cursor);
			};

			node_type* getFarRight( node_type* cursor )	
			{
				while (cursor != NULL && cursor->right != NULL)
					cursor = cursor->right;
				return (cursor);
			};

			bool isFirstNode( node_type* p )	
			{
				return (p == m_ghost->left);
			};

			bool isLastNode( node_type* p )	
			{
				return (p == m_ghost->right);
			};

			bool isLeaf(node_type* node)	
			{
				return (node->left == NULL && node->right == NULL);
			};

		};

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
