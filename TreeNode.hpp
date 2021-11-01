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
		while (node->right != NULL)
			node = node->right;
		return (node);
	}

	template <typename T>
	TreeNode<T>	*seekFarLeft(TreeNode<T> *node) 
	{
		while (node->left != NULL)
			node = node->left;
		return (node);
	}

	/*
    template<typename T>
   	class TreeNode
	{
		public :
    
			TreeNode 	*left;
			TreeNode 	*right;
			TreeNode 	*parent;
			T			item;
			bool		color;

			TreeNode(): left(NULL), right(NULL), parent(NULL)
			{
			};
			
			TreeNode(T const & elem): left(NULL), right(NULL), parent(NULL), item(elem) 
			{
			};
			
			~TreeNode()
			{
			};
			
	};

	*/

}

#endif
