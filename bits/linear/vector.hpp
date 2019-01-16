#ifndef __RUBBISH_VECTOR__
#define __RUBBISH_VECTOR__

#include <bits/move.h> // std::move
#include <initializer_list> // std::initializer_list
#include "continuous_container.hpp"

namespace rubbish{
    constexpr std::size_t __vec_base=16;
    
    template <class T> class vector: public continuous_container<T>{
        private:
            typedef continuous_container<T> base_class;
        public:
            typedef vector<T> self_type;
            
            // Inherit all constructors
            using base_class::base_class;
            
            typedef typename base_class::iterator iterator;
            typedef typename base_class::reverse_iterator reverse_iterator;
            typedef typename base_class::const_iterator const_iterator;
            
            // Remove all contents
            void clear();
            
            // Append an element to the end
            void push_back(const T&);
            
            // Remove an element at the end
            void pop_back();
            
            // Resize
            void resize();
            
            // Copy assignment
            self_type& operator=(const self_type&);
            
            // Move assignment
            self_type& operator=(self_type&&);
            
            // Subscript dereference
            T& operator[](const std::size_t);
            
        private:
            using base_class::m_base;
            using base_class::m_size;
            using base_class::m_used;
    };
    
} // namespace rubbish

#include "vector.cc"

#endif // __RUBBISH_VECTOR__
