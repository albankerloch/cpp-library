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
			typedef T																						value_type;
			typedef value_type&																				reference;
			typedef value_type*																				pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;


			MapIterator(void) : _node(NULL)
			{
			};

			MapIterator(const MapIterator &src)
			{
				*this = src; 
			};

			virtual ~MapIterator(void)
			{
			};

			MapIterator	&operator=(MapIterator const &rhs)
			{
				if (this == &rhs)
					return (*this);
				this->_node = rhs._node;
				return (*this);
			};

			template <class U> bool	operator==(const MapIterator<U, node_type> &rhs) const
			{
				return (this->_node == rhs._node);
			};

			template <class U> bool	operator!=(const MapIterator<U, node_type> &rhs) const
			{
				return (this->_node != rhs._node);
			};

			MapIterator		&operator++(void)
			{
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
			};

			MapIterator		operator++(int)
			{
				MapIterator	tmp(*this);
				++(*this);
				return (tmp);
			};

			MapIterator		&operator--(void)
			{
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
			};

			MapIterator		operator--(int)
			{
				MapIterator	tmp(*this);
				--(*this);
				return (tmp);
			};

			reference	operator*(void) const
			{
				return (this->_node->data);
			};

			pointer		operator->(void) const
			{
				return &this->operator*();
			};

			operator MapIterator<const T, node_type>(void) const {
				return MapIterator<const T, node_type>(this->_node);
			}

			template <class, class, class, class>
			friend class map;

			template <class, class>
			friend class MapIterator;

	};

}

#endif
