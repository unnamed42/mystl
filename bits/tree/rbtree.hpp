#ifndef __RUBBISH_RED_BLACK_TREE__
#define __RUBBISH_RED_BLACK_TREE__

#include "binary_tree_base.hpp"
#include <bits/move.h> // std::move
#include <initializer_list>

namespace rubbish {
    
    namespace helper {
        constexpr bool _rb_red = true;
        constexpr bool _rb_black = false;
        
        template <class T> struct rbtree_node{
            typedef rbtree_node<T> self_type;
            
            T data;
            self_type *left,*right,*parent;
            bool color;
            
            constexpr rbtree_node():data(),left(nullptr),right(nullptr),parent(nullptr),color(_rb_red) {}
            explicit rbtree_node(const T &e):data(e),left(nullptr),right(nullptr),parent(nullptr),color(_rb_red) {}
            explicit rbtree_node(T &&e):data(std::move(e)),left(nullptr),right(nullptr),parent(nullptr),color(_rb_red) {}
            rbtree_node(const self_type &o):data(o.data),left(nullptr),right(nullptr),parent(nullptr),color(o.color) {}
            rbtree_node(self_type &&o):data(std::move(o.data)),left(nullptr),right(nullptr),parent(nullptr),color(o.color) {}
            
            // Assignment operators to avoid warning [-Weffc++]
            self_type& operator=(const self_type &o) {data=o.data; left=right=parent=nullptr; color=o.color;return *this;}
            self_type& operator=(self_type &&o) {data=std::move(o.data); left=right=parent=nullptr;color=o.color;return *this;}
        };
        // Algorithms from http://www.geeksforgeeks.org/
        // Functions used for rotations
        template <class Node> void rbtree_left_rotate(Node *&root, Node *&ptr);
        template <class Node> void rbtree_right_rotate(Node *&root, Node *&ptr);
        // This function fixes violations caused by BST(Binary Search Tree) insertion
        template <class Node> void rbtree_insertion_fix(Node *&root, Node *&ptr);
        template <class Node> void rbtree_deletion_fix(Node *&root,Node *ptr);
        
    } // namespace helper
    
    template <class T,class Node = helper::rbtree_node<T> > class rbtree:public binary_tree_base<T,Node>{
        private:
            typedef binary_tree_base<T,Node> base_class;
        public:
            typedef rbtree<T,Node> self_type;
            typedef Node node;
        protected:
            void rbtree_delete(Node *&root,Node *ptr);
            
            // Insert a node with given value, return the inserted position
            template <class U> node* insert(node* &root,U&&);
        public:
            typedef typename base_class::inorder_iterator iterator;
            typedef typename base_class::const_inorder_iterator const_iterator;
            
            // Default initialization
            constexpr rbtree();
            
            // Initialize with a given list
            rbtree(std::initializer_list<T>&&);
            
            // Copy constructor
            rbtree(const self_type&);
            
            // Move constructor
            rbtree(self_type&&);
            
            // Insert a node with given value, a wrapper of protected version of insert()
            template <class U> iterator insert(U&&);
            
            // Delete nodes with given value
            template <class U> void erase(U&&);
            
            // Find the given value, and return its position
            template <class U> iterator find(U&&);
            template <class U> const_iterator find(U&&) const;
            
            // Iterator functions
            iterator begin();
            iterator end();
            const_iterator cbegin() const;
            const_iterator cend() const;
            
            // Assignment operators to avoid warning [-Weffc++]
            self_type& operator=(const self_type&);
            self_type& operator=(self_type&&);
        private:
            using base_class::m_root;
    };
} // namespace rubbish

#include "rbtree.cc"

#endif // __RUBBISH_RED_BLACK_TREE__
