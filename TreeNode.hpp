#ifndef DEF_TREE_NODE_HPP
# define DEF_TREE_NODE_HPP


namespace ft 
{
    template<class Key, class T>
   	struct BNode
	{
		std::pair<Key, T> pair;
		BNode *left;
		BNode *right;
		BNode *parent;
		bool end;
	};
}

#endif