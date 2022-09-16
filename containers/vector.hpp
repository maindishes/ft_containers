#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "type_trait.hpp"
// #include "iterator_base.hpp"

#include <cstddef>   // std::ptrdiff_t
#include <memory>    // std::allocator
#include <stdexcept> // std::out_of_range

#include <iostream>


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
    
            typedef T                                           value_type;
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
            : _alloc(alloc), _start(0), _end(0), _end_capacity(0), _size(0),_capacity(0)
            {}
            
            //fill constructor	
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
            : _alloc(alloc), _capacity(n), _size(n)
            {
                this->_start = _alloc.allocate(n);
                this->_end = this->_start;
                this->_end_capacity = this->_start + n;
                for (size_type i = 0; i < n; ++i)
                {
                    _alloc.construct(this->_end++, val);                
                }
            }

            //range constructor  (enable_if)
            template <typename InputIterator>
            vector (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last,
             const allocator_type& alloc = allocator_type())
            : _alloc(alloc)
            {
                // std::cout << "In----------" << std::endl;
                _capacity = 0;
                for (InputIterator it = first; it != last; it++)
                    _capacity++;
                _start = _alloc.allocate(_capacity);
                _end = _start + _capacity;
                for (_size = 0; _size < _capacity; _size++)
                    _alloc.construct(_start + _size, *first++);
                // std::cout << "OUT--------------" << std::endl; 
            }
            
            // copy constructor 
            vector (const vector& x)
            : _alloc(x._alloc), _capacity(x._capacity), _size(x._size)
            {
                // size_type n = x.size();
                this->_start = this->_alloc.allocate(_capacity);
                this->_end = _start;
                this->_end_capacity = _start + _capacity;
                for (size_type i = 0; i < _size; ++i)
                {
                    _alloc.construct(_end++, x[i]);
                }
            }

            //destructor
            virtual ~vector()
            {
                while(this->_start != this->_end) {
                    this->_alloc.destroy(--_end);
                }
                this->_alloc.deallocate(this->_start, size_type(this->_end_capacity - this->_start));
                // std::cout << "Finish" << std::endl;
            }

            // operator=
            vector& operator=(const vector& x)
            {
                if (this == &x)
                    return (*this);
                while(this->_start != this->_end)
                    this->_alloc.destroy(--this->_end);
                this->_alloc.deallocate(this->_start, _capacity);
                _capacity = x._capacity;
                _start = _alloc.allocate(_capacity);
                for (_size = 0; _size < x._size; ++_size)
                    _alloc.construct(_start + _size, x[_size]);
                return (*this);
            }


            // iterators
                // begin
            iterator begin()
            {
                return (iterator(this->_start));
            }
            const_iterator begin() const
            {
                return (const_iterator(this->_start));
            }
                // end
            iterator end()
            {
                return (iterator(_start + _size)); // _end
            }
            const_iterator end() const
            {
                return (const_iterator(_start + _size)); // _end
            }
            // reverse_iterator
                // rbegin
            reverse_iterator rbegin()
            {
                return (reverse_iterator(end()));
            }
            const_reverse_iterator rbegin() const
            {
                return (const_reverse_iterator(end()));
            }
                // end
            reverse_iterator rend()
            {
                return (reverse_iterator(begin()));
            }
            const_reverse_iterator rend() const
            {
                return (const_reverse_iterator(begin()));
            }

            // Capacity
                // size
            size_type size() const
            {
                // return size_type(this->end() - this->begin());
                return (_size);
            }

                // max_size
            size_type max_size() const
            {
                // maybe gcc 자료구조 ptrdiff 의 오버플로우 생각해야한다. (alloc.max_size()가 정해진 자료구조보다 커버리면 오버플로우!)
                // 1바이트 인 char 형 일때만 ?!
                return (this->_alloc.max_size() > PTRDIFF_MAX ? PTRDIFF_MAX : this->_alloc.max_size());
                // return (this->_alloc.max_size());
            }
                // resize
            void resize (size_type n, value_type val = value_type())
            {
                //erase, insert
                // if (n > this->max_size())
                //     throw std::out_of_range("ft::vector");
                if (n < this->_size)
                {
                    for(size_type i =_size - n; i < _size; i++)
                        _alloc.destroy(this->_start + i);
                }
                else if (n >= this->_size)
                {
                    this->reserve(n);
                    for (size_type i = _size; i < n; i++)
                        _alloc.construct(_start + i, val);
                }
                _size = n;
            }
                // capacity
            size_type capacity() const
            {
                // return (size_type(this->_end_capacity - this->_start));
                return (_capacity);
            }
                // empty
            bool empty() const
            {
                // return (_start == _end);
                return (_size == 0);
            }
                // reverse
            void reserve (size_type n)
            {
                // if (n > max_size())
                // {
                //     throw std::length_error("ft_vector"); // 원랜 "vector" 로만 나옴
                // }
                if (n > this->capacity())
                {
                    pointer tmp = _start;
                    _start = _alloc.allocate(n);
                    for (size_type i = 0; i < _size; i++)
                    {
                        _alloc.construct(_start + i, tmp[i]);
                        _alloc.destroy(tmp + i);
                    }
                    _alloc.deallocate(tmp, this->capacity());
                    _capacity = n;
                }
            }

            // Element access
                // operator[]
            reference operator[] (size_type n)
            {
                return (_start[n]);
            }
            const_reference operator[] (size_type n) const
            {
                return (_start[n]);
            }
                // at
            reference at (size_type n)
            {
                if (n >= size())
				    throw std::out_of_range("ft::vector");
			    return (_start[n]);
            }
            const_reference at (size_type n) const
            {
                if (n >= size())
				    throw std::out_of_range("ft::vector");
			    return (_start[n]);
            }
                // front
            reference front()
            {
                return (_start[0]);
            }
            const_reference front() const
            {
                return (_start[0]);
            }
                // back
            reference back()
            {
                return (*(end() - 1));
                // return (_start[_size-1]);
            }
            const_reference back() const
            {
                return (*(end() - 1)); 
            }

    };
}   
#endif
