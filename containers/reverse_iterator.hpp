#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP
# include "iterator_base.hpp"
// # include <vector>
// std::vector<int> i;
namespace ft
{
template <class Iterator> 
class reverse_iterator: public ft::iterator<typename ft::iterator_traits<Iterator>::iterator_category,
                                            typename ft::iterator_traits<Iterator>::value_type,
                                            typename ft::iterator_traits<Iterator>::difference_type,
                                            typename ft::iterator_traits<Iterator>::pointer,
                                            typename ft::iterator_traits<Iterator>::reference>
                                        
{
    public:
        //Member_types
        typedef Iterator iterator_type;
           
        typedef typename ft::iterator_traits<Iterator>::iterator_category   iterator_category;
        typedef typename ft::iterator_traits<Iterator>::value_type          value_type;
        typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;
        typedef typename ft::iterator_traits<Iterator>::pointer             pointer;
        typedef typename ft::iterator_traits<Iterator>::reference           reference;
    
    protected:
        iterator_type current_state; // A copy of the original iterator
    
    public:
    // 생성자
        reverse_iterator() {} // default (1)
        
        explicit reverse_iterator(iterator_type it) 
        :current_state(it) 
        {
        } // initializtion (2)
        
        // reverse_iterator(const reverse_iterator& __x)
        // : _M_current(__x._M_current) {}

        template<class Iter>       // copy (3)
        reverse_iterator(const reverse_iterator<Iter>& rev_it)
        :current_state(rev_it.base()) {}
    // 소멸자
        virtual ~reverse_iterator() {}
        
        // return base iterator
        iterator_type base() const
        {
            return current_state;
        }

        //operators
        reference operator*() const
        {
            iterator_type tmp = current_state;
            return *(--tmp);
        } 

        //pointer
        pointer operator->() const
        {
            return &(operator*());
        }

        reverse_iterator& operator++()
        {
            --current_state;
            return *this;
        }

        reverse_iterator operator++(int)
        {
            reverse_iterator __tmp = *this;
            --current_state;
            return __tmp;
        }

        reverse_iterator& operator--()
        {
            ++current_state;
            return *this;
        }

        reverse_iterator operator--(int)
        {
            reverse_iterator __tmp = *this;
            ++current_state;
            return __tmp;
        }

        reverse_iterator operator+(difference_type __n) const
        {
            return reverse_iterator(current_state - __n);
        }

        reverse_iterator& operator+=(difference_type __n)
        {
            current_state -= __n;
            return *this;
        }

        reverse_iterator operator-(difference_type __n) const
        {
            return reverse_iterator(current_state + __n);
        }

        reverse_iterator& operator-=(difference_type __n)
        {
            current_state += __n;
            return *this;
        }

        reference operator[](difference_type __n) const
        {
            return *(*this + __n);
        }
};

// Non-member function overloads
// relational operators
template <class Iterator1, class Iterator2>
bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return (lhs.base() == rhs.base());
}

template <class Iterator1, class Iterator2>
bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return !(rhs == lhs);
}

template <class Iterator1, class Iterator2>
bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return (rhs.base() < lhs.base());
}

template <class Iterator1, class Iterator2>
bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return !(rhs < lhs);
}

template <class Iterator1, class Iterator2>
bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return (rhs < lhs);
}

template <class Iterator1, class Iterator2>
bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return !(lhs < rhs);
}

/**
 * @brief Addition operator
 * Returns a reverse iterator pointing to the element located n positions away from the element pointed to by rev_it.
 * @tparam Iterator
 * @param n Number of elements to offset.
 * @param rev_it Reverse iterator.
 * @return An iterator pointing to the element n positions away from rev_it.
 */
template <typename Iterator>
reverse_iterator<Iterator> operator+(
	typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rev_it)
{ 
    return reverse_iterator<Iterator>(rev_it.base() - n); 
}

/**
 * @brief Subtraction operator
 * Returns the distance between lhs and rhs.
 * @tparam Iterator 
 * @param lhs 
 * @param rhs 
 * @return The number of elements between lhs and rhs.
 */
template <typename Iterator1, typename Iterator2>
typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
{ 
    return rhs.base() - lhs.base(); 
}

}
#endif
