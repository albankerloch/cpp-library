/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:01:32 by rchallie          #+#    #+#             */
/*   Updated: 2020/12/10 17:41:09 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Documentation :
** (en) https://en.wikipedia.org/wiki/Doubly_linked_list
*/

#ifndef LIST_HPP
#define LIST_HPP

# include "utils.hpp"
# include "List_Iterator.hpp"
# include "Node.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> > 
	class list
	{
		public :

			typedef T	    							    	    value_type;
            typedef Alloc   	    					        	allocator_type;
            typedef typename allocator_type::reference            reference;
            typedef typename allocator_type::const_reference       const_reference;
            typedef typename allocator_type::pointer	        	pointer;
            typedef typename allocator_type::const_pointer      	const_pointer;
            typedef Node<value_type>                                node_type;
            typedef ft::List_iterator<T> 							iterator;
            typedef ft::List_const_iterator<T> 						const_iterator;
            typedef ft::reverse_iterator<iterator> 					reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> 			const_reverse_iterator;
            typedef std::ptrdiff_t							        difference_type;
            typedef size_t 								    	    size_type;
		
			explicit list (const allocator_type& alloc = allocator_type()) : m_allocator(alloc)
			{
				m_last_node = m_nodeallocator.allocate(1);
				m_nodeallocator.construct(m_last_node, Doubly_Linked_Node<T>());
				m_last_node->m_previous = m_last_node;
				m_last_node->m_next = m_last_node;
			}

			/*
			** @brief Init :
			** Construct list container object of size "n".
			** If "val" is not defined, default value of container
			** is used tu initialize the values. 
			**
			** @param n the size of the list.
			** @param the values of data of the list.
			** @param alloc the Allocator type.
			*/
			explicit list (size_type n, const value_type& val = value_type(),
											const allocator_type& alloc = allocator_type())
			:
				m_allocator(alloc)
			{
				m_last_node = m_nodeallocator.allocate(1);
				m_nodeallocator.construct(m_last_node, Doubly_Linked_Node<T>());
				m_last_node->m_previous = m_last_node;
				m_last_node->m_next = m_last_node;
				this->insert(end(), n, val);
			}

			/*
			** @brief Iterator:
			** Construct a list container, of size last-first containing
			** value of [first, last).
			**
			** @param first,last the range of content.
			** @param alloc the allocator type.
			*/
			template <class InputIterator>
					list (InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
			:
				m_allocator(alloc)
			{
				bool is_valid;
				if (!(is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
					throw (ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());

				m_last_node = m_nodeallocator.allocate(1);
				m_nodeallocator.construct(m_last_node, Doubly_Linked_Node<T>());
				m_last_node->m_previous = m_last_node;
				m_last_node->m_next = m_last_node;
				this->insert(end(), first, last);
			}

			/*
			** @brief Copy :
			** Construct the container to be a copy of "x".
			**
			** @param x the lsit to copy.
			*/
			list (const list& x)
			:
				m_allocator(x.m_allocator)
			{
				m_last_node = m_nodeallocator.allocate(1);
				m_nodeallocator.construct(m_last_node, Doubly_Linked_Node<T>());
				m_last_node->m_previous = m_last_node;
				m_last_node->m_next = m_last_node;
				
				const_iterator beg = x.begin();
				const_iterator end = x.end();

				while (beg != end)
					this->_insertBefore(m_last_node, _createNode((beg++)._node->data));
			}

			/*
			** @brief Destructor:
			** Clear the container and deallocate everythings.
			*/
			~list()
			{
				this->clear();
				m_nodeallocator.destroy(m_last_node);
				m_nodeallocator.deallocate(m_last_node, 1);
			}

			/*
			** @brief Assign "x" to this.
			**
			** @param x the list where get elements.
			** @return this list.
			*/
			list& operator= (const list & x)
			{
				if (&x == this)
					return (*this);
				this->clear();
				this->insert(this->begin(), x.begin(), x.end());
				return (*this);
			}

			/*
			** @brief Return an iterator pointing on the first element
			** in the container. If the container is empty, the
			** returned iterator value shall no be dereferenced.
			** The iterator is of type iterator (bidirectional iterator
			** on value_type reference).
			**
			** @return The iterator to the first element.
			*/
			iterator begin() { return (iterator(m_last_node->m_next)); }

			/*
			** @brief Return a const iterator pointing on the first element
			** in the container. If the container is empty, the
			** returned iterator value shall no be dereferenced.
			** The iterator is of type const_iterator (bidirectional
			** iterator on const value_type reference).
			**
			** @return The const iterator to the first element.
			*/
			const_iterator begin() const { return (const_iterator(m_last_node->m_next)); }

			/*
			** @brief Return an iterator pointing on the past-the-end element
			** in the container. Past-the-end is the theorical element
			** following the last element in the container. If the container is
			** empty, return the same than begin.
			** The iterator is of type iterator (bidirectional iterator
			** on value_type reference).
			**
			** @return The iterator to the past-the-end element or begin if
			** the container is empty.
			*/
			iterator end() { return (iterator(m_last_node)); }

			/*
			** @brief Return an iterator pointing on the past-the-end element
			** in the container. Past-the-end is the theorical element
			** following the last element in the container. If the container is
			** empty, return the same than begin.
			** The iterator is of type const_iterator (bidirectional
			** iterator on const value_type reference).
			**
			** @return The iterator to the past-the-end element or begin if
			** the container is empty.
			*/
			const_iterator end() const { return (const_iterator(m_last_node)); }

			/*
			** @brief Give a reverse iterator pointing to the last element
			** in the container (this->end() - 1).
			** This is a reversed bidirectional iterator.
			**
			** @return A reverse Iterator to the reverse beginning of the container.
			*/
			reverse_iterator rbegin() { return (reverse_iterator(end())); }

			/*
			** @brief Give a const reverse iterator pointing to the last 
			** element in the container (this->end() - 1).
			** This is a constant reversed bidirectional iterator.
			**
			** @return A const reverse Iterator to the reverse beginning of the container.
			*/
			const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }

			/*
			** @brief Give a reverse iterator point to the
			** theorical element preceding the first element
			** in the container.
			**
			** @return the reverse iterator.
			*/
			reverse_iterator rend() { return (reverse_iterator(begin())); }

			/*
			** @brief Give a const reverse iterator point to the
			** theorical element preceding the first element
			** in the container. 
			**
			** @return the const reverse iterator.
			*/
			const_reverse_iterator rend() const { return (reverse_iterator(begin())); }

			/*
			** @brief Returns whether the container is empty.
			** Does not modify container in any way.
			**
			** @return true if the container size is 0, false otherwise.
			*/
			bool empty() const { return (m_last_node->m_next == m_last_node ? true : false); }

			/*
			** @brief return the number of elements
			** in the container.
			**
			** @return the number of elements.
			*/
			size_type size() const { return (_listSize()); }

			/*
			** @brief Returns the maximum potential number of elements the the
			** container can hold.
			** This size is due to known system or library limitations.
			** The container is not garanteed to have this size, it can
			** fail a allocation for exemple.
			** 
			** Documentation :
			** https://www.viva64.com/en/a/0050/
			**
			** @return The maximum potential number of elements the
			** container can hold.
			** (An unsigned integral type)
			*/
			size_type max_size() const { return nodem_allocatorator().max_size(); }

			/*
			** @brief Return a reference to the first element
			** of the container. Call this on an empty container
			** cause undefined behavior.
			**
			** @return the reference.
			*/
			reference front() { return (m_last_node->m_next->data); }

			/*
			** @brief Return a const reference to the first element
			** of the container. Call this on an empty container
			** cause undefined behavior.
			**
			** @return The const reference.
			*/
			const_reference front() const { return (m_last_node->m_next->data); }

			/*
			** @brief Return a reference to the last element in the container.
			** If the container is empty, occur undefined behavior.
			**
			** @return The reference to the last element.
			*/
			reference back() { return (m_last_node->m_previous->data); }

			/*
			** @brief Return a const reference to the last element in the container.
			** If the container is empty, occur undefined behavior.
			**
			** @return The const reference to the last element.
			*/
			const_reference back() const { return (m_last_node->m_previous->data); }

			/*
			** @brief Assign values between iterators [first; last]
			** in the container in the same order. All element held
			** in the container before the call of this function are
			** destroyed and replaced by new content.
			**
			** @param first,last the two iterators were the new
			** element are.
			*/
			template <class InputIterator>
					void assign (InputIterator first, InputIterator last)
			{
				this->clear();
				this->insert(this->end(), first, last);
			}

			/*
			** @brief Assign new content ("val") to the container
			** "n" times. All element held
			** in the container before the call of this function are
			** destroyed and replaced by new content.
			**
			** @paran n the number of new elements.
			** @param val the new element.
			*/
			void assign (size_type n, const value_type& val)
			{
				this->clear();
				this->insert(this->end(), n, val);
			}

			/*
			** @brief Add new element at the beginning of the container.
			** The content of "val" is copied (moved) to the new element.
			** 
			** @param val The value to be copied.
			*/
			void push_front (const value_type& val) { _insertBeginning(_createNode(val)); }

			/*
			** @brief Delete the first element of the container.
			** Reduce the size of the container of one.
			** If the container is empty, cause undefined behavior.
			*/
			void pop_front() { _delete(m_last_node->m_next); }

			/*
			** @brief Add new element at the end of the container.
			** The content of "val" is copied (moved) to the new element.
			** 
			** @param val The value to be copied.
			*/
			void push_back(const value_type& val) { _insertEnd(_createNode(val)); }

			/*
			** @brief Delete the last element of the container.
			** Reduce the size of the container of one.
			** If the container is empty, cause undefined behavior.
			*/
			void pop_back() { _delete(m_last_node->m_previous); }

			/*
			** @brief Insert an element a the position. Can ecrease de size
			** of the container. This action add a node to the list.
			**
			** @param position The position where insert.
			** @param val The element to insert.
			** @return An iterator to the new element in the container.
			*/
			iterator insert (iterator position, const value_type& val)
			{ return (_insertBefore(position._node, _createNode(val))); }

			/*
			** @brief Insert an element a the position. Can ecrease de size
			** of the container. This action add "n" nodes to the list.
			**
			** @param position The position where insert.
			** @param val The element to insert.
			** @return An iterator to the new element in the container.
			*/
			void insert (iterator position, size_type n, const value_type& val)
			{
				while (n--)
					_insertBefore(position._node, _createNode(val));
			}

			/*
			** @brief Insert element in range from ["first" to
			** "last") at "position". Can increase the size of
			** the container. Throw if the iterator given is not valid.
			**
			** @param position the position where insert.
			** @param first the first element in the range.
			** @param last the last element in the range.
			*/
			template <class InputIterator>
				void insert (iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
			{
				bool is_valid;
				if (!(is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
					throw (ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());

				difference_type n = ft::distance(first, last);
				while (n--)
					_insertBefore(position._node, _copyNode((first++)._node));
			}

			/*
			** @brief Remove element from the container at "position".
			** Reduce the size of 1;
			**
			** @param position the iterator pointing to the
			** element to remove.
			** @return an iterator to the m_next element after position. 
			*/
			iterator erase (iterator position)
			{
				iterator rtn(position._node->m_next);
				_delete(position._node);
				return (rtn);
			}

			/*
			** @brief Remove a range of element.
			** Reduce the size by the number of element removed.
			** 
			** @param first the first element in the range.
			** @param last the last element in the range.
			** @return An iterator that point to the first element
			** after "last".
			*/
			iterator erase (iterator first, iterator last)
			{
				iterator rtn(last._node->m_next);

				while (first != last)
					_delete((first++)._node);

				return (rtn);
			}

			/*
			** @brief Exchanges the content with "x" content.
			** "x" is of same type. Elements of "x" are elements
			** of this container and elements of this are of "x".
			** All iterators, references, pointer on the swaped
			** objects stay valid.
			**
			** @param x the container to swap.
			*/
			void swap (list& x)
			{
				if (x == *this)
					return;

				allocator_type 			savem_allocator = x.m_allocator;
				nodem_allocatorator			savem_nodeallocator = x.m_nodeallocator;
				Doubly_Linked_Node<T>	*savem_last_node = x.m_last_node;

				x.m_allocator = this->m_allocator;
				x.m_nodeallocator = this->m_nodeallocator;
				x.m_last_node = this->m_last_node;

				this->m_allocator = savem_allocator;
				this->m_nodeallocator = savem_nodeallocator;
				this->m_last_node = savem_last_node;
			}

			/*
			** @brief Resizes the container so that it contain "n"
			** element. If "n" is smaller than the actual size
			** the container is reduced to "n". If it is greater,
			** val is inserting at the end "n - size()" times.
			**
			** @param n the new size of the container.
			** @param val the element to set.
			*/
			void resize (size_type n, value_type val = value_type())
			{
				if (this->max_size() - this->size() < n)
					throw (std::length_error("list::resize"));
				if (n > this->size())
				{
					n -= this->size();
					while (n--)
						this->_insertBefore(m_last_node, _createNode(val));
				}
				else
				{
					while (this->size() > n)
						this->pop_back();
				}
			}

			/*
			** @brief Removes (destroy) & deallocate
			** all elements from the container. Final size is 0.
			*/
			void clear()
			{
				Doubly_Linked_Node<T> *tmp = m_last_node->m_next;
				Doubly_Linked_Node<T> *m_next_tmp;
				while (tmp != m_last_node)
				{
					m_next_tmp = tmp->m_next;
					_delete(tmp);
					tmp = m_next_tmp;
				}
			}

			/*
			** @brief Transfers all elements from x into the container,
			** inserting them at position. Delete this element of the
			** base list.
			**
			** @param position the position within the container where
			** to insert the list.
			** @param x the list.
			*/
			void splice (iterator position, list& x)
			{
				iterator x_beg = x.begin();
				iterator x_save;

				while (x_beg != x.end())
				{
					x_save = (++x_beg)--;
					x._disconnect(x_beg._node);
					if (x != *this)
						_insertBefore(position._node, x_beg._node);
					x_beg = x_save;
				}
			}

			/*
			** @brief Transfers element at "i" from "x" to this
			** container at "position". Increase size of one.
			**
			** @param position the position in this container
			** @param x the base container of "i".
			** @param i an iterator on the element to transfert
			** here
			*/
			void splice (iterator position, list& x, iterator i)
			{
				x._disconnect(i._node);
				_insertBefore(position._node, i._node);
			}

			/*
			** @brief Transfers all elements from the range
			** [first, last) into the container, inserting them at
			** "position". Delete this element of the base list.
			**
			** @param position the position within the container where
			** to insert the list.
			** @param x the list.
			*/
			void splice (iterator position, list& x, iterator first, iterator last)
			{
				iterator x_save;

				while (first != last)
				{
					x_save = (++first)--;
					x._disconnect(first._node);
					if (x != *this)
						_insertBefore(position._node, first._node);
					first = x_save;
				}
			}

			/*
			** @brief Remove all element in the container
			** which have "val" in data storage. Reduce the
			** size of the container.
			**
			** @param val the value of the elements to be removed.
			*/
			void remove(const value_type& val)
			{
				iterator save;
				iterator first = m_last_node->m_next;

				while (first != end())
				{
					save = (++first)--;
					if (*first == val)
						_delete(first._node);
					first = save;
				}
			}

			/*
			** @brief Removes from the container all the elements
			** for which Predicate pred returns true.
			** This calls the destructor of these objects
			** and reduces the container size by the number
			** of elements removed.
			**
			** @param pred the object / function that define
			** condition to remove an data from the list.
			*/
			template <class Predicate>
					void remove_if (Predicate pred)
			{
				iterator save;
				iterator first = m_last_node->m_next;

				while (first != end())
				{
					save = (++first)--;
					if (pred(*first))
						_delete(first._node);
					first = save;
				}
			}

			/*
			** @brief Removes all but the first element
			** from every consecutive group of equal
			** elements in the container.
			*/
			void unique()
			{
				iterator save;
				iterator first = m_last_node->m_next;

				while (first != end())
				{
					save = (++first)--;
					if (first._node->m_previous != m_last_node
						&& first._node->m_previous->data == first._node->data)
						_delete(first._node);
					first = save;
				}	
			}

			/*
			** @brief Takes as argument a specific comparison
			** function that determine the "uniqueness" of an element.
			** If an element is not defined unique by "binary_pred",
			** the element is removed.
			**
			** @param binary_pred the function / object that
			** determine the "uniqueness".
			*/
			template <class BinaryPredicate>
				void unique (BinaryPredicate binary_pred)
			{
				iterator save;
				iterator first = m_last_node->m_next;

				while (first != end())
				{
					save = (++first)--;
					if (first._node->m_previous != m_last_node
						&& binary_pred(*first,*((--first)++)))
						_delete(first._node);
					first = save;
				}	
			}
	
			/*
			** @brief Merges x into the list by transferring
			** all of its elements at their respective ordered
			** positions into the container (both containers
			** shall already be ordered).
			**
			** @param x the list to merge with this.
			*/
			void merge(list& x)
			{
				this->merge(x, ft::less<T>());
			}

			/*
			** @brief Merges x into the list by transferring
			** all of its elements at their respective ordered
			** positions into the container (both containers
			** shall already be ordered). place determined
			** by "comp".
			**
			** @param x the list to merge with this.
			** @param comp the comparator function / object
			** to determine sort of elements
			*/
			template <class Compare>
				void merge (list& x, Compare comp)
			{
				if (&x == this)
					return ;

				iterator save;
				iterator save_x;
				iterator first = m_last_node->m_next;
				iterator first_x = x.m_last_node->m_next;

				while (first_x != x.end())
				{
					save = (++first)--;
					save_x = (++first_x)--;
					if (first._node != m_last_node && comp(first._node->data, first_x._node->data))
						first = save;
					else
					{
						x._disconnect(first_x._node);
						_insertBefore(first._node, first_x._node);
						first_x = save_x;
					}
				}
			}

			/*
			** @brief Sorts the elements in the list,
			** altering their position within the container.
			** The comparison for the sort is data->operator<(),
			** so less() can be used.
			*/
			void sort()
			{
				m_last_node->m_next = _mergeSort(m_last_node->m_next, ft::less<T>());

				Doubly_Linked_Node<T> * tmp = m_last_node->m_next;
				Doubly_Linked_Node<T> * m_previous_last;

				while (tmp != m_last_node)
				{
					m_previous_last = tmp;
					tmp = tmp->m_next;
				}

				m_last_node->m_previous = m_previous_last;
			}

			/*
			** @brief Sorts the elements in the list,
			** altering their position within the container.
			** The comparison object for the sort is "comp".
			*/
			template <class Compare>
				void sort (Compare comp)
			{
				m_last_node->m_next = _mergeSort(m_last_node->m_next, comp);

				Doubly_Linked_Node<T> * tmp = m_last_node->m_next;
				Doubly_Linked_Node<T> * m_previous_last;

				while (tmp != m_last_node)
				{
					m_previous_last = tmp;
					tmp = tmp->m_next;
				}

				m_last_node->m_previous = m_previous_last;
			}

			/*
			** @brief Reverses the order of the elements in
			** the list container.
			*/
			void reverse()
			{
				Doubly_Linked_Node<T> * tmp = m_last_node->m_next;
				Doubly_Linked_Node<T> * save_m_next;

				save_m_next = m_last_node->m_next;
				m_last_node->m_next = m_last_node->m_previous;
				m_last_node->m_previous = save_m_next;
				while (tmp != m_last_node)
				{
					save_m_next = tmp->m_next;
					tmp->m_next = tmp->m_previous;
					tmp->m_previous = save_m_next;
					tmp = save_m_next;				
				}
			}

		private :

			typedef typename allocator_type::template
				rebind<Doubly_Linked_Node<T> >::other nodem_allocatorator;
			typedef typename nodem_allocatorator::pointer	_node_pointer;

			allocator_type 			m_allocator;
			nodem_allocatorator			m_nodeallocator;
			Doubly_Linked_Node<T>	*m_last_node;

			/*
			** @brief Create new node.
			*/
			_node_pointer _createNode(const T& data, Doubly_Linked_Node<T> * m_previous = u_nullptr, Doubly_Linked_Node<T> * m_next = u_nullptr)
			{
				_node_pointer new_node = m_nodeallocator.allocate(1);
				m_nodeallocator.construct(new_node, Doubly_Linked_Node<T>(data));
				new_node->m_previous = m_previous;
				new_node->m_next = m_next;
				return (new_node);
			}

			/*
			** @brief Copy a node.
			*/
			_node_pointer _copyNode(const Doubly_Linked_Node<T> * node)
			{
				_node_pointer new_node = m_nodeallocator.allocate(1);
				m_nodeallocator.construct(new_node, Doubly_Linked_Node<T>(node->data));
				new_node->m_previous = node->m_previous;
				new_node->m_next = node->m_next;
				return (new_node);
			}

			/*
			** @brief Give the list size.
			**
			** @return the list size.
			*/
			size_type _listSize(void) const
			{
				size_type count = 0;
				_node_pointer tmp = m_last_node->m_next;

				while (tmp != m_last_node)
				{
					tmp = tmp->m_next;
					count++;
				}
				return (count);
			}

			/*
			** @brief insert a doubly linked node to the beginning
			** of the doubly linked list. If the list is empty
			** the first and the last node are set to "new_node".
			** Usefull for possibly empty list.
			**
			** @param new_node the new node.
			*/
			void _insertBeginning(Doubly_Linked_Node<T>	*new_node)
			{
				if (m_last_node->m_next == m_last_node)
				{
					m_last_node->m_next = new_node;
					m_last_node->m_previous = new_node;
					new_node->m_previous = m_last_node;
					new_node->m_next = m_last_node;
				}
				else
					_insertBefore(m_last_node->m_next, new_node);
			}

			/*
			** @brief insert a doubly linked node to the end
			** of the doubly linked list. If the list is empty
			** the first and the last node are set to "new_node".
			**
			** @param new_node the new node.
			*/
			void _insertEnd(Doubly_Linked_Node<T>	*new_node)
			{
				if (m_last_node->m_next == m_last_node)
					_insertBeginning(new_node);
				else
					_insertAfter(m_last_node->m_previous, new_node);
			}

			/*
			** @brief insert a doubly linked node after "m_previous".
			** Set "m_previous" m_next node to "new_node", "new_node" m_previousious
			** to "m_previous", and if it's not u_nullptr, set "m_previous" primary 
			** m_next to "new_node" m_next.
			**
			** @param m_previous the m_previousious node before the new one.
			** @param new_node the new node to insert.
			*/
			iterator _insertAfter(Doubly_Linked_Node<T> *m_previous, Doubly_Linked_Node<T> *new_node)
			{
				new_node->m_previous = m_previous;
				if (m_previous->m_next == m_last_node)
				{
					new_node->m_next = m_last_node;
					m_last_node->m_previous = new_node;
				}
				else
				{
					new_node->m_next = m_previous->m_next;
					m_previous->m_next->m_previous = new_node;
				}
				m_previous->m_next = new_node;
				return (iterator(m_previous->m_next));
			}

			/*
			** @brief insert a doubly linked node m_previousious "m_next".
			** Set "m_next" m_previousious node to "new_node", "new_node" m_next
			** to "m_next", and if it's not u_nullptr, set "m_next" primary
			** m_previousious to "new_node" m_previousious.
			**
			** @param m_next the m_next node after the new one.
			** @param new_node the new node to insert.
			*/
			iterator _insertBefore(Doubly_Linked_Node<T> *m_next,  Doubly_Linked_Node<T> *new_node)
			{
				new_node->m_next = m_next;
				if (m_next->m_previous == m_last_node)
				{
					new_node->m_previous = m_last_node;
					m_last_node->m_next = new_node;
				}
				else
				{
					new_node->m_previous = m_next->m_previous;
					m_next->m_previous->m_next = new_node;
				}
				m_next->m_previous = new_node;
				return (iterator(m_next->m_previous));
			}

			/*
			** @brief Delete an node from the
			** list.
			**
			** @param the node to delete.
			*/
			void _delete(Doubly_Linked_Node<T> *node)
			{
				_disconnect(node);
				m_nodeallocator.destroy(node);
				m_nodeallocator.deallocate(node, 1);
			}

			/*
			** @brief Disconnect "node" from the list without
			** destroy / deallocate it.
			**
			** @param node the node to disconnect.
			*/
			void _disconnect(Doubly_Linked_Node<T> *node)
			{
				if (node->m_previous == m_last_node)
					m_last_node->m_next = node->m_next;
				else
					node->m_previous->m_next = node->m_next;
				if (node->m_next == m_last_node)
					m_last_node->m_previous = node->m_previous;
				else
					node->m_next->m_previous = node->m_previous;	
			}

			/*
			** @brief Split used tu separate the actual
			** part of the list at hafl.
			**
			** @param the head of the actual part of the
			** list.
			** @return a pointer to the second part of the
			** part of the list splited.
			*/
			_node_pointer _split(Doubly_Linked_Node<T> *head)
			{
				_node_pointer fast = head;
				_node_pointer slow = head;

				while (fast->m_next != m_last_node && fast->m_next->m_next != m_last_node)
				{
					fast = fast->m_next->m_next;
					slow = slow->m_next;
				}

				_node_pointer tmp = slow->m_next;
				slow->m_next = m_last_node;
				return (tmp);
			}

			/*
			** @brief Merge two part of the list.
			** If the par contain more than one element,
			** it will be reconnecte subs parts to be sorted,
			** and recursivly merge the sorted parts.
			** Visualization :
			** https://www.youtube.com/watch?v=ZRPoEKHXTJg
			**
			** @param first,second the two part to sort and merge.
			** @return a pointer to the two part merged.
			*/
			template <class Compare>
			_node_pointer _merge(Doubly_Linked_Node<T> *first, Doubly_Linked_Node<T> *second, Compare comp)
			{
				if (first == m_last_node)
					return (second);
				if (second == m_last_node)
					return (first);
				
				if (comp(first->data,second->data))
				{
					first->m_next = _merge(first->m_next, second, comp);
					first->m_next->m_previous = first;
					first->m_previous = m_last_node;
					return (first);
				}
				else
				{
					second->m_next = _merge(first, second->m_next, comp);
					second->m_next->m_previous = second;
					second->m_previous = m_last_node;
					return (second);
				}
			}

			/*
			** @brief Merge Sorting. Visualization : 
			** https://www.youtube.com/watch?v=ZRPoEKHXTJg
			**
			** @param head the first element of the part of list.
			** @param Compare the comparison object.
			**
			** @return a pointer to the head of the sorted part.
			*/
			template <class Compare>
			_node_pointer _mergeSort(Doubly_Linked_Node<T> *head, Compare comp)
			{
				if (head == m_last_node || head->m_next == m_last_node)
					return (head);
				
				_node_pointer second = _split(head);

				head = _mergeSort(head, comp);
				second = _mergeSort(second, comp);

				return (_merge(head, second, comp));
			}
	};

	/*
	** @brief Compare list container to know
	** if they are equal. Start to check if the size
	** is different.
	**
	** @param lhs list to compare with "rhs".
	** @param rhs list for comparison of "lhs".
	** @return true if they are equal, false otherwise.
	*/
	template <class T, class Alloc>
		bool operator== (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			typename ft::list<T>::const_iterator first1 = lhs.begin();
			typename ft::list<T>::const_iterator first2 = rhs.begin();
			while (first1 != lhs.end())
			{
				if (first2 == rhs.end() || *first1 != *first2)
					return (false);
				++first1;
				++first2;
			}
			return (true);
		}

	/*
	** @brief Compare list container to know
	** if they are different. Equivalent to !(lsh == rhs).
	**
	** @param lhs list to compare with "rhs".
	** @param rhs list for comparison of "lhs".
	** @return true if they are different, false otherwise.
	*/
	template <class T, class Alloc>
		bool operator!= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
		{
			return (!(lhs == rhs));
		}

	/*
	** @brief Compare list container to know
	** if "lhs" elements are lexicographicalement less than "rhs".
	**
	** @param lhs list to compare with "rhs".
	** @param rhs list for comparison of "lhs".
	** @return true if "lhs" is lexicographicalement less, false otherwise.
	*/
	template <class T, class Alloc>
		bool operator<  (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

	/*
	** @brief Compare list container to know
	** if "lhs" elements are lexicographicalement less or equal than "rhs".
	**
	** @param lhs list to compare with "rhs".
	** @param rhs list for comparison of "lhs".
	** @return true if "lhs" is lexicographicalement less or equal, false otherwise.
	*/
	template <class T, class Alloc>
		bool operator<= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
		{
			return (!(rhs < lhs));
		}

	/*
	** @brief Compare list container to know
	** if "lhs" elements are lexicographicalement superior than "rhs".
	**
	** @param lhs list to compare with "rhs".
	** @param rhs list for comparison of "lhs".
	** @return true if "lhs" is lexicographicalement superior, false otherwise.
	*/
	template <class T, class Alloc>
		bool operator>  (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
		{
			return (rhs < lhs);
		}

	/*
	** @brief Compare list container to know
	** if "lhs" elements are lexicographicalement superior or equal than "rhs".
	**
	** @param lhs list to compare with "rhs".
	** @param rhs list for comparison of "lhs".
	** @return true if "lhs" is lexicographicalement superior or equal, false otherwise.
	*/
	template <class T, class Alloc>
		bool operator>= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
		{
			return (!(lhs < rhs));
		}

	/*
	** @brief Overload of swap (list).
	** The contents of container are swaped.
	**
	** @param x, y the containers to swap.
	*/
	template <class T, class Alloc>
		void swap (ft::list<T,Alloc>& x, ft::list<T,Alloc>& y)
		{
			x.swap(y);
		}
}


#endif