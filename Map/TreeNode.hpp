#ifndef DEF_TREE_NODE_HPP
# define DEF_TREE_NODE_HPP

# include "Algo.hpp"

namespace ft 
{
    template<class Key, class T>
   	struct TreeNode
	{
		ft::pair<Key, T> pair;
		TreeNode *left;
		TreeNode *right;
		TreeNode *parent;
		bool end;
	};
}

#endif