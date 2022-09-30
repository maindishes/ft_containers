#ifndef RBTREE_ITERATOR_HPP
#define RBTREE_ITERATOR_HPP

#include "rbtree.hpp"
#include "iterator_base.hpp"
#include <cstddef> // std::ptrdiff_t

namespace ft
{
    template<typename T>
    class rbtree_iterator
    {
        typedef ft::bidirectional_iterator_tag iterator_category;
        typedef std::ptrdiff_t                      difference_type;
        typedef ft::rbtree_node<T> node_type;
        typedef typename node_type::node_ptr node_ptr;

        typedef T   value_type;
        typedef T   *pointer;
        typedef T   &reference;
        
        // Member variables
        node_ptr    _node;

        // Member functions
        rbtree_iterator()
        : _node(NULL) 
        {}

        explicit rbtree_iterator(const node_ptr &x)
        : _node(x)
        {}

        template <class U>    // copy
        rbtree_iterator(const rbtree_iterator<U> &x)
        : _node(x._node)
        {}

        template <class U>      // copy assignment
        rbtree_iterator &operator=(const rbtree_iterator<U> &x)
        {
            _node = x._node;
            return *this;
        }
        rbtree_iterator &operator=(const node_ptr& p)
        {
            _node= p;
            return *this;
        }

        virtual ~rbtree_iterator() {}

        //
        reference operator*() const
        {
            return _node->data;
        }
        pointer operator->() const
        {
            return &(_node->data);
        }
        // bool operator==(const rbtree_iteraotr &x)
        // {
        //     return (_node == x._node);
        // }
        // bool operator!=(const rbtree_iterator &x)
        // {
        //     return (_node != x._node);
        // }
        // operation++
        void increment()
        {
            if (_node->_right != NULL)
            {
                _node = _node->_right;
                while (_node->_left != NULL)
                    _node = _node->_left;
            }
            else
            {
                node_ptr p = _node->_parent;
                while (_node == p->_right)
                {
                    _node =p;
                    p = p->_parent;
                }
                if (_node->_right != p)
                    node = p;
            }
        }

        rbtree_iterator &operator++()
        {
            increment();
            return *this;
        }

        rbtree_iterator operator++(int)
        {
            rbtree_iterator temp = *this;
            increment();
            return temp;
        }
        // operation--
        void decrement()
        {
            // case header
            if (_node->_color == RED && _node->_parent->_parent == _node)
                _node = _node->_right;
            else if (_node->_left != NULL)
            {
                node_ptr y = _node->_left;
                while (y->_right != NULL)
                    y = y->_right;
                _node = y;
            }
            else 
            {
                node_ptr p = _node->_parent;
                while (_node == p->_left)
                {
                    _node = p;
                    p = p->_parent;
                }
                _node =p;
            }
        }
        rbtree_iterator &operator--()
        {
            decrement();
            return *this;
        }
        rbtree_iterator operator--(int)
        {
            rbtree_iterator temp = *this;
            decrement();
            return *this;
        }
        
        node_ptr base() const
        {
            return _node;
        }
    };
    template <typename Value>
    bool operator==(const rbtree_iterator<Value>& lhs, const rbtree_iterator<Value>& rhs)
    {
        return (rhs.base() == lhs.base());
    }

    template <typename Value>
    bool operator!=(const rbtree_iterator<Value>& lhs, const rbtree_iterator<Value>& rhs)
    {
        return (lhs.base() == rhs.base());
    }



    //rbtree_const_iterator
    template<class T>
    class rbtree_const_iterator
    {
        typedef ft::bidirectional_iterator_tag iterator_category;
        typedef std::ptrdiff_t                      difference_type;
        typedef ft::rbtree_node<T> node_type;
        typedef typename node_type::const_node_ptr node_ptr;

        typedef T   value_type;
        typedef const T   *pointer;
        typedef const T   &reference;
        
        // Member variables
        node_ptr    _node;

        // Member functions
        rbtree_const_iterator()
        : _node(NULL) 
        {}

        explicit rbtree_const_iterator(node_ptr x)
        : _node(x)
        {}

        template <class U>    // copy
        rbtree_const_iterator(const rbtree_const_iterator<U> &x)
        : _node(x._node)
        {}

        template <class U>      // copy assignment
        rbtree_const_iterator &operator=(const rbtree_const_iterator<U> &x)
        {
            if (this!= &x)
                _node = x._node;
            return *this;
        }
        rbtree_const_iterator& operator=(const const_node_ptr& it)
        {
            _node = p;
            return *this;
        }
        virtual ~rbtree_const_iterator() {}

        //
        reference operator*() const
        {
            return _node->data;
        }
        pointer operator->() const
        {
            return &(_node->data);
        }
        // bool operator==(const rbtree_iteraotr &x)
        // {
        //     return (_node == x._node);
        // }
        // bool operator!=(const rbtree_const_iterator &x)
        // {
        //     return (_node != x._node);
        // }
        // operation++
        void increment()
        {
            if (_node->_right != NULL)
            {
                _node = _node->_right;
                while (_node->_left != NULL)
                    _node = _node->_left;
            }
            else
            {
                node_ptr p = _node->_parent;
                while (_node == p->_right)
                {
                    _node =p;
                    p = p->_parent;
                }
                if (_node->_right != p)
                    _node = p;
            }
        }

        rbtree_const_iterator &operator++()
        {
            increment();
            return *this;
        }

        rbtree_const_iterator operator++(int)
        {
            rbtree_const_iterator temp = *this;
            increment();
            return temp;
        }
        // operation--
        void decrement()
        {
            // case header
            if (_node->_color == RED && _node->_parent->_parent == _node)
                _node = _node->_right;
            else if (_node->_left != NULL)
            {
                node_ptr y = _node->_left;
                while (y->_right != NULL)
                    y = y->_right;
                _node = y;
            }
            else 
            {
                node_ptr p = _node->_parent;
                while (_node == p->_left)
                {
                    _node = p;
                    p = p->_parent;
                }
                _node =p;
            }
        }
        rbtree_const_iterator &operator--()
        {
            decrement();
            return *this;
        }
        rbtree_const_iterator operator--(int)
        {
            rbtree_const_iterator temp = *this;
            decrement();
            return *this;
        }
        const_node_ptr base() const
        {
            return _node;
        }
    };

    template <typename Value>
    bool operator==(const rbtree_const_iterator<Value>& lhs, const rbtree_const_iterator<Value>& rhs)
    {
        return (rhs.base() == lhs.base());
    }

    template <typename Value>
    bool operator!=(const rbtree_const_iterator<Value>& lhs, const rbtree_const_iterator<Value>& rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <typename Value>
    bool operator==(const rbtree_const_iterator<Value>& lhs, const rbtree_iterator<Value>& rhs)
    {
        return (rhs.base() == lhs.base());
    }

    template <typename Value>
    bool operator!=(const rbtree_iterator<Value>& lhs, const rbtree_const_iterator<Value>& rhs)
    {
        return (lhs.base() != rhs.base());
    }

}

#endif