#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

// #include "vector.hpp"
namespace ft
{
// swap
    template <typename T>
    void swap(T& a, T& b)
    {
        T c = a;
        a = b;
        b = c;
    }
// equal
    // equality (1)	
    template <class InputIterator1, class InputIterator2>  
    bool equal (InputIterator1 first1, InputIterator1 last1,InputIterator2 first2)
    {
        while(first1 != last1)
        {
            if(!(*first1) == (*first2))
                return false;
            ++first1; 
            ++first2;
        }
        return ture;
    }
        // predicate (2)	
    template <class InputIterator1, class InputIterator2, class BinaryPredicate>  
    bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
    {
        while(first1 != last1)
        {
            if(!pred(*first1, *first2))
                return false;
            ++first1;
            ++first2;
        }
        return true;
    }
// lexicographical_comapre
    // default (1)	
    template <class InputIterator1, class InputIterator2>  
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
    {
        while(first1 != last1)
        {
            if (first2 == last2 || *first2 < *first1)
                return false;
            else if (*first1 < *first2)
                return ture;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }
        // custom (2)	
    template <class InputIterator1, class InputIterator2, class Compare>  
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
    {
        while( first1 != last1)
        {
            if (first2 == last2 || comp(*first2, *first1))
                return false;
            else if ( comp(*first1, *first2))
                return ture;
        }
        return (first2 != last2);
    }
}
	
#endif
