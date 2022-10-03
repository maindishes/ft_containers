#ifndef RBTREE_ITERATOR
#define RBTREE_ITERATOR

// #include <cstddef> // std::ptrdiff_t
// #include "rbtree.hpp"
// #include "iterator_traits.hpp" // iterator_tag

namespace ft
{
    template <typename Val>
    class rbtree_iterator
    {
	public:
		typedef Val value_type;
		typedef Val *pointer;
		typedef Val &reference;
		typedef rbtree_iterator<Val> self_type;
		typedef ft::bidirectional_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;
		typedef ft::rbtree_node<Val> node_type;
		typedef typename node_type::node_ptr node_ptr;

        // OCCF
		rbtree_iterator() // default
			: _node(0)
		{
		}

		explicit rbtree_iterator(node_ptr x) // initialization
			: _node(x)
		{
		}

		template <typename T>
		rbtree_iterator(const rbtree_iterator<T> &rhs) // copy-constructor
			: _node(rhs._node)
		{
		}

		virtual ~rbtree_iterator() // destructor
		{
		}

		template <typename T>
		self_type &operator=(const rbtree_iterator<T> &rhs) // copy-assignment
		{
			_node = rhs._node;
			return *this;
		}

		// operators
		reference operator*() const
		{
			return _node->data;
		}

		self_type &operator++()
		{
			_node = _increment(_node);
			return *this;
		}

		self_type operator++(int)
		{
			self_type tmp(*this);
			++(*this);
			return tmp;
		}

		self_type &operator--()
		{
			_node = _decrement(_node);
			return *this;
		}

		self_type operator--(int)
		{
			self_type tmp(*this);
			--(*this);
			return tmp;
		}

		pointer operator->() const
		{
			return &(_node->data);
		}

		friend bool operator==(const self_type &lhs, const self_type &rhs)
		{
			return (lhs._node == rhs._node);
		}

		friend bool operator!=(const self_type &lhs, const self_type &rhs)
		{
			return (lhs._node != rhs._node);
		}

		// Member variables
		node_ptr _node;

		private:
			node_ptr _increment(node_ptr x)
			{
				// Case 1: right child exist, return leftmost node
				if (!node_type::isTNULL(x->right))
				{
					return node_type::minimum(x->right);
				}
				// backup _TNULL
				node_ptr _TNULL = x->right;
				// Case 2: up until it came from left
				while (x->parent)
				{
					if (x->parent->left == x)
					{
						return x->parent;
					}
					x = x->parent;
				}
				// Case 3: return TNULL
				return _TNULL;
			}

			node_ptr _decrement(node_ptr x)
			{
				// Case 0: if x is end
				if (node_type::isTNULL(x))
				{
					return node_type::maximum(x->parent);
				}
				// Case 1: left child exist, return rightmost node
				if (!node_type::isTNULL(x->left))
				{
					return node_type::maximum(x->left);
				}
				// Case 2: up until it came from right
				while (x->parent)
				{
					if (x->parent->right == x)
					{
						return x->parent;
					}
					x = x->parent;
				}
				// Case 3: return NULL
				return NULL;
			}
	};

	template <typename Val>
    class rbtree_const_iterator
    {
	public:
		typedef Val value_type;
		typedef const Val *pointer;
		typedef const Val &reference;
		typedef rbtree_const_iterator<Val> self_type;
		typedef ft::bidirectional_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;
		typedef ft::rbtree_node<Val> node_type;
		typedef typename node_type::const_node_ptr node_ptr;

        // OCCF
		rbtree_const_iterator() // default
			: _node(NULL)
		{
		}

		explicit rbtree_const_iterator(node_ptr x) // initialization
			: _node(x)
		{
		}

		template <typename T>
		rbtree_const_iterator(const rbtree_iterator<T> &rhs) // copy-constructor
			: _node(rhs._node)
		{
		}

		template <typename T>
		rbtree_const_iterator(const rbtree_const_iterator<T> &rhs) // copy-constructor
			: _node(rhs._node)
		{
		}

		virtual ~rbtree_const_iterator() // destructor
		{
		}

		template <typename T>
		self_type &operator=(const rbtree_const_iterator<T> &rhs) // copy-assignment
		{
			_node = rhs._node;
			return *this;	
		}

		template <typename T>
		self_type &operator=(const rbtree_iterator<T> &rhs) // copy-assignment
		{
			_node = rhs._node;
			return *this;
		}

		// operators
		reference operator*() const
		{
			return _node->data;
		}

		self_type &operator++()
		{
			_node = _increment(_node);
			return *this;
		}

		self_type operator++(int)
		{
			self_type tmp(*this);
			++(*this);
			return tmp;
		}

		rbtree_const_iterator &operator--()
		{
			_node = _decrement(_node);
			return *this;
		}

		self_type operator--(int)
		{
			self_type tmp(*this);
			--(*this);
			return tmp;
		}

		pointer operator->() const
		{
			return &(_node->data);
		}

		friend bool operator==(const self_type &lhs, const self_type &rhs)
		{
			return (lhs._node == rhs._node);
		}

		friend bool operator!=(const self_type &lhs, const self_type &rhs)
		{
			return (lhs._node != rhs._node);
		}

		// Member variables
		node_ptr _node;

		private:
			node_ptr _increment(node_ptr x)
			{
				// Case 1: right child exist, return leftmost node
				if (!node_type::isTNULL(x->right))
				{
					return node_type::minimum(x->right);
				}
				// backup _TNULL
				node_ptr _TNULL = x->right;
				// Case 2: up until it came from left
				while (x->parent)
				{
					if (x->parent->left == x)
					{
						return x->parent;
					}
					x = x->parent;
				}
				// Case 3: return TNULL
				return _TNULL;
			}

			node_ptr _decrement(node_ptr x)
			{
				// Case 0: if x is end
				if (node_type::isTNULL(x))
				{
					return node_type::maximum(x->parent);
				}
				// Case 1: left child exist, return rightmost node
				if (!node_type::isTNULL(x->left))
				{
					return node_type::maximum(x->left);
				}
				// Case 2: up until it came from right
				while (x->parent)
				{
					if (x->parent->right == x)
					{
						return x->parent;
					}
					x = x->parent;
				}
				// Case 3: return NULL
				return NULL;
			}
	};

	template <typename Val>
	bool operator==(const rbtree_iterator<Val> &lhs, const rbtree_const_iterator<Val> &rhs)
	{
		return (lhs._node == rhs._node);
	}

	template <typename Val>
	bool operator!=(const rbtree_iterator<Val> &lhs, const rbtree_const_iterator<Val> &rhs)
	{
		return (lhs._node != rhs._node);
	}

	template <typename Val>
	bool operator==(const rbtree_const_iterator<Val> &lhs, const rbtree_iterator<Val> &rhs)
	{
		return (lhs._node == rhs._node);
	}

	template <typename Val>
	bool operator!=(const rbtree_const_iterator<Val> &lhs, const rbtree_iterator<Val> &rhs)
	{
		return (lhs._node != rhs._node);
	}
} // namespace ft

#endif