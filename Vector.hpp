#ifndef DEF_VECTOR_HPP
# define DEF_VECTOR_HPP

# include <iostream>

namespace ft 
{
    template <typename T, typename Alloc = std::allocator<T> >
    class Vector
    {
        public:

		    typedef T	    								value_type;
            typedef Alloc   	    						allocator_type;
            typedef T &										reference;
            typedef const T &								const_reference;
            typedef T * 									pointer;
            typedef const T	*								const_pointer;
           /* typedef VectorIterator<value_type>				iterator;
            typedef ConstVectorIterator<value_type>			const_iterator;
            typedef ReverseVectorIterator<value_type>		reverse_iterator;
            typedef ConstReverseVectorIterator<value_type>	const_reverse_iterator;*/
            typedef std::ptrdiff_t							difference_type;
            typedef size_t 									size_type;

        private:

            allocator_type	m_allocator;
            T *      		m_array;
            size_type		m_capacity;
            size_type		m_size;

        public:

            explicit Vector (const allocator_type & alloc = allocator_type()): m_allocator(alloc), m_array(nullptr), m_capacity(0), m_size(0)
            {};

            explicit Vector (size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type()): m_allocator(alloc), m_capacity(n), m_size(n)
            {
                m_array = new value_type[n]();
			    for (size_type i = 0; i < n; i++)
				    m_array[i] = val;
            }

            ~Vector() 
            {
                delete [] m_array;
            }

            size_type size() const 
            {
			    return (m_size);
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