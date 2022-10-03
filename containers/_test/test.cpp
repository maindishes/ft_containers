\#ifndef STACK_HPP
#define STACK_HPP

// #include "vector.hpp"

namespace ft
{
	/**
	 * @brief LIFO stack
	 * Stacks are a type of container adaptor, specifically designed to operate in a LIFO context
	 * (last-in first-out), where elements are inserted and extracted only from one end of the container.
	 * @tparam T Type of the elements.
	 * @tparam Container Type of the internal underlying container object where the elements are stored.
	 */
	template <typename T, typename Container = ft::vector<T> >
	class stack
	{
/*
 * Member types :
 */
	public :
		// The first template parameter (T)
		typedef T				value_type;
		// The second template parameter (Container)
		typedef Container		container_type;
		// an unsigned integral type
		typedef size_t			size_type;
	
/*
 * Member variables :
 */
	protected :
		container_type			_c;

/*
 * Member functions :
 */
	public :
		/**
		 * @brief Construct stack
		 * Constructs a stack container adaptor object.
		 * @param ctnr Container object.
		 */
		explicit stack(const container_type& ctnr = container_type()) : _c(ctnr) {}

		/**
		 * @brief Destruct stack
		 * This destroys all container elements, and deallocates all the storage
		 * capacity allocated by the stack using its allocater.
		 */
		virtual ~stack() {}

		/**
		 * @brief Test whether container is empty
		 * Returns whether the stack is empty: i.e. whether its size is zero.
		 * @return true 
		 * @return false 
		 */
		bool empty() const { return this->_c.empty(); }

		/**
		 * @brief Return size
		 * Returns the number of elements in the stack.
		 * @return size_type 
		 */
		size_type size() const { return this->_c.size(); }

		/**
		 * @brief Access next element
		 * Returns a reference to the top element in the stack.
		 * @return value_type& / const value_type& 
		 */
		value_type& top() { return this->_c.back(); }
		const value_type& top() const { return this->_c.back(); }

		/**
		 * @brief Insert element
		 * Inserts a new element at the top of the stack, above its current top element.
		 * @param val Value to which the inserted element is initialized.
		 */
		void push(const value_type& val) { this->_c.push_back(val); }

		/**
		 * @brief Remove top element
		 * Removes the element on top of the stack, effectively reducing its size by one.
		 */
		void pop() { this->_c.pop_back(); }

		template <typename Tp, typename C>
		friend bool operator==(const stack<Tp, C>& x, const stack<Tp, C>& y);
		template <typename Tp, typename C>
		friend bool operator<(const stack<Tp, C>& x, const stack<Tp, C>& y);
	};

/*
* Non-Member overloads :
*/

	/**
	 * @brief Relational operators for stack
	 * Performs the appropriate comparison operation between lhs and rhs.
	 * @tparam T 
	 * @tparam Container 
	 * @param lhs stack object (to the left-hand side of the operator).
	 * @param rhs stack object (to the right-hand side of the operator).
	 * @return true 
	 * @return false 
	 */
	template <typename T, typename Container>
	bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return lhs._c == rhs._c; }

	template <typename T, typename Container>
	bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return lhs._c < rhs._c; }

	template <typename T, typename Container>
	bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return !(lhs == rhs); }

	template <typename T, typename Container>
	bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return !(rhs < lhs); }

	template <typename T, typename Container>
	bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return rhs < lhs; }

	template <typename T, typename Container>
	bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return !(lhs < rhs); }

}

#endif