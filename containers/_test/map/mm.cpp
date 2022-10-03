/**
 * @file map.hpp
 * @author Minjune (minjune8506@gmail.com)
 * @brief Map header file
 * @date 2022-08-14
 */
#ifndef MAP_HPP
# define MAP_HPP

// #include <memory>		// allocator
// #include <functional>	// less
// #include "utility.hpp"	// pair
// #include "tree.hpp"		// tree

namespace ft
{
	/**
	 * @brief map
	 * STL map
	 * @tparam Key 
	 * @tparam T 
	 * @tparam Compare 
	 * @tparam std::allocator<ft::pair<const Key, T> > 
	 */
	template <	typename Key,                                     			// map::key_type
				typename T,                                       			// map::mapped_type
           		typename Compare = std::less<Key>,                     		// map::key_compare
           		typename Alloc = std::allocator<ft::pair<const Key, T> > >	// map::allocator_type
	class map {
	/** Member types **/
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef ft::pair<const key_type, mapped_type>		value_type;
		typedef Compare										key_compare;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ptrdiff_t									difference_type;
		typedef size_t										size_type;
		typedef RB_tree<Key, T, Compare, Alloc>				tree_type;
		typedef typename tree_type::iterator				iterator;
		typedef typename tree_type::const_iterator			const_iterator;
		typedef typename tree_type::reverse_iterator		reverse_iterator;
		typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;

		class value_compare : public std::binary_function<value_type, value_type, bool> {
			friend class map;
		protected:
			Compare comp;
			value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
		public:
			typedef bool		result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const
			{ return comp(x.first, y.first); }
		};

	/** Member variable **/
	private:
		tree_type tree;

	/** Member functions **/
	public:
		/** Constructors **/
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		: tree(comp, alloc) { }

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()) : tree(comp, alloc) {
			tree.insert(first, last);
		}

		// Copy Constructor
		map(const map &x) : tree(x.tree) { }

		// Assign Operator
		map &operator=(const map& x) {
			if (x != *this) {
				tree = x.tree;
			}
			return *this;
		}

		iterator begin() { return tree.begin(); }
		const_iterator begin() const { return tree.begin(); }
		iterator end() { return tree.end(); }
		const_iterator end() const { return tree.end(); }
		reverse_iterator rbegin() { return tree.rbegin(); }
		const_reverse_iterator rbegin() const { return tree.rbegin(); }
		reverse_iterator rend() { return tree.rend(); }
		const_reverse_iterator rend() const { return tree.rend(); }

		allocator_type get_allocator() const { return tree.empty(); }
		bool empty() const { return tree.empty(); }
		size_type size() const { return tree.size(); }
		size_type max_size() const { return tree.max_size(); }
		mapped_type &operator[](const key_type &k) {
			iterator it = lower_bound(k);
			if (it == end() || key_comp()(k, (*it).first))
				it = insert(it, value_type(k, T()));
			return (*it).second;
		}
		pair<iterator, bool> insert(const value_type &val) { return tree.insert(val); }
		iterator insert(iterator position, const value_type &val) { return tree.insert(position, val); }
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last) { return tree.insert(first, last); }
		void erase(iterator position) { return tree.erase(position); }
		size_type erase(const key_type &k) { return tree.erase(k); }
		void erase(iterator first, iterator last) { return tree.erase(first, last); }
		void swap(map &x) { return tree.swap(x.tree); }
		void clear() { return tree.clear(); }

		/** Observers **/
		key_compare key_comp() const { return tree.key_compare(); }
		value_compare value_comp() const { return value_compare(tree.key_compare()); }

		/** Operations **/
		iterator find(const key_type &k) { return tree.find_key(k); }
		const_iterator find(const key_type &k) const { return tree.find_key(k); }
		size_type count(const key_type &k) const { return tree.count(k); }

		iterator lower_bound(const key_type &k) { return tree.lower_bound(k); }
		const_iterator lower_bound(const key_type &k) const { return tree.lower_bound(k); }

		iterator upper_bound(const key_type &k) { return tree.upper_bound(k); }
		const_iterator upper_bound(const key_type &k) const { return tree.upper_bound(k); }
		pair<const_iterator, const_iterator> equal_range (const key_type &k) const { return tree.equal_range(k); }
		pair<iterator, iterator> equal_range (const key_type &k) { return tree.equal_range(k); }

		bool operator==(const map<Key, T, Compare, Alloc> &x) const
		{ return this->tree == x.tree; }

		bool operator<(const map<Key, T, Compare, Alloc> &x) const
		{ return this->tree < x.tree; }

		bool operator!=(const map<Key, T, Compare, Alloc> &x) const
		{ return !(this->tree == x.tree); }

		bool operator>(const map<Key, T, Compare, Alloc> &x) const
		{ return x.tree < this->tree; }

		bool operator<=(const map<Key, T, Compare, Alloc> &x) const
		{ return !(x.tree < this->tree); }

		bool operator>=(const map<Key, T, Compare, Alloc> &x) const
		{ return !(this->tree < x.tree); }
	};

template <class Key, class T, class Compare, class Alloc>
inline void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y) {
	x.swap(y);
}
}

#endif