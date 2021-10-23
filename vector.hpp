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

	// Member functions

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
	vector(typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type first,
			Ite last, const allocator_type &alloc = allocator_type());
	vector(const vector &src);
	virtual ~vector(void);

	vector	&operator=(vector const &rhs);

	// Iterators
	iterator		begin(void);
	const_iterator	begin(void) const;
	iterator		end(void);
	const_iterator	end(void) const;

	reverse_iterator		rbegin(void);
	const_reverse_iterator	rbegin(void) const;
	reverse_iterator		rend(void);
	const_reverse_iterator	rend(void) const;

	// Capacity
	size_type	size(void) const;
	size_type	capacity(void) const;
	size_type	max_size(void) const;
	void		resize(size_type size, value_type val = value_type());
	bool		empty(void) const;
	void		reserve(size_type n);

	// Element access
	reference			operator[](size_type n);
	const_reference		operator[](size_type n) const;
	reference			at(size_type n);
	const_reference		at(size_type n) const;
	reference			front(void);
	const_reference		front(void) const;
	reference			back(void);
	const_reference		back(void) const;

	// Modifiers
	template <class Ite>
	void		assign(typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type first, Ite last);
	void		assign(size_type n, const value_type &val);
	void		push_back(const value_type &val);
	void		pop_back(void);

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



template <typename T, typename Alloc> template <class Ite>
vector<T, Alloc>::vector(typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type first,
		Ite last, const allocator_type &alloc) : m_allocator(alloc), m_array(NULL), m_capacity(0) , m_size(0) {
	this->_createm_array(ft::itlen(first, last), first, last);
}

template<typename T, typename Alloc>
vector<T, Alloc>::vector(vector const &src) : \
	m_allocator(allocator_type()), m_array(NULL), m_capacity(0) , m_size(0){
	*this = src;
}

template<typename T, typename Alloc>
vector<T, Alloc>::~vector(void) {
	this->_destroym_array();
}

template<typename T, typename Alloc>
vector<T, Alloc>	&vector<T, Alloc>::operator=(vector const &rhs) {
	if (this == &rhs)
		return (*this);
	const_iterator first = rhs.begin();
	const_iterator last = rhs.end();
	size_type len = ft::itlen(first, last);
	this->_createm_array((len > this->m_capacity) ? len : this->m_capacity, first, last);
	return (*this);
}

// ****************************** Iterators ********************************* //

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::begin(void) {
	return (iterator(this->m_array));
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin(void) const {
	return (const_iterator(this->m_array));
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::end(void) {
	return (iterator(&this->m_array[this->m_size]));
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end(void) const {
	return (const_iterator(&this->m_array[this->m_size]));
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rbegin(void) {
	return (reverse_iterator(&this->m_array[this->m_size]));
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rbegin(void) const {
	return (const_reverse_iterator(&this->m_array[this->m_size]));
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rend(void) {
	return (reverse_iterator(this->m_array));
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rend(void) const {
	return (const_reverse_iterator(this->m_array));
}

// ******************************* Capacity ********************************* //

template<typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::size(void) const {
	return (this->m_size);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity(void) const {
	return (this->m_capacity);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size(void) const {
	return (std::numeric_limits<difference_type>::max() / (sizeof(value_type) / 2 ?: 1));
}

template<typename T, typename Alloc>
void		vector<T, Alloc>::reserve(size_type n) {
	if (n > this->max_size())
		throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
	if (n <= this->capacity())
		return ;
	this->_createm_array(n, this->begin(), this->end());
}

template<typename T, typename Alloc>
void		vector<T, Alloc>::resize(size_type size, value_type val) {
	if (size < this->m_size)
	{
		while (size < this->m_size)
			this->m_allocator.destroy(&this->m_array[--this->m_size]);
	}
	else
	{
		size_type const &lambda = (this->m_size);

		if (size <= this->m_capacity)
			;
		else if (size <= lambda * 2)
			this->reserve(lambda * 2);
		else
			this->reserve(size);
		while (this->m_size < size)
			this->m_allocator.construct(&this->m_array[this->m_size++], val);
	}
}

template<typename T, typename Alloc>
bool	vector<T, Alloc>::empty(void) const {
	return (this->m_size == 0 ? true : false);
}

// ******************************* Ele Access ******************************* //

template<typename T, typename Alloc> typename vector<T, Alloc>::
reference		vector<T, Alloc>::operator[](size_type n) {
	return this->m_array[n];
}

template<typename T, typename Alloc> typename vector<T, Alloc>::
const_reference	vector<T, Alloc>::operator[](size_type n) const {
	return this->m_array[n];
}

template<typename T, typename Alloc> typename vector<T, Alloc>::
reference		vector<T, Alloc>::at(size_type n) {
	if (n < this->m_size)
		return ((*this)[n]);
	std::ostringstream ostr;

	ostr << "vector";
	ostr << "::_M_range_check: __n (which is " << n
		<< ") >= this->size() (which is " << this->m_size << ")";
	throw std::out_of_range(ostr.str());
}

template<typename T, typename Alloc> typename vector<T, Alloc>::
const_reference	vector<T, Alloc>::at(size_type n) const {
	if (n < this->m_size)
		return ((*this)[n]);
	std::ostringstream ostr;

	ostr << "vector";
	ostr << "::_M_range_check: __n (which is " << n
		<< ") >= this->size() (which is " << this->m_size << ")";
	throw std::out_of_range(ostr.str());
}

template<typename T, typename Alloc> typename vector<T, Alloc>::
reference		vector<T, Alloc>::front(void) {
	return (*this)[0];
}

template<typename T, typename Alloc> typename vector<T, Alloc>::
const_reference	vector<T, Alloc>::front(void) const {
	return (*this)[0];
}

template<typename T, typename Alloc> typename vector<T, Alloc>::
reference		vector<T, Alloc>::back(void) {
	return (*this)[this->m_size - 1];
}

template<typename T, typename Alloc> typename vector<T, Alloc>::
const_reference	vector<T, Alloc>::back(void) const {
	return (*this)[this->m_size - 1];
}

// ******************************** Modifiers ******************************* //

template<typename T, typename Alloc> template <class Ite>
void	vector<T, Alloc>::assign(typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type first, Ite last) {
	size_type size = ft::itlen(first, last);

	if (size > this->m_capacity)
		this->_createm_array(size, first, last);
	else
	{
		this->clear();
		while (first != last)
			this->m_allocator.construct(&this->m_array[this->m_size++], *first++);
	}
}

template<typename T, typename Alloc>
void	vector<T, Alloc>::assign(size_type n, const value_type &val) {
	if (n > this->m_capacity)
		this->_createm_array(n, val);
	else
	{
		this->clear();
		while (this->m_size < n)
			this->m_allocator.construct(&this->m_array[this->m_size++], val);
	}
}

template<typename T, typename Alloc>
void		vector<T, Alloc>::push_back(const value_type &val) {
	if (this->m_size == this->m_capacity)
		this->resize(this->m_size + 1, val);
	else
		this->m_allocator.construct(&this->m_array[this->m_size++], val);
}

// Do not protect this function or it will not behave like the original!
template<typename T, typename Alloc>
void		vector<T, Alloc>::pop_back(void) {
	this->m_allocator.destroy(&this->m_array[--this->m_size]);
}

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
