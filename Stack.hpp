#ifndef DEF_STACK_HPP
# define DEF_STACK_HPP

# include <stack>

template <typename T>
class : public std::stack<T>
{
    public:
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
};

#endif