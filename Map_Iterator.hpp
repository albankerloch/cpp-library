#ifndef DEF_MAP_ITERATOR_HPP
# define DEF_MAP_ITERATOR_HPP

# include "Utils.hpp"
# include "TreeNode.hpp"

namespace ft	{

	template< class T, class Compare, typename node_type>
	class bidirectional_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T > 
	{

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

			bidirectional_iterator( node_type* ptr = NULL, node_type* dumbNode = NULL, const key_compare& comp = key_compare()) : m_pointer(ptr),  m_ghost(dumbNode), m_compare(comp)
			{
			};

			bidirectional_iterator(const bidirectional_iterator<T, Compare, node_type> & itSrc) : m_pointer(itSrc.base()), m_ghost(itSrc.getGhostNode()),m_compare(itSrc.getCompare())		
			{
			};

			~bidirectional_iterator()
			{
			};

			operator bidirectional_iterator<const T, Compare, node_type>() const 
			{
				return (bidirectional_iterator<const T, Compare, node_type>(this->m_pointer, this->m_ghost , this->m_compare));
			};

			bidirectional_iterator& operator=(const bidirectional_iterator &src)	
			{
				if (*this != src)	
				{
					m_pointer = src.base();
					m_ghost = src.getGhostNode();
					m_compare = src.getCompare();
				}
				return (*this);
			}

			bidirectional_iterator& operator++() 
			{
				if (m_pointer == m_ghost)
					m_pointer = m_ghost->left;
				else if (m_pointer == m_ghost->right)
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
						m_pointer = seekFarLeft(m_pointer->right);
					else
						getNextBranch();
				}
				return (*this);
			}

			bidirectional_iterator operator++(int) 
			{
				bidirectional_iterator tmp(*this);

				operator++();
				return tmp;
			}

			bidirectional_iterator &operator--() 
			{
				if (m_pointer == m_ghost)
					m_pointer = m_ghost->right;
				else if (m_pointer == m_ghost->left)
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
						m_pointer = seekFarRight(m_pointer->left);
					else
						getPreviousBranch();
				}
				return (*this);
			}

			bidirectional_iterator operator--(int) 
			{
				bidirectional_iterator tmp(*this);

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

			void getPreviousBranch()	
			{
				node_type*		cursor;
				
				cursor = m_pointer->parent;
				while (cursor != NULL && m_compare(m_pointer->item.first, cursor->item.first) == true)
					cursor = cursor->parent;
				m_pointer = cursor;
			};

		};

		template <typename T, typename T2, typename Compare, typename node_type> 
		bool operator==(const bidirectional_iterator<T, Compare, node_type>& rhs, const bidirectional_iterator<T2, Compare, node_type>& lhs)	
		{ 
			return (lhs.base() == rhs.base());
		};

		template <typename T, typename T2, typename Compare, typename node_type> 
		bool operator!=(const bidirectional_iterator<T, Compare, node_type>& rhs, const bidirectional_iterator<T2, Compare, node_type>& lhs)		
		{ 
			return (lhs.base() != rhs.base());
		};

}

#endif
