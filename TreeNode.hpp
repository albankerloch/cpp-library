#ifndef DEF_TREE_NODE_HPP
# define DEF_TREE_NODE_HPP

# include "base.hpp"

namespace ft 
{
    template<class Key, class T>
   	class TreeNode
	{
		public :
		typedef Key	key_type;
		typedef T	mapped_type;
		ft::pair<const key_type, mapped_type>	pair;
		TreeNode 	*left;
		TreeNode 	*right;
		TreeNode 	*parent;
		bool		end;

		public:

		TreeNode(key_type const key, mapped_type value, TreeNode *parent, bool end = false) : pair(ft::make_pair(key, value))
		{
			this->right = 0;
			this->left = 0;
			this->parent = parent;
			this->end = end;
		};
	};
}

#endif