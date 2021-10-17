#ifndef DEF_TREE_NODE_HPP
# define DEF_TREE_NODE_HPP

# include "base.hpp"

namespace ft 
{
    template<typename T>
   	struct TreeNode
	{
		T 			pair;
		TreeNode 	*left;
		TreeNode 	*right;
		TreeNode 	*parent;
		bool 		end;
	};
}

#endif