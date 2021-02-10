#ifndef FT_CONTAINERS_RBNODE_HPP
#define FT_CONTAINERS_RBNODE_HPP

namespace ft {
	enum e_br_color {
		RED,
		BLACK
	};
	template<typename Key, typename T>
	struct s_br_node {
		s_br_node	*parent;
		s_br_node	*left;
		s_br_node	*right;
		e_br_color	color;
		std::pair<Key, T>	data;
	};
}
#endif //FT_CONTAINERS_RBNODE_HPP
