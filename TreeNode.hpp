#ifndef DEF_TREE_NODE_HPP
# define DEF_TREE_NODE_HPP

# include "Utils.hpp"

namespace ft 
{
    template<typename T>
   	class TreeNode
	{
		public :
    
			TreeNode 	*m_left;
			TreeNode 	*m_right;
			TreeNode 	*m_parent;
			T			m_data;
			bool		m_color;

			TreeNode(): m_left(NULL), m_right(NULL), m_parent(NULL)
			{
			};
			
			TreeNode(T const & elem): m_left(NULL), m_right(NULL), m_parent(NULL), m_data(elem) 
			{
			};
			
			~TreeNode()
			{
			};
			
	};

	template <typename T>
	TreeNode<T>	*SeekRight(TreeNode<T> *node) 
	{
		while (node->m_right != NULL)
			node = node->m_right;
		return (node);
	}

	template <typename T>
	TreeNode<T>	*SeekLeft(TreeNode<T> *node) 
	{
		while (node->m_left != NULL)
			node = node->m_left;
		return (node);
	}

}

#endif
