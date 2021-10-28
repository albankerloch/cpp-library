#ifndef DEF_MAP_HPP
# define DEF_MAP_HPP

# include "Utils.hpp"
# include "Map_Iterator.hpp"
# include "Reverse_Iterator.hpp"
# include "TreeNode.hpp"

namespace ft 
{

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map 
	{
		public:

			typedef Key																key_type;
			typedef T																mapped_type;
			typedef ft::pair<const key_type, mapped_type>							value_type;
			typedef Compare															key_compare;
			typedef Alloc															allocator_type;
			typedef typename allocator_type::reference								reference;
			typedef typename allocator_type::const_reference						const_reference;
			typedef typename allocator_type::pointer								pointer;
			typedef typename allocator_type::const_pointer							const_pointer;
			typedef ptrdiff_t														difference_type;
			typedef size_t															size_type;
			typedef ft::MapIterator<value_type, ft::TreeNode<value_type> >			iterator;
			typedef ft::MapIterator<const value_type, ft::TreeNode<value_type> >	const_iterator;
			typedef ft::reverse_iterator<iterator>									reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;

			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map;

				protected :

					Compare comp;

					value_compare (Compare compare) : comp(compare) 
					{
					};

				public:

					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					
					bool operator() (const value_type& value1, const value_type& value2) const
					{
						return (comp(value1.first, value2.first));
					};
			};

		private:

			typedef typename allocator_type::template rebind<ft::TreeNode<value_type> >::other	type_node_allocator;
			typedef typename type_node_allocator::pointer													node_pointer;
			type_node_allocator																				node_allocator;
			
			node_pointer																					m_root;
			key_compare																						m_compare;
			allocator_type																					m_allocator;
			size_type																						m_size;
			node_pointer																					m_last_node;

			void ft_init_tree(void)
			{
				this->m_last_node = node_allocator.allocate(1);
				node_allocator.construct(m_last_node, ft::TreeNode<value_type>());
			};

			node_pointer ft_create_node(const value_type & data)
			{
				node_pointer new_node;
				
				new_node = node_allocator.allocate(1);
				node_allocator.construct(new_node, ft::TreeNode<value_type>(data));
				this->m_size = this->m_size  + 1;
				return (new_node);
			};

			void ft_delete_node(node_pointer node)
			{
				ft_disconnect(node);
				this->m_size = this->m_size  - 1;
				node_allocator.destroy(node);
				node_allocator.deallocate(node, 1);
			};
		
		public:

			void print_tree()
			{
				std::string indent;

				ft_print_tree(this->m_root, indent, true);
			};

			void ft_print_tree(node_pointer root, std::string indent, bool last) 
			{
				if (root != NULL) 
				{
					std::cout << indent;
					if (last) 
					{
						std::cout << "R---- ";
						indent += "   ";
					} 
					else 
					{
						std::cout << "L---- ";
						indent += "|  ";
					}
					std::cout << root->m_data.first << std::endl;
					ft_print_tree(root->m_left, indent, false);
					ft_print_tree(root->m_right, indent, true);
				}
			};

			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : m_root(), m_compare(comp), m_allocator(alloc), m_size(0) 
			{
				this->ft_init_tree();
			};

			~map()
			{
//				this->clear();
				node_allocator.destroy(this->m_last_node);
				node_allocator.deallocate(this->m_last_node, 1);
			};



			size_type size() const
			{
				return (this->m_size);
			};
	
	};

} 

#endif