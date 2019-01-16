#ifndef __RUBBISH_STACK__
#define __RUBBISH_STACK__

#include "../linear/deque.hpp"
#include <bits/move.h>

namespace rubbish{
    
    // Minimum requirements of type `Container`:
    //   Can push an element to its end by member function `void push_back(const T&)` or `void push(T&&)`
    //   Can destruct the element at its end by member function `void pop_back()`;
    //   Can access its final element by member function `front()`;
    //   Can return its length by member function `std::size_t size()`;
    //   Copy-constructible, move-constructible;
    //   Can be default-initialized.
    template <class T,class Container = rubbish::deque<T> > class stack{
        public:
            typedef typename Container::iterator iterator;
            typedef typename Container::const_iterator const_iterator;
            typedef typename Container::reverse_iterator reverse_iterator;
            typedef typename Container::const_reverse_iterator const_reverse_iterator;
            
            typedef stack<T,Container> self_type;
            
            // Default constructor
            stack();
            
            // Copy constructor
            stack(const self_type&);
            
            // Move constructor
            stack(self_type&&);
            
            ~stack() = default;
            
            // Return the length current in use
            std::size_t size() const noexcept;
            
            // Check if the stack holds no element
            bool empty() const;
            
            // Push an element to stack top
            void push(const T&);
            
            // Just an rvalue reference overload
            void push(T&&);
            
            // Delete the element at stack top. May throw an exception.
            void pop();
            
            // Get the element at stack top. May throw an exception.
            T top() const;
            
            // Iterators
            iterator begin();
            iterator end();
            const_iterator cbegin() const;
            const_iterator cend() const;
            reverse_iterator rbegin();
            reverse_iterator rend();
            const_reverse_iterator crbegin() const;
            const_reverse_iterator crend() const;
            
            self_type& operator=(const self_type &);
            self_type& operator=(self_type&&);
        private:
            Container m_base;
    };
    
} // namespace rubbish

#include "stack.cc"

#endif // __RUBBISH_STACK__
