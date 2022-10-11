#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
    template <class T, class Container = ft::vector<T> > 
    class stack
    {   
        // Member types
        public:
            typedef T value_type;
            typedef Container   container_type;
            typedef size_t size_type;
        // Member variables
        protected:
            container_type _x;
        public:
            // Constructor
            explicit stack (const container_type& ctnr = container_type())
            :_x(ctnr) {}
            // destructor
            virtual ~stack() {}

            // Member function
            
            bool empty() const
            {
                return (this->_x.empty());
            }
            size_type size() const
            {
                return (this->_x.size());
            }
            value_type& top()
            {
                return (this->_x.back());
            }
            const value_type& top() const
            {
                return (this->_x.back());
            }
            void push (const value_type& val)
            {
                this->_x.push_back(val);
            }
            void pop()
            {
                this->_x.pop_back();
            }

            template <class _Tp1, class _Seq1>
            friend bool operator== (const stack<_Tp1, _Seq1>&, const stack<_Tp1, _Seq1>&);
            template <class _Tp1, class _Seq1>
            friend bool operator< (const stack<_Tp1, _Seq1>&, const stack<_Tp1, _Seq1>&);
                    
    };
    // Non-member function overloads
    template <class T, class Container>
    bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return (lhs._x == rhs._x);
    }

    template <class T, class Container>
    bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return !(lhs == rhs);
    }
	
    template <class T, class Container>
    bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs._x < rhs._x;
    }

    template <class T, class Container>
    bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return !(rhs < lhs);
    }
	
    template <class T, class Container>
    bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return rhs < lhs;
    }

    template <class T, class Container>
    bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return !(lhs < rhs); 
    }
}
#endif
