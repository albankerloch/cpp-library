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
            typedef std::ptrdiff_t							difference_type;
            typedef size_t 									size_type;

        private:

            allocator_type	m_allocator;
            T *      		m_array;
            size_type		m_capacity;
            size_type		m_size;

            void copy_construct(size_type idx, const_reference val)
            {
		        new(&this->m_array[idx]) value_type(val);
        	}

        public:

            explicit Vector (const allocator_type & alloc = allocator_type()): m_allocator(alloc), m_array(nullptr), m_capacity(0), m_size(0)
            {}

            explicit Vector (size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type()): m_allocator(alloc), m_capacity(n), m_size(n)
            {
                size_type i;

                this->m_array = new value_type[n]();
			    for (i = 0; i < n; i++)
				    this->m_array[i] = val;
            }

            Vector(iterator first, iterator last): m_array(nullptr), m_capacity(0), m_size(0) 
            {
                this->assign(first, last);
            }

            ~Vector() 
            {
                delete [] this->m_array;
            }

            size_type size() const 
            {
			    return (this->m_size);
		    }

            iterator begin(void) 
            {
		        return (iterator(this->m_array));
	        }

            iterator end(void) 
            {
		        return (iterator(&(this->m_array[m_size])));
	        }

            void reserve(size_t lenght)
            {
                value_type * tmp;
                size_type i;

                if (this->m_capacity < lenght)
                {
                    tmp = new value_type[lenght];
                    for (i = 0; i < lenght; i++)
				        tmp[i] = this->m_array[i];
                    delete [] this->m_array;
                    this->m_array = tmp;
                    this->m_capacity = lenght;
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
                while (first != last) {
                    if (i >= this->m_size)
                        this->copy_construct(i, *first);
                    else
                        this->m_container[i] = *first;
                    ++first;
                    ++i;
                }
                while (i < this->m_size)
                    this->m_container[i++].value_type::~value_type();
                this->m_size = length;
            }

      /*  public:
            Stack() : std::stack<T>() {};
            Stack(Stack const & Stack_to_copy) : std::stack<T>(Stack_to_copy) {};
            
            Stack &operator=(Stack const & Stack_to_copy) 
            {
                if (this != &Stack_to_copy)
                    this->c = Stack_to_copy.c;
                return (*this);
            };
            
            typedef typename std::stack<T>::container_type::iterator iterator;
            
            iterator begin() 
            {
                return (this->c.begin());
            };

            iterator end() 
            {
                return (this->c.end());
            };
            
            virtual ~Stack() {};
            */
    };
}

#endif