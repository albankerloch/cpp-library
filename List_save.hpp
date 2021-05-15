#ifndef DEF_LIST_HPP
# define DEF_LIST_HPP

# include "Algo.hpp"
# include "List_Iterator.hpp"
# include "Node.hpp"
# include "Reverse_Iterator.hpp"
# include <iostream>

namespace ft 
{
    template < class T, class Alloc = std::allocator<T> > 
    class list
    {
        public:

		    typedef T	    							    	    value_type;
            typedef Alloc   	    					        	allocator_type;
            typedef typename allocator_type::reference            reference;
            typedef typename allocator_type::const_reference       const_reference;
            typedef typename allocator_type::pointer	        	pointer;
            typedef typename allocator_type::const_pointer      	const_pointer;
            typedef Node<value_type>                                node_type;
            typedef ListIterator<value_type>           	            iterator;/*
            typedef ListIterator<value_type const>                  const_iterator;
            typedef ReverseIterator<iterator>           	    	reverse_iterator;
            typedef ReverseIterator<const_iterator>             	const_reverse_iterator;*/
            typedef std::ptrdiff_t							        difference_type;
            typedef size_t 								    	    size_type;

        private:

            allocator_type	m_allocator;
			Node<T>	        *m_last_node;
           
            typedef typename allocator_type::template rebind< Node<T> >::other node_allocator;
			typedef typename node_allocator::pointer	node_pointer;

			node_allocator	m_node_allocator;

        public:

            explicit list (const allocator_type& alloc = allocator_type()) : m_allocator(alloc)
            {
                m_last_node = m_node_allocator.allocate(1);
				m_node_allocator.construct(m_last_node, Node<T>());
				m_last_node->m_previous = m_last_node;
				m_last_node->m_next = m_last_node;
            }

            iterator begin(void) 
            {
		        return (iterator(this->m_last_node->m_next));
	        }

            iterator end(void) 
            {
		        return (iterator(this->m_last_node));
	        }

            size_type size() const 
            {
                size_t      i;
                iterator    it;

                if (!(this->begin()))
                    return (0);
                it = this->begin() + 1;
                i = 1;
                while (it != this->begin())
                    it++;
			    return (i);
		    }

            /*explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : m_allocator(alloc)
            {
                m_last_node = m_node_allocator.allocate(1);
				m_node_allocator.construct(m_last_node, Node<T>());
				m_last_node->prev = m_last_node;
				m_last_node->next = m_last_node;
            }*/

           /* explicit list (const allocator_type & alloc = allocator_type()): m_allocator(alloc), m_array(0), m_capacity(0), m_size(0) {}

            explicit list (size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type()): m_allocator(alloc), m_capacity(n), m_size(n)
            {
                size_type i;

                this->m_array = m_allocator.allocate(n);
			    i = 0;
                while(i < n)
                {
                    m_allocator.construct(&this->m_array[i], val);
                    i++;
                }
            }

            explicit list(iterator first, iterator last): m_array(0), m_capacity(0), m_size(0) 
            {
                this->assign(first, last);
            }

            list (const list  & list_to_copy) : m_allocator(list_to_copy.m_allocator), m_array(0), m_capacity(0), m_size(0)
            {
                *this = list_to_copy;
            }

            ~list() 
            {
                this->clear();
                m_allocator.deallocate(this->m_array, this->m_capacity);
            }

            list & operator=(const list  & list_to_copy) 
            {
                size_t i;

                i = 0;
                while (i < list_to_copy.m_size)
                {
                    this->push_back(list_to_copy.m_array[i]);
                    i++;
                }
                return *this;
		    }
                    
            reference operator[](size_type idx) 
            {
                return (this->m_array[idx]);
            }

            const_reference operator[](size_type idx) const 
            {
                return (this->m_array[idx]);
            }

            reference at(size_type idx) 
            {
                if (idx >= this->m_size)
                    throw std::out_of_range("At : index out of range");
                return (this->m_array[idx]);
            }

            const_reference at(size_type idx) const 
            {
                if (idx >= this->m_size)
                    throw std::out_of_range("At : index out of range");
                return (this->m_array[idx]);
            }

            reference front(void) 
            {
                return (this->m_array[0]);
            }

            const_reference front(void) const 
            {
                return (this->m_array[0]);
            }

            reference back(void) 
            {
                return (this->m_array[this->m_size - 1]);
            }

            const_reference back(void) const 
            {
                return (this->m_array[this->m_size - 1]);
            }


            bool empty() const
            {
                if (this->m_size == 0)
                    return (true);
                return (false);
            }

            size_type max_size() const 
            {
			    return (this->m_allocator.max_size());
		    }

            

            const_iterator begin(void) const
            {
		        return (const_iterator(this->m_array));
	        }

            reverse_iterator rbegin(void) 
            {
		        return (reverse_iterator(&(this->m_array[m_size])));
	        }

            const_reverse_iterator rbegin(void) const
            {
		        return (const_reverse_iterator(&(this->m_array[m_size])));
	        }

            iterator end(void) 
            {
		        return (iterator(&(this->m_array[m_size])));
	        }           

            const_iterator end(void) const
            {
		        return (const_iterator(&(this->m_array[m_size])));
	        }

            reverse_iterator rend(void)
            {
		        return (reverse_iterator(this->m_array));
	        }           

            const_reverse_iterator rend(void) const
            {
		        return (const_reverse_iterator(this->m_array));
	        }

            void clear()
            {
                while(this->m_size > 0)
                {
                    m_allocator.destroy(&this->m_array[m_size]);
                    this->m_size--;
                }
            }

            void reserve(size_t length)
            {
                size_type i;
                value_type *tmp;

                if (length > this->max_size())
					throw (std::length_error("list : max size reached during reserve"));
                else if (length > this->m_capacity)
                {
                    tmp = this->m_allocator.allocate(length);
                    if (this->m_array)
                    {
                        for (i = 0; i < m_size; i++)
                        {
                            m_allocator.construct(&tmp[i], this->m_array[i]);
                            m_allocator.destroy(&this->m_array[i]);
                        }
                        m_allocator.deallocate(this->m_array, this->m_capacity);
                    }
                    this->m_array = tmp;
                    this->m_capacity = length;
                }
            }

            void assign(iterator first, iterator last) 
            {
                size_t length;
                size_t i;
                
                length = last - first;
                if (length > this->m_capacity)
                    this->reserve(length);
                i = 0;
                while (first != last) 
                {
                    m_allocator.construct(&this->m_array[i], *first);
                    first++;
                    i++;
                }
                this->m_size = length;
            }

            void assign(size_type length, const_reference value) 
            {
                size_t i;

                if (length > this->m_capacity)
                    this->reserve(length);
                i = 0;
                while (i < length) 
                {
                    m_allocator.construct(&this->m_array[i], value);
                    ++i;
                }
                this->m_size = length;
            }

            void push_back(value_type value)
            {
                if (this->m_size == this->m_capacity)
                    this->reserve(this->m_capacity + 1);
                m_allocator.construct(&m_array[this->m_size], value);
                this->m_size++;
            }

            void pop_back(void)
            {
                m_allocator.destroy(this->m_array + this->m_size);
                this->m_size--;
            }

            void resize (size_type length, value_type value = value_type())
            {
                size_t i;

                if (length < this->m_size)
                {
                    i = length;
                    while (i < this->m_size)
                    {
                        this->m_allocator.destroy(&this->m_array[i]);
                        i++;
                    }
                    this->m_size = length;
                }
                else if (length > this->m_size)
                {
                    if (length > this->m_capacity)
                        this->reserve(length);
                    i = this->m_size;
                    while (i < length)
                    {
                        this->m_allocator.construct(&this->m_array[i], value);
                        i++;
                    }
                    this->m_size = length;
                }
            }

            iterator erase (iterator position)
            {
                iterator save_position(position);

                while (position != this->end() - 1)
                {
                    this->m_allocator.construct(&(*position), *(position + 1));
                    position++;
                }
                this->m_size--;
                return (save_position);
            }

            iterator erase(iterator first, iterator last)
            {
                iterator save_first(first);
                size_t n;

                n = last - first;
                while (last != this->end())
                {
                    this->m_allocator.construct(&(*first), *(last));
                    first++;
                    last++;
                }
                this->m_size = this->m_size - n;
                return (save_first);
            }

            void print()
            {
                typename ft::list<T>::iterator it;
                size_t i;

                it = this->begin();
                i = 0;
                while(it != this->end())
                {
                    std::cout << " SHOW -> at pos "<< i++ << " got " << *it << std::endl;
                    it++;
                }
            }
            
            iterator insert (iterator position, const value_type& value)
            {
                difference_type ret;
                
                ret = position - this->begin();
                this->insert(position, 1, value);
                return (iterator(this->begin() + ret));
            }          

            void insert (iterator position, size_type n, const value_type& value)
            {
                size_t begin_insert;
                size_t i;

                begin_insert = position - this->begin();
                if (this->m_size + n > this->capacity())
                    this->reserve(this->m_size + n);
                this->m_size = this->m_size + n;
                i = this->size() - 1;
                while(i != begin_insert + n - 1)
                {
                    m_allocator.construct(&this->m_array[i], this->m_array[i - n]);
                    i--;
                }
                while(i != begin_insert)
                {
                    m_allocator.destroy(&this->m_array[i]);
                    m_allocator.construct(&this->m_array[i], value);
                    i--;
                }
                m_allocator.destroy(&this->m_array[i]);
                m_allocator.construct(&this->m_array[i], value);
            }

            void insert (iterator position, iterator first, iterator last)
            {
                iterator it;
                size_t i;
                size_t n;
                size_t begin_insert;

                n = last - first;
                begin_insert = position - this->begin();
                if (this->m_size + n > this->capacity())
                    this->reserve(this->m_size + n);
                this->m_size = this->m_size + n;
                i = this->size() - 1;
                while(i != begin_insert + n - 1)
                {
                    m_allocator.construct(&this->m_array[i], this->m_array[i - n]);
                    i--;
                }
                while(i != begin_insert)
                {
                    m_allocator.destroy(&this->m_array[i]);
                    m_allocator.construct(&this->m_array[i], *(last - 1));
                    last--;
                    i--;
                }
                m_allocator.destroy(&this->m_array[i]);
                m_allocator.construct(&this->m_array[i], *(last - 1));
            }

            void swap(list & x)
            {
                T	*temp_array;
                size_t temp_size;
                size_t temp_capacity;
                allocator_type	temp_allocator;

                temp_array = x.m_array;
                temp_size = x.m_size;
                temp_capacity = x.m_capacity;
                temp_allocator = x.m_allocator;

                x.m_array = this->m_array;
                x.m_size = this->m_size;
                x.m_capacity = this->m_capacity;
                x.m_allocator = this->m_allocator;

                this->m_array = temp_array;
                this->m_size = temp_size;
                this->m_capacity = temp_capacity;
                this->m_allocator = temp_allocator;
            }
            
    };

    template<typename T>
    void swap(list<T> &x, list<T> &y) 
    {
        x.swap(y);
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
        return (!(lhs < rhs));*/
    };
}

#endif