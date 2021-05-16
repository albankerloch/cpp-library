#ifndef LIST_HPP
#define LIST_HPP

# include "List_Iterator.hpp"
# include "Reverse_Iterator.hpp"
# include "Node.hpp"
# include "utils.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> > 
	class list
	{
		public :

			typedef T	    							    	value_type;
            typedef Alloc   	    					        allocator_type;
            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::const_reference	const_reference;
            typedef typename allocator_type::pointer	        pointer;
            typedef typename allocator_type::const_pointer      const_pointer;
            typedef Node<value_type>                            node_type;
            typedef List_iterator<value_type, node_type>		iterator;
            typedef List_iterator<value_type const, node_type const> 						const_iterator;
            typedef ReverseIterator<iterator>           		reverse_iterator;
            typedef ReverseIterator<const_iterator>    	        const_reverse_iterator;
            typedef std::ptrdiff_t							    difference_type;
            typedef size_t 								    	size_type;

		private :

			allocator_type 		m_allocator;
			Node<T>				*m_last_node;

			typedef typename allocator_type::template 		rebind<Node<T> >::other type_node_allocator;
			typedef typename type_node_allocator::pointer	node_pointer;
			type_node_allocator								node_allocator;

			void ft_init_node(void)
			{
				this->m_last_node = node_allocator.allocate(1);
				node_allocator.construct(m_last_node, Node<T>(0));
				this->m_last_node->m_previous = this->m_last_node;
				this->m_last_node->m_next = this->m_last_node;
			}

			node_pointer ft_add_node(const T & data, Node<T> * m_previous = NULL, Node<T> * m_next = NULL)
			{
				node_pointer new_node = node_allocator.allocate(1);
				node_allocator.construct(new_node, Node<T>(data));
				new_node->m_previous = m_previous;
				new_node->m_next = m_next;
				m_last_node->data++;
				return (new_node);
			}

			void ft_disconnect(Node<T> *node)
			{
				if (node->m_previous == m_last_node)
					m_last_node->m_next = node->m_next;
				else
					node->m_previous->m_next = node->m_next;
				if (node->m_next == m_last_node)
					m_last_node->m_previous = node->m_previous;
				else
					node->m_next->m_previous = node->m_previous;	
			}

			void ft_delete(Node<T> *node)
			{
				ft_disconnect(node);
				m_last_node->data--;
				node_allocator.destroy(node);
				node_allocator.deallocate(node, 1);
			}
		
		public :
		
			explicit list (const allocator_type& alloc = allocator_type()) : m_allocator(alloc)
			{
				this->ft_init_node();
			}

			explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : m_allocator(alloc)
			{
				this->ft_init_node();
				this->insert(this->begin(), n, val);
			}

			list (iterator first, iterator last, const allocator_type& alloc = allocator_type()) : m_allocator(alloc)
			{
				this->ft_init_node();
				this->insert(this->begin(), first, last);
			}

			list (const list & x) : m_allocator(x.m_allocator)
			{
				const_iterator begin;
				const_iterator end ;
				
				begin = x.begin();
				end = x.end();
				this->ft_init_node();
				while (begin != end)
				{
					this->insert(this->begin(), begin.p->data);
					begin++;
				}
			}
		
			~list()
			{
				this->clear();
				node_allocator.destroy(m_last_node);
				node_allocator.deallocate(m_last_node, 1);
			}

			list& operator= (const list & x)
			{
				const_iterator begin;
				const_iterator end ;
				
				begin = x.begin();
				end = x.end();
				if (&x == this)
					return (*this);
				this->clear();
				while (begin != end)
				{
					this->insert(this->begin(), begin.p->data);
					begin++;
				}
				return (*this);
			}
		
			iterator begin() 
			{ 
				return (iterator(m_last_node->m_next)); 
			}

			const_iterator begin() const 
			{
				return (const_iterator(m_last_node->m_next)); 
			}

			reverse_iterator rbegin() 
			{ 
				return (reverse_iterator(m_last_node)); 
			}

			const_reverse_iterator rbegin() const 
			{
				return (const_reverse_iterator(m_last_node)); 
			}

			iterator end()
			{ 
				return (iterator(m_last_node)); 
			}

			const_iterator end() const 
			{ 
				return (const_iterator(m_last_node)); 
			}

			reverse_iterator rend()
			{ 
				return (reverse_iterator(m_last_node->m_next)); 
			}

			const_reverse_iterator rend() const 
			{
				return (const_reverse_iterator(m_last_node->m_next)); 
			}

			size_type size() const 
			{ 
				return (this->m_last_node->data);
			}

			reference front()
			{ 
				return (m_last_node->m_next->data); 
			}

			reference back()
			{ 
				return (reference(m_last_node->m_previous->data));
			}

			bool empty() const 
            {
				if (m_last_node->data == 0)
					return (true);
				return (false);
		    }

			size_type max_size() const 
            {
			    return (type_node_allocator().max_size());
		    }

			iterator insert (iterator position, const value_type & val)
			{ 
				node_pointer new_node;

				new_node = ft_add_node(val);
				new_node->m_next = position.p;
				if (position.p->m_previous == this->m_last_node)
				{
					new_node->m_previous = this->m_last_node;
					this->m_last_node->m_next = new_node;
				}
				else
				{
					new_node->m_previous = position.p->m_previous;
					position.p->m_previous->m_next = new_node;
				}
				position.p->m_previous = new_node;
				return (iterator(position.p->m_previous));
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				while (n--)
					this->insert(position, val);
			}
	
			void insert (iterator position, iterator first, iterator last)
			{
				while (first != last)
				{
					this->insert(position, *first);
					first++;
				}
			}

			void push_front (const value_type& val)
			{
				this->insert(this->m_last_node->m_next, val);
			}

			void push_back (const value_type& val)
			{
				this->insert(this->m_last_node, val);
			}

			void clear()
			{
				Node<T> *tmp = m_last_node->m_next;
				Node<T> *m_next_tmp;
				while (tmp != m_last_node)
				{
					m_next_tmp = tmp->m_next;
					ft_delete(tmp);
					tmp = m_next_tmp;
				}
			}

			iterator erase (iterator position)
			{
				iterator tmp;

				tmp = position;
				tmp++;
				ft_delete(position.p);
				return (tmp);		
			}

			iterator erase (iterator first, iterator last)
			{
				iterator tmp;

				while(first != last)
				{
					tmp = first;
					tmp++;
					ft_delete(first.p);
					first = tmp;
				}
				return (first);
			}

			void pop_front()
			{
				ft_delete(m_last_node->m_next);
			}	

			void pop_back()
			{
				ft_delete(m_last_node->m_previous);
			}

			void swap (list& x)
			{

				Node<T>			*temp_last_node;
                allocator_type	temp_allocator;

                temp_last_node = x.m_last_node;
                temp_allocator = x.m_allocator;

                x.m_last_node = this->m_last_node;
                x.m_allocator = this->m_allocator;

                this->m_last_node = temp_last_node;
                this->m_allocator = temp_allocator;
			}
	};

	template<typename T>
    void swap(list<T> &x, list<T> &y) 
    {
        x.swap(y);
    };
}


#endif