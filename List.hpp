#ifndef LIST_HPP
#define LIST_HPP

# include "List_Iterator.hpp"
# include "Reverse_Iterator.hpp"
# include "Node.hpp"
# include <cstring>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> > 
	class list
	{
		public :

			typedef T	    							    			value_type;
            typedef Alloc   	    					     		  	allocator_type;
            typedef typename allocator_type::reference        		  	reference;
            typedef typename allocator_type::const_reference			const_reference;
            typedef typename allocator_type::pointer	     		 	pointer;
            typedef typename allocator_type::const_pointer   		   	const_pointer;
            typedef Node<value_type>                         	 	  	node_type;
            typedef List_iterator<value_type, node_type>				iterator;
            typedef List_iterator<value_type const, node_type const>	const_iterator;
            typedef ReverseIterator<iterator>           				reverse_iterator;
            typedef ReverseIterator<const_iterator>    	    		    const_reverse_iterator;
            typedef std::ptrdiff_t									    difference_type;
            typedef size_t 								  			  	size_type;

		private :

			allocator_type 		m_allocator;
			Node<T>				*m_last_node;
			size_t				m_size;

			typedef typename allocator_type::template rebind<Node<T> >::other	type_node_allocator;
			typedef typename type_node_allocator::pointer						node_pointer;
			type_node_allocator													node_allocator;

			void ft_init_node(void)
			{
				this->m_last_node = node_allocator.allocate(1);
				node_allocator.construct(m_last_node, Node<T>());
				this->m_last_node->m_previous = this->m_last_node;
				this->m_last_node->m_next = this->m_last_node;
				this->m_size = 0;
			}

			node_pointer ft_add_node(const T & data, Node<T> * m_previous = u_nullptr, Node<T> * m_next = u_nullptr)
			{
				node_pointer new_node = node_allocator.allocate(1);
				node_allocator.construct(new_node, Node<T>(data));
				new_node->m_previous = m_previous;
				new_node->m_next = m_next;
				this->m_size = this->m_size  + 1;
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
				this->m_size = this->m_size  - 1;
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
				return (this->m_size);
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
				if (this->m_size == 0)
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

			void push_front(const value_type& val)
			{
				this->insert(this->m_last_node->m_next, val);
			}

			void push_back(const value_type& val)
			{
				this->insert(this->m_last_node, val);
			}

			void assign (size_type n, const value_type& val)
			{
				this->clear();
				while (n--)
					this->push_front(val);
			}

 			void assign (iterator first, iterator last)
			{
				this->clear();
				while (first != last)
				{
					this->push_back(*first);
					first++;
				}
			}
 			void assign (const_iterator const first, const_iterator const last)
			{
				this->clear();
				while (first != last)
				{
					this->push_back(*first);
					first++;
				}
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

			void resize (size_type length, value_type val = value_type())
			{
				size_t i;

                i = this->m_size;
                if (length < this->m_size)
                {
                    while (i > length)
                    {
                        this->pop_back();
                        i--;
                    }
                }
                else if (length > this->m_size)
                {
                    while (i < length)
                    {
                        this->push_back(val);
                        i++;
                    }
                }
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
				size_t			temp_size;

                temp_last_node = x.m_last_node;
                temp_allocator = x.m_allocator;
                temp_size = x.m_size;

                x.m_last_node = this->m_last_node;
                x.m_allocator = this->m_allocator;
                x.m_size = this->m_size;

                this->m_last_node = temp_last_node;
                this->m_allocator = temp_allocator;
                this->m_size = temp_size;
			}

			void splice (iterator position, list& x)
			{
				this->insert(position, x.begin(), x.end());
				x.clear();
			}

			void splice (iterator position, list& x, iterator i)
			{
				x.ft_disconnect(i);
				this->insert(position, i);
			}

			void splice (iterator position, list& x, iterator first, iterator last)
			{
				this->insert(position, first, last);
				x.erase(first, last);
			}

			void remove (const value_type& val)
			{
				iterator it;

				it = this->begin();
				while (it != this->end())
				{
					if (*it == val)
						ft_delete(it);
					it++;
				}
			}

			template <class Predicate>
			void remove_if (Predicate pred)
			{
				iterator it;

				it = this->begin();
				while (it != this->end())
				{
					if (pred(*it))	
						ft_delete(it);
					it++;
				}
			}

			void unique()
			{
				iterator prev;
				iterator it;

				prev = this->begin();
				it = this->begin()++;
				while (it != this->end())
				{
					if (*it == *prev)	
						ft_delete(it);
					it++;
					prev++;
				}
			}

			template <class BinaryPredicate>
  			void unique (BinaryPredicate binary_pred)
			{
				iterator prev;
				iterator it;

				prev = this->begin();
				it = this->begin()++;
				while (it != this->end())
				{
					if (binary_pred(*it, *prev))
						ft_delete(it);
					it++;
					prev++;
				}
			}

			void merge (list& x)
			{
				this->merge(x, &ft::less<value_type>)
			}

			template <class Compare>
			void merge (list& x, Compare comp)
			{
				iterator	itx;
				iterator	it;

				if (&x == this)
					return;
				itx = x.begin();
				itx = this->begin();
				while (itx != x.end())
				{
					while (comp(*it, *itx))
						it++;
					itx.p->m_previous->next = it.p->next;
					itx.p->m_previous = it.p
					it.p->m_next->m_previous = itx.p;
					it.p->m_next = itx.p;
					itx.p->m_next->m_previous = itx.p->m_previous;
					itx.p->m_next = it.p->next;
					itx++;
				}
			}

			void sort()
			{
				this->merge(&ft::less<value_type>)
			}

			template <class Compare>
			void sort (Compare comp)
			{
				iterator	it;

				if (this->empty())
					return;
				it = this->begin();
				while (it != this->end())
				{
					it = this->begin();
					while(comp(*it, *it(it + 1))) 
						it++;
					if (it != this->end())
						swap(it, it + 1);
				}
			}

			void reverse()
			{
				Node<value_type>	*tmp;
				iterator			it;

				if (this->empty())
					return;
				it = this->begin();
				while (it != this->end())
				{
					tmp = it->previous;
					it->previous = it->next;
					it->next = tmp;
					it++;
				}
			}
		};

	 template <class T, class Alloc>
    bool operator== (const ft::list<T, Alloc>& lhs, const ft::list<T, Alloc>& rhs)
    {
        typename ft::list<T>::const_iterator it_lhs;
        typename ft::list<T>::const_iterator it_rhs;

        if (lhs.size() != rhs.size())
            return (false);
        it_lhs = lhs.begin();
        it_rhs = rhs.begin();
        while (it_lhs != lhs.end())
        {
            if (it_rhs == rhs.end() || *it_lhs != *it_rhs)
                return (false);
            it_lhs++;
            it_rhs++;
        }
        return (true);
    };

    template <class T, class Alloc>
    bool operator!= (const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
    {
        return (!(lhs == rhs));
    };

    template <class T, class Alloc>
    bool operator<  (const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
    {
       	typename ft::list<T>::const_iterator it_lhs;
        typename ft::list<T>::const_iterator it_rhs;

        if (lhs == rhs)
            return (false);
        it_lhs = lhs.begin();
        it_rhs = rhs.begin();
        while (it_lhs != lhs.end() && it_rhs != rhs.end() && *it_lhs == *it_rhs)
        {
            it_lhs++;
            it_rhs++;
        }
        if (it_rhs != rhs.end())
            return (true);
        return (false);
    };

    template <class T, class Alloc>
    bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
    {
        if (lhs == rhs)
            return (true);
        return (lhs < rhs);
    };

    template <class T, class Alloc>
    bool operator>(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
    {
        if (lhs == rhs)
            return (false);
        return (!(lhs < rhs));
    };

    template <class T, class Alloc>
    bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
    {
        if (lhs == rhs)
            return (true);
        return (!(lhs < rhs));
    };

	template<typename T>
    void swap(list<T> &x, list<T> &y) 
    {
        x.swap(y);
    };
}


#endif