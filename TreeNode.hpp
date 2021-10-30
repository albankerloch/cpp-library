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
			int			m_height;
			T			m_data;

			TreeNode(): m_left(NULL), m_right(NULL), m_parent(NULL), m_height(1) 
			{
			};
			
			TreeNode(T const & elem): m_left(NULL), m_right(NULL), m_parent(NULL), m_height(1), m_data(elem) 
			{
			};
			
	};

	template <typename T>
	int get_balance_factor(TreeNode<T> *node) 
	{
		if (node == NULL)
			return (0);
		return (get_height(node->m_left) - get_height(node->m_right));
	};

	template <typename T>
	int get_height(TreeNode<T> *node) 
	{
		if (node == NULL)
			return (0);
		return (node->m_height);
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
