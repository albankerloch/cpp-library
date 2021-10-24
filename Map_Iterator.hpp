#ifndef MAP_ITE_CLASS_HPP
# define MAP_ITE_CLASS_HPP

# include "Utils.hpp"

namespace ft 
{

	template <typename T, typename node_type>
	class MapIterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		protected:
			node_type						*_node;
			MapIterator(node_type *src)
			{ 
				this->_node = src; 
			};

		public:
			typedef T						value_type;
			typedef ptrdiff_t				difference_type;
			typedef value_type&				reference;
			typedef value_type*				pointer;

			MapIterator(void) : _node(NULL)
			{
			};

			MapIterator(const MapIterator &src)
			{
				*this = src; 
			};

			
			virtual ~MapIterator(void);
			MapIterator	&operator=(MapIterator const &rhs);

			template <class U> bool	operator==(const MapIterator<U, node_type> &rhs) const;
			template <class U> bool	operator!=(const MapIterator<U, node_type> &rhs) const;

			MapIterator		&operator++(void);
			MapIterator		operator++(int);
			MapIterator		&operator--(void);
			MapIterator		operator--(int);

			reference	operator*(void) const;
			pointer		operator->(void) const;

			operator MapIterator<const T, node_type>(void) const {
				return MapIterator<const T, node_type>(this->_node);
			}

			template <class, class, class, class>
			friend class map;

			template <class, class>
			friend class MapIterator;

	};

	template <typename T, typename node_type>
	MapIterator<T, node_type>::~MapIterator(void) { return ; }

	template <typename T, typename node_type>
	MapIterator<T, node_type> &MapIterator<T, node_type>::operator=(const MapIterator &rhs) {
		if (this == &rhs)
			return (*this);
		this->_node = rhs._node;
		return (*this);
	}

	template <typename T, typename node_type> template <class U>
	bool	MapIterator<T, node_type>::operator==(const MapIterator<U, node_type> &rhs) const {
		return (this->_node == rhs._node);
	}

	template <typename T, typename node_type> template <class U>
	bool	MapIterator<T, node_type>::operator!=(const MapIterator<U, node_type> &rhs) const {
		return (this->_node != rhs._node);
	}

	template <typename T, typename node_type>
	MapIterator<T, node_type> &MapIterator<T, node_type>::operator++(void) {
		if (this->_node->right != NULL)
			this->_node = farLeft(this->_node->right);
		else
		{
			node_type	*child = this->_node;

			this->_node = this->_node->parent;
			while (this->_node && child == this->_node->right)
			{
				child = this->_node;
				this->_node = this->_node->parent;
			}
		}
		return (*this);
	}

	template <typename T, typename node_type>
	MapIterator<T, node_type> MapIterator<T, node_type>::operator++(int) {
		MapIterator	tmp(*this);
		++(*this);
		return (tmp);
	}

	template <typename T, typename node_type>
	MapIterator<T, node_type>& MapIterator<T, node_type>::operator--(void) {
		if (this->_node->left != NULL)
			this->_node = farRight(this->_node->left);
		else
		{
			node_type	*child = this->_node;

			this->_node = this->_node->parent;
			while (this->_node && child == this->_node->left)
			{
				child = this->_node;
				this->_node = this->_node->parent;
			}
		}
		return (*this);
	}

	template <typename T, typename node_type>
	MapIterator<T, node_type> MapIterator<T, node_type>::operator--(int) {
		MapIterator	tmp(*this);
		--(*this);
		return (tmp);
	}

	template <typename T, typename node_type>
	typename MapIterator<T, node_type>::reference MapIterator<T, node_type>::operator*(void) const {
		return (this->_node->data);
	}

	template <typename T, typename node_type>
	typename MapIterator<T, node_type>::pointer MapIterator<T, node_type>::operator->(void) const {
		return &this->operator*();
	}

}

#endif
