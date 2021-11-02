#ifndef DEF_UTILS_HPP
# define DEF_UTILS_HPP

# include <cstddef>
# include <limits>
# include <sstream>
# include <typeinfo>
# include <iostream>
# include <string>
# include <memory>
# include <iterator>
# include <stdexcept>
# include <algorithm>  
# include <cstddef>

namespace ft 
{
	
	struct input_iterator_tag 
	{	
	};

  	struct output_iterator_tag
	{	
	};

  	struct forward_iterator_tag : public input_iterator_tag
	{	
	};

  	struct bidirectional_iterator_tag : public forward_iterator_tag
	{	
	};

  	struct random_access_iterator_tag : public bidirectional_iterator_tag
	{	
	};

	template <class T>
    struct iterator_traits 
	{
        typedef typename T::value_type            value_type;
        typedef typename T::difference_type       difference_type;
        typedef typename T::iterator_category     iterator_category;
        typedef typename T::pointer               pointer;
        typedef typename T::reference             reference;
    };

	template <class T>
    struct iterator_traits<T*> 
	{
        typedef T                          		value_type;
        typedef ptrdiff_t                  		difference_type;
        typedef ft::random_access_iterator_tag	iterator_category;
        typedef T*                         		pointer;
        typedef T&                         		reference;
    };
	
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator
	{
		public:
			typedef T           value_type;
			typedef Distance    difference_type;
			typedef Pointer     pointer;
			typedef Reference   reference;
			typedef Category    iterator_category;
	};

	template <bool is_valid, typename T>
	struct valid_iterator_tag_res 
	{ 
		typedef T type; 
		const static bool value = is_valid; 
	};
    
    template <typename T>
	struct is_input_iterator_tagged : public valid_iterator_tag_res<false, T>
	{ 
	};

    template <>
	struct is_input_iterator_tagged<std::random_access_iterator_tag> : public valid_iterator_tag_res<true, std::random_access_iterator_tag>
	{ 
	};

    template <>
	struct is_input_iterator_tagged<std::bidirectional_iterator_tag> : public valid_iterator_tag_res<true, std::bidirectional_iterator_tag> 
	{ 
	};

   template <>
	struct is_input_iterator_tagged<std::forward_iterator_tag> : public valid_iterator_tag_res<true, std::forward_iterator_tag> 
	{ 
	};

    template <>
	struct is_input_iterator_tagged<std::input_iterator_tag> : public valid_iterator_tag_res<true, std::input_iterator_tag> 
	{ 
	};

    template <>
	struct is_input_iterator_tagged<ft::random_access_iterator_tag> : public valid_iterator_tag_res<true, ft::random_access_iterator_tag>
	{ 
	};

    template <>
	struct is_input_iterator_tagged<ft::bidirectional_iterator_tag> : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> 
	{ 
	};

    template <>
	struct is_input_iterator_tagged<ft::forward_iterator_tag> : public valid_iterator_tag_res<true, ft::forward_iterator_tag> 
	{ 
	};

    template <>
	struct is_input_iterator_tagged<ft::input_iterator_tag> : public valid_iterator_tag_res<true, ft::input_iterator_tag> 
	{ 
	};

    template <typename T>
    class InvalidIteratorException : public std::exception
    {
        private:

            std::string m_msg;
        
        public :

            InvalidIteratorException () throw() 
			{
				m_msg = "Is invalid iterator tag : " + std::string(typeid(T).name()); 
			};

            InvalidIteratorException (const InvalidIteratorException&) throw()
			{ 
			};

            InvalidIteratorException& operator= (const InvalidIteratorException&) throw()
			{ 
			};

            virtual ~InvalidIteratorException() throw()
			{ 
			};

            virtual const char* what() const throw() 
			{ 
				return (m_msg.c_str()); 
			};
    };

	template<bool B, class T = void>
	struct enable_if 
	{
	};

	template<class T>
	struct enable_if<true, T> 
	{
		typedef T type; 
	};

	template <class Ite>
	size_t	itlen(Ite first, Ite last) {
		size_t	i = 0;

		while (first != last)
		{
			++first;
			++i;
		}
		return (i);
	}

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

	template <class Ite1, class Ite2>
	bool	equal(Ite1 first1, Ite1 last1, Ite2 first2)
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
				return false;
			++first1; ++first2;
		}
		return true;
	}


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
	}

    template <class T1, class T2>
	bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return !(lhs == rhs);
	}
    
    template <class T1, class T2>
	bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

    template <class T1, class T2>
	bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return !(rhs < lhs);
	}

    template <class T1, class T2>
	bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return (rhs < lhs);
	}
  
    template <class T1, class T2>
	bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return !(lhs < rhs);
	}
    
    template <class T1, class T2>
	ft::pair<T1,T2> make_pair(T1 x, T2 y)
	{
		return (ft::pair<T1, T2>(x, y));
	}

	template <bool is_integral, typename T>
	struct is_integral_res 
	{
		typedef T type;
		static const bool value = is_integral;
	};

    template <typename>
    struct is_integral_type : public is_integral_res<false, bool>
	{ 
	};

    template <>
    struct is_integral_type<bool> : public is_integral_res<true, bool>
	{ 
	};

    template <>
    struct is_integral_type<char> : public is_integral_res<true, char>
	{ 
	};

    template <>
    struct is_integral_type<signed char> : public is_integral_res<true, signed char>
	{ 
	};

    template <>
    struct is_integral_type<short int> : public is_integral_res<true, short int>
	{ 
	};
    
    template <>
    struct is_integral_type<int> : public is_integral_res<true, int>
	{ 
	};

    template <>
    struct is_integral_type<long int> : public is_integral_res<true, long int>
	{ 
	};

    template <>
    struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char>
	{ 
	};

    template <>
    struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int>
	{ 
	};

    template <>
    struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int>
	{ 
	};

    template <>
    struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int>
	{ 
	};
    
    template <typename T>
    struct is_integral : public is_integral_type<T> 
	{ 
	};

}

#endif
