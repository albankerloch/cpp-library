/**
 * @file Reverse_Iterator.hpp
 * @author alban kerloc'h
 * @date 11/04/2021
 * @version 1.0
 */

#ifndef DEF_REVERSE_ITERATOR_HPP
# define DEF_REVERSE_ITERATOR_HPP

# include "Utils.hpp"

namespace ft 
{

    template <class Iterator>
    class reverse_iterator
    {
        public:

            typedef Iterator    												iterator_type;
            typedef typename ft::iterator_traits<Iterator>::iterator_category 	iterator_category;
            typedef typename ft::iterator_traits<Iterator>::value_type      	value_type;
            typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;
            typedef typename ft::iterator_traits<Iterator>::pointer     		pointer;
            typedef typename ft::iterator_traits<Iterator>::reference   		reference;
        

        private:

            iterator_type     m_element;

        public:
            
            reverse_iterator() : m_element()
            {
			};

            explicit reverse_iterator (iterator_type it) : m_element(it)
            {
			};

            template <class Iter> reverse_iterator (const reverse_iterator<Iter>& rev_it) : m_element(rev_it.base())
            {
			};

            virtual ~reverse_iterator() 
			{
			};

            iterator_type base() const
            { 
				return (m_element); 
			};

            reference operator*() const
            {
                iterator_type tmp = m_element;
                return (*(--tmp));
            };

            reverse_iterator operator+ (difference_type n) const 
			{ 
				return (reverse_iterator(m_element - n)); 
			};

            reverse_iterator& operator++()
            {
                m_element--;
                return (*this);
            };

            reverse_iterator operator++(int)
            {
                reverse_iterator tmp;
                
                tmp = *this;
                ++(*this);
                return (tmp);
            };

            reverse_iterator& operator+= (difference_type n)
            {
                m_element -= n;
                return (*this);
            };

            reverse_iterator operator- (difference_type n) const 
			{ 
				return (reverse_iterator(m_element + n)); 
			};

            reverse_iterator& operator--()
            {
                m_element++;
                return (*this);
            };

            reverse_iterator operator--(int)
            {
                reverse_iterator tmp;
                
                tmp = *this;
                --(*this);
                return (tmp);
            };

            reverse_iterator& operator-= (difference_type n)
            {
                m_element += n;
                return (*this);
            };

            pointer operator->() const 
			{ 
				return (&(operator*())); 
			};

            reference operator[] (difference_type n) const 
			{ 
				return (this->base()[-n - 1]); 
			};

    };

    template <class Iterator>
    bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) 
    { 
        return (lhs.base() == rhs.base()); 
    }

    template <class Iterator_L, class Iterator_R>
 	bool operator== (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
    { 
        return (lhs.base() == rhs.base());
    }

    template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    { 
        return (lhs.base() != rhs.base());
    }

    template <class Iterator_L, class Iterator_R>
	bool operator!= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
    { 
        return (lhs.base() != rhs.base());
    }

    template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    { 
        return (lhs.base() > rhs.base());
    }

    template <class Iterator_L, class Iterator_R>
	bool operator< (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
    { 
        return (lhs.base() > rhs.base());
    }

    template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    { 
        return (lhs.base() >= rhs.base());
    }

    template <class Iterator_L, class Iterator_R>
	bool operator<= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
    { 
        return (lhs.base() >= rhs.base());
    }

    template <class Iterator>
	bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    { 
        return (lhs.base() < rhs.base());
    }

    template <class Iterator_L, class Iterator_R>
	bool operator> (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
    { 
        return (lhs.base() < rhs.base());
    }
    
    template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    { 
        return (lhs.base() <= rhs.base());
    }

    template <class Iterator_L, class Iterator_R>
	bool operator>= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
    { 
        return (lhs.base() <= rhs.base());
    }

    template <class Iterator>
	reverse_iterator<Iterator> operator+ ( typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
    { 
        return (rev_it + n);
    }

    template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) 
	{
		return (rhs.base() - lhs.base()); 
	}

    template <class Iterator_L, class Iterator_R>
	typename reverse_iterator<Iterator_L>::difference_type operator- (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) 
	{ 
		return (rhs.base() - lhs.base()); 
	}

}

#endif
