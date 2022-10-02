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
            // typedef rbtree<value_type, value_compare, allocator_type> tree_type;
            typedef ft::rbtree<value_type> tree_type;
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
            typedef rbtree<value_type, value_compare, allocator_type>	_tree;
            value_compare _comp_val; // gcc 따라서 이거 없이 도 해보자 컴파일 
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
			iterator begin()
			{
				return this->_tree._begin();
			}
			const_iterator begin() const
			{
				return this->_tree._begin();
			}
			// ft::pair<iterator, bool> insert(const value_type &__x)
			// {

			// }



    };
}
#endif 