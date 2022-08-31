#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

namespace ft
{
    // Empty class to identify the category of an iterator as each other
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forword_iterator_tag         : public input_iterator_tag {};
    struct bidirectional_iterator_tag   : public forword_iterator_tag {};
    struct random_access_iterator_tag   : public bidirectional_iterator_tag {};

/**
 * @param Category  : Category to which the iterator belongs to
 * @param T		    : Type of elements pointed by the iterator
 * @param Distance  : Type to represent the difference between two iterators
 * @param Pointer   : Type to represent a pointer to an element pointed by the iterator
 * @param Reference : Type to represent a reference to an element pointed by the iterator
**/
    template <typename Category,
              typename T,
              typename Distance = ptrdiff_t,
              typename Pointer = T *,
              typename Reference = T &>
    struct iterator
    {
        typedef T           value_type;
        typedef Distance    difference_type;
        typedef Pointer     pointer;
        typedef Reference   reference;
        typedef Category    iterator_category;
    };
    
/**
 * Traits class defining properties of iterators.
 **/
    template <typename Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
        typedef typename Iterator::iterator_category    iterator_category;
    };
/**
 * Traits class defining properties of iterators. (T * sepcializtion)
 **/
    template <typename T>
    struct iterator_traits<T *>
    {
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef T*                              pointer;
        typedef T&                              reference;
        typedef random_access_iterator_tag      iterator_category;
    };
/**
 * Traits class defining properties of iterators. (const T * sepcializtion)
 **/
    template <typename T>
    struct iterator_traits<const T *>
    {
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef const T*                              pointer;
        typedef const T&                              reference;
        typedef random_access_iterator_tag      iterator_category;
    };            

// 나중에 algorithm.hpp 로 옮겨 . 
template<typename InputIterator>
typename ft::iterator_traits<InputIterator>::difference_type
    distance (InputIterator first, InputIterator last)
    {
        typename ft::iterator_traits<InputIterator>::difference_type n = 0;
        for ( first != last; first++)
            n++;
        return (n)
    }
}
#endif 