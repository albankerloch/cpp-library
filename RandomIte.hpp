/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomIte.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 21:25:14 by mli               #+#    #+#             */
/*   Updated: 2021/01/12 13:38:06 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOMITE_CLASS_HPP
# define RANDOMITE_CLASS_HPP

# include "RandomIte_decl.hpp"

namespace ft {


template <typename Spe>
RandIte<Spe> RandIte<Spe>::operator-(difference_type n) const {
	return (RandIte(this->_value - n));
}

/*
template <typename Spe>
typename RandIte<Spe>::reference
	RandIte<Spe>::operator*(void) const {
	return (*this->_value);
}

template <typename Spe>
typename RandIte<Spe>::pointer
	RandIte<Spe>::operator->(void) const {
	return (this->_value);
}

template <typename Spe>
typename RandIte<Spe>::reference
	RandIte<Spe>::operator+=(difference_type n) {
	return (*(this->_value += n));
}

template <typename Spe>
typename RandIte<Spe>::reference
	RandIte<Spe>::operator-=(difference_type n) {
	return (*this += -n);
}

template <typename Spe>
typename RandIte<Spe>::reference
	RandIte<Spe>::operator[](difference_type n) {
	return (this->_value[n]);
}
*/

} // ******************************************************* ft namespace end //

#endif // ******************************************* RANDOMITE_CLASS_HPP end //
