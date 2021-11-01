/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterator_base.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:51:45 by bvalette          #+#    #+#             */
/*   Updated: 2021/06/08 15:52:01 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_BASE_HPP
# define ITERATOR_BASE_HPP

# include "ft_enable_if.hpp"
# include <cstddef>

#ifndef DEBUG_MODE
# define DEBUG_MODE 0
#endif

namespace ft	{


	template <class Category,            // iterator::iterator_category
			class T,                     // iterator::value_type
			bool B,						// false == non const, true == const
			class Distance = std::ptrdiff_t>  // iterator::difference_type
	class iterator_base	{

			public:
				typedef Category					iterator_category;
				typedef T							value_type;
				typedef size_t						size_type;
				typedef Distance					difference_type;
				typedef typename	ft::ft_enable_if<B, value_type&, const value_type&>::type	reference;
				typedef typename	ft::ft_enable_if<B, value_type*, const value_type*>::type	pointer;
	}; //-------------- iterator

} // ----------------- ft namespace

#endif
