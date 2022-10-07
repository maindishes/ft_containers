#ifndef RBTREE_ITERATOR_HPP
#define RBTREE_ITERATOR_HPP

#include "iterator_base.hpp"
#include "rbtree.hpp"
// #include "reverse_iterator.hpp"
#include <cstddef> // std::ptrdiff_t

    enum node_color
    {
        RED,
        BLACK
    };  

namespace ft
{
    template <typename T> 
    struct rbtree_node;

    template<typename T>
    class rbtree_iterator
    {
        public:
            typedef ft::bidirectional_iterator_tag iterator_category;
            typedef std::ptrdiff_t                      difference_type;
            typedef ft::rbtree_iterator<T> _Self;
            typedef ft::rbtree_node<T> node_type;
            typedef typename node_type::node_ptr node_ptr;

            typedef T   value_type;
            typedef T   *pointer;
            typedef T   &reference;
        // Member variables
        // private:
            node_ptr    _node;

        // Member functions
        public:
            rbtree_iterator()
            : _node(NULL) 
            {}

            explicit rbtree_iterator(const node_ptr &x)
            : _node(x)
            {
            }

            template <typename U>    // copy
            rbtree_iterator(const rbtree_iterator<U> &x)
            : _node(x._node)
            {}

            template <typename U>      // copy assignment
            _Self &operator=(const rbtree_iterator<U> &x)
            {
                _node = x._node;
                return *this;
            }

            // _Self &operator=(const node_ptr& p)
            // {
            //     _node= p;
            //     return *this;
            // }

            virtual ~rbtree_iterator() {}

            //
            reference operator*() const
            {
                return _node->_data;
            }
            pointer operator->() const
            {
                return &(_node->_data);
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
			node_ptr _increment(node_ptr x)
			{
				// Case 1: right child exist, return leftmost node
				if (!node_type::isTNULL(x->_right))
				{
					return node_type::tree_minimum(x->_right);
				}
				// backup _TNULL
				node_ptr _TNULL = x->_right;
				// Case 2: up until it came from left
				while (x->_parent)
				{
					if (x->_parent->_left == x)
					{
						return x->_parent;
					}
					x = x->_parent;
				}
				// Case 3: return TNULL
				return _TNULL;
			}

            _Self &operator++()
            {
                _node = _increment(_node);
                return *this;
            }

            _Self operator++(int)
            {
                _Self temp(*this);
                ++(*this);
                return temp;
            }
            // operation--
            // void decrement() // 나보다 작은값중 제일 큰값 찾아 가는것.
            // {
            //     //   내가 end 일때  그냥 부모에서 제일 최대값 리턴
            //     if (node_type::isTNULL(_node))
            //     {
            //         node_type::tree_maximum(_node->_parent);
            //         return ;
            //     }
            //     // 왼쪽 자식이 존재 할땐 부모의 오른쪽 자식 리턴하면 이함수에서 찾는 값이 충족 된다.
            //     if (!node_type::isTNULL(_node->_left))
            //     {
            //         node_type::tree_maximum(_node->_left);
            //         return ;
            //     }
            //     else 
            //     {
            //         node_ptr p = _node->_parent;
            //         while (p->_parent)
            //         {
            //             if (p->_parent->_right == _node) // ㄴㅐ가 오른쪽 자식일때는 ->  부모로 올로가는거 (한칸만 올라가면 작은값중 제일 큰값 되기 때문.) 
            //             {
            //                 p = p->_parent;
            //                 return ;
            //             }
            //             p = p->_parent;
            //         }
            //         _node = p;
            //     }
            // }
            node_ptr decrement(node_ptr _node)
            {
            // case header
            if (node_type::isTNULL(_node))
            {
                // node_type::tree_maximum(_node->_parent);
                return node_type::tree_maximum(_node->_parent);
            }
            // 왼쪽 자식이 존재 할땐 부모의 오른쪽 자식 리턴하면 이함수에서 찾는 값이 충족 된다.
            if (!node_type::isTNULL(_node->_left))
            {
                // node_type::tree_maximum(_node->_left);
                return node_type::tree_maximum(_node->_left);
            }

            while (_node->_parent)
            {
                if (_node->_parent->_right == _node) // ㄴㅐ가 오른쪽 자식일때는 부모로 올로가는거. 
                {
                    return _node->_parent;
                }
                _node = _node->_parent;
            }
            return NULL;
        }

            _Self &operator--()
            {
                _node = decrement(_node);
                return *this;
            }

            _Self operator--(int)
            {
                 _Self temp(*this);
                --(*this);
                return temp;
            }

            
            node_ptr base() const
            {
                return _node;
            }
            
            
            // friend bool operator==(const _Self& lhs, const _Self& rhs)
            // {
            //     return (rhs.base() == lhs.base());
            // }

           
            // friend bool operator!=(const _Self& lhs, const _Self& rhs)
            // {
            //     return (lhs.base() == rhs.base());
            // }


    };
    template <typename Value>
    bool operator==(const rbtree_iterator<Value>& lhs, const rbtree_iterator<Value>& rhs)
    {
        return (rhs.base() == lhs.base());
    }

    template <typename Value>
    bool operator!=(const rbtree_iterator<Value>& lhs, const rbtree_iterator<Value>& rhs)
    {
        return (lhs.base() != rhs.base());
    }



    //rbtree_const_iterator
    template<class T>
    class rbtree_const_iterator
    {
    public:
        typedef ft::bidirectional_iterator_tag iterator_category;
        typedef std::ptrdiff_t                     difference_type;
        typedef rbtree_const_iterator<T> _Self;
        typedef ft::rbtree_node<T> node_type;
        typedef typename node_type::const_node_ptr node_ptr;

        typedef T   value_type;
        typedef const T   *pointer;
        typedef const T   &reference;
        
        // Member variables
    // private:
        node_ptr    _node;

        // Member functions
    public:
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
        template <class U>    // copy
        rbtree_const_iterator(const rbtree_iterator<U> &x)
        : _node(x._node)
        {}

        template <class U>      // copy assignment
        _Self &operator=(const rbtree_const_iterator<U> &x)
        {
            if (this!= &x)
                _node = x._node;
            return *this;
        }

        template <typename U>
        _Self& operator=(const rbtree_iterator<U>& it)
        {
            if (this != &it)
                _node = it._node;
            return *this;
        }
        virtual ~rbtree_const_iterator() {}

        //
        reference operator*() const
        {
            return _node->_data;
        }
        pointer operator->() const
        {
            return &(_node->_data);
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
        node_ptr _increment(node_ptr x)
        {
            // Case 1: right child exist, return leftmost node
            if (!node_type::isTNULL(x->_right))
            {
                return node_type::tree_minimum(x->_right);
            }
            // backup _TNULL
            node_ptr _TNULL = x->_right;
            // Case 2: up until it came from left
            while (x->_parent)
            {
                if (x->_parent->_left == x)
                {
                    return x->_parent;
                }
                x = x->_parent;
            }
            // Case 3: return TNULL
            return _TNULL;
        }

        _Self &operator++()
        {
            _node = _increment(_node);
            return *this;
        }

        _Self operator++(int)
        {
            _Self temp(*this);
            ++(*this);
            return temp;
        }
        // // operation--
        // void decrement()
        // {
        //     // case header
        //     if (node_type::isTNULL(_node))
        //     {
        //         node_type::tree_maximum(_node->_parent);
        //         return ;
        //     }
        //     // 왼쪽 자식이 존재 할땐 부모의 오른쪽 자식 리턴하면 이함수에서 찾는 값이 충족 된다.
        //     if (!node_type::isTNULL(_node->_left))
        //     {
        //         node_type::tree_maximum(_node->_left);
        //         return ;
        //     }
        //     else 
        //     {
        //         node_ptr p = _node->_parent;
        //         while (p->_parent)
        //         {
        //             if (p->_parent->_right == _node) // ㄴㅐ가 오른쪽 자식일때는 부모로 올로가는거. 
        //             {
        //                 p = p->_parent;
        //                 return ;
        //             }
        //             p = p->_parent;
        //         }
        //         _node = p;
        //     }
        // }
        // //////

        node_ptr decrement(node_ptr _node)
        {
            // case header
            if (node_type::isTNULL(_node))
            {
                // node_type::tree_maximum(_node->_parent);
                return node_type::tree_maximum(_node->_parent);
            }
            // 왼쪽 자식이 존재 할땐 부모의 오른쪽 자식 리턴하면 이함수에서 찾는 값이 충족 된다.
            if (!node_type::isTNULL(_node->_left))
            {
                // node_type::tree_maximum(_node->_left);
                return node_type::tree_maximum(_node->_left);
            }
            while (_node->_parent)
            {
                if (_node->_parent->_right == _node) // ㄴㅐ가 오른쪽 자식일때는 부모로 올로가는거. 
                {
                    return _node->_parent;
                }
                _node = _node->_parent;
            }
            return NULL;
        }
        /// @brief //
        /// @return /

        _Self &operator--()
        {
            _node = decrement(_node);
            return *this;
        }
        _Self operator--(int)
        {
            _Self temp(*this);
            --(*this);
            return temp;
        }
        node_ptr base() const
        {
            return _node;
        }
    };
    template <typename Value>
    bool operator==(const rbtree_const_iterator<Value>& lhs, const rbtree_const_iterator<Value>& rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <typename Value>
    bool operator!=(const rbtree_const_iterator<Value>& lhs, const rbtree_const_iterator<Value>& rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <typename Value>
    bool operator==(const rbtree_iterator<Value>& lhs, const rbtree_const_iterator<Value>& rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <typename Value>
    bool operator!=(const rbtree_iterator<Value>& lhs, const rbtree_const_iterator<Value>& rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <typename Value>
    bool operator==(const rbtree_const_iterator<Value>& lhs, const rbtree_iterator<Value>& rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <typename Value>
    bool operator!=(const rbtree_const_iterator<Value>& lhs, const rbtree_iterator<Value>& rhs)
    {
        return (lhs.base() != rhs.base());
    }

}

#endif