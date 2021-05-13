#ifndef DEF_VECTOR_HPP
# define DEF_VECTOR_HPP

# include "Vector_Iterator.hpp"
# include <iostream>

namespace ft 
{
    template <typename T, typename Alloc = std::allocator<T> >
    class Vector
    {
        public:

		    typedef T	    							    	value_type;
            typedef Alloc   	    					    	allocator_type;
            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::const_reference    const_reference;
            typedef typename allocator_type::pointer	    	pointer;
            typedef typename allocator_type::const_pointer    	const_pointer;
            typedef VectorIterator<value_type>          		iterator;
        /*    typedef ConstVectorIterator<value_type>			const_iterator;
            typedef ReverseVectorIterator<value_type>		reverse_iterator;
            typedef ConstReverseVectorIterator<value_type>	const_reverse_iterator;*/
            typedef std::ptrdiff_t							    difference_type;
            typedef size_t 									    size_type;

        private:

            allocator_type	m_allocator;
            T *      		m_array;
            size_type		m_capacity;
            size_type		m_size;

        public:

            explicit Vector (const allocator_type & alloc = allocator_type()): m_allocator(alloc), m_array(nullptr), m_capacity(0), m_size(0) 
            {}

            explicit Vector (size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type()): m_allocator(alloc), m_capacity(n), m_size(n)
            {
                size_type i;

                this->m_array = m_allocator.allocate(n);
			    i = 0;
                while(i < n)
                {
                    m_allocator.construct(m_array + i, val);
                    i++;
                }
            }

            Vector(iterator first, iterator last): m_array(nullptr), m_capacity(0), m_size(0) 
            {
                this->assign(first, last);
            }

            Vector (const Vector  & Vector_to_copy) : m_allocator(Vector_to_copy.m_allocator), m_array(nullptr), m_capacity(0), m_size(0)
            {
                *this = Vector_to_copy;
            }

            Vector & operator=(const Vector  & Vector_to_copy) 
            {
                size_t i;

                i = 0;
                while (i < Vector_to_copy.m_size)
                {
                    this->push_back(Vector_to_copy.m_array[i]);
                    i++;
                }
                return *this;
		    }

            ~Vector() 
            {
                this->clear();
                m_allocator.deallocate(this->m_array, this->m_capacity);
            }

            size_type size() const 
            {
			    return (this->m_size);
		    }

            size_type max_size() const 
            {
			    return (this->m_allocator.max_size());
		    }

            iterator begin(void) 
            {
		        return (iterator(this->m_array));
	        }

            iterator end(void) 
            {
		        return (iterator(&(this->m_array[m_size])));
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
					throw (std::length_error("Vector : max size reached during reserve"));
                else if (length > this->m_capacity)
                {
                    tmp = this->m_allocator.allocate(length);
                    if (this->m_array)
                    {
                        for (i = 0; i < m_size; i++)
                        {
                            m_allocator.construct(tmp + i, this->m_array[i]);
                            m_allocator.destroy(&this->m_array + i);
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
                    m_allocator.construct(m_array + i, *first);
                    ++first;
                    ++i;
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
                    m_allocator.construct(m_array + i, value);
                    ++i;
                }
                this->m_size = length;
            }

            void push_back(value_type value)
            {
                if (this->m_size == this->m_capacity)
                    this->reserve(1);
                m_allocator.construct(&m_array[this->m_size], value);
                this->m_size++;
            }
    };
}

#endif