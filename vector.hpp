#ifndef VECTOR_DECL_CLASS_HPP
# define VECTOR_DECL_CLASS_HPP

# include "Utils.hpp"
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

	iterator	insert(iterator position, const value_type &val);
	void		insert(iterator position, size_type n, const value_type &val);
	template <class Ite>
		void	insert(iterator position, Ite first,
			typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type last);

	iterator	erase(iterator ite);
	iterator	erase(iterator first, iterator last);
	void		swap(vector &x);
	void		clear(void);

	protected:
	private:
	allocator_type			m_allocator;
	value_type				*m_array;
	size_type				m_capacity;
	size_type				m_size;

	template <class Ite>
	void				_createm_array(difference_type capacity, Ite first, Ite last);
	void				_createm_array(size_type size, const value_type &val = value_type());
	void				_destroym_array(void);
	template <class Ite, class Iterator>
	static void			_cpym_array(Ite start, Iterator first, Iterator last);
	void				_cpy_content(vector &vct);

}; // ************************************************** class ft::vector end //


// ******************************** Modifiers ******************************* //


template<typename T, typename Alloc> typename vector<T, Alloc>::
iterator	vector<T, Alloc>::insert(iterator position, const value_type &val) {
	difference_type idx = position - this->begin();

	this->insert(position, 1, val);
	return (iterator(this->begin() + idx));
}

template<typename T, typename Alloc>
void	vector<T, Alloc>::insert(iterator position, size_type n, const value_type &val) {
	difference_type const	idx = position - this->begin();
	difference_type const	old_end_idx = this->end() - this->begin();
	iterator				old_end, end;

	this->resize(this->m_size + n);

	end = this->end();
	position = this->begin() + idx;
	old_end = this->begin() + old_end_idx;
	while (old_end != position)
		*--end = *--old_end;
	while (n-- > 0)
		*position++ = val;
}

template<typename T, typename Alloc> template <class Ite>
void	vector<T, Alloc>::insert(iterator position, Ite first, typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type last) {
	difference_type const	idx = position - this->begin();
	difference_type const	old_end_idx = this->end() - this->begin();
	iterator				old_end, end;

	this->resize(this->m_size + (ft::itlen(first, last)));

	end = this->end();
	position = this->begin() + idx;
	old_end = this->begin() + old_end_idx;
	while (old_end != position)
		*--end = *--old_end;
	while (first != last)
		*position++ = *first++;
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator	vector<T, Alloc>::erase(iterator ite) {
	return (this->erase(ite, ite + 1));
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator	vector<T, Alloc>::erase(iterator first, iterator last) {
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

template<typename T, typename Alloc>
void	vector<T, Alloc>::swap(vector &x) {
	vector<T, Alloc> tmp;

	tmp._cpy_content(x);
	x._cpy_content(*this);
	this->_cpy_content(tmp);
}

template<typename T, typename Alloc>
void	vector<T, Alloc>::clear(void) {
	while (this->m_size > 0)
		this->m_allocator.destroy(&this->m_array[--this->m_size]);
}

// ################################ Private ####################################

template<typename T, typename Alloc> template <class Ite>
void	vector<T, Alloc>::_createm_array(difference_type capacity, Ite first, Ite last) {
	vector<T, Alloc> res;
	difference_type len = ft::itlen(first, last);

	if (capacity < len || capacity < 0)
		throw std::bad_alloc();
	res.m_allocator = this->m_allocator;
	res.m_size = len; res.m_capacity = capacity;
	res.m_array = res.m_allocator.allocate(capacity);
	for (size_type i = 0; first != last; ++first)
		res.m_allocator.construct(&res.m_array[i++], *first);
	this->_destroym_array();
	this->_cpy_content(res);
}

template<typename T, typename Alloc>
void	vector<T, Alloc>::_createm_array(size_type size, const value_type &val) {
	this->_destroym_array();
	this->m_array = this->m_allocator.allocate(size);
	for (size_type i = 0; i < size; ++i)
		this->m_allocator.construct(&this->m_array[i], val);
	this->m_size = size; this->m_capacity = size;
}

template<typename T, typename Alloc>
void	vector<T, Alloc>::_destroym_array(void) {
	if (!this->m_array)
		return ;
	this->clear();
	this->m_allocator.deallocate(this->m_array, this->m_capacity);
	this->m_array = NULL; this->m_size = 0; this->m_capacity = 0;
}

template<typename T, typename Alloc> template <class Ite, class Iterator>
void	vector<T, Alloc>::_cpym_array(Ite start, Iterator first, Iterator last) {
	while (first != last)
	{
		*start = *first;
		++start;
		++first;
	}
}

template<typename T, typename Alloc>
void	vector<T, Alloc>::_cpy_content(vector<T, Alloc> &vct) {
	this->m_array = vct.m_array;
	this->m_allocator = vct.m_allocator;
	this->m_size = vct.m_size;
	this->m_capacity = vct.m_capacity;
	vct.m_array = NULL; vct.m_size = 0; vct.m_capacity = 0;
}


// ############################## Iterators ####################################

// Regular Iterator

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator::reference
	vector<T, Alloc>::iterator::operator*(void) const {
	return (*this->_value);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator::pointer
	vector<T, Alloc>::iterator::operator->(void) const {
	return (this->_value);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator&
	vector<T, Alloc>::iterator::operator+=(difference_type n) {
	this->_value += n; return *this;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator&
	vector<T, Alloc>::iterator::operator-=(difference_type n) {
	this->_value -= n; return *this;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator::reference
	vector<T, Alloc>::iterator::operator[](difference_type n) const {
	return (this->_value[n]);
}

// Const Iterator

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator::reference
	vector<T, Alloc>::const_iterator::operator*(void) const {
	return (*this->_value);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator::pointer
	vector<T, Alloc>::const_iterator::operator->(void) const {
	return (this->_value);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator&
	vector<T, Alloc>::const_iterator::operator+=(difference_type n) {
	this->_value += n; return *this;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator&
	vector<T, Alloc>::const_iterator::operator-=(difference_type n) {
	this->_value -= n; return *this;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator::reference
	vector<T, Alloc>::const_iterator::operator[](difference_type n) const {
	return (this->_value[n]);
}

// ####################### Non-member function overloads #######################

template <class T, class Alloc>
bool	operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
	if (lhs.size() != rhs.size())
		return false;
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Alloc>
bool	operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool	operator< (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Alloc>
bool	operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
	return !(rhs < lhs);
}

template <class T, class Alloc>
bool	operator> (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
	return (rhs < lhs);
}

template <class T, class Alloc>
bool	operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
	return !(lhs < rhs);
}

template <class T, class Alloc>
void	swap(vector<T, Alloc> &x, vector<T, Alloc> &y) { x.swap(y); }

} // ******************************************************* ft namespace end //

#endif // ***************************************** VECTOR_DECL_CLASS_HPP end //
