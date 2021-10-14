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

    template <class T1, class T2>
        struct pair
        {
            public :

                typedef T1 first_type;
                typedef T2 second_type;

                first_type first;
                second_type second;

                pair() : first(), second()
                {
				};

                template<class U, class V> pair (const pair<U, V>& pr) : first(pr.first), second(pr.second)
                {
				};

                pair (const first_type& a, const second_type& b) : first(a), second(b)
                {
				};

                pair& operator= (const pair& p)
                {
                    if (*this == p)
                        return (*this);
                    this->first = p.first;
                    this->second = p.second;
                    return (*this);
                }
        };
    
    template <class T1, class T2>
	bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	};

    template <class T1, class T2>
	bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return !(lhs == rhs);
	};
    
    template <class T1, class T2>
	bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	};

    template <class T1, class T2>
	bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return !(rhs < lhs);
	};

    template <class T1, class T2>
	bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return (rhs < lhs);
	};
  
    template <class T1, class T2>
	bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return !(lhs < rhs);
	};
    
    template <class T1, class T2>
	ft::pair<T1,T2> make_pair(T1 x, T2 y)
	{
		return (ft::pair<T1, T2>(x, y));
	};

}

#endif