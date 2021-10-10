#ifndef DEF_ALGO_HPP
# define DEF_ALGO_HPP

# include <cstddef>
# include <limits>
# include <sstream>
# include <typeinfo>
# include <iostream>

namespace ft 
{
    struct IteratorTrait {};

   template<class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

	static class nullptr_t
	{
		public:
		
			template<class T>
			operator T*() const { return (0); }

			template<class C, class T>
			operator T C::*() const { return (0); }

		private:
			
			void operator&() const;

	} u_nullptr = {};

	template <class T>
    struct less : std::binary_function<T, T, bool>
    {
        bool operator() (const T& x, const T& y) const 
		{ 
			return (x < y); 
		}
    };

}

#endif