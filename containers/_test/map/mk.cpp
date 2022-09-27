#ifndef MAP_HPP
#define MAP_HPP

#include "RBTree.hpp"

namespace ft
{
	/**
     * @brief Map
     * Maps are associative containers that store elements formed by a combination of a key value and a mapped value, following a specific order.
     * @tparam Key 
     * @tparam T 
     * @tparam Compare 
     * @tparam std::allocator<ft::pair<const Key, T> > 
     */
	template <typename Key, typename T, typename Compare = std::less<Key>,
				typename Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
/*
 * Member types :
 */
	public:
		// The first template parameter (Key)
		typedef Key													key_type;
		// The second template parameter (T)
		typedef T													mapped_type;
		// pair<const key_type,mapped_type>
		typedef ft::pair<const key_type, mapped_type>				value_type;
		// The third template parameter (Compare)
		typedef Compare												key_compare;
		// The fourth template parameter (Alloc)
		typedef Alloc												allocator_type;
		// allocator_type::reference
		typedef typename allocator_type::reference					reference;
		// allocator_type::const_reference
		typedef typename allocator_type::const_reference			const_reference;
		// allocator_type::pointer
		typedef typename allocator_type::pointer					pointer;
		// allocator_type::const_pointer
		typedef typename allocator_type::const_pointer				const_pointer;

		// subclass
		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class		map;
		
		protected :
			key_compare			comp;
			value_compare(key_compare c) : comp(c) {}

		public:
			typedef bool		result_type;
			bool operator()(const value_type& x, const value_type& y) const
			{ return comp(x.first, y.first); }

		};

		// tree_type
		typedef RBtree<value_type, value_compare, allocator_type>	tree_type;
		// a bidirectional iterator to value_type
		typedef typename tree_type::iterator						iterator;
		// a bidirectional iterator to const value_type
		typedef typename tree_type::const_iterator					const_iterator;
		// reverse_iterator<iterator>
		typedef typename tree_type::reverse_iterator				reverse_iterator;
		// reverse_iterator<const_iterator>
		typedef typename tree_type::const_reverse_iterator			const_reverse_iterator;
		// a signed integral type, identical to: iterator_traits<iterator>::difference_type
		typedef ptrdiff_t											difference_type;
		// an unsigned integral type that can represent any non-negative value of difference_type
		typedef size_t												size_type;
/*
 * Member variables :
 */
	private :
		tree_type			_tree;
/*
 * Member functions :
 */
	public :
		/**
		 * @brief Default constructor
		 * Constructs an empty container, with no elements.
		 * @param comp 
		 * @param alloc
		 */
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _tree(comp, alloc) {}

		/**
		 * @brief Range constructor
		 * Constructs a container with as many elements as the range [first,last),
		 * with each element constructed from its corresponding element in that range.
		 * @tparam InputIterator 
		 * @param first Input iterators to the initial position in a range.
		 * @param last Input iterators to the final position in a range.
		 * @param comp Binary predicate that, taking two element keys as argument, returns true if the first
		 * argument goes before the second argument in the strict weak ordering it defines, and false otherwise.
		 * @param alloc Allocator object
		 */
		template<typename InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _tree(comp, alloc)
		{ this->insert(first, last); }

		/**
		 * @brief Copy constructor
		 * Constructs a container with a copy of each of the elements in x.
		 * @param x Another map object of the same type, whose contents are either copied or acquired.
		 */
		map(const map& x) : _tree(x._tree) {}

		/**
		 * @brief Map destructor
		 * This destroys all container elements, and deallocates all the storage
		 * capacity allocated by the map container using its allocator.
		 */
		~map() {}

		/**
		 * @brief Assign content
		 * Assigns new contents to the container, replacing its current content.
		 * @param x A map object of the same type.
		 * @return map& 
		 */
		map& operator= (const map& x)
		{
			if (this != &x)
				this->_tree = x._tree;
			return *this;
		}

		/* Iterators */

		iterator begin() { return this->_tree.begin(); }
		const_iterator begin() const { return this->_tree.begin(); }
		iterator end() { return this->_tree.end(); }
		const_iterator end() const { return this->_tree.end(); }
		reverse_iterator rbegin() { return this->_tree.rbegin(); }
		const_reverse_iterator rbegin() const { return this->_tree.rbegin(); }
		reverse_iterator rend() { return this->_tree.rend(); }
		const_reverse_iterator rend() const { return this->_tree.rend(); }

		/* Capacity */

		bool empty() const { return this->_tree.empty(); }
		size_type size() const { return this->_tree.size(); }
		size_type max_size() const { return this->_tree.max_size(); }

		/* Element Access */

		/**
		 * @brief Access element
		 * If k matches the key of an element in the container, the function returns a reference to its mapped value.
		 * @param k Key value of the element whose mapped value is accessed.
		 * @return mapped_type& 
		 */
		mapped_type& operator[](const key_type& k)
		{
			return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
		}

		/* Modifiers */

		ft::pair<iterator, bool> insert(const value_type &val)
		{ return this->_tree.insert(val); }
		iterator insert(iterator position, const value_type &val)
		{ return this->_tree.insert(position, val); }
		template <typename InputIterator>
		void insert(InputIterator first, InputIterator last)
		{ return this->_tree.insert(first, last); }
		void erase(iterator position)
		{ this->_tree.erase(position); }
		size_type erase(const key_type &k)
		{ return this->_tree.erase(ft::make_pair(k, mapped_type())); }
		void erase(iterator first, iterator last)
		{ this->_tree.erase(first, last); }
		void swap(map &x)
		{ this->_tree.swap(x._tree); }
		void clear()
		{ this->_tree.clear(); }

		/* Observers */

		key_compare key_comp() const
		{ return key_compare(); }
		value_compare value_comp() const
		{ return this->_tree.value_comp(); }

		/* Operations */

		iterator find(const key_type &k)
		{ return this->_tree.find(ft::make_pair(k, mapped_type())); }

		const_iterator find(const key_type &k) const
		{ return this->_tree.find(ft::make_pair(k, mapped_type())); }

		size_type count(const key_type &k) const
		{ return this->_tree.count(ft::make_pair(k, mapped_type())); }

		iterator lower_bound(const key_type &k)
		{ return this->_tree.lower_bound(ft::make_pair(k, mapped_type())); }

		const_iterator lower_bound(const key_type &k) const
		{ return this->_tree.lower_bound(ft::make_pair(k, mapped_type())); }

		iterator upper_bound(const key_type &k)
		{ return this->_tree.upper_bound(ft::make_pair(k, mapped_type())); }

		const_iterator upper_bound(const key_type &k) const
		{ return this->_tree.upper_bound(ft::make_pair(k, mapped_type())); }

		ft::pair<iterator, iterator> equal_range(const key_type &k)
		{ return this->_tree.equal_range(ft::make_pair(k, mapped_type())); }

		ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{ return this->_tree.equal_range(ft::make_pair(k, mapped_type())); }
		
		/* Alloc */

		allocator_type get_allocator() const
		{ return this->_tree.get_allocator(); }
	};

/*
* Non-Member overloads :
*/
	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{ return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }

	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{ return !(lhs == rhs); }

	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{ return rhs < lhs; }

	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{ return !(rhs < lhs); }

	template <typename Key, typename T, typename Compare, typename Alloc>
	inline bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{ return !(lhs < rhs); }

	template <typename Key, typename T, typename Compare, typename Alloc>
	void swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y)
	{ x.swap(y); }
}

#endif