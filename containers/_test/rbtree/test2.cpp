#ifndef TREE_HPP
#define TREE_HPP

#include <memory>
#include <iostream>
#include <functional>
#include "utility.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"

namespace ft
{
// Red Black Tree Colors
enum RB_tree_color {RED, BLACK};

/**
 * @brief Red Black Tree Node
 * @tparam Key	key
 * @tparam T	value
 */
template <typename Key, typename T>
struct RB_tree_node {
	/** Member types **/
	typedef ft::pair<const Key, T>	data_type;
	typedef RB_tree_color			color_type;
	typedef RB_tree_node<Key, T> *	pointer;

	/** Member variables **/
	pointer		parent;
	pointer		left;
	pointer		right;
	color_type	color;
	data_type	data;

	/** Member functions **/
	RB_tree_node(const RB_tree_node &x) : data(x.data), color(x.color) { }
	const Key &getKey() { return data.first; }
	T &getValue() { return data.second; }

	static pointer minimum(const pointer x) {
		pointer temp = x;
		while (temp->left != NULL)
			temp = temp->left;
		return temp;
	}

	static pointer maximum(const pointer x) {
		pointer temp = x;
		while (temp->right != NULL)
			temp = temp->right;
		return temp;
	}
};

/**
 * @brief Red Black Tree Iterator
 * @tparam Key		key
 * @tparam T		value
 * @tparam IsConst	is const iterator
 */
template <typename Key, typename T, bool IsConst>
struct RB_tree_iterator {
	/** Member types **/
	typedef ft::bidirectional_iterator_tag	iterator_category;
	typedef ptrdiff_t						difference_type;
	typedef T								value_type;
	typedef Key								key_type;

	typedef typename ft::conditional<IsConst, const ft::pair<const Key, T>, ft::pair<const Key, T> >::type	data_type;
	typedef typename ft::conditional<IsConst, const RB_tree_node<Key, T>, RB_tree_node<Key, T> >::type		node_type;

	typedef RB_tree_iterator<Key, T, false>	iterator;
	typedef RB_tree_iterator<Key, T, true>	const_iterator;
	typedef data_type *						pointer;
	typedef data_type &						reference;

	/** Member variable **/
	node_type *node;

	/** Member functions **/
	explicit RB_tree_iterator() : node(NULL) { }
	RB_tree_iterator(node_type *x) { node = x; }
	template <bool B>
	RB_tree_iterator(const RB_tree_iterator<Key, T, B> &x, typename ft::enable_if<!B>::type* = 0) { node = x.node; }

	void increment() {
		if (node->right != NULL) {
			node = node->right;
			while (node->left != NULL)
				node = node->left;
		} else {
			RB_tree_node<Key, T> *p = node->parent;
			while (node == p->right) {
				node = p;
				p = p->parent;
			}
			if (node->right != p)
				node = p;
		}
  	}
  	
	void decrement() {
		if (node->color == RED && node->parent->parent == node) // case header
      		node = node->right;
    	else if (node->left != NULL) {
      		RB_tree_node<Key, T> *y = node->left;
      		while (y->right != NULL)
        		y = y->right;
      		node = y;
    	} else {
			RB_tree_node<Key, T> *p = node->parent;
			while (node == p->left) {
				node = p;
				p = p->parent;
      		}
      		node = p;
  	  	}
  	}

	// Operator overlaoding
	// Forward : == != * -> ++
	reference operator*() const { return node->data; }
	pointer operator->() const { return &(operator*()); }
	RB_tree_iterator &operator++() { increment(); return *this; }
	RB_tree_iterator operator++(int) { RB_tree_iterator temp = *this; increment(); return temp; }
	// Bidirectional : --
	RB_tree_iterator &operator--() { decrement(); return *this; }
	RB_tree_iterator operator--(int) { RB_tree_iterator temp = *this; decrement(); return temp; }
};

template <typename Key, typename T, bool B1, bool B2>
inline bool operator==(const RB_tree_iterator<Key, T, B1> &x, const RB_tree_iterator<Key, T, B2> &y)
{ return x.node == y.node; }

template <typename Key, typename T, bool B1, bool B2>
inline bool operator!=(const RB_tree_iterator<Key, T, B1> &x, const RB_tree_iterator<Key, T, B2> &y)
{ return x.node != y.node; }

/**
 * @brief RB_tree
 * Red Black Tree
 * @tparam Key 
 * @tparam T 
 * @tparam Compare 
 * @tparam std::alloc<ft::pair<const Key, T> >
 */
template <typename Key, typename T, typename Compare = std::less<Key>, typename Alloc = std::allocator<ft::pair<const Key, T> > >
class RB_tree {
public:
	/** type definitions **/
	typedef Key										key_type;
	typedef T										mapped_type;
	typedef ft::pair<const Key, T>					value_type;
	typedef Compare									key_comp;

	typedef Alloc									data_alloc_type;
	typedef typename Alloc::template
		rebind<RB_tree_node<key_type, mapped_type> >::other	allocator_type;
	typedef size_t									size_type;
	typedef ptrdiff_t								difference_type;

	typedef RB_tree_node<key_type, mapped_type>		node_type;
	typedef node_type *								link_type;
	typedef RB_tree_color							color_type;
	
	typedef value_type *							pointer;
	typedef const value_type *						const_pointer;
	typedef value_type &							reference;
	typedef const value_type &						const_reference;

	typedef RB_tree_iterator<Key, T, false>			iterator;
	typedef RB_tree_iterator<Key, T, true>			const_iterator;
	typedef ft::reverse_iterator<iterator>			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	/** member variables **/
	allocator_type	alloc;
	key_comp		comp;
	link_type		header;
	size_type		node_cnt;

	/** member functions **/
	link_type &root() const { return header->parent; }
	link_type &leftmost()  const { return header->left; }
	link_type &rightmost() const { return header->right; }
	link_type minimum(link_type x) { return node_type::minimum(x); }
	link_type maximum(link_type x) { return node_type::maximum(x); }

	allocator_type get_allocator() { return alloc; }
	key_comp key_compare() const { return comp; }
	iterator begin() { return leftmost(); }
	const_iterator begin() const { return leftmost(); }
	iterator end() { return header; }
	const_iterator end() const { return header; }
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
	bool empty() const { return node_cnt == 0; }
	size_type size() const { return node_cnt; }
	size_type max_size() const { return alloc.max_size(); }
	void swap(RB_tree<Key, T, Compare, Alloc> &t) {
		ft::swap(header, t.header);
		ft::swap(node_cnt, t.node_cnt);
		ft::swap(comp, t.comp);
	}

	// rotate && rebalance
	void RB_tree_rotate_left(node_type *x, node_type *&root);
	void RB_tree_rotate_right(node_type *x, node_type *&root);
	void RB_tree_insert_rebalance(node_type *x, node_type *&root);
	node_type *RB_tree_erase_rebalance(node_type *z,
										node_type *&root,
										node_type *&left_most,
										node_type *&right_most);

	// util functions
	link_type allocate_node() { return alloc.allocate(1); }
	void deallocate_node(link_type p) { alloc.deallocate(p, 1); }

	void empty_initialize() {
		header = allocate_node();
		header->color = RED;
		root() = NULL;
		leftmost() = header;
		rightmost() = header;
	}

	link_type copy(link_type x, link_type p) {
		link_type top = clone_node(x);
		top->parent = p;
		if (x->right)
			top->right = copy(x->right, top);
		p = top;
		x = x->left;
		while (x != NULL) {
			link_type y = clone_node(x);
			p->left = y;
			y->parent = p;
			if (x->right)
				y->right = copy(x->right, y);
			p = y;
			x = x->left;
		}
		return top;
	}

	// Constructors
	RB_tree(): alloc(allocator_type()), node_cnt(0) {
		empty_initialize();
	}
	RB_tree(const Compare &comp) : alloc(allocator_type()), node_cnt(0), comp(comp) {
		empty_initialize();
	}
	RB_tree(const Compare &comp, const allocator_type &alloc) : alloc(alloc), comp(comp), node_cnt(0) {
		empty_initialize();
	}

	// Copy Constructor
	RB_tree(const RB_tree<Key, T, Compare, Alloc> &x) : alloc(x.alloc), comp(x.comp), node_cnt(x.node_cnt) {
		if (x.root() == NULL) {
			empty_initialize();
		}
		else {
			header = allocate_node();
			header->color = RED;
			root() = copy(x.root(), header);
			leftmost() = minimum(root());
			rightmost() = maximum(root());
		}
		node_cnt = x.node_cnt;
	}

	// Assign Operator
	RB_tree<Key, T, Compare, Alloc> &operator=(const RB_tree &x) {
		clear();
		node_cnt = 0;
		comp = x.comp;
		if (x.root() == NULL) {
			root() = NULL;
			leftmost() = header;
			rightmost() = header;
		} else {
			root() = copy(x.root(), header);
			leftmost() = minimum(root());
			rightmost() = maximum(root());
			node_cnt = x.node_cnt;
		}
		return *this;
	}

	// Destructor
	~RB_tree() {
		clear();
	}

	link_type create_node(const value_type &x) {
		link_type node = allocate_node();
		alloc.construct(&node->data, x);
		return node;
	}

	link_type clone_node(link_type x) {
		link_type node = create_node(x->data);
		node->color = x->color;
		node->left = NULL;
		node->right = NULL;
		return node;
	}

	void destroy_node(link_type node) {
		alloc.destroy(node);
		deallocate_node(node);
	}

	iterator insert_aux(link_type x, link_type p, const value_type &v) {
		link_type node = create_node(v);
		if (p == header || x != NULL || comp(v.first, p->getKey())) {
			p->left = node;
			if (p == header) {
				root() = node;
				rightmost() = node;
			} else if (p == leftmost()) {
				leftmost() = node;
			}
		} else {
			p->right = node;
			if (p == rightmost())
				rightmost() = node;
		}
		node->parent = p;
		node->left = NULL;
		node->right = NULL;
		RB_tree_insert_rebalance(node, header->parent);
		node_cnt++;
		return iterator(node);
	}

	ft::pair<iterator, bool> insert(const value_type& val) {
		iterator pos = find_key(val.first);
		if (pos != end()) {
			return ft::make_pair<iterator, bool>(pos, false);
		} else {
			link_type prev = header;
			link_type curr = root();
			while (curr != NULL) {
				prev = curr;
				curr = comp(val.first, curr->getKey()) ? curr->left : curr->right;
			}
			return ft::make_pair(insert_aux(curr, prev, val), true);
		}
	}

	iterator insert(iterator position, const value_type& val) {
		(void)position;
		iterator it = find_key(val.first);
		if (it != end()) {
			return it;
		}
		link_type prev = header;
		link_type curr = root();
		while (curr != NULL) {
			prev = curr;
			curr = comp(val.first, curr->getKey()) ? curr->left : curr->right;
		}
		return insert_aux(curr, prev, val);
	}

	template <typename InputIterator>
  	void insert(InputIterator first, InputIterator last) {
		for ( ; first != last ; ++first) {
			this->insert(*first);
		}
	}

    void erase(iterator position) {
		link_type y = RB_tree_erase_rebalance(position.node, header->parent, header->left, header->right);
		destroy_node(y);
		--node_cnt;
	}

    void erase(iterator first, iterator last) {
		if (first == begin() && last == end()) {
			clear();
		} else {
			while (first != last) {
				erase(first++);
			}
		}
	}

	size_type erase(const key_type& k) {
		ft::pair<iterator, iterator> p = equal_range(k);
		size_type n = ft::distance(p.first, p.second);
		erase(p.first, p.second);
		return n;
	}

	void erase_without_rebalance(link_type x) {
		while (x != NULL) {
			erase_without_rebalance(x->right);
			link_type y = x->left;
			destroy_node(x);
			x = y;
		}
	}

	void clear() {
		if (node_cnt) {
			erase_without_rebalance(root());
			leftmost() = header;
			root() = NULL;
			rightmost() = header;
			node_cnt = 0;
		}
	}
	
	iterator find_key(const key_type &key) {
		link_type temp = root();

		while (temp != NULL) {
			if (temp->getKey() == key)
				break ;
			temp = comp(temp->getKey(), key) ? temp->right : temp->left;
		}
		if (temp && temp->getKey() == key)
			return iterator(temp);
		return end();
	}

	const_iterator find_key(const key_type &key) const {
		link_type temp = root();

		while (temp != NULL) {
			if (temp->getKey() == key)
				break ;
			temp = comp(temp->getKey(), key) ? temp->right : temp->left;
		}
		if (temp && temp->getKey() == key)
			return iterator(temp);
		return end();
	}

	size_type count(const key_type &key) const {
		const_iterator temp = find_key(key);
		return temp == end() ? 0 : 1;
	}

	iterator lower_bound(const key_type &k) {
		link_type less = header;
		link_type curr = root();

		while (curr != NULL) {
			if (!comp(curr->data.first, k)) {
				less = curr;
				curr = curr->left;
			} else {
				curr = curr->right;
			}
		}
		return iterator(less);
	}

	const_iterator lower_bound(const key_type &k) const {
		link_type less = header;
		link_type curr = root();

		while (curr != NULL) {
			if (!comp(curr->data.first, k)) {
				less = curr;
				curr = curr->left;
			} else {
				curr = curr->right;
			}
		}
		return const_iterator(less);
	}

	iterator upper_bound(const key_type& k) {
		link_type greater = header;
		link_type curr = root();

		while (curr != NULL) {
			if (comp(k, curr->data.first)) {
				greater = curr;
				curr = curr->left;
			} else {
				curr = curr->right;
			}
		}
		return iterator(greater);
	}

	const_iterator upper_bound(const key_type& k) const {
		link_type greater = header;
		link_type curr = root();

		while (curr != NULL) {
			if (comp(k, curr->data.first)) {
				greater = curr;
				curr = curr->left;
			} else {
				curr = curr->right;
			}
		}
		return const_iterator(greater);
	}

	ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
		return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
	}

	ft::pair<iterator,iterator> equal_range(const key_type& k) {
		return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
	}
};

template <class Key, class T, class Compare, class Alloc>
inline bool operator==(const RB_tree<Key,T,Compare,Alloc>& x, const RB_tree<Key,T,Compare,Alloc>& y)
{ return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()); }

template <class Key, class T, class Compare, class Alloc>
inline bool operator<(const RB_tree<Key,T,Compare,Alloc>& x, const RB_tree<Key,T,Compare,Alloc>& y)
{ return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }

template <class Key, class T, class Compare, class Alloc>
inline bool operator!=(const RB_tree<Key,T,Compare,Alloc>& x, const RB_tree<Key,T,Compare,Alloc>& y)
{ return !(x == y); }

template <class Key, class T, class Compare, class Alloc>
inline bool operator>(const RB_tree<Key,T,Compare,Alloc>& x, const RB_tree<Key,T,Compare,Alloc>& y)
{ return y < x; }

template <class Key, class T, class Compare, class Alloc>
inline bool operator<=(const RB_tree<Key,T,Compare,Alloc>& x, const RB_tree<Key,T,Compare,Alloc>& y)
{ return !(y < x); }

template <class Key, class T, class Compare, class Alloc>
inline bool operator>=(const RB_tree<Key,T,Compare,Alloc>& x, const RB_tree<Key,T,Compare,Alloc>& y)
{ return !(x < y); }

/**
 * @brief RB_tree_rotate_left
 * Rotate RB-tree to left
 * @param x 회전할 node의 parent node
 * @param root root node
 */
template <typename Key, typename T, typename Compare, typename Alloc>
inline void RB_tree<Key, T, Compare, Alloc>::RB_tree_rotate_left(RB_tree_node<Key, T> *x, RB_tree_node<Key, T> *&root) {
	RB_tree_node<Key, T> *y = x->right; // y : 회전할 기준 노드
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;
	y->parent = x->parent;
	if (x == root)
		root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
}

/**
 * @brief RB_tree_rotate_right
 * Rotate RB-tree to right
 * @param x 회전할 node의 parent node
 * @param root root node
 */
template <typename Key, typename T, typename Compare, typename Alloc>
inline void RB_tree<Key, T, Compare, Alloc>::RB_tree_rotate_right(RB_tree_node<Key, T> *x, RB_tree_node<Key, T> *&root) {
	RB_tree_node<Key, T> *y = x->left;
	x->left = y->right;
	if (y->right != NULL)
		y->right->parent = x;
	y->parent = x->parent;
	if (x == root)
		root = y;
	else if (x == x->parent->right)
		x->parent->right = y;
	else
		x->parent->left = y;
	y->right = x;
	x->parent = y;
}

/**
 * @brief RB_tree_insert_rebalance
 * RB-tree rebalance for insert new node
 * Case 1 -> Recoloring
 * Case 2 -> Restructuring
 * @param x new node
 * @param root root node
 */
template <typename Key, typename T, typename Compare, typename Alloc>
inline void RB_tree<Key, T, Compare, Alloc>::RB_tree_insert_rebalance(RB_tree_node<Key, T> *x, RB_tree_node<Key, T> *&root) {
	x->color = RED; // new node => RED
	while (x != root && x->parent->color == RED) { // RB-tree의 조건을 만족할 동안 (Double Red)
		if (x->parent == x->parent->parent->left) { // x의 parent가 GrandParent의 왼쪽 자식인 경우
			RB_tree_node<Key, T> *y = x->parent->parent->right; // Uncle node
			// Case 1
			if (y && y->color == RED) { // Uncle node => RED
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent; // GrandParent를 기준으로 다시 검사
			} else { // Uncle node => BLACK
				// Case 2-1
				if (x == x->parent->right) {
					x = x->parent;
					RB_tree_rotate_left(x, root);
				}
				// Case 2-2
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				RB_tree_rotate_right(x->parent->parent, root);
			}
		} else { // x의 Parent가 GrandParent의 오른쪽 자식인 경우
			RB_tree_node<Key, T> *y = x->parent->parent->left; // Uncle Node
			// Case 1
			if (y && y->color == RED) {
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			} else {
				// Case 2-1
				if (x == x->parent->left) {
					x = x->parent;
					RB_tree_rotate_right(x, root);
				}
				// Case 2-2
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				RB_tree_rotate_left(x->parent->parent, root);
			}
		}
	}
	root->color = BLACK; // Root Node => BLACK
}

template <typename Key, typename T, typename Compare, typename Alloc>
inline RB_tree_node<Key, T> *RB_tree<Key, T, Compare, Alloc>::RB_tree_erase_rebalance(RB_tree_node<Key, T> *z,
																					RB_tree_node<Key, T> *&root,
																					RB_tree_node<Key, T> *&left_most,
																					RB_tree_node<Key, T> *&right_most) {
	RB_tree_node<Key, T> *y = z;
	RB_tree_node<Key, T> *x = NULL;
	RB_tree_node<Key, T> *x_parent = NULL;
	if (y->left == NULL)
		x = y->right; // 자식 노드가 1개인 경우, 후계 노드는 y의 오른쪽 노드
	else {
		if (y->right == NULL)
			x = y->left; // 자식 노드가 1개인 경우, 후계 노드는 y의 왼쪽 노드
		else { // 자식 노드가 2개인 경우
			y = y->right;
			while (y->left != NULL)
				y = y->left; // y => Successor
			x = y->right; // x => Successor의 유일한 자식 노드
		}
	}
	if (y != z) { // 자식 노드가 2개인 경우
	// y : successor
	// z : 삭제할 노드
	// x : successor의 자식 노드
		z->left->parent = y;
		y->left = z->left;
		if (y != z->right) {
			x_parent = y->parent;
			if (x) x->parent = y->parent;
			y->parent->left = x;
			y->right = z->right;
			z->right->parent = y;
		} else { // successor가 삭제하려는 노드 바로 오른쪽 자식일때
			x_parent = y;
		}
		if (root == z)
			root = y;
		else if (z->parent->left == z) {
			z->parent->left = y;
		} else {
			z->parent->right = y;
		}
		y->parent = z->parent;
		ft::swap(y->color, z->color);
		y = z; // y now points to node to be actually deleted
	} else { // 자식 노드가 1개인 경우
		x_parent = y->parent;
		if (x) x->parent = y->parent;
		if (root == z)
			root = x;
		else {
			if (z->parent->left == z)
				z->parent->left = x;
			else
				z->parent->right = x;
		}
		if (left_most == z) {
			if (z->right == NULL)
				left_most = z->parent;
			else
				left_most = minimum(x);
		}
		if (right_most == z) {
			if (z->left == NULL)
				right_most = z->parent;
			else
				right_most = maximum(x);
		}
	} // y now points to node to be actually deleted
	if (y->color != RED) { // RED => 그냥 삭제
		while (x != root && (x == NULL || x->color == BLACK)) { // y가 BLACK이고, x가 BLACK인 경우 문제 발생
			if (x == x_parent->left) {
				RB_tree_node<Key, T> *s = x_parent->right;
				if (s->color == RED) { // Case 2-4) (s가 RED인 경우는 이 경우밖에 없음)
					s->color = BLACK;
					x_parent->color = RED;
					RB_tree_rotate_left(x_parent, root);
					s = x_parent->right;
				}
				// s is always BLACK
				if ((s->left == NULL || s->left->color == BLACK) && (s->right == NULL || s->right->color == BLACK)) 
				{ // Case 1-1) && 2-1)
					s->color = RED;
					x = x_parent;
					x_parent = x_parent->parent;
				} 
				else 
				{
					if (s->right == NULL || s->right->color == BLACK) 
					{ // Case *-3)
						if (s->left) s->left->color = BLACK;
						s->color = RED;
						RB_tree_rotate_right(s, root);
						s = x_parent->right;
					}
					// Case *-2)
					// s->right is always RED or NULL
					s->color = x_parent->color;
					x_parent->color = BLACK;
					if (s->right) s->right->color = BLACK;
					RB_tree_rotate_left(x_parent, root);
					break ;
				}
			} 
			else 
			{ // 위의 반대 버전
				RB_tree_node<Key, T> *s = x_parent->left;
				if (s->color == RED) { // Case 2-4)
					s->color = BLACK;
					x_parent->color = RED;
					RB_tree_rotate_right(x_parent, root);
					s = x_parent->left;
				}
				if ((s->right == NULL || s->right->color == BLACK) && (s->left == NULL || s->left->color == BLACK)) { // Case 1-1) && 2-1)
					s->color = RED;
					x = x_parent;
					x_parent = x_parent->parent;
				} else {
					if (s->left == NULL || s->left->color == BLACK) { // Case *-3)
						if (s->right) s->right->color = BLACK;
						s->color = RED;
						RB_tree_rotate_left(s, root);
						s = x_parent->left;
					}
					// Case *-2)
					s->color = x_parent->color;
					x_parent->color = BLACK;
					if (s->left) s->left->color = BLACK;
					RB_tree_rotate_right(x_parent, root);
					break ;
				}
			}
		}
		if (x) x->color = BLACK;
	}
	return y;
}
}
#endif