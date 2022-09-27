#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "reverse_iterator.hpp"
#include "utility.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"
#include <memory>
#include <iostream>
#include <functional>
#include <cmath>

namespace ft
{
	enum node_color
	{ RED, BLACK };

	/* Red-Black Tree Node */

	template <typename T>
	class RBtree_node
	{
/*
 * Member types :
 */
	public :
		typedef T 								data_type;
		typedef node_color 						color_type;
		typedef RBtree_node<data_type>*			node_ptr;
		typedef const RBtree_node<data_type>*	const_node_ptr;

/*
 * Member variables :
 */
		data_type 							_data;
		color_type 							_color;
		node_ptr							_parent;
		node_ptr							_left;
		node_ptr							_right;

/*
 * Member functions :
 */
		RBtree_node() : _data(), _color(BLACK), _parent(), _left(), _right() {}
		
		RBtree_node(const RBtree_node& n)
			: _data(n._data), _color(n._color), _parent(n._parent), _left(n._left), _right(n._right) {}
		
		virtual ~RBtree_node() {}
		
		RBtree_node& operator=(const RBtree_node& n)
		{
			if (this != &n)
			{
				_data = n._data;
				_color = n._color;
				_parent = n._parent;
				_left = n._left;
				_right = n._right;
			}
			return *this;
		}

		void flip_color()
		{
			this->_color = _color == RED ? BLACK : RED;
		}
	};

	/* Tree utility functions */

	template <typename T>
	bool
	tree_is_left_child(typename RBtree_node<T>::node_ptr node)
	{
		if (node && node->_parent && node->_parent->_left)
			return node == node->_parent->_left;
		else
			return false;
	}

	template <typename T>
	bool
	tree_is_left_child(typename RBtree_node<T>::const_node_ptr node)
	{
		if (node && node->_parent && node->_parent->_left)
			return node == node->_parent->_left;
		else
			return false;
	}

	template <typename T>
	typename RBtree_node<T>::node_ptr
	tree_min(typename RBtree_node<T>::node_ptr root)
	{
		while (root->_left != NULL)
			root = root->_left;
		return root;
	}

	template <typename T>
	typename RBtree_node<T>::const_node_ptr
	tree_min(typename RBtree_node<T>::const_node_ptr root)
	{
		while (root->_left != NULL)
			root = root->_left;
		return root;
	}

	template <typename T>
	typename RBtree_node<T>::node_ptr
	tree_max(typename RBtree_node<T>::node_ptr root)
	{
		while (root->_right != NULL)
			root = root->_right;
		return root;
	}

	template <typename T>
	typename RBtree_node<T>::const_node_ptr
	tree_max(typename RBtree_node<T>::const_node_ptr root)
	{
		while (root->_right != NULL)
			root = root->_right;
		return root;
	}

	/* Red-Black Tree Iterator */

	template <typename Node_ptr, typename Value>
	class RBtree_iterator
	{
/*
 * Member types :
 */
	public :
		typedef ft::bidirectional_iterator_tag		iterator_category;
		typedef ptrdiff_t							difference_type;
		typedef Value								value_type;
		typedef Value*								pointer;
		typedef Value&								reference;

/*
 * Member variables :
 */
	private :
		Node_ptr	_node;

/*
 * Member functions :
 */
	public :
		RBtree_iterator() : _node() {}

		RBtree_iterator(const RBtree_iterator& it) : _node(it._node) {}

		RBtree_iterator(const Node_ptr& val) : _node(val) {}

		RBtree_iterator& operator=(const RBtree_iterator& it)
		{
			if (this != &it)
				_node = it._node;
			return *this;
		}

		RBtree_iterator& operator=(const Node_ptr& p)
		{
			_node = p;
			return *this;
		}

		reference operator*() const { return _node->_data; }
		pointer operator->() const { return &_node->_data; }
		
		RBtree_iterator& operator++()
		{
			if (_node->_right != NULL)
				_node = tree_min<value_type>(_node->_right);
			else
			{
				while (!tree_is_left_child<value_type>(_node))
					_node = _node->_parent;
				_node = _node->_parent;
			}
			return *this;
		}

		RBtree_iterator operator++(int)
		{
			RBtree_iterator tmp(*this);
			++(*this);
			return tmp;
		}

		RBtree_iterator& operator--()
		{
			if (_node->_left != NULL)
				_node = tree_max<value_type>(_node->_left);
			else
			{
				while (tree_is_left_child<value_type>(_node))
					_node = _node->_parent;
				_node = _node->_parent;
			}
			return *this;
		}

		RBtree_iterator operator--(int)
		{
			RBtree_iterator tmp(*this);
			--(*this);
			return tmp;
		}

		Node_ptr base() const
		{ return _node; }
	};

	template<typename Node_ptr, typename Value>
	inline bool
		operator==(const RBtree_iterator<Node_ptr, Value>& rhs, const RBtree_iterator<Node_ptr, Value>& lhs)
	{ return rhs.base() == lhs.base(); }

	template<typename Node_ptr, typename Value>
	inline bool
		operator!=(const RBtree_iterator<Node_ptr, Value>& rhs, const RBtree_iterator<Node_ptr, Value>& lhs)
	{ return rhs.base() != lhs.base(); }

/* Red-Black Tree Const Iterator */

	template <typename Const_node_ptr, typename Value>
	class RBtree_const_iterator
	{
/*
 * Member types :
 */
	public :
		typedef ft::bidirectional_iterator_tag									iterator_category;
		typedef ptrdiff_t														difference_type;
		typedef Value															value_type;
		typedef const Value*													pointer;
		typedef const Value&													reference;
		typedef RBtree_iterator<typename RBtree_node<Value>::node_ptr, Value>	RBtree_normal_iterator;

/*
 * Member variables :
 */
	private :
		Const_node_ptr	_node;

/*
 * Member functions :
 */
	public :
		RBtree_const_iterator() : _node() {}

		RBtree_const_iterator(const RBtree_const_iterator& it) : _node(it._node) {}

		RBtree_const_iterator(const RBtree_normal_iterator& it) : _node(it.base()) {}

		RBtree_const_iterator(const Const_node_ptr& val) : _node(val) {}

		RBtree_const_iterator& operator=(const RBtree_const_iterator& it)
		{
			if (this != &it)
				_node = it._node;
			return *this;
		}

		RBtree_const_iterator& operator=(const Const_node_ptr& p)
		{
			_node = p;
			return *this;
		}

		reference operator*() const { return _node->_data; }
		pointer operator->() const { return &(_node->_data); }

		RBtree_const_iterator& operator++()
		{
			if (_node->_right != NULL)
				_node = tree_min<value_type>(_node->_right);
			else
			{
				while (!tree_is_left_child<value_type>(_node))
					_node = _node->_parent;
				_node = _node->_parent;
			}
			return *this;
		}

		RBtree_const_iterator operator++(int)
		{
			RBtree_const_iterator tmp(*this);
			++(*this);
			return tmp;
		}

		RBtree_const_iterator& operator--()
		{
			if (_node->_left != NULL)
				_node = tree_max<value_type>(_node->_left);
			else
			{
				while (tree_is_left_child<value_type>(_node))
					_node = _node->_parent;
				_node = _node->_parent;
			}
			return *this;
		}

		RBtree_const_iterator operator--(int)
		{
			RBtree_const_iterator tmp(*this);
			--(*this);
			return tmp;
		}

		Const_node_ptr base() const
		{ return _node; }
	};

	template <typename Const_node_ptr, typename Value>
	inline bool
	operator==(const RBtree_const_iterator<Const_node_ptr, Value> &rhs,
			   const RBtree_const_iterator<Const_node_ptr, Value> &lhs)
	{
		return rhs.base() == lhs.base();
	}

	template <typename Const_node_ptr, typename Value>
	inline bool
	operator!=(const RBtree_const_iterator<Const_node_ptr, Value> &rhs,
			   const RBtree_const_iterator<Const_node_ptr, Value> &lhs)
	{
		return rhs.base() != lhs.base();
	}

	template <typename Const_node_ptr, typename Node_ptr, typename Value>
	inline bool
	operator==(const RBtree_const_iterator<Const_node_ptr, Value> &rhs,
			   const RBtree_iterator<Node_ptr, Value> &lhs)
	{
		return rhs.base() == lhs.base();
	}

	template <typename Const_node_ptr, typename Node_ptr, typename Value>
	inline bool
	operator!=(const RBtree_const_iterator<Const_node_ptr, Value> &rhs,
			   const RBtree_iterator<Node_ptr, Value> &lhs)
	{
		return rhs.base() != lhs.base();
	}

	template <typename Const_node_ptr, typename Node_ptr, typename Value>
	inline bool
	operator==(const RBtree_iterator<Node_ptr, Value> &rhs,
			   const RBtree_const_iterator<Const_node_ptr, Value> &lhs)
	{
		return rhs.base() == lhs.base();
	}

	template <typename Const_node_ptr, typename Node_ptr, typename Value>
	inline bool
	operator!=(const RBtree_iterator<Node_ptr, Value> &rhs,
			   const RBtree_const_iterator<Const_node_ptr, Value> &lhs)
	{
		return rhs.base() != lhs.base();
	}

	/* Red-Black Tree */

	template <typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<T> >
	class RBtree
	{
/*
 * Member types :
 */
	public :
		typedef ft::RBtree_node<T>											node_type;
		typedef T															value_type;
		typedef Compare														value_compare;
		typedef Alloc														allocator_type;
		typedef typename allocator_type::template rebind<node_type>::other	node_allocator_type;
		typedef typename allocator_type::pointer							pointer;
		typedef typename allocator_type::const_pointer						const_pointer;
		typedef typename allocator_type::reference							reference;
		typedef typename allocator_type::const_reference					const_reference;
		typedef typename allocator_type::size_type							size_type;
		typedef typename allocator_type::difference_type					difference_type;
		typedef typename node_type::node_ptr								node_ptr;
		typedef typename node_type::const_node_ptr							const_node_ptr;

		typedef ft::RBtree_iterator<node_ptr, value_type>					iterator;
		typedef ft::RBtree_const_iterator<const_node_ptr, value_type>		const_iterator;
		typedef ft::reverse_iterator<iterator>								reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;

/*
 * Member variables :
 */
	private :
		size_type				_size;
		node_type				_parent;
		node_ptr				_begin_node;
		value_compare			_compare;
		allocator_type			_allocator;
		node_allocator_type		_node_allocator;

/*
 * Member functions :
 */
	public :
		
		// Constructors
		RBtree(const value_compare& comp, const allocator_type& alloc)
			: _size(), _parent(), _begin_node(&_parent), _compare(comp), _allocator(alloc), _node_allocator(alloc) {}
		
		RBtree(const RBtree& t)
			: _size(), _parent(), _begin_node(&_parent), _compare(t._compare), _allocator(t._allocator), _node_allocator(t._node_allocator)
		{
			if (t.root() != NULL)
			{
				this->root() = this->copy(t.root());
				this->root()->_parent = &this->_parent;
			}
		}

		// Destructor
		~RBtree()
		{
			if (this->root() != NULL)
			{
				this->destroy(this->root());
				this->root() = NULL;
				this->_begin_node = this->end_node();
			}
		}

		// Operator Overload
		RBtree& operator=(const RBtree& t)
		{
			if (this != &t)
			{
				this->clear();
				this->_compare = t._compare;
				if (t.root() != NULL)
				{
					this->root() = this->copy(t.root());
					this->root()->_parent = &this->_parent;
				}
			}
			return *this;
		}

		// Iterators
		iterator begin() { return iterator(this->_begin_node); }
		const_iterator begin() const { return const_iterator(this->_begin_node); }
		iterator end() { return iterator(&this->_parent); }
		const_iterator end() const { return const_iterator(&this->_parent); }
		reverse_iterator rbegin() { return reverse_iterator(this->end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }
		reverse_iterator rend() { return reverse_iterator(this->begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }

		// Capacity
		bool empty() const { return this->_size == 0; }
		size_type size() const { return this->_size; }
		size_type max_size() const { return this->_allocator.max_size() / 5; }

		// Modifiers
		ft::pair<iterator, bool> insert(const value_type& val)
		{
			iterator it = find(val);
			if (it != end())
				return ft::make_pair<iterator, bool>(it, false);

			node_ptr new_node = this->construct_node(val);
			bool inserted = false;
			iterator pos;

			this->root() = this->insert(this->root(), new_node, inserted, pos);
			this->root()->_parent = &this->_parent;
			if (!inserted)
				this->destroy_node(new_node);
			else
				this->rebalance_after_insertion(new_node);
			this->root()->_color = BLACK;
			return ft::make_pair(pos, inserted);
		}

		iterator insert(iterator position, const value_type& val)
		{
			(void)position;
			return this->insert(val).first;
		}

		template<typename InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			for (; first != last; first++)
				this->insert(*first);
		}

		void erase(iterator position)
		{
			node_ptr pos = position.base();
			if (pos == this->_begin_node)
			{
				position++;
				this->_begin_node = position.base();
			}
			this->erase(this->root(), pos);
			if (this->root() != NULL)
			{
				this->root()->_parent = this->end_node();
				this->root()->_color = BLACK;
			}
			this->destroy_node(pos);
		}

		size_type erase(const value_type& val)
		{
			iterator pos = this->find(val);
			if (pos == this->end())
				return 0;
			this->erase(pos);
			return 1;
		}

		void erase(iterator first, iterator last)
		{
			while (first != last)
				this->erase(first++);
		}

		void swap(RBtree& t)
		{
			ft::swap(this->_begin_node, t._begin_node);
			ft::swap(this->_parent._left, t._parent._left);
			ft::swap(this->_size, t._size);
			if (this->_size != 0 && t._size != 0)
				ft::swap(this->root()->_parent, t.root()->_parent);
			else if (this->_size != 0)
				this->root()->_parent = this->end_node();
			else if (t._size != 0)
				t.root()->_parent = t.end_node();
			ft::swap(this->_compare, t._compare);
			
		}

		void clear()
		{
			if (this->root() != NULL)
			{
				this->destroy(this->root());
				this->root() = NULL;
				this->_begin_node = this->end_node();
			}
		}

		// Observer
		value_compare value_comp() const { return this->_compare; }

		// Operations
		iterator find(const value_type& val)
		{
			node_ptr node = this->root();

			while (node != NULL)
			{
				if (this->_compare(node->_data, val))
					node = node->_right;
				else if (this->_compare(val, node->_data))
					node = node->_left;
				else
					return iterator(node);
			}
			return this->end();
		}

		const_iterator find(const value_type& val) const
		{
			const_node_ptr node = this->root();

			while (node != NULL)
			{
				if (this->_compare(node->_data, val))
					node = node->_right;
				else if (this->_compare(val, node->_data))
					node = node->_left;
				else
					return const_iterator(node);
			}
			return this->end();
		}

		size_type count(const value_type& val) const
		{ return this->find(val) == this->end() ? 0 : 1; }

		iterator lower_bound(const value_type& val)
		{
			node_ptr node = this->root();
			node_ptr pos = this->end_node();

			while (node != NULL)
			{
				if (!this->_compare(node->_data, val))
				{
					pos = node;
					node = node->_left;
				}
				else
					node = node->_right;
			}
			return iterator(pos);
		}

		const_iterator lower_bound(const value_type& val) const
		{
			const_node_ptr node = this->root();
			const_node_ptr pos = this->end_node();

			while (node != NULL)
			{
				if (!this->_compare(node->_data, val))
				{
					pos = node;
					node = node->_left;
				}
				else
					node = node->_right;
			}
			return const_iterator(pos);
		}

		iterator upper_bound(const value_type& val)
		{
			node_ptr node = this->root();
			node_ptr pos = this->end_node();

			while (node != NULL)
			{
				if (this->_compare(val, node->_data))
				{
					pos = node;
					node = node->_left;
				}
				else
					node = node->_right;
			}
			return iterator(pos);
		}

		const_iterator upper_bound(const value_type& val) const
		{
			const_node_ptr node = this->root();
			const_node_ptr pos = this->end_node();

			while (node != NULL)
			{
				if (this->_compare(val, node->_data))
				{
					pos = node;
					node = node->_left;
				}
				else
					node = node->_right;
			}
			return const_iterator(pos);
		}

		ft::pair<iterator, iterator> equal_range(const value_type& val)
		{
			node_ptr node = this->root();
			node_ptr pos = this->end_node();

			while (node != NULL)
			{
				if (this->_compare(val, node->_data))
				{
					pos = node;
					node = node->_left;
				}
				else if (this->_compare(node->_data, val))
					node = node->_right;
				else
					return ft::make_pair(iterator(node), iterator(node->_right == NULL ? pos : tree_min<value_type>(node->_right)));
			}
			return ft::make_pair(iterator(pos), iterator(pos));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const value_type& val) const
		{
			const_node_ptr node = this->root();
			const_node_ptr pos = this->end_node();

			while (node != NULL)
			{
				if (this->_compare(val, node->_data))
				{
					pos = node;
					node = node->_left;
				}
				else if (this->_compare(node->_data, val))
					node = node->_right;
				else
					return ft::make_pair(const_iterator(node), const_iterator(node->_right == NULL ? pos : tree_min<value_type>(node->_right)));
			}
			return ft::make_pair(const_iterator(pos), const_iterator(pos));
		}

		// Allocator
		allocator_type get_allocator() const { return this->_allocator; }

	private :
		// utility
		node_ptr& root() { return this->_parent._left; }
		const_node_ptr& root() const { return const_cast<const_node_ptr&>(this->_parent._left); }
		node_ptr end_node() { return &this->_parent; }
		const_node_ptr end_node() const { return const_cast<const_node_ptr>(&this->_parent); }
		
		node_ptr get_sibling(node_ptr node) const
		{
			if (tree_is_left_child<value_type>(node))
				return node->_parent->_right;
			else
				return node->_parent->_left;
		}
		
		node_color get_node_color(node_ptr node)
		{
			if (node == NULL)
				return BLACK;
			else
				return node->_color;
		}

		void rotate_left(node_ptr node)
		{
			node_ptr right_node = node->_right;
			node->_right = right_node->_left;
			if (node->_right != NULL)
				node->_right->_parent = node;
			right_node->_parent = node->_parent;
			if (tree_is_left_child<value_type>(node))
				node->_parent->_left = right_node;
			else
				node->_parent->_right = right_node;
			right_node->_left = node;
			node->_parent = right_node;
		}

		void rotate_right(node_ptr node)
		{
			node_ptr left_node = node->_left;
			node->_left = left_node->_right;
			if (node->_left != NULL)
				node->_left->_parent = node;
			left_node->_parent = node->_parent;
			if (tree_is_left_child<value_type>(node))
				node->_parent->_left = left_node;
			else
				node->_parent->_right = left_node;
			left_node->_right = node;
			node->_parent = left_node;
		}

		// insertion
		node_ptr construct_node(const value_type& data)
		{
			node_ptr new_node = this->_node_allocator.allocate(1);
			this->_allocator.construct(&new_node->_data, data);
			new_node->_color = RED;
			new_node->_parent = NULL;
			new_node->_left = NULL;
			new_node->_right = NULL;
			if (this->empty() || this->_compare(data, this->_begin_node->_data))
				this->_begin_node = new_node;
			++this->_size;
			return new_node;
		}

		node_ptr copy(const_node_ptr node)
		{
			if (node == NULL)
				return NULL;
			node_ptr new_node = this->construct_node(node->_data);
			new_node->_left = copy(node->_left);
			if (new_node->_left != NULL)
				new_node->_left->_parent = new_node;
			new_node->_right = copy(node->_right);
			if (new_node->_right != NULL)
				new_node->_right->_parent = new_node;
			return new_node;
		}

		node_ptr insert(node_ptr node, node_ptr new_node, bool& inserted, iterator& pos)
		{
			if (node == NULL)
			{
				pos = new_node;
				inserted = true;
				return new_node;
			}
			if (this->_compare(node->_data, new_node->_data) == this->_compare(new_node->_data, node->_data))
			{
				node->_left = insert(node->_left, new_node, inserted, pos);
				node->_left->_parent = node;
			}
			else if (this->_compare(node->_data, new_node->_data))	// greater than
			{
				node->_right = insert(node->_right, new_node, inserted, pos);
				node->_right->_parent = node;
			}
			else if (this->_compare(new_node->_data, node->_data))	// less than
			{
				node->_left = insert(node->_left, new_node, inserted, pos);
				node->_left->_parent = node;
			}
			else	// equal
			{
				pos = node;
				inserted = false;
			}
			return node;
		}

		void rebalance_after_insertion(node_ptr node)
		{
			while (node != this->root() && this->get_node_color(node->_parent) == RED)	// Case 1 & 2
			{
				node_ptr uncle = this->get_sibling(node->_parent);
				if (this->get_node_color(uncle) == RED)	// Case 3
				{
					uncle->flip_color();
					node = node->_parent;
					node->flip_color();
					node = node->_parent;
					node->flip_color();
				}
				else if (tree_is_left_child<value_type>(node->_parent))		// Case 4
				{
					if (!tree_is_left_child<value_type>(node))		// Case 4.1
					{
						node = node->_parent;
						this->rotate_left(node);
					}
					node = node->_parent;		// Case 4.2
					node->flip_color();
					node = node->_parent;
					node->flip_color();
					this->rotate_right(node);
					break ;
				}
				else	// Case 4
				{
					if (tree_is_left_child<value_type>(node))		// Case 4.3
					{
						node = node->_parent;
						this->rotate_right(node);
					}
					node = node->_parent;		// Case 4.4
					node->flip_color();
					node = node->_parent;
					node->flip_color();
					this->rotate_left(node);
					break ;
				}
			}
		}

		// deletion
		void destroy_node(node_ptr node)
		{
			this->_allocator.destroy(&node->_data);
			this->_node_allocator.deallocate(node, 1);
			--this->_size;
		}

		void destroy(node_ptr node)
		{
			if (node == NULL)
				return ;
			destroy(node->_left);
			destroy(node->_right);
			this->destroy_node(node);
		}

		node_ptr replacement_node(node_ptr node) const
		{
			if (node->_left == NULL || node->_right == NULL)
				return node;
			else
				return tree_min<value_type>(node->_right);
		}

		void erase(node_ptr root, node_ptr node)
		{
			node_ptr replmt = this->replacement_node(node);
			node_ptr replmt_child = replmt->_left == NULL ? replmt->_right : replmt->_left;
			node_ptr sibling = NULL;

			if (replmt_child != NULL)
				replmt_child->_parent = replmt->_parent;
			if (tree_is_left_child<value_type>(replmt))
			{
				replmt->_parent->_left = replmt_child;
				if (replmt == root)
					root = replmt_child;	// sibling will be null in this case
				else
					sibling = replmt->_parent->_right;
			}
			else
			{
				// root can't be this->_parent's right child
				replmt->_parent->_right = replmt_child;
				sibling = replmt->_parent->_left;
			}

			node_color replmt_color = replmt->_color;
			
			if (replmt != node) // copy the content of node into replmt
			{
				replmt->_parent = node->_parent;
				if (tree_is_left_child<value_type>(node))
					replmt->_parent->_left = replmt;
				else
					replmt->_parent->_right = replmt;
				replmt->_left = node->_left;
				replmt->_left->_parent = replmt;
				replmt->_right = node->_right;
				if (replmt->_right != NULL)
					replmt->_right->_parent = replmt;
				replmt->_color = node->_color;
				if (node == root)
					root = replmt;
			}

			// we don't need to rebalance if we removed a red node or if there are no more nodes in the tree
			if (replmt_color == BLACK && root != NULL)		// Case 1
			{
				// replmt had either no children or one red child (replmt_child).
				// so, if replmt_child != NULL it is either red or root.
				// root can't be double black and a red node will be flipped to black.
				if (replmt_child != NULL)		// Case 2
					replmt_child->_color = BLACK;
				else
					this->rebalance_before_erasion(root, replmt_child, sibling);	// replmt_child is always NULL at the start
			}
		}

		void rebalance_before_erasion(node_ptr root, node_ptr node, node_ptr sibling)
		{
			while (true)	// (node != root && this->get_node_color(node) == BLACK)
			{
				if (!tree_is_left_child<value_type>(sibling))	// tree_is_left_child(node)
				{
					if (this->get_node_color(sibling) == RED)	// Case 3
					{
						sibling->flip_color();
						sibling->_parent->flip_color();
						this->rotate_left(sibling->_parent);
						if (root == sibling->_left)
							root = sibling;
						sibling = sibling->_left->_right;
					}
					if (this->get_node_color(sibling->_left) == BLACK && this->get_node_color(sibling->_right) == BLACK)	// Case 4
					{
						sibling->flip_color();
						node = sibling->_parent;
						if (node == root || this->get_node_color(node) == RED)
						{
							node->_color = BLACK;
							break ;
						}
						sibling = this->get_sibling(node);
					}
					else	// sibling has one red child
					{
						if (this->get_node_color(sibling->_right) == BLACK)		// Case 5
						{
							sibling->_left->flip_color();	// the left child is red
							sibling->flip_color();
							this->rotate_right(sibling);
							sibling = sibling->_parent;
						}
						sibling->_color = sibling->_parent->_color;		// Case 6
						sibling->_parent->_color = BLACK;
						sibling->_right->_color = BLACK;
						this->rotate_left(sibling->_parent);
						break ;
					}
				}
				else	// the same as before, but in reverse color
				{
					if (this->get_node_color(sibling) == RED)		// Case 3
					{
						sibling->flip_color();
						sibling->_parent->flip_color();
						this->rotate_right(sibling->_parent);
						if (root == sibling->_right)
							root = sibling;
						sibling = sibling->_right->_left;
					}
					if (this->get_node_color(sibling->_left) == BLACK && this->get_node_color(sibling->_right) == BLACK)	// Case 4
					{
						sibling->flip_color();
						node = sibling->_parent;
						if (node == root || this->get_node_color(node) == RED)
						{
							node->_color = BLACK;
							break ;
						}
						sibling = this->get_sibling(node);
					}
					else	// sibling has one red child
					{
						if (this->get_node_color(sibling->_left) == BLACK)		// Case 5
						{
							sibling->_right->flip_color();	// the right child is red
							sibling->flip_color();
							this->rotate_left(sibling);
							sibling = sibling->_parent;
						}
						sibling->_color = sibling->_parent->_color;		// Case 6
						sibling->_parent->_color = BLACK;
						sibling->_left->_color = BLACK;
						this->rotate_right(sibling->_parent);
						break ;
					}
				}
			}
		}
	};

	template<typename T, typename Compare, typename Alloc>
	void swap(RBtree<T, Compare, Alloc>& first, RBtree<T, Compare, Alloc>& second)
	{ first.swap(second); }
}

#endif