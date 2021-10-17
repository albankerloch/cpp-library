/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_decl.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 22:46:13 by mli               #+#    #+#             */
/*   Updated: 2021/02/18 21:58:27 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_DECL_CLASS_HPP
# define VECTOR_DECL_CLASS_HPP

# include "base.hpp"
# include "RandomIte.hpp"
# include "ReverseIte.hpp"

namespace ft {

template< typename T, typename Alloc = std::allocator<T> >
class vector {
	public:

	typedef T											value_type;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;

	typedef ptrdiff_t									difference_type;
	typedef size_t										size_type;

	class iterator : public RandIte<value_type> {
		protected:
		typedef RandIte<value_type> super;
		iterator(value_type *src) : RandIte<value_type>(src) {};
		private:
		iterator(const RandIte<value_type> &src) : RandIte<value_type>(src) {};

		public:
		iterator(void) : RandIte<value_type>() {};
		iterator(const iterator &src) : RandIte<value_type>(src) {};

		typedef value_type&			reference;
		typedef value_type*			pointer;

		reference			operator*(void) const;
		pointer				operator->(void) const;
		iterator			&operator+=(difference_type n);
		iterator			&operator-=(difference_type n);
		reference			operator[](difference_type n) const;

		difference_type		operator-(const RandIte<value_type> &n) const { return super::operator-(n); };
		iterator			operator-(difference_type n) const { return super::operator-(n); };
		iterator			operator+(difference_type n) const { return super::operator+(n); };
		friend iterator		operator+(difference_type n, const iterator &rhs) { return rhs.operator+(n); };

		iterator			&operator++(void) { super::operator++(); return *this; };
		iterator			operator++(int) { return super::operator++(0); };
		iterator			&operator--(void) { super::operator--(); return *this; };
		iterator			operator--(int) { return super::operator--(0); };

		friend class vector;
	};
	class const_iterator : public RandIte<value_type> {
		protected:
		typedef RandIte<value_type> super;
		const_iterator(value_type *src) : RandIte<value_type>(src) {};
		public:
		const_iterator(void) : RandIte<value_type>() {};
		const_iterator(const RandIte<value_type> &src) : RandIte<value_type>(src) {};

		typedef const value_type&		reference;
		typedef const value_type*		pointer;

		reference			operator*(void) const;
		pointer				operator->(void) const;
		const_iterator		&operator+=(difference_type n);
		const_iterator		&operator-=(difference_type n);
		reference			operator[](difference_type n) const;

		difference_type		operator-(const RandIte<value_type> &n) const { return super::operator-(n); };
		const_iterator		operator-(difference_type n) const { return super::operator-(n); };
		const_iterator		operator+(difference_type n) const { return super::operator+(n); };
		friend const_iterator	operator+(difference_type n, const const_iterator &rhs) { return rhs.operator+(n); };

		const_iterator		&operator++(void) { super::operator++(); return *this; };
		const_iterator		operator++(int) { return super::operator++(0); };
		const_iterator		&operator--(void) { super::operator--(); return *this; };
		const_iterator		operator--(int) { return super::operator--(0); };

		friend class vector;
	};
	typedef ft::reverse_iterator<iterator>			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	private:

            allocator_type	m_allocator;
            T *      		m_array;
            size_type		m_capacity;
            size_type		m_size;

	 public:

            explicit vector (const allocator_type & alloc = allocator_type()): m_allocator(alloc), m_array(0), m_capacity(0), m_size(0) 
            {
            }

            explicit vector (size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type()): m_allocator(alloc), m_capacity(n), m_size(n)
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

            template <class Ite>
            explicit vector(Ite first, Ite last): m_array(0), m_capacity(0), m_size(0) 
            {
                this->assign(first, last);
            }

            vector (const vector  & vector_to_copy) : m_allocator(vector_to_copy.m_allocator), m_array(0), m_capacity(0), m_size(0)
            {
                *this = vector_to_copy;
            }

            ~vector() 
            {
                this->clear();
                m_allocator.deallocate(this->m_array, this->m_capacity);
            }

            vector & operator=(const vector  & vector_to_copy) 
            {
                size_t i;

                this->m_size = 0;
                this->m_capacity = 0;
                i = 0;
                while (i < vector_to_copy.m_size)
                {
                    this->push_back(vector_to_copy.m_array[i]);
                    i++;
                }
                return *this;
		    }

            template <class Ite>
            void assign(typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type first, Ite last) 
            {
                size_t length;
                size_t i;
                
                length = ft::itlen(first, last);
                if (length > this->m_capacity)
                    this->reserve(length);
                i = 0;
                while (first != last) 
                {
                    this->m_allocator.construct(&this->m_array[i], *first);
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

            allocator_type get_allocator() const
			{
				return (m_allocator);
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
			    return (std::numeric_limits<difference_type>::max() / (sizeof(value_type) / 2 ?: 1));
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
					throw (std::length_error("vector : max size reached during reserve"));
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
                /*
                iterator save_first(first);
                size_t n;

                n = ft::itlen(first, last);
                while (last != this->end())
                {
                    this->m_allocator.construct(&(*first), *(last));
                    first++;
                    last++;
                }
                this->m_size = this->m_size - n;
                return (save_first);
                */
                iterator tmp = first;
                iterator end = this->end();
                size_type deleted = ft::itlen(first, last);

                while (last != end)
                {
                    *first = *last;
                    ++first;
                    ++last;
                }
                while (deleted-- > 0)
                    this->m_allocator.destroy(&this->m_array[--this->m_size]);
                return (tmp);
            }

            void print()
            {
                typename ft::vector<T>::iterator it;
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

            template <class Ite>
            void insert (iterator position, Ite first, Ite last)
            {
                difference_type	idx;
                difference_type	old_end_idx;
                iterator		old_end;
                iterator		end;

                idx = position - this->begin();
                old_end_idx = this->end() - this->begin();
                this->resize(this->m_size + (ft::itlen(first, last)));
                end = this->end();
                position = this->begin() + idx;
                old_end = this->begin() + old_end_idx;
                while (old_end != position)
                    *--end = *--old_end;
                while (first != last)
                    *position++ = *first++;
            }

            void swap(vector & x)
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

}; // ************************************************** class ft::vector end //


} // ******************************************************* ft namespace end //

#endif // ***************************************** VECTOR_DECL_CLASS_HPP end //