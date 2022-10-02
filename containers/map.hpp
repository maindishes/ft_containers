#ifndef MAP_HPP
#define MAP_HPP

#include "rbtree.hpp"
#include <functional>
#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "rbtree_iterator.hpp"
#include "rbtree.hpp"
#include <cstddef>
#include <iostream>

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
            typedef Key                                     key_type;
            typedef T                                       mapped_type;
            typedef ft::pair<const key_type, mapped_type>   value_type;

            typedef ptrdiff difference_type;
            typedef size_t  size_type;

            typedef Compare     key_compare;
            typedef Alloc   allocator_type;
            
            typedef typename allocator_type::reference	        reference;
            typedef typename allocator_type::const_reference	const_reference;
            typedef typename allocator::pointer                 pointer;
            typedef typename allocator::const_pointer           const_pointer;

        protected:
            typedef rbtree<value_type, value_compare, allocator_type> tree_type;
            typedef typename tree_type::node_type node_type;
            typedef typename tree_type::node_ptr node_ptr;
        public:
            class value_compare : public std::binary_function<value_type, value_type, bool>
            {
                friend class	map;
                
                protected :
                    key_compare comp;
                    // constructed with map's comparison object
                    value_compare(key_compare c)
                    : comp(c)
                    {}
                public :
                    typedef bool		result_type;
                    typedef value_type	first_argument_type;
                    typedef value_type	second_argument_type;
                    bool operator()( const value_type& lhs, const value_type& rhs ) const
                    {
                        return comp(lhs.first, rhs.first);
                    }
            };
            typedef typename tree_type::iterator                			iterator;
            typedef typename tree_type::const_iterator          			const_iterator;
            typedef typename ft::reverse_iterator<iterator>                 reverse_iterator;       
            typedef typename ft::const_reverse_iterator<const_iterator>		const_reverse_iterator;

		private:
            tree_type	_tree;
            // value_compare _comp_val; // gcc 따라서 이거 없이 도 해보자 컴파일 
            // ft::rbtree<value_type, value_compare, allocator_type> _tree;


        public:
            // Constructor
            explicit map( const key_comapre &comp = key_compare(),const allocator_type &alloc = allocator_type())
            : _tree(comp, alloc) {}

				/**
				 * @brief Range constructor
				 * Constructs a container with as many elements as the range [first,last),
				 * with each element constructed from its corresponding element in that range.
				 * @tparam InputIterator 
				 * @param first Input iterators to the initial position in a range.
				 * @param last Input iterators to the final position in a range.
				 * @param comp Binary predicate that, taking two element keys as argument, returns true if the first
				 * argument goes before the second argument in the strict weak ordering it defines, and false otherwise.
				 * @param alloc Allocator object
				 */
            template<class InputIt>
            map( InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() )
            : _tree(comp, alloc)
			{
                // this->
			}
				// Copy constructor
			map(const map& x) : _tree(x._tree) {}
				// Destructor
			virtual ~map() 
			{
				while(this->_begin() != this->_end())
					this->erase(this->begin());
			}
			// Operator=
			map& operator=(const map& __x)
			{
				if (this != &__x)
					this->_tree = __x._tree;
				return *this;
			}
			// Member functions
                // begin()
			iterator begin()
			{
				return this->_tree.begin();
			}
			const_iterator begin() const
			{
				return this->_tree.begin();
			}
                // end()
            iterator end()
			{
				return this->_tree.end();
			}
			const_iterator end() const
			{
				return this->_tree.end();
			}
                // rbegin()
			iterator rbegin()
			{
				return this->_tree.rbegin();
			}
			const_iterator rbegin() const
			{
				return this->_tree.rbegin();
			}
                // rend()
            reverse_iterator rend()
			{
				return this->_tree.rend();
			}
			const_reverse_iterator rend() const
			{
				return this->_tree.rend();
			}
                // empty
            bool empty() const 
            { 
                return (_tree->size() == 0); 
            }
                // size
            size_type size() const
            {
                return (_tree.size());
            }
                // max_size
            size_type max_size() const
            {
                return _tree.max_size();
            }
            // Element access:
                // operation[]
            mapped_type& operator[] (const key_type& k)
            {
                ((this->insert(ft::make_pair(k, mapped_type()))));
                return this->find(k)->second;
                // return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
            }

            // Modifiers:
                // insert
                    //single element (1)	
            ft::pair<iterator,bool> insert (const value_type& val)
            {
                node_ptr temp = _tree._find_key(val.first);
                if (temp)
                    return ft::make_pair(iterator(temp), false);
                else
                {
                    temp = _tree._rb_insert(val);
                    return ft::make_pair(iterator(temp), true);
                }
            }
                    // with hint (2)	
            iterator insert (iterator position, const value_type& val)
            {
                (void)position;
			    return this->insert(val).first;
            }
                    //range (3)	
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last)
            {
                for (; first != last; first++)
				this->insert(*first);
            }
                // erase
                    // (1)	
            void erase (iterator position)
            {
                _tree._rb_delete(position._node);
            }
            // size_type erase(const key_type &k)
            // {
            //     node_ptr tmp = _bst.searchKey(k);
            //     if (tmp)
            //     {
            //         _bst.rbDelete(tmp);
            //         return 1;
            //     }
            //     return 0;
            // }	
                    // (2)
            size_type erase (const key_type& k)
            {
                iterator pos this->_find_key(val);
                if (pos == this->end())
                    return 0;
                this->erase(pos);
                return 1;
            }
                    // (3)	
            void erase (iterator first, iterator last)
            {
                while(first != last)
                {
                    this->erase(first++);
                    // _tree._rb_delete(first._node);
                    // first++;
                }
            }
                // swap
            void swap(map &x)
            {
                _tree.swap(x._tree);
            }

                // clear
            void clear()
            {
                while(!this->empty())
                    this->erase(this->begin());
            }
            
            // Observers
                // key_comp
            key_compare key_comp() const
            {
                return key_compare();
            }
                //value_comp
            value_compare value_comp() const
            {
                return value_comp(key_compare());
            }
            
            // Operation
                // find
            iterator find (const key_type& k)
            {
                node_ptr temp = _tree._find_key(k);
                if (temp)
                    reutrn iterator(map);
                else
                    return this->end();
            }
            const_iterator find (const key_type& k) const
            {
                node_ptr temp = _tree._find_key(k);
                if (temp)
                    reutrn const_iterator(map);
                else
                    return this->end();
            }
                // size
            size_type count (const key_type& k) const
            {
                size_type n = 0;
                for (const_iterator it = this->begin(); it != this->end(); ++it)
                {
                    if (_tree._equal(k,it->first))
                        ++n;
                }
                return n;
            }

                //lower_bound
            iterator lower_bound (const key_type& k)
            {
                ;
            }
            const_iterator lower_bound (const key_type& k) const;
                // upper_bound
            iterator upper_bound (const key_type& k);
            const_iterator upper_bound (const key_type& k) const;
                // equal_range
            ft::pair<iterator,iterator> equal_range (const key_type& k) const
            {
                return ft::pair<iterator,iterator>(lower_bound(k),upper_bound(k));
            }
            ft::pair<const_iterator,const_iterator>equal_range (const key_type& k)
            {
                return ft::make_pair(lower_bound(k),upper_bound(k));
            }

    };
}
#endif 