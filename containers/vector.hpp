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
            size_type       _size;    // current size
            size_type       _capacity;// allocated size

            allocator_type  _alloc;
            pointer         _end_capacity;
            pointer         _start;
            pointer         _end;


        //Member functions
        public:
            //empty container constructor (default constructor)
            explicit vector (const allocator_type& alloc = allocator_type())
            : _alloc(alloc), _start(0), _end(0), _end_capacity(0), _size(0)
            {}
            //fill constructor	
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
            : _alloc(alloc), _end_capacity(n), _capacity(n), _size(n)
            {
                this->_start = _alloc.allocate(n);
                this->_end = this->_start;
                this->_end_capacity = this->_start + n;
                for (size_type i = 0; i < n; ++i)
                {
                    _alloc.construct(this->_end++, val);                
                }
            }

            //range constructor
            template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
            
            // copy constructor 
            vector (const vector& x)
            : _alloc(x._alloc), _capacity(x._capacity), _size(x._size)
            {
                // size_type n = x.size();
                this->_start = this->_alloc.allocate(n);
                this->_end = _start;
                this->_end_capacity = _start + n;
                for (size_type i =0; i < n; ++i)
                {
                    _alloc.construct(_end + i, x[i])
                }
            }

            //destructor
            virtual ~vector()
            {
                while (this->_start != this->_end)
                    this->_alloc.destroy(--this->_end);
                this->alloc.deallocate(this->_start, this->size_type(this->_end_capacity - this->_start));
            }

            // size_type capacity() const
            // {
            //     return size_type(_end_capacity - _start);
            // }

            // operator=
            vector& operator=(const vector& x)
            {
                if (this == &x)
                    return (*this);
                
            }


    }  
}



#endif