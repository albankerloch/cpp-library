#ifndef DEF_TREE_NODE_HPP
# define DEF_TREE_NODE_HPP


namespace ft 
{
    template<class Key, class T>
   	struct TreeNode
	{
		std::pair<Key, T> pair;
		TreeNode *left;
		TreeNode *right;
		TreeNode *parent;
		bool end;
	};
}

#endif