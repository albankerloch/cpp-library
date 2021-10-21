#ifndef DEF_TREE_NODE_HPP
# define DEF_TREE_NODE_HPP

# include "base.hpp"

namespace ft 
{
    template<typename T>
   	class TreeNode
	{
		public :
		typedef T	data_type;
		data_type	data;
		TreeNode 	*left;
		TreeNode 	*right;
		TreeNode 	*parent;
		bool		end;

		public:

		TreeNode(const data_type &src = data_type()) : data(src), left(NULL), right(NULL), parent(NULL), end(false)
		{
		};

	};

	template <typename T>
	TreeNode<T>	*farRight(TreeNode<T> *node) 
	{
		while (node->right != NULL)
			node = node->right;
		return (node);
	}

	template <typename T>
	TreeNode<T>	*farLeft(TreeNode<T> *node) 
	{
		while (node->left != NULL)
			node = node->left;
		return (node);
	}
}

#endif