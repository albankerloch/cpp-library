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

			TreeNode(): m_left(NULL), m_right(NULL), m_parent(NULL), m_height(0) 
			{
			};
			
			TreeNode(T const & elem): m_left(NULL), m_right(NULL), m_parent(NULL), m_height(0), m_data(elem) 
			{
			};

			int get_height(TreeNode *node) 
			{
				if (node == NULL)
					return (0);
				return node->height;
			};
	};

}

#endif
