#ifndef FT_CONTAINERS_NODE_HPP
#define FT_CONTAINERS_NODE_HPP
namespace ft {
	template<typename T>
	struct s_node {
		T data;
		s_node *prev;
		s_node *next;
	};
}
#endif //FT_CONTAINERS_NODE_HPP
