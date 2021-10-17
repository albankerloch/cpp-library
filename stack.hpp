#ifndef DEF_STACK_HPP
# define DEF_STACK_HPP

# include "Vector_Iterator.hpp"
# include "Reverse_Iterator.hpp"
# include "vector.hpp"
# include "Algo.hpp"
# include <iostream>

namespace ft 
{
    template <typename T, class Container = ft::vector<T> >
    class stack
    {

        public:

            typedef T           value_type;
            typedef Container   container_type;
            typedef size_t      size_type;

        protected :
        
           container_type m_ctnr;

        public :

            explicit stack (const container_type& ctnr = container_type()) : m_ctnr(ctnr) {}

            ~stack() {}

            bool empty() const 
            {
                return this->m_ctnr.empty();
            }

            size_type size() const
            {
                return this->m_ctnr.size();
            }

            value_type& top()
            {
                return this->m_ctnr.back();
            }

            const value_type& top() const 
            {
                return this->m_ctnr.back();
            }

            void push (const value_type& val) 
            {
                this->m_ctnr.push_back(val);
            }

            void pop() 
            {
                this->m_ctnr.pop_back();
            }
              
            friend bool	operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) 
            {
                return (lhs.m_ctnr == rhs.m_ctnr);
            }

            friend bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) 
            {
                return (lhs.m_ctnr != rhs.m_ctnr);
            }
            friend bool	operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) 
            {
                return (lhs.m_ctnr < rhs.m_ctnr);
            }

            friend bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) 
            {
                return (lhs.m_ctnr > rhs.m_ctnr);
            }

            friend bool	operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) 
            {
                return (lhs.m_ctnr <= rhs.m_ctnr);
            }

            friend bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) 
            {
                return (lhs.m_ctnr >= rhs.m_ctnr);
            }
    };
}

#endif