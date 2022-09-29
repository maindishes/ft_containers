#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
    template <class T1, class T2>
    struct pair
    {
        // Member types
        typedef T1 first_type;
        typedef T2 second_type;

        // Member variables
        T1 first;
        T2 second;

        // Member functions
            // constructor
            //  default (1)
        pair()
        :first(T1()), second(T2()) {}
            // copy (2)	
        template<class U, class V> 
        pair (const pair<U,V>& pr)
        : first(pr.first), second(pr.second) {}
            // initialization (3)	
        pair (const first_type& a, const second_type& b)
        : first(a), second(b) {}

        pair& operator= (const pair& pr)
        {
            if (this != &pr)
            {
                first = pr.first;
                second = pr.second;
            }
            return (*this);
        }
    }; 
    // Non-member function overloads
        // (1)	
    template <class T1, class T2>
    bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
         return ((lhs.first == rhs.first) && (lhs.second == rhs.second));
    }
        // (2)	
    template <class T1, class T2>
    bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return !(lhs == rhs);
    }
        // (3)	
    template <class T1, class T2>
    bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return (lhs.first < rhs.first ||  (!(rhs.first < lhs.first) && (lhs.second < rhs.second))); 
    }
        // (4)	
    template <class T1, class T2>
    bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return !(rhs < lhs);
    }
        // (5)	
    template <class T1, class T2>
    bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return rhs < lhs;
    }
        // (6)	
    template <class T1, class T2>
    bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return !(lhs < rhs);
    }

    template <class T1,class T2>
    pair<T1,T2> make_pair (T1 x, T2 y)
    {
        return ( pair<T1,T2>(x,y) );
    }
}
#endif
