/**
 * @file Vector_Iterator.hpp
 * @author alban kerloc'h
 * @date 11/04/2021
 * @version 1.0
 */

#ifndef DEF_VECTOR_ITERATOR_HPP
# define DEF_VECTOR_ITERATOR_HPP


namespace ft
{
    
    template <typename T>
        class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
        {
            public:
                
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category     iterator_category;
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type            value_type;
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type       difference_type;
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference             reference;
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer               pointer;

            private:
            
                pointer                                                                                 m_pointer;

            public:
                
                random_access_iterator(void): m_pointer(NULL)
                {
                }

                random_access_iterator(pointer elem) : m_pointer(elem)
                {
                }

                random_access_iterator(const random_access_iterator& op) : m_pointer(op.m_pointer)
                {
                }

                random_access_iterator &operator=(const random_access_iterator& op)
                {
                    if (this == &op)
		                return (*this);
                    this->m_pointer = op.m_pointer;
                    return (*this);
                };

                virtual ~random_access_iterator()
                {
                };

                pointer base() const
                {
                    return (this->m_pointer); 
                };

                reference operator*(void) const 
                { 
                    return (*m_pointer); 
                };

                pointer operator->(void) 
                { 
                    return (&(this->operator*())); 
                };

                random_access_iterator& operator++(void)
                {
                    m_pointer++;
                    return (*this);
                };

                random_access_iterator operator++(int)
                {
                    random_access_iterator rtn(*this);

                    operator++();
                    return (rtn);
                };

                random_access_iterator& operator--(void)
                {
                    m_pointer--;
                    return (*this);
                };

                random_access_iterator operator--(int)
                {
                    random_access_iterator rtn(*this);
                    
                    operator--();
                    return (rtn);
                };

                random_access_iterator operator+(difference_type n) const 
                { 
                    return (m_pointer + n); 
                };

                random_access_iterator operator-(difference_type n) const 
                { 
                    return (m_pointer - n); 
                };

                random_access_iterator& operator+=(difference_type n)
                {
                    m_pointer += n;
                    return (*this);
                };

                random_access_iterator& operator-=(difference_type n)
                {
                    m_pointer -= n;
                    return (*this);
                };

                reference operator[](difference_type n) 
                { 
                    return (*(operator+(n))); 
                };

                operator random_access_iterator<const T> () const
                { 
                    return (random_access_iterator<const T>(this->m_pointer)); 
                };

        };

    template <typename T>
    bool operator==(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template<typename T_L, typename T_R>
    bool operator==(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <typename T>
    bool operator!=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template<typename T_L, typename T_R>
    bool operator!=(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <typename T>
    bool operator<(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template<typename T_L, typename T_R>
    bool operator<(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <typename T>
    bool operator>(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template<typename T_L, typename T_R>
    bool operator>(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename T>
    bool operator<=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template<typename T_L, typename T_R>
    bool operator<=(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename T>
    bool operator>=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template<typename T_L, typename T_R>
    bool operator>=(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template<typename T>
    ft::random_access_iterator<T> operator+( typename ft::random_access_iterator<T>::difference_type n, typename ft::random_access_iterator<T>& rai)
    {
        return (&(*rai) + n);
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type operator-(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() - rhs.base());
    }

    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type operator-(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() - rhs.base());
    }

}

#endif
