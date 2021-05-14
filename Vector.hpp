#ifndef DEF_VECTOR_HPP
# define DEF_VECTOR_HPP

# include "Vector_Iterator.hpp"
# include "Reverse_Iterator.hpp"
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
            typedef VectorIterator<value_type const>			const_iterator;
            typedef ReverseIterator<iterator>           		reverse_iterator;
            typedef ReverseIterator<const_iterator>    	const_reverse_iterator;
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

            explicit Vector(iterator first, iterator last): m_array(nullptr), m_capacity(0), m_size(0) 
            {
                this->assign(first, last);
            }

            Vector (const Vector  & Vector_to_copy) : m_allocator(Vector_to_copy.m_allocator), m_array(nullptr), m_capacity(0), m_size(0)
            {
                *this = Vector_to_copy;
            }

            ~Vector() 
            {
                this->clear();
                m_allocator.deallocate(this->m_array, this->m_capacity);
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

            size_type size() const 
            {
			    return (this->m_size);
		    }

            size_type capacity() const 
            {
			    return (this->m_capacity);
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

            iterator begin(void) 
            {
		        return (iterator(this->m_array));
	        }

            const_iterator begin(void) const
            {
		        return (const_iterator(this->m_array));
	        }

            reverse_iterator rbegin(void) 
            {
		        return (reverse_iterator(this->m_array[m_size]));
	        }

            const_reverse_iterator rbegin(void) const
            {
		        return (const_reverse_iterator(this->m_array[m_size]));
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
		        return (reverse_iterator(&(this->m_array[m_size])));
	        }           

            const_reverse_iterator rend(void) const
            {
		        return (const_reverse_iterator(&(this->m_array[m_size])));
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
                    m_allocator.construct(m_array + i, value);
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
                m_allocator.destroy(&this->m_array + this->m_size);
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
                        this->m_allocator.construct(this->m_array + i, value);
                        i++;
                    }
                    this->m_size = length;
                }
            }

            iterator erase (iterator position)
            {
                iterator temp(position);

                temp++;
                return (this->erase(position, temp));
            }


            iterator erase(iterator first, iterator last)
            {
                size_t i;

                i = 0;
                while (first != last)
                {
                    this->m_allocator.destroy(first);
                    first++;
                    this->m_size--;
                    i++;
                }
                while (first != this->end())
                {
                    this->m_allocator.construct(first, first + i);
                    first++;
                    this->m_allocator.destroy(first);
                }
                first++;
                return (first);
            };

            iterator insert (iterator position, const value_type& value)
            {
                return (this->insert(position, 1, value));
            }

            void insert (iterator position, size_type n, const value_type& value)
            {
                iterator it;

                if (this->m_size + n > this->capacity)
                    this->reserve(this->m_size + n);
                it = this->end() + n;
                while(it != position + n)
                {
                    m_allocator.construct(it, it - n);
                    it--;
                }
                while(it != position)
                {
                    m_allocator.destroy(it);
                    m_allocator.construct(it, value);
                    it--;
                }
                return (position + n);
            }

            void insert (iterator position, iterator first, iterator last)
            {
                iterator it;
                size_t n;

                n = last - first;
                if (this->m_size + n > this->capacity)
                    this->reserve(this->m_size + n);
                it = this->end() + n;
                while(it != position + n)
                {
                    m_allocator.construct(it, it - n);
                    it--;
                }
                while(it != position)
                {
                    m_allocator.destroy(it);
                    m_allocator.construct(it, last);
                    last--;
                    it--;
                }
                return (first);
            }

            void swap(Vector & x)
            {
                iterator save_end(this->end());

                this->insert(this->end(), x->begin(), x->end());
                this->erase(x->begin(), x->end());
                this->insert(x->begin(), this->begin(), save_end);
                this->erase(this->begin(), save_end);              
            }
            
    };

    template<typename T>
    void swap(Vector<T> &x, Vector<T> &y) 
    {
        x.swap(y);
    };

    template <class T, class Alloc>
    bool operator== (const ft::Vector<T, Alloc>& lhs, const ft::Vector<T, Alloc>& rhs)
    {
        typename ft::Vector<T>::const_iterator it_lhs;
        typename ft::Vector<T>::const_iterator it_rhs;

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
    bool operator!= (const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs)
    {
        return (!(lhs == rhs));
    };

    template <class T, class Alloc>
    bool operator<  (const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs)
    {
       	typename ft::Vector<T>::const_iterator it_lhs;
        typename ft::Vector<T>::const_iterator it_rhs;

        if (lhs == rhs)
            return (false);
        it_lhs = lhs.begin();
        it_rhs = rhs.begin();
        while (it_lhs != lhs.end() && it_rhs != rhs.end() &&
                *it_lhs == *it_rhs)
        {
            it_lhs++;
            it_rhs++;
        }
        if (it_rhs != rhs.end())
            return (true);
        return (false);
    };

    template <class T, class Alloc>
    bool operator<= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
    {
        if (lhs == rhs)
            return (true);
        return (lhs < rhs);
    };

    template <class T, class Alloc>
    bool operator>(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
    {
        if (lhs == rhs)
            return (false);
        return (!(lhs < rhs));
    };

    template <class T, class Alloc>
    bool operator>= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
    {
        if (lhs == rhs)
            return (true);
        return (!(lhs < rhs));
    };
}

#endif