#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

# include "iterator_base.hpp"

namespace ft
{
template <typename Iterator, typename Container> 
class random_access_iterator: public ft::iterator<typename ft::iterator_traits<Iterator>::iterator_category,
                                                  typename ft::iterator_traits<Iterator>::value_type,
                                                  typename ft::iterator_traits<Iterator>::difference_type,
                                                  typename ft::iterator_traits<Iterator>::pointer,
                                                  typename ft::iterator_traits<Iterator>::reference>
                                        
{
    public:
        // //Member_types
        typedef Iterator iterator_type;
        // typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
        // typedef typename iterator_traits<Iterator>::value_type          value_type;
        typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;
        typedef typename ft::iterator_traits<Iterator>::pointer             pointer;
        typedef typename ft::iterator_traits<Iterator>::reference           reference;
    
    protected:
        iterator_type current_state; // A copy of the original iterator
    
    public:
    // 생성자
        random_access_iterator() {} // default (1)
        
        explicit random_access_iterator(iterator_type it) 
        :current_state(it) {} // initializtion (2)
        
        // random_access_iterator(const random_access_iterator& __x)
        // : _M_current(__x._M_current) {}

        template<class Iter>       // copy (3)
        random_access_iterator(const random_access_iterator<Iter, Container>& it)
        :current_state(it.base()) {}
    // 소멸자
        virtual ~random_access_iterator() {}
        
        // return base iterator
        iterator_type base() const
        {
            return current_state;
        }

        // const iterator_type& base() const
        // {
        //     return current_state;
        // }

        //operators
        reference operator*() const
        {
            // iterator_type tmp = current_state;
            return *(current_state);
        } 

        //pointer
        pointer operator->() const
        {
            return &(operator*());
            // return current_state;
        }

        random_access_iterator& operator++()
        {
            ++current_state;
            return *this;
        }

        random_access_iterator operator++(int)
        {
            random_access_iterator __tmp = *this;
            ++current_state;
            return __tmp;
        }

        random_access_iterator& operator--()
        {
            --current_state;
            return *this;
        }

        random_access_iterator operator--(int)
        {
            random_access_iterator __tmp = *this;
            --current_state;
            return __tmp;
        }

        random_access_iterator operator+(difference_type __n) const
        {
            return random_access_iterator(current_state + __n);
        }

        random_access_iterator& operator+=(difference_type __n)
        {
            current_state += __n;
            return *this;
        }

        random_access_iterator operator-(difference_type __n) const
        {
            return random_access_iterator(current_state - __n);
        }

        random_access_iterator& operator-=(difference_type __n)
        {
            current_state -= __n;
            return *this;
        }

        reference operator[](difference_type __n) const
        {
            return *(*this + __n);
        }
};

// Non-member function overloads
// relational operators
// list 에선 random_access_
template <class Iterator1, class Iterator2, typename Container>
bool operator==(const random_access_iterator<Iterator1, Container>& lhs, const random_access_iterator<Iterator2, Container>& rhs)
{
    return (lhs.base() == rhs.base());
}

template <class Iterator1, class Iterator2, typename Container>
bool operator!=(const random_access_iterator<Iterator1, Container>& lhs, const random_access_iterator<Iterator2, Container>& rhs)
{
    return !(lhs == rhs);
}

template <class Iterator1, class Iterator2, typename Container>
bool operator<(const random_access_iterator<Iterator1, Container>& lhs, const random_access_iterator<Iterator2, Container>& rhs)
{
    return (lhs.base() < rhs.base());
}

template <class Iterator1, class Iterator2, typename Container>
bool operator<=(const random_access_iterator<Iterator1, Container>& lhs, const random_access_iterator<Iterator2, Container>& rhs)
{
    return !(rhs < lhs);
}

template <class Iterator1, class Iterator2, typename Container>
bool operator>(const random_access_iterator<Iterator1, Container>& lhs, const random_access_iterator<Iterator2, Container>& rhs)
{
    return (rhs < lhs);
}

template <class Iterator1, class Iterator2, typename Container>
bool operator>=(const random_access_iterator<Iterator1, Container>& lhs, const random_access_iterator<Iterator2, Container>& rhs)
{
    return !(lhs < rhs);
}

/**
 * @brief Addition operator
 * Returns a reverse iterator pointing to the element located n positions away from the element pointed to by it.
 * @tparam Iterator
 * @param n Number of elements to offset.
 * @param it iterator.
 * @return An iterator pointing to the element n positions away from it.
 */
template <typename Iterator, typename Container>
random_access_iterator<Iterator, Container> operator+(
	typename random_access_iterator<Iterator, Container>::difference_type n, const random_access_iterator<Iterator, Container> &it)
{ 
    return random_access_iterator<Iterator, Container>(it.base() + n); 
}

/**
 * @brief Subtraction operator
 * Returns the distance between lhs and rhs.
 * @tparam Iterator 
 * @param lhs 
 * @param rhs 
 * @return The number of elements between lhs and rhs.
 */
template <typename Iterator1, typename Iterator2, typename Container>
typename random_access_iterator<Iterator1, Container>::difference_type operator-(const random_access_iterator<Iterator1, Container> &lhs, const random_access_iterator<Iterator2, Container> &rhs)
{ 
    return lhs.base() - rhs.base(); 
}

}
#endif
