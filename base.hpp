/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:57:26 by mli               #+#    #+#             */
/*   Updated: 2021/03/08 23:31:38 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_CLASS_HPP
# define BASE_CLASS_HPP

# ifndef __APPLE__
#  define __APPLE__ 0
# endif

# include <iostream>
# include <string>
# include <memory>
# include <limits>
# include <cstddef> // ptrdiff_t
# include <sstream> // ostring

namespace ft {

// struct choose<bool, true, false>

template <bool flag, class IsTrue, class IsFalse>
struct choose;

template <class IsTrue, class IsFalse>
struct choose<true, IsTrue, IsFalse> {
	typedef IsTrue type;
};

template <class IsTrue, class IsFalse>
struct choose<false, IsTrue, IsFalse> {
	typedef IsFalse type;
};

// struct enable_if<bool, true>

template <bool, class IsTrue = void>
struct enable_if;

template <class IsTrue>
struct enable_if<true, IsTrue> {
	typedef IsTrue type;
};

// Relational Operators Comparison Functions

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

// Ite len

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

// true if the first range compares lexicographically less than the second.
// false otherwise (including when all the elements of both ranges are equivalent).

template <class Ite1, class Ite2>
bool	lexicographical_compare(Ite1 first1, Ite1 last1, Ite2 first2, Ite2 last2)
{
	while (first1 != last1 && first2 != last2 && *first1 == *first2)
	{
		++first1; ++first2;
	}
	if (first1 == last1)
		return (first2 != last2);
	else if (first2 == last2)
		return (false);
	return (*first1 < *first2);
}

template <typename T>
struct	lstNode
{
	T			data;
	lstNode		*next;
	lstNode		*prev;

	lstNode(const T &src = T()) : data(src), next(this), prev(this) {};
};

// pair struct for ft::map

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


} // ******************************************************* ft namespace end //

#endif // ************************************************ BASE_CLASS_HPP end //
