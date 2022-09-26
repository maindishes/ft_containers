#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <functional> // std::less
#include <iostream>
#include "type_trait.hpp"

namespace ft
{
    
    enum node_color
    {
        RED,
        BLACK
    };
    // Red-Black Tree Node

    template <typename T> 
    class rbtree_node
    {
        public :
            // Member types
            typedef T   value_type;
            typedef rbtree_node<value_type> *node_ptr;
            typedef const rbtree_node<value_type> *const_node_ptr;
            
            value_type _data;
            // color_type  _color;
            int         _color;
            node_ptr    _parent;
            node_ptr    _left;
            node_ptr    _right;

            // Member functions :
            rbtree_node()
            : _data(NULL),_color(BLACK),_parent(NULL), _left(NULL), _right(NULL)
            {}

            rbtree_node(value_type data, int color)
            : _parent(NULL), _left(NULL), _right(NULL), _color(color),_data(data)
            {}

            rbtree_node(const rbtree_node &x)
            : _data(x._data), color(x._color)
            {}

          
            virtual ~rbtree_node() {}
            
            static bool isTNULL(node_ptr x)
            {
                return (x->_parent == NULL);
            }
            static bool isTNULL(const_node_ptr x)
            {
                return (x->_parent == NULL);
            }
            static node_ptr minimum(node_ptr x)
            {
                while (!isTNULL(x->_left))
                    x = x->_left;
                return x;
            }
            static const_node_ptr minimum(const_node_ptr x)
            {
                while (!isTNULL(x->_left))
                    x = x->_left;
                return x;
            }
            static node_ptr maximum(node_ptr x)
            {
                while (!isTNULL(x->_right))
                    x = x->_right;
                return x;
            }
            static const_node_ptr minimum(const_node_ptr x)
            {
                while (!isTNULL(x->_right))
                    x = x->_right;
                return x;
            }

            rbtree_node &operator=(const rbtree_node& n)
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
            static node_ptr increment(node_ptr x)
            {
                // (!isTNULL(x->right))
                if (x->_right != NULL)
                {
                    x = x->right;
                }
                while(x->_left != NULL)
                    x = x->_left;
                else
                {
                    node_ptr p = x->_parent;
                    while (x == p->_right)
                    {
                        x = p;
                        p = p->parent;
                    }
                    if (x->_right != p)
                    {
                        x = p;
                    }
                }
                return x;
            }

            static node_ptr decrement(node_ptr x)
            {
                if (x->_color == RED && x->_parent->_parent == x) // case header
                    x = x->_right;
        
                else if (x->_left != NULL)
                {
                    node_ptr y = x->_left;
                    while (y->_right != NULL)
                        y = y->_right;
                    x = y;
                }
                else
                {
                    node_ptr p = x->_parent;
                    while ( x == p->_left)
                    {
                        x = p;
                        p = p->_parent;
                    }
                    x = p;
                }
                return x;
            }

    };
    template <typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<T> >
    class rbtree
    {
        public:
        // type definitions
            // Member types
            typedef T value_type;
            typedef Alloc allocator_type;
            typedef Compare value_compare;

            typedef rbtree_node<value_type> node_type;
            typedef std::allocator<node_type> node_allocator_type;
            typedef typename ft::rbtree_node<value_type>::node_ptr node_ptr;
            typedef typename ft::rbtree_node<value_type>::const_node_ptr const_node_ptr;

            // Member variables
            node_allocator_type _node_alloc;
            node_ptr _root;
            node_ptr _TNULL;
            value_compare _comp_val;
            
            // size_type _node_cnt;

            // Member functions
                // 왜 이렇게 하는지,,? 
            rb_tree()
            :_comp_val(value_compare())
            {
                _TNULL = _node_alloc.allocate(1);
                node_type temp(value_type(), BLACK);
                _node_alloc.construct(_TNULL, temp);
                _root = _TNULL;
            }
                // get_root
            const node_ptr &get_root() const
            {
                return _root;
            }
                // insertNode
            void insert_node(const value_type &data)
            {
                // 왜 getnode 를 private 로 빼줬는지 여기서 그냥 할당해 주면 안 되낭.
                node_ptr z = _getnode(NULL, data, RED);
                node_ptr y = NULL;
                node_ptr x = _root;

                while (x != _TNULL)
                {
                    y = x;
                    // data < x->data
                    if (_comp_val(z->data, x->data))
                        x = x->_left;
                    else
                        x = x->_right;
                }

                z->_parent = y;
                if (y == NULL)
                    _root = z;
                else if (_comp_val(z->data, y->data))
                    y->_left = z;
                else
                    y->_right = z;
                if (z->_parent == NULL)
                {
                    z->_color = BLACK;
                    return ;
                }
                if (z->_parnet->_parent == NULL)
                    return ;
                _insert_fix(z);
            }
        private:
            // Private member functions
            node_ptr _getnode(node_ptr parent, const value_type &data, const int &color)
            {
                node_ptr ptr = _node_alloc.allocate(1);
                node_type temp(data, color);

                temp._parent = _TNULL;
                temp._left = _TNULL;
                temp._right = _TNULL;
                _node_alloc.construct(ptr, tmep);

                return ptr;
            }

            void _left_rotate(node_ptr x)
            {
                node_ptr y = x->_right;
                x->_right = y->_left;
                if (y->_left != _TNULL)
            }
    }


}

#endif
