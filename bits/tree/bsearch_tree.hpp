#ifndef __RUBBISH_BINARY_SEARCH_TREE__
#define __RUBBISH_BINARY_SEARCH_TREE__

#include "binary_tree_base.hpp"
#include <initializer_list>
#include <bits/move.h> // std::move

namespace rubbish{
    // Minimum requirements of type `Node`:
    //   Same as requirements of `node` used in `binary_tree_base`.
    
    template <class T,class Node = rubbish::helper::binary_tree_node<T> > class bsearch_tree: public binary_tree_base<T,Node>{
        private:
            typedef binary_tree_base<T,Node> base_class;
        public:
            typedef bsearch_tree<T,Node> self_type;
            
            typedef typename base_class::node node;
            typedef typename base_class::inorder_iterator iterator;
            typedef typename base_class::reverse_inorder_iterator reverse_iterator;
            typedef typename base_class::const_inorder_iterator const_iterator;
            typedef typename base_class::const_reverse_inorder_iterator const_reverse_iterator;
            
        private:
            using base_class::m_root;
            
            // Insert a node to a tree(represented as a raw pointer), and return its position
            template <class U> node* insert(node*&,U&&);
            
        public:
            // Default initialization
            constexpr bsearch_tree();
            
            // Wrap a raw pointer into a class
            explicit bsearch_tree(node *root);
            
            // Initialize with a given list
            explicit bsearch_tree(std::initializer_list<T>&&);
            
            // Copy constructor
            bsearch_tree(const self_type&);
            
            // Move constructor
            bsearch_tree(self_type&&);
            
            // Insert a node to this tree
            template <class U> iterator insert(U&&);
            
            // Find an element and return itrses location
            template <class U> iterator find(U&&);
            template <class U> const_iterator find(U&&) const;
            
            iterator begin();
            iterator end();
            reverse_iterator rbegin();
            reverse_iterator rend();
            const_iterator cbegin() const;
            const_iterator cend() const;
            const_reverse_iterator crbegin() const;
            const_reverse_iterator crend() const;
            
            // Assignment operators to avoid warning [-Weffc++]
            self_type& operator=(const self_type&);
            self_type& operator=(self_type&&);
    };

} // namespace rubbish

#include "bsearch_tree.cc"

#endif // __RUBBISH_BINARY_SEARCH_TREE__

