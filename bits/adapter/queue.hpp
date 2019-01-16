#ifndef __RUBBISH_QUEUE__
#define __RUBBISH_QUEUE__

#include <stdexcept>
#include <bits/move.h> // std::move
#include "../deque.hpp"

namespace rubbish{
    
    // Minimum requirements of type `Container`:
    //   Can push an element to its end by member function `void push_back(const T&)`
    //   Can destruct the element at its front by member function `void pop_front()`;
    //   Can access its first element by dereferencing `begin()`;
    //   Can return its length by member function `std::size_t size()`;
    //   Copy-constructible, move-constructible;
    //   Can be default-initialized.
    
    template <class T,class Container = rubbish::deque<T> > class queue{
        private:
            Container m_base;
        public:
            typedef typename Container::iterator iterator;
            typedef typename Container::const_iterator const_iterator;
            typedef typename Container::reverse_iterator reverse_iterator;
            typedef typename Container::const_reverse_iterator const_reverse_iterator;
            
            typedef queue<T,Container> self_type;
            
            // Initialize an empty queue
            queue();
            
            // Copy-constructor
            queue(const queue<T,Container>&);
            
            // Move-constructor
            queue(queue<T,Container>&&);
            
            // Destructor
            ~queue()=default;
            
            // Return the length of this queue
            std::size_t size() const;
            
            // Check if the queue holds no element
            bool empty() const;
            
            // Push an element to queue back
            void push(const T &elem);
            
            // Just an rvalue reference overload
            void push(T&&);
            
            // Delete the element at queue front. May throw an exception
            void pop();
            
            // Get the element at queue front. May throw an exception
            T front() const;
            
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
    };
    
} // namespace rubbish

#include "queue.cc"

#endif // __RUBBISH_QUEUE__
