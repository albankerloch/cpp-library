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

			void ft_init_tree(void)
			{
				this->m_root = node_allocator.allocate(1);
				node_allocator.construct(m_root, ft::TreeNode<value_type>());
			};

			node_pointer ft_create_node(node_pointer parent, const value_type & data)
			{
				node_pointer new_node;
				
				new_node = node_allocator.allocate(1);
				node_allocator.construct(new_node, ft::TreeNode<value_type>(data));
				new_node->m_parent = parent;
				this->m_size = this->m_size  + 1;
				std::cout << " node created " << new_node->m_data.first << " - " << new_node->m_data.second << " - " << new_node->m_height << " - " << std::endl;
				return (new_node);
			};


			node_pointer ft_right_rotate(node_pointer y) 
			{
				node_pointer x = y->m_left;
				node_pointer T2 = x->m_right;

				x->m_right = y;
				y->m_parent = x;
				x->m_parent = NULL;
				y->m_left = T2;
				if (T2)
					T2->m_parent = y;
				y->m_height = std::max(get_height(y->m_left), get_height(y->m_right)) + 1;
				x->m_height = std::max(get_height(x->m_left), get_height(x->m_right)) + 1;
				return (x);
			}

			node_pointer ft_left_rotate(node_pointer x) 
			{
				node_pointer y = x->m_right;
				node_pointer T2 = y->m_left;
				
				y->m_left = x;
				x->m_parent = y;
				y->m_parent = NULL;
				x->m_right = T2;
				if (T2)
					T2->m_parent = x;
				x->m_height = std::max(get_height(x->m_left), get_height(x->m_right)) + 1;
				y->m_height = std::max(get_height(y->m_left), get_height(y->m_right)) + 1;
				return (y);
			}

			node_pointer ft_insert_node(node_pointer node, node_pointer parent, value_type value)
			{
				int balance_factor;

				if (node == NULL)
					return (ft_create_node(parent, value));
				if (this->m_compare(value.first, node->m_data.first))
				{
					node->m_left = ft_insert_node(node->m_left, node, value);
				}
				else if (this->m_compare(node->m_data.first, value.first))
					node->m_right = ft_insert_node(node->m_right, node, value);
				else
					return (node);
				
				node->m_height = 1 + std::max(get_height(node->m_left), get_height(node->m_right));
				balance_factor = get_balance_factor(node);

				if (balance_factor > 1) 
				{
					if (this->m_compare(value.first, node->m_left->m_data.first))	
					{
						return (ft_right_rotate(node));
					} 
					else if (this->m_compare(node->m_left->m_data.first, value.first))	
					{
						std::cout << "test" << std::endl;
						node->m_left = ft_left_rotate(node->m_left);
						return (ft_right_rotate(node));
					}
				}
				if (balance_factor < -1) 
				{
					if (this->m_compare(value.first, node->m_left->m_data.first))
					{
						return (ft_left_rotate(node));
					} 
					else if (this->m_compare(node->m_left->m_data.first, value.first))
					{
						node->m_right = ft_right_rotate(node->m_right);
						return (ft_left_rotate(node));
					}
				}
				return (node);								
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
					if (root->m_parent)
						std::cout << root->m_data.first << " | " << root->m_data.second << " | " << root->m_height << " << " << root->m_parent->m_data.first << std::endl;
					else
						std::cout << root->m_data.first << " | " << root->m_data.second << " | " << root->m_height << std::endl;
					ft_print_tree(root->m_left, indent, false);
					ft_print_tree(root->m_right, indent, true);
				}
			};

			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : m_root(), m_compare(comp), m_allocator(alloc), m_size(0) 
			{
				this->m_root = NULL;
			};

			template <class Ite>
			map(Ite first, Ite last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type(), typename ft::enable_if<!ft::is_integral_type<Ite>::value, Ite>::type* = NULL) : m_root(), m_compare(comp), m_allocator(alloc), m_size(0) 
			{
				this->m_root = NULL;
				this->insert(first, last);
			};

			~map()
			{
//				this->clear();
			};

			allocator_type get_allocator() const
			{
				return (this->m_allocator);
			};

			iterator begin() 
			{
				return (iterator(SeekLeft(this->m_root)));
			};

			const_iterator begin() const 
			{
				return (const_iterator(SeekLeft(this->m_root)));
			};

			iterator end() 
			{
				return (iterator(SeekRight(this->m_root)));
			};

			const_iterator end() const 
			{
				return (const_iterator(SeekRight(this->m_root)));
			};

			reverse_iterator rbegin() 
			{
				return (reverse_iterator(this->end()));
			};

			const_reverse_iterator rbegin() const 
			{
				return (const_reverse_iterator(this->end()));
			};

			reverse_iterator rend() 
			{
				return (reverse_iterator(this->begin()));
			};

			const_reverse_iterator rend() const 
			{
				return (const_reverse_iterator(this->begin()));
			};

			mapped_type & operator[](const key_type &key) 
			{
				return (this->insert(value_type(key, mapped_type())).first->second);
			};

			size_type size() const
			{
				return (this->m_size);
			};

			template <class Ite>
			void insert(Ite first, Ite last) 
			{
				bool is_valid;

				if (!(is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<Ite>::iterator_category>::value))
					throw (ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<Ite>::iterator_category >::type>());
				while (first != last)
				{
					this->insert(*first);
					std::cout << "test1 " << (*first).first << " " << (*first).second  << std::endl;
					first++;
					std::cout << "test2 " << (*first).first << " " << (*first).second  << std::endl;
				}
			};
			
			ft::pair<iterator, bool> insert(const value_type &value) 
			{
				ft::pair<iterator, bool> ret;

				ret.second = true;
				this->m_root = this->ft_insert_node(this->m_root, NULL, value);
				ret.first = iterator(this->m_root);
				return (ret);
			};
	
	};

} 

#endif