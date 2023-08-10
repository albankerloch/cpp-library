/**
 * @file TreeNode.hpp
 * @author alban kerloc'h
 * @date 11/04/2021
 * @version 1.0
 */

#ifndef DEF_TREE_NODE_HPP
# define DEF_TREE_NODE_HPP

# include "Utils.hpp"

namespace ft 
{
	template< typename T>
	class TreeNode	{

		public:
			
			T				item;
			TreeNode*		left;
			TreeNode*		parent;
			TreeNode*		right;
			int				height;

			TreeNode(const T& itemSrc ) : item(itemSrc), left(NULL), parent(NULL), right(NULL), height(1)	 
			{
			};

			~TreeNode()
			{
			};
	};

	template <typename T>
	TreeNode<T>	*seekFarRight(TreeNode<T> *node) 
	{
		while (node != NULL && node->right != NULL)
			node = node->right;
		return (node);
	}

	template <typename T>
	TreeNode<T>	*seekFarLeft(TreeNode<T> *node) 
	{
		while (node != NULL && node->left != NULL)
			node = node->left;
		return (node);
	}

	template <typename T>
	bool isLeaf(TreeNode<T> *node)  
	{
		return (node->left == NULL && node->right == NULL);
	}

	template <typename T>
	int get_balance_factor(TreeNode<T> *node) 
	{
		if (node == NULL)
			return (0);
		return (get_height(node->left) - get_height(node->right));
	};

	template <typename T>
	int get_height(TreeNode<T> *node) 
	{
		if (node == NULL)
			return (0);
		return (node->height);
	};
}

#endif
