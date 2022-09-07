#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"
#include <memory>
#include <stdexcept>
#include <cassert>

namespace ft
{
	/**
	 * @brief Vector
	 * Vectors are sequence containers representing arrays that can change in size.
	 * @tparam T 
	 * @tparam Alloc 
	 */
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
/*
 * Member types :
 */
	private :
		typedef vector<T, Alloc> vector_type;

	public :
		// The first template parameter (T)
		typedef T																value_type;
		// The second template parameter (Alloc)
		typedef Alloc															allocator_type;
		// allocator_type::reference
		typedef typename allocator_type::reference								reference;
		// allocator_type::const_reference
		typedef typename allocator_type::const_reference						const_reference;
		// allocator_type::pointer
		typedef typename allocator_type::pointer								pointer;
		// allocator_type::const_pointer
		typedef typename allocator_type::const_pointer							const_pointer;
		// 	a random access iterator to value_type
		typedef ft::random_access_iterator<pointer, vector_type>				iterator;
		// a random access iterator to const value_type
		typedef ft::random_access_iterator<const_pointer, vector_type>			const_iterator;
		// reverse_iterator<iterator>
		typedef typename ft::reverse_iterator<iterator>							reverse_iterator;
		// reverse_iterator<const_iterator>
		typedef typename ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		// 	a signed integral type, identical to: iterator_traits<iterator>::difference_type
		typedef std::ptrdiff_t													difference_type;
		// an unsigned integral type that can represent any non-negative value of difference_type
		typedef std::size_t														size_type;

/*
 * Member variables :
 */
	protected :
		allocator_type		_alloc;
		pointer				_start;
		pointer				_end;
		pointer				_end_capacity;

/*
 * Member functions :
 */
	public :
		/**
		 * @brief Default constructor
		 * Constructs an empty container, with no elements.
		 * @param alloc 
		 */
		explicit vector(const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _start(0), _end(0), _end_capacity(0) {}
		
		/**
		 * @brief Fill constructor
		 * Constructs a container with n elements. Each element is a copy of val.
		 * @param n 
		 * @param val 
		 * @param alloc 
		 */
		explicit vector(size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
			: _alloc(alloc)
		{
			this->_start = this->_alloc.allocate(n);
			this->_end = this->_start;
			this->_end_capacity = this->_start + n;
			while (n--)
				this->_alloc.construct(this->_end++, val);
		}
		
		/**
		 * @brief Range constructor
		 * Constructs a container with as many elements as the range[first, last), with each
		 * element constructed from its corresponding element in that range, in the same order.
		 * @tparam InputIterator 
		 * @param first 
		 * @param last 
		 * @param alloc 
		 */
		template <typename InputIterator>
		vector(InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			: _alloc(alloc)
		{
			size_type n = ft::difference(first, last);
			this->_start = this->_alloc.allocate(n);
			this->_end_capacity = this->_start + n;
			this->_end = this->_start;
			while (n--)
				this->_alloc.construct(this->_end++, *first++);
		}
		
		/**
		 * @brief Copy constructor
		 * Constructs a container with a copy of each of the elements in x, in the same order.
		 * @param x 
		 */
		vector(const vector& x) : _alloc(x._alloc)
		{
			size_type n = x.size();
			this->_start = this->_alloc.allocate(n);
			this->_end_capacity = this->_start + n;
			this->_end = this->_start;
			pointer x_start = x._start;
			while (n--)
				this->_alloc.construct(this->_end++, *x_start++);
		}

		/**
		 * @brief Vector destructor
		 * This destroys all container elements, and deallocates all the storage
		 * capacity allocated by the vector using its allocater.
		 */
		~vector()
		{
			this->clear();
			this->_alloc.deallocate(this->_start, this->capacity());
		}

		/**
		 * @brief Assign content
		 * Assigns new contents to the container, replacing its
		 * current contents, and modifying its size accordingly.
		 * @param x A vector object of the same type.
		 * @return vector& 
		 */
		vector& operator=(const vector& x)
		{
			if (*this == x)
				return *this;
			this->clear();
			this->_alloc.deallocate(this->_start, this->capacity());
			size_type n = x.size();
			this->_start = this->_alloc.allocate(n);
			this->_end = this->_start;
			this->_end_capacity = this->_start + n;
			pointer x_start = x._start;
			while (n--)
				this->_alloc.construct(this->_end++, *x_start++);
			return *this;
		}

		/* Iterators */

		/**
		 * @brief Return iterator to beginning
		 * Returns an iterator pointing to the first element in the vector.
		 * 
		 * @return iterator / const_iterator
		 */
		iterator begin() { return iterator(this->_start); }
		const_iterator begin() const { return const_iterator(this->_start); }

		/**
		 * @brief Return iterator to end
		 * Returns an iterator referring to the past-the-end element in the vector.
		 * The past-the-end element is the theoretical element that would follow the last element in the vector.
		 * @return iterator / const_iterator
		 */
		iterator end() { return iterator(this->_end); }
		const_iterator end() const { return const_iterator(this->_end); }

		/**
		 * @brief Return reverse iterator to reverse beginning
		 * Returns a reverse iterator pointing to the last element in the vector.
		 * 
		 * @return reverse_iterator / const_reverse_iterator
		 */
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

		/**
		 * @brief Return reverse iterator to reverse end
		 * Returns a reverse iterator pointing to the theoretical
		 * element preceding the first element in the vector.
		 * 
		 * @return reverse_iterator / const_reverse_iteroator
		 */
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		/* Capacity */

		/**
		 * @brief Return size
		 * Returns the number of elements in the vector.
		 * @return size_type 
		 */
		size_type size() const { return size_type(this->end() - this->begin()); }

		/**
		 * @brief Return maximum size
		 * Returns the maximum number of elements that the vector can hold.
		 * @return size_type 
		 */
		size_type max_size() const
		{ return (this->_alloc.max_size() > PTRDIFF_MAX ? PTRDIFF_MAX : this->_alloc.max_size()); }

		/**
		 * @brief Change size
		 * Resizes the container so that it contains n elements.
		 * @param n New container size, expressed in number of elements.
		 * @param val Object whose content is copied to the added elements 
		 * in case that n is greater than the current container size.
		 */
		void resize (size_type n, value_type val = value_type())
		{
			if (n > this->max_size())
				throw std::out_of_range("ft::vector");
			if (n < this->size())
				this->erase(this->begin() + n, this->end());
			else
				this->insert(this->end(), n - this->size(), val);
		}

		/**
		 * @brief Return size of allocated storage capacity
		 * Returns the size of the storage space currently allocted
		 * for the vector, expressed in terms of elements.
		 * @return size_type 
		 */
		size_type capacity() const { return size_type(this->_end_capacity - this->_start); }

		/**
		 * @brief Test whether vector is empty
		 * Returns whether the vector is empty.
		 * @return true 
		 * @return false 
		 */
		bool empty() const { return this->begin() == this->end(); }

		/**
		 * @brief Request a change in capacity
		 * Requests that the vector capacity be at least enough to contain n elements.
		 * @param n Minimum capacity for the vector.
		 */
		void reserve(size_type n)
		{
			if (n > this->max_size())
				throw std::out_of_range("ft::vector");
			if (this->capacity() >= n)
				return ;
			
			pointer prev_start = this->_start;
			pointer prev_end = this->_end;
			size_type prev_capacity = this->capacity();

			this->_start = this->_alloc.allocate(n);
			this->_end = this->_start;
			this->_end_capacity = this->_start + n;

			for (pointer it = prev_start; it != prev_end; it++)
				this->_alloc.construct(this->_end++, *it);
			for (pointer it = prev_start; it != prev_end; it++)
				this->_alloc.destroy(it);
			this->_alloc.deallocate(prev_start, prev_capacity);
		}

		/* Element Access */

		/**
		 * @brief Access element
		 * Returns a reference to the element at position n in the vector.
		 * @param n Position of an element in the container.
		 * @return reference / const_reference
		 */
		reference operator[](size_type n) { return *(this->begin() + n); }
		const_reference operator[](size_type n) const { return *(this->begin() + n); }

		/**
		 * @brief Access element
		 * Returns a reference to the element at position n in the vector.
		 * The function automatically checks whether n is within the bounds of valid
		 * elements in the vector, throwing an out_of_range exception if it is not.
		 * @param n Position of an element in the container.
		 * @return reference / const_reference
		 */
		reference at(size_type n)
		{
			if (n >= size())
				throw std::out_of_range("ft::vector");
			return (*this)[n];
		}
		const_reference at(size_type n) const
		{
			if (n >= size())
				throw std::out_of_range("ft::vector");
			return (*this)[n];
		}

		/**
		 * @brief Access first element
		 * Returns a reference to the first element in the vector.
		 * @return reference / const_reference
		 */
		reference front() { return *begin(); }
		const_reference front() const { return *begin(); }

		/**
		 * @brief Access last element
		 * Returns a reference to the last element in the vector.
		 * @return reference / const_reference
		 */
		reference back() { return *(end() - 1); }
		const_reference back() const { return *(end() - 1); }

		/* Modifiers */

		/**
		 * @brief Assign vector content (Range version)
		 * Assign new contents to the vector, replacing its
		 * current contents, and modifying its size accordingly.
		 * @tparam InputIterator 
		 * @param first Input iterators to the initial position in a sequence.
		 * @param last Input iterators to the final position in a sequence.
		 */
		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			size_type n = ft::difference(first, last);
			this->clear();
			if (this->capacity() < n)
			{
				this->_alloc.deallocate(this->_start, this->capacity());
				this->_start = this->_alloc.allocate(n);
				this->_end = this->_start;
				this->_end_capacity = this->_start + n;
			}
			while (n--)
				this->_alloc.construct(this->_end++, *first++);
		}

		/**
		 * @brief Assign vector content (Fill version)
		 * Assign new contents to the vector, replacing its
		 * current contents, and modifying its size accordingly.
		 * @param n New size for the container.
		 * @param val Value to fill the container with.
		 */
		void assign(size_type n, const value_type &val)
		{
			this->clear();
			if (this->capacity() < n)
			{
				this->_alloc.deallocate(this->_start, this->capacity());
				this->_start = this->_alloc.allocate(n);
				this->_end = this->_start;
				this->_end_capacity = this->_start + n;
			}
			while (n--)
				this->_alloc.construct(this->_end++, val);
		}
		
		/**
		 * @brief Add element at the end
		 * Adds a new element at the end of the vector, after its current last element.
		 * @param val Value to be copied(or moved) to the new element.
		 */
		void push_back(const value_type &val)
		{
			if (this->_end == this->_end_capacity)
			{
				size_type capacity = (this->capacity() == 0) ? 1 : this->capacity() * 2;
				this->reserve(capacity);
			}
			this->_alloc.construct(this->_end++, val);
		}

		/**
		 * @brief Delete last element
		 * Removes the last element in the vector, effectively reducing the container size by one.
		 */
		void pop_back()
		{
			this->_alloc.destroy(--this->_end);
		}

		/**
		 * @brief Insert elements (Single element)
		 * The vector is extended by inserting new elements before the element at the specified
		 * position, effectively increasing the container size by the number of elements inserted.
		 * @param position Position in the vector where the new elements are inserted.
		 * @param val Value to be copied(or moved) to the inserted elements.
		 * @return iterator 
		 */
		iterator insert(iterator position, const value_type &val)
		{
			size_type pos = position - this->begin();
			this->insert(position, 1, val);
			return begin() + pos;
		}

		/**
		 * @brief Insert elements (Fill)
		 * The vector is extended by inserting new elements before the element at the specified
		 * position, effectively increasing the container size by the number of elements inserted.
		 * @param position Position in the vector where the new elements are inserted.
		 * @param n Number of elements to insert.
		 * @param val Value to be copied(or moved) to the inserted elements.
		 */
		void insert(iterator position, size_type n, const value_type &val)
		{
			insert_aux(position, n, val, true_type());
		}

		template <typename InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last)
		{
			typedef typename ft::is_integral<InputIterator>::type Integral;
			insert_aux(position, first, last, Integral());
		}

		void insert_aux(iterator position, size_type n, const value_type &val, true_type)
		{
			if (n < 0)
				return ;
			
			size_type pos = position - begin();

			if (this->capacity() >= this->size() + n)
			{
				for (size_type i = 1; i <= this->size() - pos; i++)
				{
					this->_alloc.construct(this->_end + n - i, *(this->_end - i));
					this->_alloc.destroy(this->_end - i);
				}
				this->_end += n;
				for (size_type i = 0; i < n; i++)
					this->_alloc.construct(this->_start + pos + i, val);
				return ;
			}

			size_type next_capacity = this->size() + n;

			pointer prev_start = this->_start;
			size_type prev_size = this->size();
			size_type prev_capacity = this->capacity();

			this->_start = this->_alloc.allocate(next_capacity);
			this->_end = this->_start;
			this->_end_capacity = this->_start + next_capacity;

			for (size_type i = 0; i < pos; i++)
			{
				this->_alloc.construct(this->_end++, *(prev_start + i));
				this->_alloc.destroy(prev_start + i);
			}

			for (size_type i = 0; i < n; i++)
				this->_alloc.construct(this->_end++, val);

			for (size_type i = 0; i < prev_size - pos; i++)
			{
				this->_alloc.construct(this->_end++, *(prev_start + pos + i));
				this->_alloc.destroy(prev_start + pos + i);
			}
			
			this->_alloc.deallocate(prev_start, prev_capacity);
		}
		
		/**
		 * @brief Insert elements (Range)
		 * The vector is extended by inserting new elements before the element at the specified
		 * position, effectively increasing the container size by the number of elements inserted.
		 * @tparam InputIterator 
		 * @param position Position in the vector where the new elements are inserted.
		 * @param first Iterator specifying a range of elements. [first, last)
		 * @param last Copies of the elements in the range are inserted at position.
		 */
		template <typename InputIterator>
		void insert_aux(iterator position, InputIterator first, InputIterator last, false_type)
		{
			size_type pos = position - begin();
			size_type n = ft::difference(first, last);
			if (n == 0)
				return ;

			if (this->capacity() >= this->size() + n)
			{
				for (size_type i = 1; i <= this->size() - pos; i++)
				{
					this->_alloc.construct(this->_end + n - i, *(this->_end - i));
					this->_alloc.destroy(this->_end - i);
				}
				this->_end += n;
				for (size_type i = 0; i < n; i++, first++)
					this->_alloc.construct(this->_start + pos + i, *first);
				return ;
			}

			size_type next_capacity = this->size() + n;

			pointer prev_start = this->_start;
			size_type prev_size = this->size();
			size_type prev_capacity = this->capacity();

			this->_start = this->_alloc.allocate(next_capacity);
			this->_end = this->_start;
			this->_end_capacity = this->_start + next_capacity;

			for (size_type i = 0 ; i < pos; i++)
			{
				this->_alloc.construct(this->_end++, *(prev_start + i));
				this->_alloc.destroy(prev_start + i);
			}

			for (size_type i = 0; i < n; i++, first++)
				this->_alloc.construct(this->_end++, *first);

			for (size_type i = 0; i < prev_size - pos; i++)
			{
				this->_alloc.construct(this->_end++, *(prev_start + pos + i));
				this->_alloc.destroy(prev_start + pos + i);
			}

			this->_alloc.deallocate(prev_start, prev_capacity);
		}

		/**
		 * @brief Erase elements
		 * Removes from the vector a single element(position).
		 * @param position Iterator pointing to a single element to be removed from the vector
		 * @return iterator 
		 */
		iterator erase(iterator position)
		{
			pointer pos = &(*position);
			if (position + 1 != this->end())
			{
				for (pointer p = pos; p + 1 != this->_end; p++)
				{
					_alloc.destroy(p);
					_alloc.construct(p, *(p + 1));
				}
			}
			this->_end--;
			_alloc.destroy(this->_end);
			return iterator(pos);
		}

		/**
		 * @brief Erase elements
		 * Removes from the vector a range of elements ([first,last)).
		 * @param first Iterators specifying a range within the vector] to be removed: [first,last).
		 * @param last 
		 * @return iterator 
		 */
		iterator erase(iterator first, iterator last)
		{
			pointer p_first = &(*first);
			pointer p_last = &(*last);
			difference_type diff = p_last - p_first;

			for (pointer p = p_first; p + diff != this->_end; p++)
			{
				this->_alloc.destroy(p);
				this->_alloc.construct(p, *(p + diff));
			}
			for (size_type s = 0; s < static_cast<size_type>(diff); s++)
			{
				this->_end--;
				this->_alloc.destroy(this->_end);
			}
			return iterator(p_first);
		}

		/**
		 * @brief Swap content
		 * Exchange the content of the container by the content of x,
		 * which is another vector object of the same type.
		 * @param x Another vector container of the same type
		 * whose content is swapped with that of this container.
		 */
		void swap(vector& x)
		{
			if (&x == this)
				return ;

			ft::swap(this->_start, x._start);
			ft::swap(this->_end, x._end);
			ft::swap(this->_end_capacity, x._end_capacity);
		}

		/**
		 * @brief Clear content
		 * Removes all elements from the vector(which are destroyed),
		 * leaving the container with a size of 0.
		 */
		void clear()
		{
			while (this->_start != this->_end)
				this->_alloc.destroy(--this->_end);
		}

		/* Alloc */

		/**
		 * @brief Get allocator
		 * Returns a copy of the allocator object associated with the vector
		 * @return allocator_type 
		 */
		allocator_type get_allocator() const
		{
			return this->_alloc;
		}
	};

/*
* Non-Member overloads :
*/

	/**
	 * @brief Relational operaors for vector
	 * Performs the appropriate comparison operation between the vector containers lhs and rhs.
	 * @tparam T 
	 * @tparam Alloc 
	 * @param lhs vector containers, having both the same template parameters. (left-hand side of the operator)
	 * @param rhs (right-hand side of the operator)
	 * @return true 
	 * @return false 
	 */
	template <typename T, typename Alloc>
	inline bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{ return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }

	template <typename T, typename Alloc>
	inline bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{ return !(lhs == rhs); }

	template <typename T, typename Alloc>
	inline bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

	template <typename T, typename Alloc>
	inline bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{ return !(rhs < lhs); }

	template <typename T, typename Alloc>
	inline bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{ return rhs < lhs; }

	template <typename T, typename Alloc>
	inline bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{ return !(lhs < rhs); }

	/**
	 * @brief Exchange contents of vectors
	 * The contents of container x are exchanged with those of y.
	 * @tparam T 
	 * @tparam Alloc 
	 * @param x vector container of the same type.
	 * @param y vector container of the same type.
	 */
	template <typename T, typename Alloc>
	void swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
	{ x.swap(y); }
}

#endif
