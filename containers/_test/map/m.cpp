#ifndef MAP_HPP
#define MAP_HPP

// #include "utility.hpp" // ft::pair
// #include "rbtree.hpp"
// #include "rbtree_iterator.hpp"
// #include "reverse_iterator.hpp"
// #include <functional> // std::less
// #include <cstddef>	  // std::ptrdiff_t, std::size_t
// #include <iostream>

namespace ft
{
	template <typename Key,										   // map::key_type
			  typename T,											   // map::mapped_type
			  typename Compare = std::less<Key>,					   // map::key_compare
			  typename Alloc = std::allocator<ft::pair<const Key, T> > // map::allocator_type
			  >
	class map
	{
	public:
		// Member types
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::rbtree_iterator<value_type> iterator;
		typedef ft::rbtree_const_iterator<value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;

	protected:
		typedef ft::rbtree<value_type> tree_type;
		typedef typename tree_type::node_type node_type;
		typedef typename tree_type::node_ptr node_ptr;

	public:
		class value_compare
		{
			friend class map;

		protected:
			Compare _comp;
			value_compare(Compare c) : _comp(c) {} // constructed with map's comparison object

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator()(const value_type &x, const value_type &y) const
			{
				return _comp(x.first, y.first);
			}
		};

		// Constructor
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: _comp_val(value_compare(comp)), _bst(_comp_val)
		{
		}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: _comp_val(value_compare(comp)), _bst(_comp_val)
		{
		}

		map(const map &x)
			: _comp_val(x._comp_val), _bst(_comp_val)
		{
			for (const_iterator it = x.begin(); it != x.end(); it++)
			{
				this->insert(*it);
			}
		}

		~map()
		{
			this->clear();
		}

		// Member functions
		ft::pair<iterator, bool> insert(const value_type &val)
		{
			node_ptr tmp = _bst.searchKey(val);
			if (tmp == _bst.getTNULL())
			{
				_bst.insertNode(val);
				return ft::make_pair(iterator(tmp), true);
			}
			else
			{
				return ft::make_pair(iterator(tmp), false);
			}
		}

		size_type count(const key_type &k) const
		{
			size_type n = 0;
			value_type tmp(k, mapped_type());

			for (const_iterator it = this->begin(); it != this->end(); it++)
			{
				if (_bst._equal(tmp, it))
				{
					n++;
				}
			}
			return n;
		}

		iterator begin()
		{
			node_ptr tmp = ft::rbtree_node<value_type>::minimum(_bst.getRoot());
			return (iterator(tmp));
		}

		const_iterator begin() const
		{
			node_ptr tmp = ft::rbtree_node<value_type>::minimum(_bst.getRoot());
			return (const_iterator(tmp));
		}

		iterator end()
		{
			return iterator(_bst.getTNULL());
		}

		const_iterator end() const
		{
			return const_iterator(_bst.getTNULL());
		}

		iterator find(const key_type &k)
		{
			value_type tmp(k, mapped_type());
			return iterator(_bst.searchKey(tmp));
		}

		const_iterator find(const key_type &k) const
		{
			value_type tmp(k, mapped_type());
			return const_iterator(_bst.searchKey(tmp));
		}

		key_compare key_comp() const
		{
			return key_compare();
		}

		value_compare value_comp() const
		{
			return value_compare(key_compare());
		}

		void erase(iterator position)
		{
			_bst.deleteNode(position._node);
		}

		size_type erase(const key_type &k)
		{
			node_ptr tmp = _bst.searchKey(value_type(k, mapped_type()));
			if (tmp != _bst.getTNULL())
			{
				_bst.deleteNode(tmp);
				return 1;
			}
			return 0;
		}

		void erase(iterator first, iterator last)
		{
			for (iterator it = first; it != last; ++it)
			{
				this->erase(it);
			}
		}

		void clear()
		{
			while (this->begin() != this->end())
			{
				this->erase(this->begin());
			}
		}

	private:
		value_compare _comp_val;
		ft::rbtree<value_type, value_compare, allocator_type> _bst;
	};

} // namespace ft

#endif