#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <functional> // std::less
#include <iostream>
#include "type_trait.hpp"
#include "pair.hpp"
#include "rbtree_iterator.hpp"
#include "reverse_iterator.hpp"
#include "iterator_base.hpp"
#include "algorithm.hpp"



namespace ft
{   
    // Red-Black Tree Node
    enum 
    {
        RED,
        BLACK
    };    

    template <typename T> 
    struct rbtree_node
    {
        
        public :
            // Member types
            typedef T   value_type;
            typedef rbtree_node<value_type> node_type;
            typedef std::allocator<node_type> node_allocator_type;
            typedef node_type *node_ptr;
            typedef const node_type *const_node_ptr;

            value_type _data;
            // color_type  _color;
            int         _color;
            node_ptr    _parent;
            node_ptr    _left;
            node_ptr    _right;

            // Member functions :
            // rbtree_node()
            // : _data(NULL),_color(BLACK),_parent(NULL), _left(NULL), _right(NULL)
            // {}

            rbtree_node(node_ptr parent, node_ptr left, node_ptr right, value_type data, int color)
            : _data(data),_color(color), _parent(parent), _left(left), _right(right)
            {}

            rbtree_node(const rbtree_node &x)
            : _data(x._data), _color(x._color), _parent(x._parent), _left(x._left), _right(x._right)
            {}

          
            virtual ~rbtree_node() {}
            
            // rbtree_node &operator=(const rbtree_node& n)
            // {
            //     if (this != &n)
            //     {
            //         _data = n._data;
            //         _color = n._color;
            //         _parent = n._parent;
            //         _left = n._left;
            //         _right = n._right;
            //     }
            //     return *this;
            // }

            static bool isTNULL(node_ptr x)
            {
                if (x && x->_left == NULL)
                    return true;
                else
                    return false;
            }
            static bool isTNULL(const_node_ptr x)
            {
                if (x && x->_left == NULL)
                    return true;
                else
                    return false;
            }
            static node_ptr tree_minimum(node_ptr x)
            {
                while (x && !isTNULL(x->_left))
                    x = x->_left;
                return x;
            }
            static const_node_ptr tree_minimum(const_node_ptr x)
            {
                while (x && !isTNULL(x->_left))
                    x = x->_left;
                return x;
            }
            static node_ptr tree_maximum(node_ptr x)
            {
                while (x && !isTNULL(x->_right))
                    x = x->_right;
                return x;
            }
            static const_node_ptr tree_maximum(const_node_ptr x)
            {
                while (x && !isTNULL(x->_right))
                    x = x->_right;
                return x;
            }

    };

    // template<typename T>
    // class rbtree_iterator
    // {
    //     public:
    //         typedef ft::bidirectional_iterator_tag iterator_category;
    //         typedef std::ptrdiff_t                      difference_type;
    //         typedef ft::rbtree_iterator<T> _Self;
    //         typedef ft::rbtree_node<T> node_type;
    //         typedef typename node_type::node_ptr node_ptr;

    //         typedef T   value_type;
    //         typedef T   *pointer;
    //         typedef T   &reference;
    //     // Member variables
    //     private:
    //         node_ptr    _node;

    //     // Member functions
    //     public:
    //         rbtree_iterator()
    //         : _node(NULL) 
    //         {}

    //         explicit rbtree_iterator(const node_ptr &x)
    //         : _node(x)
    //         {}

    //         template <class U>    // copy
    //         rbtree_iterator(const rbtree_iterator<U> &x)
    //         : _node(x._node)
    //         {}

    //         template <class U>      // copy assignment
    //         _Self &operator=(const rbtree_iterator<U> &x)
    //         {
    //             _node = x._node;
    //             return *this;
    //         }
    //         _Self &operator=(const node_ptr& p)
    //         {
    //             _node= p;
    //             return *this;
    //         }

    //         virtual ~rbtree_iterator() {}

    //         //
    //         reference operator*() const
    //         {
    //             return _node->data;
    //         }
    //         pointer operator->() const
    //         {
    //             return &(_node->data);
    //         }
    //         // bool operator==(const rbtree_iteraotr &x)
    //         // {
    //         //     return (_node == x._node);
    //         // }
    //         // bool operator!=(const rbtree_iterator &x)
    //         // {
    //         //     return (_node != x._node);
    //         // }
    //         // operation++
    //         void increment()
    //         {
    //             if (_node->_right != NULL)
    //             {
    //                 _node = _node->_right;
    //                 while (_node->_left != NULL)
    //                     _node = _node->_left;
    //             }
    //             else
    //             {
    //                 node_ptr p = _node->_parent;
    //                 while (_node == p->_right)
    //                 {
    //                     _node =p;
    //                     p = p->_parent;
    //                 }
    //                 if (_node->_right != p)
    //                     _node = p;
    //             }
    //         }

    //         _Self &operator++()
    //         {
    //             increment();
    //             return *this;
    //         }

    //         _Self operator++(int)
    //         {
    //             _Self temp = *this;
    //             increment();
    //             return temp;
    //         }
    //         // operation--
    //         void decrement()
    //         {
    //             // case header
    //             if (_node->_color == RED && _node->_parent->_parent == _node)
    //                 _node = _node->_right;
    //             else if (_node->_left != NULL)
    //             {
    //                 node_ptr y = _node->_left;
    //                 while (y->_right != NULL)
    //                     y = y->_right;
    //                 _node = y;
    //             }
    //             else 
    //             {
    //                 node_ptr p = _node->_parent;
    //                 while (_node == p->_left)
    //                 {
    //                     _node = p;
    //                     p = p->_parent;
    //                 }
    //                 _node =p;
    //             }
    //         }
    //         _Self &operator--()
    //         {
    //             decrement();
    //             return *this;
    //         }
    //         _Self operator--(int)
    //         {
    //             _Self temp = *this;
    //             decrement();
    //             return *this;
    //         }
            
    //         node_ptr base() const
    //         {
    //             return _node;
    //         }
    // };
    // template <typename Value>
    // bool operator==(const rbtree_iterator<Value>& lhs, const rbtree_iterator<Value>& rhs)
    // {
    //     return (rhs.base() == lhs.base());
    // }

    // template <typename Value>
    // bool operator!=(const rbtree_iterator<Value>& lhs, const rbtree_iterator<Value>& rhs)
    // {
    //     return (lhs.base() == rhs.base());
    // }



    // //rbtree_const_iterator
    // template<class T>
    // class rbtree_const_iterator
    // {
    // public:
    //     typedef ft::bidirectional_iterator_tag iterator_category;
    //     typedef std::ptrdiff_t                     difference_type;
    //     typedef rbtree_const_iterator<T> _Self;
    //     typedef ft::rbtree_node<T> node_type;
    //     typedef typename node_type::const_node_ptr node_ptr;

    //     typedef T   value_type;
    //     typedef const T   *pointer;
    //     typedef const T   &reference;
        
    //     // Member variables
    // private:
    //     node_ptr    _node;

    //     // Member functions
    // public:
    //     rbtree_const_iterator()
    //     : _node(NULL) 
    //     {}

    //     explicit rbtree_const_iterator(node_ptr x)
    //     : _node(x)
    //     {}

    //     template <class U>    // copy
    //     rbtree_const_iterator(const rbtree_const_iterator<U> &x)
    //     : _node(x._node)
    //     {}

    //     template <class U>      // copy assignment
    //     _Self &operator=(const rbtree_const_iterator<U> &x)
    //     {
    //         if (this!= &x)
    //             _node = x._node;
    //         return *this;
    //     }
    //     template <typename U>
    //     _Self& operator=(const rbtree_iterator<U>& it)
    //     {
    //         _node = it;
    //         return *this;
    //     }
    //     virtual ~rbtree_const_iterator() {}

    //     //
    //     reference operator*() const
    //     {
    //         return _node->data;
    //     }
    //     pointer operator->() const
    //     {
    //         return &(_node->data);
    //     }
    //     // bool operator==(const rbtree_iteraotr &x)
    //     // {
    //     //     return (_node == x._node);
    //     // }
    //     // bool operator!=(const rbtree_const_iterator &x)
    //     // {
    //     //     return (_node != x._node);
    //     // }
    //     // operation++
    //     void increment()
    //     {
    //         if (_node->_right != NULL)
    //         {
    //             _node = _node->_right;
    //             while (_node->_left != NULL)
    //                 _node = _node->_left;
    //         }
    //         else
    //         {
    //             node_ptr p = _node->_parent;
    //             while (_node == p->_right)
    //             {
    //                 _node =p;
    //                 p = p->_parent;
    //             }
    //             if (_node->_right != p)
    //                 _node = p;
    //         }
    //     }

    //     _Self &operator++()
    //     {
    //         increment();
    //         return *this;
    //     }

    //     _Self operator++(int)
    //     {
    //         rbtree_const_iterator temp = *this;
    //         increment();
    //         return temp;
    //     }
    //     // operation--
    //     void decrement()
    //     {
    //         // case header
    //         if (_node->_color == RED && _node->_parent->_parent == _node)
    //             _node = _node->_right;
    //         else if (_node->_left != NULL)
    //         {
    //             node_ptr y = _node->_left;
    //             while (y->_right != NULL)
    //                 y = y->_right;
    //             _node = y;
    //         }
    //         else 
    //         {
    //             node_ptr p = _node->_parent;
    //             while (_node == p->_left)
    //             {
    //                 _node = p;
    //                 p = p->_parent;
    //             }
    //             _node =p;
    //         }
    //     }
    //     rbtree_const_iterator &operator--()
    //     {
    //         decrement();
    //         return *this;
    //     }
    //     rbtree_const_iterator operator--(int)
    //     {
    //         rbtree_const_iterator temp = *this;
    //         decrement();
    //         return *this;
    //     }
    //     node_ptr base() const
    //     {
    //         return _node;
    //     }
    // };

    // template <typename Value>
    // bool operator==(const rbtree_const_iterator<Value>& lhs, const rbtree_const_iterator<Value>& rhs)
    // {
    //     return (rhs.base() == lhs.base());
    // }

    // template <typename Value>
    // bool operator!=(const rbtree_const_iterator<Value>& lhs, const rbtree_const_iterator<Value>& rhs)
    // {
    //     return (lhs.base() != rhs.base());
    // }

    // template <typename Value>
    // bool operator==(const rbtree_const_iterator<Value>& lhs, const rbtree_iterator<Value>& rhs)
    // {
    //     return (rhs.base() == lhs.base());
    // }

    // template <typename Value>
    // bool operator!=(const rbtree_iterator<Value>& lhs, const rbtree_const_iterator<Value>& rhs)
    // {
    //     return (lhs.base() != rhs.base());
    // }


    // rbtree;
    // template <typename Key, typename Val, typename KeyOfValue, typename Compare = std::less<T>, typename Alloc = std::allocator<T> >
    template <typename Key,
            typename Val,
            typename KeyOfValue,
            typename Compare = std::less<Key>,
            typename Alloc = std::allocator<Val>
            >
    class rbtree
    {
        public:
        // type definitions
            // Member types
            typedef Key                                                    key_type;
            typedef Val                                                    value_type;
            typedef Alloc                                                  allocator_type;
            typedef Compare                                                key_compare;
            typedef std::size_t size_type;
            typedef ft::rbtree_node<value_type>                            node_type;
            typedef typename node_type::node_allocator_type                node_allocator_type;
            typedef typename ft::rbtree_node<value_type>::node_ptr         node_ptr;
            typedef typename ft::rbtree_node<value_type>::const_node_ptr   const_node_ptr;

            typedef ft::rbtree_iterator<value_type>					iterator;
		    typedef ft::rbtree_const_iterator<value_type>		    const_iterator;
            typedef ft::reverse_iterator<iterator>					reverse_iterator;
		    typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
        // Member variables
        private:
            node_allocator_type     _node_alloc;
            node_ptr                _root;
            node_ptr                _TNULL;
            key_compare             _comp;
            size_type               _node_cnt;

            // Member functions
                // rbtree val 은 mapped_type과  key_type을 pair 로 묶은 val 이다.
                // std::less() 에서 () 연산자 가 val.first,(first로만) 로 값을 비교해준다.
        public:
            // Constructor
            rbtree()
            :_node_cnt(0)
            {
                _TNULL = _getnode(node_type(NULL, NULL, NULL, value_type(), BLACK));
                _root = _getnode(node_type(NULL, _TNULL, _TNULL, value_type(), RED));
                _TNULL->_parent = _root;
            }
            bool _equal(const key_type &a, const key_type &b) const
			{
				return (!_comp(a,b) && !_comp(b,a));
			}
            // Iterator
                // begin
            iterator begin()
            {
                node_ptr temp = ft::rbtree_node<value_type>::tree_minimum(this->get_root());
                return (iterator(temp));
            }
            const_iterator begin() const
            {
                node_ptr temp = ft::rbtree_node<value_type>::tree_minimum(this->get_root());
                return (const_iterator(temp));
            }
            //     // end
            iterator end() 
            {
                // node_ptr temp =ft::rbtree_node<value_type>::tree_minum()
                return iterator(this->getTNULL());
                // return iterator(this->_TNULL);
            }
            const_iterator end() const
            {
                return const_iterator(this->getTNULL());
                // return const_iterator(this->_TNULL);
            }
            node_ptr _getnode(node_type temp)
            {
                node_ptr ptr = _node_alloc.allocate(1);
                _node_alloc.construct(ptr, temp);
                return ptr;
            }
                // rbegin()
            reverse_iterator rbegin() 
            { 
                return reverse_iterator(this->end()); 
            }
            const_reverse_iterator rbegin() const 
            { 
                return const_reverse_iterator(this->end()); 
            }
                // rend();
            reverse_iterator rend() 
            { 
                return reverse_iterator(this->begin()); 
            }
            const_reverse_iterator rend() const 
            {
                return const_reverse_iterator(this->begin()); 
            }

            
            node_ptr _find_key(key_type key) const
            {
                node_ptr temp = _root;
                if (_root->_color == RED)
                    return NULL;
                while (temp != _TNULL && !_equal(key, KeyOfValue()(temp->_data)))
                {
                    if (_comp(key, KeyOfValue()(temp->_data)))
						temp = temp->_left;
					else
						temp = temp->_right;
                }
                if (temp == _TNULL)
                    return NULL;
				return temp;
            }
            void swap(rbtree &x)
            {
                ft::swap(_node_alloc, x._node_alloc);
                ft::swap(_root, x._root);
                ft::swap(_TNULL, x._TNULL);
                ft::swap(_comp, x._comp);
                ft::swap(_node_cnt, x._node_cnt);
            }

            // insert node in rb
            node_ptr _rb_insert(const value_type &data)
            {
                ++_node_cnt;
                node_ptr temp = _insert_node(data);
                _TNULL->_parent = _root;
                return temp;
            }
                // insertNode
            node_ptr _insert_node(const value_type &data)
            {
                node_ptr z = _getnode(node_type(NULL, _TNULL, _TNULL, data, RED));
                node_ptr y = NULL;
                node_ptr x = _root;

                if (_root->_color == RED)
                {
                    _node_alloc.destroy(_root);
                    _node_alloc.deallocate(_root, 1);
                    _root = z;
                    _root->_color = BLACK;
                    return z;
                }

                while (x != _TNULL)
                {
                    node_ptr z = _getnode(node_type(NULL, _TNULL,_TNULL, data,RED));
                    y = x;
                    // data < x->data
                    if (_comp( KeyOfValue()(z->_data),   KeyOfValue()(x->_data)))
                        x = x->_left;
                    else
                        x = x->_right;
                }

                z->_parent = y;
                if (y == NULL)
                    _root = z;
                else if (_comp( KeyOfValue()(z->_data), KeyOfValue()(y->_data)))
                    y->_left = z;
                else
                    y->_right = z;
                if (z->_parent == NULL)
                {
                    z->_color = BLACK;
                    return z;
                }
                if (z->_parent->_parent == NULL)
                    return z;
                return z; // 이부분 정확히 모름
                _insert_fix(z);
            }
            // delete node in rbtree
            void _rb_delete(const node_ptr &x)
            {
                --_node_cnt;
                _delete_node(x);
                if (_root == _TNULL)
                    _root = _getnode(node_type(NULL, _TNULL, _TNULL, value_type(), RED));
                _TNULL->_parent = _root;
            }
			// deleteNode
			bool _delete_node(const node_ptr &z)
			{
				node_ptr x, y;
                y = z;
				int y_original_color = y->_color;
				if (z->_left == _TNULL)
				{
					x = z->_right;
					_rb_transplant(z, z->_right);
				}
				else if (z->_right == _TNULL)
				{
					x = z->_left;
					_rb_transplant(z,z->_left);
				}
				else
				{
					y = node_type::tree_minimum(z->_right);
					y_original_color = y->_color;
					x = y->_right;
					if (y->_parent == z)
						x->_parent = y;
					else
					{
						_rb_transplant(y, y->_right);
						y->_right = z->_right;
						y->_right->_parent = y;
					}
					_rb_transplant(z,y);
					y->_left = z->_left;
					y->_left->_parent = y;
					y->_color = z->_color;
				}
                _node_alloc.destroy(z);
				_node_alloc.deallocate(z, 1);
				if (y_original_color == BLACK)
					_delete_fix(x);
				return true;
			}
                        
                // get_root
            const node_ptr &get_root() const
            {
                return _root;
            }
                // getTNULL
            const node_ptr &getTNULL() const
            {
                return _TNULL;
            }
            
            size_type size() const
            {
                return _node_cnt;
            }
            size_type max_size() const
            {
                return (_node_alloc.max_size() < PTRDIFF_MAX) ? _node_alloc.max_size() : PTRDIFF_MAX;
            }

        private:
            // Private member functions
			    // *Transplant => 삭제 시 이용하며, 삭제할 노드의 자식 노드를 부모노드에 연결해주는 함수
			void _rb_transplant(node_ptr u, node_ptr v)
			{
				if (u->_parent == NULL)
					_root = v;
				else if (u == u->_parent->_left)
					u->_parent->_left = v;
				else
					u->_parent->_right = v;
				v->_parent = u->_parent;
			}

            void _left_rotate(node_ptr x)
            {
                node_ptr y = x->_right;
                x->_right = y->_left;
                if (y->_left != _TNULL)
                    y->_left->_parent = x;
                y->_parent = x->_parent;
                if (x->_parent == NULL)
                    _root = y;
                else if (x == x->_parent->_left)
                    x->_parent->_left = y;
                else
                    x->_parent->_right = y;
                y->_left = x;
                x->_parent = y;
            }

            void _right_rotate(node_ptr x)
            {
                node_ptr y = x->_left;
                x->_left = y->_right;
                if (y->_right != _TNULL)
                    y->_right->_parent = x;
                y->_parent = x->_parent;
                if (x->_parent == NULL)
                    _root = y;
                else if (x == x->_parent->_right)
                    x->_parent->_right = y;
                else
                    x->_parent->_left = y;
                y->_right = x;
                x->_parent = y;
            }
            /**
             * @brief rbtree_insert_rebalance
             * RB-tree rebalance for insert new node
             * Case 1 -> Recoloring
             * Case 2 -> Restructuring
             * @param x new node
             * @param root root node
             */

            void _insert_fix(node_ptr k)
            {
                k->_color = RED; // new node => RED
                // if parent is left child of grandparent, side is true else side is false
                bool side = (k->_parent == k->_parent->_parent->_left); // x의 parent가 GrandParent의 왼쪽 자식인 경우
                
                // set uncle node
                node_ptr u = side ? k->_parent->_parent->_right : k->_parent->_parent->_left;
                
                // RB-tree의 조건을 만족할 동안 (Double Red)
                while( k != _root && k->_parent->_color == RED)
                {
                    // Case 1
                    if (u->_color == RED)
                    {
                        // if uncle's color is RED -> recoloring
                        u->_color = BLACK;
                        k->_parent->_color = BLACK;
                        k->_parent->_parent->_color = RED;
                        k = k->_parent->_parent; // GrandParent를 기준으로 다시 검사
                    }
                    // Case 2-1
                    else // Uncle node => BLACK
                    {
                        // if uncle is not exist or uncle's color is BLACK -> restructuring
                        if ( k == (side ? k->_parent->_right : k->_parent->_left))
                        {
                            k = k->_parent;
                            side ? _left_rotate(k) : _right_rotate(k);
                        }
                        k->_parent->_color = BLACK;
                        k->_parent->_parent->_color = RED;
                        side ? _right_rotate(k->_parent->_parent) : _left_rotate(k->_parent->_parent);
                    }
                }
                _root->_color = BLACK;
            }
            // link_type &root() const { return header->parent; }
            // link_type &leftmost()  const { return header->left; }
            // link_type &rightmost() const { return header->right; }
            void _delete_fix(node_ptr x)
            {
            //     node_ptr y = z;
            //     node_ptr x = NULL;
            //     node_ptr x_parent = NULL;

            //     if (y->_left == NULL)
            //         x = y->_right; // 자식 노드가 1개인 경우, 후계 노드는 y의 오른쪽 노드
            //     else
            //     {
            //         if (y->_right == NULL)
            //             x = y->_left; // 자식 노드가 1개인 경우, 후계 노드는 y의 왼쪽노드
            //         else // 자식 노드가 2개인 경우
            //         {
            //             y = y->_right;
            //             while (y->_left != NULL)
            //                 y = y->_left; // y => Successor
            //             x = y->_right; // x => Succexssor 의 유일한 자식노드
            //         }
            //     }
            //     if (y != z) // 자식 노드가 2개인 경우
            //     {
            //         // y : successor
            //         // z : 삭제할 노드 
            //         // x : sucessor 의 자식 노드
            //         z->_left->_parent = y;
            //         y->_left = z->_left;
            //         if (y != z->_right)
            //         {
            //             x_parent = y->_parent;
            //             if (x)
            //                 x->_parent = y->_parent;
            //             y->_parent->_left = x;
            //             y->_right = z->_right;
            //             z->_right->_parent = y;
            //         }
            //         else
            //         {
            //          // Successor 가 삭제하려는 노드 바로 오른쪽 자식일때
            //             x_parent = y;
            //         }
            //         if (z->_root == z)
            //             z->_root = x;
            //         else if (z->_parent->_left == z)
            //         {
            //             z->_parent->_left = y;
            //         }    
            //         else
            //             z->_parent->_right = y;
            //         y->_parent = z->_parent;
            //         ft::swap(y->_color, z->_color);
            //         y = z; // y now points to node to be actually deleted
            //         if (z->_root->_left == z)
            //         {
            //             if (z->_right == NULL)
            //                 z->_root->_left = z->_parent;
            //             else
            //                 z->_root->_left = tree_minimum(x);
            //         }
            //         if (z->_root->_right == z)
            //         {
            //             if (z->_left == NULL)
            //                 z->_root->_right = z->_parent;
            //             else
            //                 z->_root->_right = tree_minimum(x);
            //         }
            //     } 
            //     // y now points to node to be actually deleted
            //     if (y->_color != RED)
            //     { 
            //         // RED => 그냥 삭제
            //         while( x!= z->_root && (x == NULL || x->_color == BLACK)) // y가 BLACK이고, x가 BLACK인 경우 문제 발생
            //         {
            //             if (x == x_parent->_left)
            //             {
            //                 node_ptr s = x_parent->_right;
            //                 if(s->_color == RED)
            //                 {
            //                     // case 2-4 (s가 RED인 경우는 이 경우 밖에 없다.)
            //                     s->_color = BLACK;
            //                     x_parent->_color = RED;
            //                     _rotate_left(x_parent);
            //                     s = x_parent->_right;
            //                 }
            //                 //s is always BLACK
            //                 if ((s->_left == NULL) || (s->_left->_color == BLACK && (s->_right == NULL || s->_right->color == BLACK))) 
            //                 { 
            //                     // Case 1-1) && 2-1))
            //                     s->_color = RED;
            //                     x = x_parent;
            //                     x_parent = x_parent->_parent;
            //                 }
            //                 else
            //                 {
            //                     if(s->_right == NULL || s->_right->_color == BLACK)
            //                     { // Case *-3
            //                         if (s->_left)
            //                             s->_left->_color = BLACK;
            //                         s->_color = RED;
            //                         _rotate_right(s);
            //                         s = x_parent->_right;
            //                     }
            //                     // Case *-2)
            //                     // s->right is always RED or NULL
            //                     s->_color = x_parent->_color;
            //                     x_parent->_color = BLACK;
            //                     if (s->_right)
            //                         s->_right->_color = BLACK;
            //                     _rotate_left(x_parent);
            //                     break ;
            //                 }
            //             }
            //             else
            //             { 
            //                 // 위의 반대 버전 
            //                 node_ptr s = x_parent->_left;
            //                 if(s->_color == RED)
            //                 {
            //                     // case 2-4 (s가 RED인 경우는 이 경우 밖에 없다.)
            //                     s->_color = BLACK;
            //                     x_parent->_color = RED;
            //                     _rotate_right(x_parent);
            //                     s = x_parent->_left;
            //                 }
            //                 //s is always BLACK
            //                 if ((s->_right == NULL) || (s->_right->_color == BLACK && (s->_left == NULL || s->_left->color == BLACK))) 
            //                 { // Case 1-1) && 2-1))
            //                     s->_color = RED;
            //                     x = x_parent;
            //                     x_parent = x_parent->_parent;
            //                 }
            //                 else
            //                 {
            //                     if(s->_left == NULL || s->_left->_color == BLACK)
            //                     { // Case *-3
            //                         if (s->_right)
            //                             s->_right->_color = BLACK;
            //                         s->_color = RED;
            //                         _rotate_left(s);
            //                         s = x_parent->_left;
            //                     }
            //                     // Case *-2)
            //                     // s->right is always RED or NULL
            //                     s->_color = x_parent->_color;
            //                     x_parent->_color = BLACK;
            //                     if (s->_left)
            //                         s->_left->_color = BLACK;
            //                     _rotate_right(x_parent);
            //                     break ;
            //                 }
            //             }
            //         }
            //         if (x) 
            //             x->_color = BLACK;
            //     }
            //     return y;
            // }
			while (x != _root && x->_color == BLACK)
			{
				// if x is left child, side is true else side is false
				bool side = (x == x->_parent->_left);
				// set sibling node
				node_ptr s = side ? x->_parent->_right : x->_parent->_left;

				// case 1
				if (s->_color == RED)
				{
					s->_color = BLACK;
					x->_parent->_color = RED;
					side ? _left_rotate(x->_parent) : _right_rotate(x->_parent);
					s = side ? x->_parent->_right : x->_parent->_left;
				}
				// case 2
				if (s->_left->_color == BLACK && s->_right->_color == BLACK)
				{
					s->_color = RED;
					x = x->_parent;
				}
				else
				{
					// case 3
					if ((side ? s->_right->_color : s->_left->_color) == BLACK)
					{
						(side ? s->_left->_color : s->_right->_color) = BLACK;
						s->_color = RED;
						side ? _right_rotate(s) : _left_rotate(s);
						s = side ? x->_parent->_right : x->_parent->_left;
					}
					// case 4
					s->_color = x->_parent->_color;
					x->_parent->_color = BLACK;
					(side ? s->_right->_color : s->_left->_color) = BLACK;
					side ? _left_rotate(x->_parent) : _right_rotate(x->_parent);
					x = _root;
				}
			}
			x->_color = BLACK;
			_root->_color = BLACK;
		}
    };
    


}
#endif
