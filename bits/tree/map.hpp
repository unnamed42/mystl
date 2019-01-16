#ifndef __RUBBISH_MAP__
#define __RUBBISH_MAP__

#include "avl_tree.hpp"
#include "../utility/pair.hpp"
#include <bits/move.h> // std::forward, std::move
#include <initializer_list>

namespace rubbish{
    
    // Key is `T1`, value is `T2`
    template <class T1,class T2> class map{
        public:
            typedef pair<T1,T2> value_type;
        private:
            typedef avl_tree<value_type> base_class;
        public:
            typedef typename base_class::node node;
            typedef typename base_class::inorder_iterator iterator;
            typedef typename base_class::reverse_inorder_iterator reverse_iterator;
            typedef typename base_class::const_inorder_iterator const_iterator;
            typedef typename base_class::const_reverse_inorder_iterator const_reverse_iterator;
            
            // Default constructor
            constexpr map();
            
            // Copy constructor
            map(const map<T1,T2>&);
            
            // Move constructor
            map(map<T1,T2>&&);
            
            // Initialize with given list
            map(std::initializer_list<value_type>&&l);
            
            // The templates below are universal reference wrappers
            
            // Insert a node
            iterator insert(value_type&&);
            
            // Find a node whose `first` equals key
            template <class key> const_iterator find(key&&) const;
            template <class key> iterator find(key&&);
            
            // Delete nodes that equal to given value
            template <class key> void erase(key&&);
            
            // Reset to an empty map
            void clear();
            
            // Check emptiness
            bool empty() const noexcept;
            
            // Iterator functions
            iterator begin();
            iterator end();
            reverse_iterator rbegin();
            reverse_iterator rend();
            const_iterator cbegin() const;
            const_iterator cend() const;
            const_reverse_iterator crbegin() const;
            const_reverse_iterator crend() const;
            
            // Return the associated value if found. If not found, insert first
            template <class key> T2& operator[](key&&);
        private:
            base_class m_base;
    };
    
} // namespace rubbish

#include "map.cc"

#endif // __RUBBISH_MAP__
