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
			bool			color;

			TreeNode( const T& itemSrc ) : item(itemSrc), left(NULL), parent(NULL), right(NULL)	 
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
}

#endif
