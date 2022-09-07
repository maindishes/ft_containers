/**
 * @file vector.hpp
 * @author Minjune (minjune8506@gmail.com)
 * @brief Vector reimplementation
 * @date 2022-07-21
 */
#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "random_access_iterator.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"
#include <memory>
#include <stdexcept>

namespace ft
{
/**
 * @brief Vector
 * Vectors are sequence containers representing arrays that can change in size.
 * Just like arrays, vectors use contiguous storage locations for their elements,
 * which means that their elements can also be accessed using offsets on regular pointers to its elements, and just as efficiently as in arrays.
 * But unlike arrays, their size can change dynamically, with their storage being handled automatically by the container.
 * @tparam T Type of the elements.
 * @tparam Alloc Type of the allocator object used to define the storage allocation model
 */
template <typename T, typename Alloc = std::allocator<T> >
class vector {
private:
	typedef vector<T, Alloc>							vector_type;

public:
	typedef T											value_type;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef ft::random_access_iterator<pointer>			iterator;
	typedef ft::random_access_iterator<const_pointer>	const_iterator;
	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
	typedef ptrdiff_t									differece_type;
	typedef size_t										size_type;

protected:
	allocator_type	allocator;
	pointer			start_;
	pointer			finish_;
	pointer			end_of_storage_;
	void assign_aux(size_type n, const value_type &val, ft::true_type);
	template <typename InputIterator>
	void assign_aux(InputIterator first, InputIterator last, ft::false_type);
	void initialize_aux(size_type n, const value_type &val, true_type);
	template <typename InputIterator>
	void initialize_aux(InputIterator first, InputIterator last, false_type);
	void insert_aux(iterator position, size_type n, const value_type &val, ft::true_type);
	template <typename InputIterator>
	void insert_aux(iterator position, InputIterator first, InputIterator last, ft::false_type);
public:
	/** Member Functions **/
	/**
	 * @brief empty container constructor (default constructor)
	 * Constructs an empty container, with no elements.
	 */
	explicit vector(const allocator_type &alloc = allocator_type()) : allocator(alloc), start_(0), finish_(0), end_of_storage_(0) { }

	/**
	 * @brief fill constructor
	 * Constructs a container with n elements. Each element is a copy of val.
	 */
	explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : allocator(alloc) {
		initialize_aux(n, val, true_type());
	}
	
	/**
	 * @brief range constructor
	 * Constructs a container with as many elements as the range [first,last),
	 * with each element constructed from its corresponding element in that range, in the same order.
	 */
	template <typename InputIterator>
	vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : allocator(alloc) {
		typedef typename ft::is_integral<InputIterator>::Integral _Integral;
		initialize_aux(first, last, _Integral());
	}

	/**
	 * @brief copy constructor
	 * Constructs a container with a copy of each of the elements in x, in the same order.
	 */
	vector(const vector<T, Alloc>& x) : allocator(x.allocator) {
		size_type n = x.size();
		start_ = allocator.allocate(n);
		finish_ = start_;
		end_of_storage_ = start_ + n;
		pointer x_start = x.start_;
		while (n--) {
			allocator.construct(finish_, *x_start);
			finish_++, x_start++;
		}
	}

	/**
	 * @brief Vector destructor
	 * Destroys the container object.
	 */
	virtual ~vector() {
		clear();
		allocator.deallocate(start_, capacity());
	}
	
	/**
	 * @brief Assign content
	 * Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.
	 * @return *this
	 */
	vector_type &operator=(const vector_type &x) {
		if (this != &x) {
			clear();
			allocator.deallocate(start_, capacity());
			size_type n = x.size();
			start_ = allocator.allocate(n);
			finish_ = start_;
			end_of_storage_ = start_ + n;
			pointer x_start = x.start_;
			while (n--) {
				allocator.construct(finish_, *x_start);
				finish_++, x_start++;
			}
		}
		return *this;
	}

	/** Iterators **/
	iterator begin() { return iterator(start_); }
	const_iterator begin() const { return const_iterator(start_); }
	iterator end() { return iterator(finish_); }
	const_iterator end() const { return const_iterator(finish_); }
    reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

	/** Capacity **/
	/**
	 * @brief Returns the number of elements in the vector.
	 */
	size_type size() const { return size_type(end() - begin()); }
	/**
	 * @brief Returns the maximum number of elements that the vector can hold.
	 */
	size_type max_size() const { return (allocator.max_size() < PTRDIFF_MAX) ? allocator.max_size() : PTRDIFF_MAX;}
	/**
	 * @brief Resizes the container so that it contains n elements.
	 */
	void resize(size_type n, value_type val = value_type()) {
		if (n < size())
      		erase(begin() + n, end());
    	else
      		insert(end(), n - size(), val);
	}
	/**
	 * @brief Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
	 */
	size_type capacity() const { return size_type(end_of_storage_ - start_); }
	/**
	 * @brief Returns whether the vector is empty (i.e. whether its size is 0).
	 */
	bool empty() const { return start_ == finish_; }
	/**
	 * @brief Requests that the vector capacity be at least enough to contain n elements.
	 */
	void reserve(size_type n) {
		if (n > max_size()) {
			throw std::length_error("ft_vector");
		}
		if (n > capacity()) {
			pointer prev_start_ = start_;
			pointer prev_finish_ = finish_;
			size_type prev_capacity_ = capacity();

			start_ = allocator.allocate(n);
			finish_ = start_;
			end_of_storage_ = start_ + n;
			for (pointer it = prev_start_ ; it != prev_finish_ ; it++, finish_++) {
				allocator.construct(finish_, *it);
			}
			pointer temp = prev_start_;
			while (temp != prev_finish_)
				allocator.destroy(temp++);
			allocator.deallocate(prev_start_, prev_capacity_);
		}
	}

	/** Element access **/

	/**
	 * @brief Access element
	 * Returns a reference to the element at position n in the vector container.
	 * @return reference / const_reference
	 */
	reference operator[](size_type n) { return *(begin() + n); }
	const_reference operator[](size_type n) const { return *(begin() + n); }
	/**
	 * @brief Access element
	 * Returns a reference to the element at position n in the vector.
	 * @return reference / const_reference
	 */
	reference at(size_type n) {
		if (n >= size()) {
			throw std::out_of_range("ft_vector");
		}
		return (*this)[n];
	}
	const_reference at(size_type n) const {
		if (n >= size()) {
			throw std::out_of_range("ft_vector");
		}
		return (*this)[n];
	}
	/**
	 * @brief Access first element
	 * Returns a reference to the first element in the vector.
	 * @return reference / const_reference
	 */
	reference front() {
		return *begin();
	}
	const_reference front() const {
		return *begin();
	}
	/**
	 * @brief Access last element
	 * Returns a reference to the last element in the vector.
	 * @return reference / const_reference
	 */
    reference back() {
		return *(end() - 1);
	}
	const_reference back() const {
		return *(end() - 1);
	}

	/** Modifiers **/
	
	/**
	 * @brief Assign vector content
	 * Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
	 * 1) the new contents are elements constructed from each of the elements in the range [first, last), in the same order.
	 * 2) the new contents are n elements, each initialized to a copy of val.
	 */
	template <typename InputIterator>
	void assign(InputIterator first, InputIterator last) {
		typedef typename ft::is_integral<InputIterator>::Integral Integral_;
		assign_aux(first, last, Integral_());
	}

	void assign(size_type n, const value_type& val) {
		assign_aux(n, val, true_type());
	}

	/**
	 * @brief Add element at the end
	 * Adds a new element at the end of the vector, after its current last element.
	 * @param val 
	 */
	void push_back(const value_type& val) {
		if (finish_ == end_of_storage_) {
			size_type new_capacity = (capacity() == 0) ? 1 : capacity() * 2;
			reserve(new_capacity);
		}
		allocator.construct(finish_, val);
		++finish_;
	}

	/**
	 * @brief Delete last element
	 * Removes the last element in the vector, effectively reducing the container size by one.
	 */
	void pop_back() {
		--finish_;
		allocator.destroy(finish_);
	}

	/**
	 * @brief Insert elements
	 * The vector is extended by inserting new elements before the element at the specified position,
	 * effectively increasing the container size by the number of elements inserted.
	 * single element (1) iterator insert (iterator position, const value_type& val);
	 * fill (2) void insert (iterator position, size_type n, const value_type& val);
	 * range (3) void insert (iterator position, InputIterator first, InputIterator last);
	 */
	iterator insert(iterator position, const value_type& val) {
		size_type n = position - begin();
		insert(position, 1, val);
		return begin() + n;
	}

	void insert(iterator position, size_type n, const value_type& val) {
		insert_aux(position, n, val, ft::true_type());
	}

	template <typename InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last) {
		typedef typename ft::is_integral<InputIterator>::Integral _Integral;
		insert_aux(position, first, last, _Integral());
	}
	/**
	 * @brief Erase elements
	 * Removes from the vector either a single element (position) or a range of elements [first,last).
	 */
	iterator erase(iterator position) {
		if (position + 1 != end())
			ft::copy(position + 1, end(), position);
		--finish_;
		allocator.destroy(finish_);
		return position;
	}

	iterator erase(iterator first, iterator last) {
		iterator it(ft::copy(last, end(), first)); // copy (reference)
		while (it != end()) {
			allocator.destroy(&*it);
			++it;
		}
		finish_ = finish_ - (last - first);
		return first;
	}

	/**
	 * @brief Swap content
	 * Exchanges the content of the container by the content of x, which is another vector object of the same type.
	 * Sizes may differ.
	 */
	void swap(vector_type& x) {
		ft::swap(start_, x.start_);
		ft::swap(finish_, x.finish_);
		ft::swap(end_of_storage_, x.end_of_storage_);
	}
	/**
	 * @brief Clear content
	 * Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
	 */
	void clear() {
		while (start_ != finish_) {
			allocator.destroy(--finish_);
		}
	}

	/** Allocator **/
	allocator_type get_allocator() const {
		return allocator;
	}
};

/** Non-member function overloads **/
/** relational operators **/
template <typename T, typename Alloc>
inline bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{ return (lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }

template <typename T, typename Alloc>
inline	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{ return !(lhs == rhs); }

template <typename T, typename Alloc>
inline	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

template <typename T, typename Alloc>
inline	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{ return !(rhs < lhs); }

template <typename T, typename Alloc>
inline	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{ return rhs < lhs; }

template <typename T, typename Alloc>
inline	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{ return !(lhs < rhs); }

template <typename T, typename Alloc>
inline void swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
{ x.swap(y); }

/** auxiliary methods **/
template <typename T, typename Alloc>
void ft::vector<T, Alloc>::assign_aux(size_type n, const value_type &val, ft::true_type) {
	size_type prev_capacity = capacity();
	clear();
	if (prev_capacity < n) {
		allocator.deallocate(start_, prev_capacity);
		start_ = allocator.allocate(n);
		finish_ = start_;
		end_of_storage_ = start_ + n;
	}
	while (n--) {
		allocator.construct(finish_++, val);
	}
}

template <typename T, typename Alloc>
template <typename InputIterator>
void ft::vector<T, Alloc>::assign_aux(InputIterator first, InputIterator last, ft::false_type) {
	size_type n = ft::distance(first, last);
	size_type prev_capacity = capacity();
	clear();
	if (prev_capacity < n) {
		allocator.deallocate(start_, prev_capacity);
		start_ = allocator.allocate(n);
		finish_ = start_;
		end_of_storage_ = start_ + n;
	}
	while (first != last) {
		allocator.construct(finish_, *first);
		++finish_; ++first++;
	}
}

template <typename T, typename Alloc>
void ft::vector<T, Alloc>::initialize_aux(size_type n, const value_type &val, ft::true_type) {
	start_ = allocator.allocate(n);
	finish_ = start_;
	end_of_storage_ = start_ + n;
	while (n--)
		allocator.construct(finish_++, val);
}

template <typename T, typename Alloc>
template <typename InputIterator>
void ft::vector<T, Alloc>::initialize_aux(InputIterator first, InputIterator last, ft::false_type) {
	size_type n = ft::distance(first, last);
	start_ = allocator.allocate(n);
	finish_ = start_;
	end_of_storage_ = start_ + n;
	while (n--) {
		allocator.construct(finish_, *first);
		++finish_; ++first;
	}
}

template <typename T, typename Alloc>
void ft::vector<T, Alloc>::insert_aux(iterator position, size_type n, const value_type &val, ft::true_type) {
	size_type pos = position - begin();

	if (n >= 0) {
		if (capacity() >= size() + n) {
			size_type after = size() - pos;
			for (size_type i = 1 ; i <= after ; i++) {
				allocator.construct(finish_ + n - i, *(finish_ - i));
				allocator.destroy(finish_ - i);
			}
			finish_ += n;
			for (size_type i = 0 ; i < n ; i++) {
				allocator.construct(start_ + pos + i, val);
			}
			return ;
		}
		pointer prev_start = start_;
		size_type prev_size = size();
		size_type prev_capacity = capacity();

		size_type new_capacity = prev_capacity + ft::max(prev_capacity, n);
		start_ = allocator.allocate(new_capacity);
		finish_ = start_;
		end_of_storage_ = start_ + new_capacity;

		for (size_type i = 0 ; i < pos ; i++) {
			allocator.construct(finish_++, *(prev_start + i));
			allocator.destroy(prev_start + i);
		}
		for (size_type i = 0 ; i < n ; i++) {
			allocator.construct(finish_++, val);
		}
		for (size_type i = 0 ; i < prev_size - pos ; i++) {
			allocator.construct(finish_++, *(prev_start + pos + i));
			allocator.destroy(prev_start + pos + i);
		}
		allocator.deallocate(prev_start, prev_capacity);
	}
}

template <typename T, typename Alloc>
template <typename InputIterator>
void ft::vector<T, Alloc>::insert_aux(iterator position, InputIterator first, InputIterator last, ft::false_type) {
	size_type pos = position - begin();
	size_type n = ft::distance(first, last);
	if (n != 0) {
		if (capacity() >= size() + n) {
			size_type after = size() - pos;
			for (size_type i = 1 ; i <= after ; i++) {
				allocator.construct(finish_ + n - i, *(finish_ - i));
				allocator.destroy(finish_ - i);
			}
			finish_ += n;
			for (size_type i = 0 ; i < n ; i ++) {
				allocator.construct(start_ + pos + i, *first);
				first++;
			}
			return ;
		}
		size_type after = size() - pos;
		pointer prev_start = start_;
		size_type prev_capacity = capacity();

		size_type new_capacity = prev_capacity + ft::max(prev_capacity, n);
		start_ = allocator.allocate(new_capacity);
		finish_ = start_;
		end_of_storage_ = start_ + new_capacity;
		for (size_type i = 0 ; i < pos ; i++) {
			allocator.construct(finish_++, *(prev_start + i));
			allocator.destroy(prev_start + i);
		}
		for (size_type i = 0 ; i < n ; i++) {
			allocator.construct(finish_++, *first);
			first++;
		}
		for (size_type i = 0 ; i < after ; i++) {
			allocator.construct(finish_++, *(prev_start + pos + i));
			allocator.destroy(prev_start + pos + i);
		}
		allocator.deallocate(prev_start, prev_capacity);
	}
}
} // namespace ft

#endif

