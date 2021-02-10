#ifndef FT_CONTAINERS_HELPERS_HPP
#define FT_CONTAINERS_HELPERS_HPP
namespace ft {
	template <typename T>
	void swap_element(T &s1, T &s2){
		T temp(s1);

		s1 = s2;
		s2 = temp;
	}

	template <typename T>
	T min(T s1, T s2){
		if (s1 < s2){
			return s1;
		}
		return s2;
	}
}


#endif //FT_CONTAINERS_HELPERS_HPP
