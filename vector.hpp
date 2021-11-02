#ifndef DEF_VECTOR_HPP
# define DEF_VECTOR_HPP

# include "Utils.hpp"
# include "Vector_Iterator.hpp"
# include "Reverse_Iterator.hpp"

namespace ft 
{

	template< typename T, typename Alloc = std::allocator<T> >
	class vector 
	{
		public:

			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef ptrdiff_t										difference_type;
			typedef size_t											size_type;
			typedef ft::random_access_iterator<value_type>			iterator;
			typedef ft::random_access_iterator<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		private:
		
			allocator_type											m_allocator;
			value_type												*m_array;
			size_type												m_capacity;
			size_type												m_size;

		public: 

			explicit vector (const allocator_type & alloc = allocator_type()): m_allocator(alloc), m_array(0), m_capacity(0), m_size(0) 
			{
			};
			
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
			};

			template <class Ite>
			explicit vector(Ite first, Ite last): m_array(0), m_capacity(0), m_size(0) 
			{
				this->assign(first, last);
			};

			vector (const vector  & vector_to_copy) : m_allocator(vector_to_copy.m_allocator), m_array(0), m_capacity(0), m_size(0)
			{
				*this = vector_to_copy;
			};

			~vector() 
			{
				this->clear();
				m_allocator.deallocate(this->m_array, this->m_capacity);
			};

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
			};

			iterator begin(void) 
			{
				return (iterator(this->m_array));
			};

			const_iterator begin(void) const
			{
				return (const_iterator(this->m_array));
			};

			reverse_iterator rbegin(void) 
			{
				return (reverse_iterator(&(this->m_array[m_size])));
			};

			const_reverse_iterator rbegin(void) const
			{
				return (const_reverse_iterator(&(this->m_array[m_size])));
			};

			iterator end(void) 
			{
				return (iterator(&(this->m_array[m_size])));
			};         

			const_iterator end(void) const
			{
				return (const_iterator(&(this->m_array[m_size])));
			};

			reverse_iterator rend(void)
			{
				return (reverse_iterator(this->m_array));
			};      

			const_reverse_iterator rend(void) const
			{
				return (const_reverse_iterator(this->m_array));
			};


			size_type size() const 
			{
				return (this->m_size);
			};

			size_type capacity() const 
			{
				return (this->m_capacity);
			};

			bool empty() const
			{
				if (this->m_size == 0)
					return (true);
				return (false);
			};

			size_type max_size() const 
			{
				return (this->m_allocator.max_size());
			};

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
			};

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
			};

			allocator_type get_allocator() const
			{
				return (m_allocator);
			};
					
			reference operator[](size_type idx) 
			{
				return (this->m_array[idx]);
			};

			const_reference operator[](size_type idx) const 
			{
				return (this->m_array[idx]);
			};

			reference at(size_type idx)
			{
				if (idx < 0 || idx >= this->m_size)
					throw std::out_of_range("At : index out of range");
				return (this->m_array[idx]);
			};

			const_reference at(size_type idx) const 
			{
				if (idx < 0 || idx >= this->m_size)
					throw std::out_of_range("At : index out of range");
				return (this->m_array[idx]);
			};

			reference front(void) 
			{
				return (this->m_array[0]);
			};

			const_reference front(void) const 
			{
				return (this->m_array[0]);
			};

			reference back(void) 
			{
				return (this->m_array[this->m_size - 1]);
			};

			const_reference back(void) const 
			{
				return (this->m_array[this->m_size - 1]);
			};

			template <class Ite>
			void assign(Ite first, Ite last, typename ft::enable_if<!ft::is_integral_type<Ite>::value, Ite>::type* = NULL) 
			{					
				size_t length;
				size_t i;
				bool is_valid;

				if (!(is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<Ite>::iterator_category>::value))
					throw (ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<Ite>::iterator_category >::type>());
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
			};

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
			};

			void push_back(value_type value)
			{
				if (this->m_size == this->m_capacity)
					this->reserve(this->m_capacity + 1000);
				m_allocator.construct(&m_array[this->m_size], value);
				this->m_size++;
			};

			void pop_back(void)
			{
				m_allocator.destroy(this->m_array + this->m_size);
				this->m_size--;
			};

			iterator insert (iterator position, const value_type& value)
			{
				difference_type ret;
				
				ret = position - this->begin();
				this->insert(position, 1, value);
				return (iterator(this->begin() + ret));
			};  

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
			};

			template <class Ite>
			void insert (iterator position, Ite first, Ite last, typename ft::enable_if<!ft::is_integral_type<Ite>::value, Ite>::type* = NULL) 
			{
				difference_type	idx;
				difference_type	old_end_idx;
				iterator		old_end;
				iterator		end;
				bool is_valid;

				if (!(is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<Ite>::iterator_category>::value))
					throw (ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<Ite>::iterator_category >::type>());
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
			};

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
			};

			iterator erase(iterator first, iterator last)
			{
				iterator save_first(first);
				size_t n;

				n = last - first;
				while (last != this->end())
				{
					this->m_allocator.construct(&(*first), *(last));
					first++;
					last++;
				}
				this->m_size = this->m_size - n;
				return (save_first);
			};

			void swap(vector & x)
			{
				T				*temp_array;
				size_t 			temp_size;
				size_t 			temp_capacity;
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
			};
			
			void clear()
			{
				while(this->m_size > 0)
				{
					m_allocator.destroy(&this->m_array[m_size]);
					this->m_size--;
				}
			};

	};

	template<typename T>
	void swap(vector<T> &x, vector<T> &y) 
	{
		x.swap(y);
	}

	template <class T, class Alloc>
	bool	operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) 
	{
		if (lhs.size() != rhs.size())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool	operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) 
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool	operator< (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) 
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool	operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) 
	{
		if (lhs == rhs)
			return (true);
		return (lhs < rhs);
	}

	template <class T, class Alloc>
	bool	operator> (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) 
	{
		if (lhs == rhs)
			return (false);
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	bool	operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) 
	{
		if (lhs == rhs)
			return (true);
		return (!(lhs < rhs));
	}

}

#endif
