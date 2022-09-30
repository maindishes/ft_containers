/*
* C++ 이용하여 Red Black Tree 구현하기
*
* 목적 : Red Black Tree 공부 하기 위해 작성했으며,
*       C++ 이용하여 작성하시는 분들에게 도움이 되고자 했다.
*
* 설명 : key 값은 int만 가능 하며 중복 key는 허용 x
*       이중 연결 리스트로 구현
*       Red / Black은 식별하기 쉽게 enum이용 했으며, bool 이용시 데이터 크기 절약
*
*       class RBTree
*
*       변수 :   root node => root노드는 항상 black
*               leaf node => 끝에 해당하는 노드들은 leaf node들을 가지고 있다.
*                            leaf node라는 것만 알면 되기 때문에 새로운 노드 삽입 때마다 leaf node를 생성 해줄 필요없이
*                            모든 말단 노드들은 이 leaf node를 가리키는 식으로 구현
*                            leaf node는 항상 black
*
*       생성자 : RBTREE =>  node 구조체 생성후
*                          색은 black 초기화
*                          모든 자식은 nullptr로 초기화.
*
*       함수 :   IsKey => key값이 있는지 검사하는 함수
*               Insert => 삽입 함수
*               InsertFixUp => 삽입 후 규칙 깨졌을 시 재조정 함수
*               Delete => 삭제 함수
*               DeleteFixUp => 삭제 후 규칙 깨졌을 시 재조정 함수
*               Transplant => 삭제 시 이용하며, 삭제할 노드의 자식 노드를 부모노드에 연결해주는 함수
*               RotateRight(x) => x기준 오른쪽으로 회전
*               RotateLeft(x) => x기준 왼쪽으로 회전
*
*               Inorder,Preorder,Postorder => 순회 함수
*               tree_minimum(x), tree_maximum(x) => 노드 x 기준으로 가장 왼쪽, 오른쪽 return 함수
*
*               DisplayMenu, SelectMenu => 초기 Menu판 print 함수
*               Insert_helper,Delete_helper,order_helper,print_helper => 각각 수행시 입력받고 조건 에러 처리 위한 함수 와 tree print 해주는 함수
*
* 작성자 : gowoonsori
* github : https://github.com/gowoonsori/my-tech/tree/master/dataStructure/Tree
* 해당 source gist : https://gist.github.com/gowoonsori/a725e29ef1880f0592fe5760f4908c6b
*/

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <functional> // std::less
#include <iostream>
#include "type_trait.hpp"
#include "pair.hpp"


namespace ft
{
    
    enum node_color
    {
        RED,
        BLACK
    };
    // Red-Black Tree Node

    template <typename T > 
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
            // rbtree_node()
            // : _data(NULL),_color(BLACK),_parent(NULL), _left(NULL), _right(NULL)
            // {}

            rbtree_node(node_ptr parent, node_ptr left, node_ptr right, value_type data, int color)
            : _parent(parent), _left(left), _right(right), _data(data), _color(color)
            {}

            rbtree_node(const rbtree_node &x)
            : _data(x._data), _color(x._color), _parent(x._parent), _left(x._left), _right(x._right)
            {}

          
            virtual ~rbtree_node() {}
            
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

            static bool isTNULL(node_ptr x)
            {
                if (x && x->_left == NULL)
                    return true;
                else
                    return false;
            }
            static bool isTNULL(const_node_ptr x)
            {
                if (x->_left == NULL)
                    return true;
                else
                    return false;
            }
            static node_ptr minimum(node_ptr x)
            {
                while (x->_left != NULL)
                    x = x->_left;
                return x;
            }
            static const_node_ptr minimum(const_node_ptr x)
            {
                while (x->_left != NULL)
                    x = x->_left;
                return x;
            }
            static node_ptr maximum(node_ptr x)
            {
                while (x->_right != NULL)
                    x = x->_right;
                return x;
            }
            static const_node_ptr maximum(const_node_ptr x)
            {
                while (x->_right != NULL)
                    x = x->_right;
                return x;
            }

    };


    // rbtree;
    template <typename Key, typename Val, typename KeyOfValue, typename Compare = std::less<T>, typename Alloc = std::allocator<T> >
    class rbtree
    {
        public:
        // type definitions
            // Member types
            typedef Key key_type;
            typedef Val value_type;
            typedef Alloc allocator_type;
            typedef Compare key_compare;

            typedef rbtree_node<value_type> node_type;
            typedef std::allocator<node_type> node_allocator_type;
            typedef typename ft::rbtree_node<value_type>::node_ptr node_ptr;
            typedef typename ft::rbtree_node<value_type>::const_node_ptr const_node_ptr;

            // Member variables
            node_allocator_type _node_alloc;
            node_ptr _root;
            node_ptr _TNULL;
            key_compare _comp;
            size_type _node_cnt;
            
            // size_type _node_cnt;

            // Member functions
                // rb_tree val 은 mapped_type과  key_type을 pair 로 묶은 val 이다.
                // std::less() 에서 () 연산자 가 val.first,(first로만) 로 값을 비교해준다.
            rb_tree()
            :_node_cnt(0)
            {
                _TNULL = _getnode(node_type(NULL, NULL, NULL, value_type(), BLACK));
                _root = _getnode(node_type(NULL, _TNULL, _TNULL, value_type(), RED));
                _TNULL->_parent = _root;
            }
            
            bool _equal(const value_type &a, const value_type &b)
			{
				return (!_comp(a,b) && !_comp(b,a));
			}
            
            node_ptr _getnode(node_type temp)
            {
                node_ptr ptr = _node_alloc.allocate(1);
                _node_alloc.construct(ptr, tmep);
                return ptr;
            }
            
            node_ptr _find_key(key_type data)
            {
                node_ptr temp = _root;

                while (temp != _TNULL && !_eual(data, KeyOfValue()(temp->data))
                {
                    if (_comp(data, KeyOfValue()(temp->data))
						temp = temp->_left;
					else
						temp = temp->_right;
                }
                if (temp == _TNULL)
                    return NULL;
				return temp;
            }
                // insertNode
            void insert_node(const value_type &data)
            { 
                node_ptr z = _getnode(NULL, data, RED);
                node_ptr y = NULL;
                node_ptr x = _root;

                while (x != _TNULL)
                {
                    y = x;
                    // data < x->data
                    if (_comp(z->data, x->data))
                        x = x->_left;
                    else
                        x = x->_right;
                }

                z->_parent = y;
                if (y == NULL)
                    _root = z;
                else if (_comp(z->data, y->data))
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

			// deleteNode
			bool deleteNode(const value_type &data)
			{
				node_ptr z = _find_key(data);
				node_ptr x, y;
				// if key is not find
				if (z == _TNULL)
					return false;

				// if key is exist
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
					y = minimum(z->_right);
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
				_node_alloc.deallocate(z);
				if (y_original_color == BLACK)
				{
					node_ptr temp = _delete_fix(x)
					_node_alloc.destroy(temp);
					_node_alloc.deallocate(temp);
				}
				return true;
			}

        private:
            // Private member functions
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
            

			// *Transplant => 삭제 시 이용하며, 삭제할 노드의 자식 노드를 부모노드에 연결해주는 함수
			void _rb_transplant(node_ptr u, node_ptr v)
			{
				if (u->_parent == NULL)
					_root = v;
				else if (u == u->_parent->_left)
					u->_parent->_left = v;
				else
					u->_parent->_right = v;
				v->_parent = u->_parnet;
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
                else if (x == x->_parnet->_left)
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
                if (x->_parnet == NULL)
                    _root = y;
                else if (x == x->_parent->_right)
                    x->_parent->_right = y;
                else
                    x->_parent->_left y;
                y->_right = x;
                x->_parent = y;
            
            /**
             * @brief RB_tree_insert_rebalance
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
                bool size = (k->parent == k->_parent->_parent->_left); // x의 parent가 GrandParent의 왼쪽 자식인 경우
                
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
                        k->parent->parent->color = RED;
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
            node_ptr _delete_fix(node_ptr z)
            {
                node_ptr y = z;
                node_ptr x = NULL;
                node_ptr x_parent = NULL;

                if (y->_left == NULL)
                    x = y->_right; // 자식 노드가 1개인 경우, 후계 노드는 y의 오른쪽 노드
                else
                {
                    if (y->_right == NULL)
                        x = y->_left // 자식 노드가 1개인 경우, 후계 노드는 y의 왼쪽노드
                    else // 자식 노드가 2개인 경우
                    {
                        y = y->_right;
                        while (y->_left != NULL)
                            y = y->_left; // y => Successor
                        x = y->_right; // x => Succexssor 의 유일한 자식노드
                    }
                }
                if (y != z) // 자식 노드가 2개인 경우
                {
                    // y : successor
                    // z : 삭제할 노드 
                    // x : sucessor 의 자식 노드
                    z->_left->_parnet = y;
                    y->_left = z->_left;
                    if (y != z->_right)
                    {
                        x_parent = y->_parent;
                        if (x)
                            x->_parent = y->_parent;
                        y->_parent->_left = x;
                        y->_right = z->_right;
                        z->_right->_parent = y;
                    }
                    else
                     // Successor 가 삭제하려는 노드 바로 오른쪽 자식일때
                        x_parent = y;
                    if (z._root == z)
                        z_root = x;
                    else
                    {
                        if (z->_parent->_left == z)
                            z->_parent->_left = x;
                        else
                            z->_parent->_right = x;
                    }
                    if (z._root->_left == z)
                    {
                        if (z->_right == NULL)
                            z._root->_left = z->_parent;
                        else
                            z._root->_left = minimum(x);
                    }
                    if (z._root->_right == z)
                    {
                        if (z->_left == NULL)
                            z._root->_right = z->_parent;
                        else
                            z._root->_right = minimum(x);
                    }
                } // y now points to node to be actually deleted
                if (y->_color != RED)
                { // RED => 그냥 삭제
                    while( x!= z._root && (x == NULL || x->_color == BLACK)) // y가 BLACK이고, x가 BLACK인 경우 문제 발생
                    {
                        if (x == x_parent->_left)
                        {
                            node_ptr s = x_parent->_right;
                            if(s->_color == RED)
                            {// case 2-4 (s가 RED인 경우는 이 경우 밖에 없다.)
                                s->_color = BLACK;
                                x_parent->_color = RED;
                                _rotate_left(x_parent);
                                s = x_parent->_right;
                            }
                            //s is always BLACK
                            if ((s->_left == NULL) || s->_left->_color == BLACK && (s->_right == NULL || s->_right->color == BLACK)) 
                            { // Case 1-1) && 2-1))
                                s->_color = RED;
                                x = x_parent;
                                x_parent = x_parent->_parent;
                            }
                            else
                            {
                                if(s->_right == NULL || s->_right->_color == BLACK)
                                { // Case *-3
                                    if (s->_left)
                                        s->_left->_color = BLACK;
                                    s->_color = RED;
                                    _rotate_right(s);
                                    s = x_parent->_right;
                                }
                                // Case *-2)
                                // s->right is always RED or NULL
                                s->_color = x_parent->_color;
                                x_parent->_color = BLACK;
                                if (s->_right)
                                    s->_right->_color = BLACK;
                                _rotate_left(x_parent);
                                break ;
                            }
                        }
                        else
                        { // 위의 반대 버전 
                            nnode_ptr s = x_parent->_left;
                            if(s->_color == RED)
                            {// case 2-4 (s가 RED인 경우는 이 경우 밖에 없다.)
                                s->_color = BLACK;
                                x_parent->_color = RED;
                                _rotate_right(x_parent);
                                s = x_parent->_left;
                            }
                            //s is always BLACK
                            if ((s->_right == NULL) || s->_right->_color == BLACK && (s->_left == NULL || s->_left->color == BLACK)) 
                            { // Case 1-1) && 2-1))
                                s->_color = RED;
                                x = x_parent;
                                x_parent = x_parent->_parent;
                            }
                            else
                            {
                                if(s->_left == NULL || s->_left->_color == BLACK)
                                { // Case *-3
                                    if (s->_right)
                                        s->_right->_color = BLACK;
                                    s->_color = RED;
                                    _rotate_left(s);
                                    s = x_parent->_left;
                                }
                                // Case *-2)
                                // s->right is always RED or NULL
                                s->_color = x_parent->_color;
                                x_parent->_color = BLACK;
                                if (s->_left)
                                    s->_left->_color = BLACK;
                                _rotate_right(x_parent);
                                break ;
                            }
                        }
                    }
                    if (x) x->_color = BLACK;
                }
                return y;
            }


    };


}

#endif
