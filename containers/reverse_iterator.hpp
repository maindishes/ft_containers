#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP
# include "iterator_base.hpp"
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
           
        typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
        typedef typename iterator_traits<Iterator>::value_type          value_type;
        typedef typename iterator_traits<Iterator>::difference_type     difference_type;
        typedef typename iterator_traits<Iterator>::pointer             pointer;
        typedef typename iterator_traits<Iterator>::reference           reference;
    
    protected:
        iterator_type current_state;
    
    public:
};
}
#endif