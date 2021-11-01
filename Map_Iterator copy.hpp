#ifndef DEF_MAP_ITERATOR_HPP
# define DEF_MAP_ITERATOR_HPP

# include "Utils.hpp"

namespace ft 
{

	template <typename T, typename node_type>
	class MapIterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{

		public:

			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type 					value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;

		private:

			node_type																						*m_node;

		public:

			MapIterator(node_type *src)
			{ 
				this->m_node = src; 
			};

			MapIterator(void) : m_node(NULL)
			{
			};

			MapIterator(const MapIterator &src)
			{
				*this = src; 
			};

			virtual ~MapIterator(void)
			{
			};

			node_type *node() const
			{
				return (this->m_node); 
			};

			MapIterator	&operator=(MapIterator const &rhs)
			{
				if (this == &rhs)
					return (*this);
				this->m_node = rhs.node();
				return (*this);
			};

			template <class U> 
			bool	operator==(const MapIterator<U, node_type> &rhs) const
			{
				return (this->m_node == rhs.node());
			};

			template <class U> 
			bool	operator!=(const MapIterator<U, node_type> &rhs) const
			{
				return (this->m_node != rhs.node());
			};

			MapIterator &operator++(void)
			{
				node_type	*parent;

				std::cout << this->m_node->m_data.first << " | " << this->m_node->m_data.second << " | " << this->m_node->m_height << std::endl;
				if (this->m_node->m_right != NULL)
				{
					std::cout << "+" << this->m_node->m_right->m_data.first << std::endl;
					this->m_node = this->m_node->m_right;
					while (this->m_node->m_left != NULL) 
						this->m_node = this->m_node->m_left;
				}
				else
				{
					std::cout << "++" << this->m_node->m_data.first << std::endl;
					parent = this->m_node->m_parent;
					while (parent && this->m_node == parent->m_right)
					{
						this->m_node = parent;
						parent = this->m_node->m_parent;
					}
					this->m_node = parent;
				}
				return (*this);
			};

			MapIterator operator++(int)
			{
				MapIterator	tmp(*this);

				++(*this);
				return (tmp);
			};

			MapIterator &operator--(void)
			{
				node_type	*child;

				if (this->m_node->m_left != NULL)
					this->m_node = SeekRight(this->m_node->m_left);
				else
				{
					child = this->m_node;
					this->m_node = this->m_node->m_parent;
					while (this->m_node && child == this->m_node->m_left)
					{
						child = this->m_node;
						this->m_node = this->m_node->m_parent;
					}
				}
				return (*this);
			};

			MapIterator operator--(int)
			{
				MapIterator	tmp(*this);

				--(*this);
				return (tmp);
			};

			reference operator*(void) const
			{
				return (this->m_node->m_data);
			};

			pointer operator->(void) const
			{
				return (&this->operator*());
			};

			operator MapIterator<const T, node_type>(void) const 
			{
				return (MapIterator<const T, node_type>(this->m_node));
			};

	};

}

#endif
