/**
 * @file Stack.hpp
 * @author alban kerloc'h
 * @date 11/04/2021
 * @version 1.0
 */

#ifndef DEF_STACK_HPP
# define DEF_STACK_HPP

# include "Vector.hpp"
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
        
           container_type       c;

        public :

            explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {}

            ~stack() {}

            bool empty() const 
            {
                return this->c.empty();
            }

            size_type size() const
            {
                return this->c.size();
            }

            value_type& top()
            {
                return this->c.back();
            }

            const value_type& top() const 
            {
                return this->c.back();
            }

            void push (const value_type& val) 
            {
                this->c.push_back(val);
            }

            void pop() 
            {
                this->c.pop_back();
            }
              
            friend bool	operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) 
            {
                return (lhs.c == rhs.c);
            }

            friend bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) 
            {
                return (lhs.c != rhs.c);
            }
            friend bool	operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) 
            {
                return (lhs.c < rhs.c);
            }

            friend bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) 
            {
                return (lhs.c > rhs.c);
            }

            friend bool	operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) 
            {
                return (lhs.c <= rhs.c);
            }

            friend bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) 
            {
                return (lhs.c >= rhs.c);
            }
    };
}

#endif