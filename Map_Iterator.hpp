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
				if (this->m_node->m_right == NULL)
				{
					std::cout << "test NULL"  << std::endl;
					while(this->m_node->m_left)
					{
						std::cout << "this->m_node->m_left" << this->m_node->m_left->m_data.first << std::endl;
						if (this->m_node->m_left->m_right)
						{
							this->m_node = this->m_node->m_left->m_right;
							break;
						}
						this->m_node = this->m_node->m_left->m_right;
					}
				}
				else
				{
					std::cout << "test right"  << std::endl;
					this->m_node = this->m_node->m_right;
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

				if (this->m_node->left != NULL)
					this->m_node = SeekRight(this->m_node->left);
				else
				{
					child = this->m_node;
					this->m_node = this->m_node->parent;
					while (this->m_node && child == this->m_node->left)
					{
						child = this->m_node;
						this->m_node = this->m_node->parent;
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
