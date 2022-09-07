#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"

#include <cstddef>   // std::ptrdiff_t
#include <memory>    // std::allocator
#include <stdexcept> // std::out_of_range

namespace ft
{
    template < class T, class Alloc = std::allocator<T> >  // generic template  
    class vector
    {

        // member types:
        private:
            typedef vector<T, Alloc> vector_type;
        public:
            //The first template parameter (T)
            //The second template parameter (Alloc)
            //allocator_type::reference
            //allocator_type::pointer
            //allocator_type::const_pointer 
            //a random access iterator to value_type
            // ~  const
            // reverse_iterator<iterator>
            // reverse_iterator<const_iterator>
            // a signed integral type, identical to: iterator_traits<iterator>::difference_type
            //an unsigned integral type that can represent any non-negative value of difference_type
    
            typedef T                                           value;
            typedef Alloc                                       allocator_type;
            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::const_reference    const_reference;
            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::const_pointer      const_pointer;
            typedef ft::random_access_iterator<pointer, vector_type> iterator;
            typedef ft::random_access_iterator<const_pointer, vector_type> const_iterator;
            typedef typename ft::reverse_iterator<iterator> reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
            typedef std::ptrdiff_t  difference_type;
            typedef std::size_t    size_type;

        //Member variables
        protected:
            allocator_type  _alloc;
            pointer         _capacity;
            pointer         _start;
            pointer         _end;


        //Member functions
        public:
            //default (1)	
            explicit vector (const allocator_type& alloc = allocator_type())
            : _alloc(alloc), _start(0), _end(0), _capacity(0)
            {}
            //fill (2)	
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
            : _alloc(alloc), _capacity(n), _
            {

            }
            //range (3)	
            template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
            //copy (4)	
            vector (const vector& x);


    }  
}



#endif