#ifndef VECTOR_H
#define VECTOR_H

#include "type_traits.hpp"
#include "reverse_iterator.hpp"
#include "vector_iterator.hpp"
#include <cstddef>   // std::ptrdiff_t
#include <memory>    // std::allocator
#include <stdexcept> // std::out_of_range

namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
    class vector
    {
    public:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef ft::vector_iterator<value_type> iterator;
        typedef ft::vector_iterator<const value_type> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef std::ptrdiff_t difference_type;
        typedef std::size_t size_type;

        // constructor
        explicit vector(const allocator_type &alloc = allocator_type())
            : _allocator(alloc), _capacity(0), _size(0), _data(NULL)
        {
        } // default

        explicit vector(size_type n, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type())
            : _allocator(alloc), _capacity(n), _size(n)
        {
            _data = _allocator.allocate(_capacity);
            for (size_type i = 0; i < _size; ++i)
            {
                _allocator.construct(_data + i, val);
            }
        } // fill

        template <class InputIterator>
        vector(
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
            InputIterator last,
            const allocator_type &alloc = allocator_type())
            : _allocator(alloc)
        {
            _capacity = 0;
            for (InputIterator it = first; it != last; ++it)
            {
                _capacity++;
            }
            _data = _allocator.allocate(_capacity);
            for (_size = 0; _size < _capacity; ++_size)
            {
                _allocator.construct(_data + _size, *first++);
            }
        } // range

        vector(const vector &x)
            : _allocator(x._allocator), _capacity(x._capacity), _size(x._size)
        {
            _data = _allocator.allocate(_capacity);
            for (size_type i = 0; i < _size; ++i)
            {
                _allocator.construct(_data + i, x[i]);
            }
        } // copy

        // destructor
        ~vector()
        {
            for (size_type i = 0; i < _size; ++i)
            {
                _allocator.destroy(_data + i);
            }
            _allocator.deallocate(_data, _capacity);
        }

        // operator=
        vector& operator=(const vector& x)
        {
            if (this != &x)
            {
                for (size_type i = 0; i < _size; ++i)
                {
                    _allocator.destroy(_data + i);
                }
                _allocator.deallocate(_data, _capacity);
                _capacity = x._capacity;
                _data = _allocator.allocate(_capacity);
                for (_size = 0; _size < x._size; ++_size)
                {
                    _allocator.construct(_data + _size, x[_size]);
                }
            }
            return (*this);
        }

        // Iterators
        iterator begin()
        {
            return (iterator(_data));
        }

        const_iterator begin() const
        {
            return (const_iterator(_data));
        }

        iterator end()
        {
            return (iterator(_data + _size));
        }

        const_iterator end() const
        {
            return (const_iterator(_data + _size));
        }

        reverse_iterator rbegin()
        {
            return (reverse_iterator(end()));
        }

        const_reverse_iterator rbegin() const
        {
            return (const_reverse_iterator(end()));
        }

        reverse_iterator rend()
        {
            return (reverse_iterator(begin()));
        }

        const_reverse_iterator rend() const
        {
            return (const_reverse_iterator(begin()));
        }

        // Capacity
        size_type size() const
        {
            return (_size);
        }

        size_type max_size() const
        {
            return (_allocator.max_size());
        }

        size_type capacity() const
        {
            return (_capacity);
        }

        bool empty() const
        {
            return (_size == 0);
        }

        void reserve(size_type n)
        {
            if (n > _capacity)
            {
                pointer tmp = _data;

                _data = _allocator.allocate(n);
                for (size_type i = 0; i < _size; i++)
                {
                    _allocator.construct(_data + i, tmp[i]);
                    _allocator.destroy(tmp + i);
                }
                _allocator.deallocate(tmp, _capacity);
                _capacity = n;
            }
        }

        // Element access
        reference operator[](size_type n)
        {
            return (_data[n]);
        }

        const_reference operator[](size_type n) const
        {
            return (_data[n]);
        }

        reference at(size_type n)
        {
            if (n < _size)
                return (_data[n]);
            throw std::out_of_range("vector");
        }

        const_reference at(size_type n) const
        {
            if (n < _size)
                return (_data[n]);
            throw std::out_of_range("vector");
        }

        reference front()
        {
            return (_data[0]);
        }

        const_reference front() const
        {
            return (_data[0]);
        }

        reference back()
        {
            return (_data[_size - 1]);
        }

        const_reference back() const
        {
            return (_data[_size - 1]);
        }

    private:
        size_type _size;     // current size
        size_type _capacity; // allocated size
        allocator_type _allocator;
        pointer _data;
    };
} // namespace ft

#endif