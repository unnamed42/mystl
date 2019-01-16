#ifndef __RUBBISH_AVL_TREE__
#define __RUBBISH_AVL_TREE__

#include <initializer_list>
#include "binary_tree_base.hpp"
#include <bits/move.h> // std::forward, std::move

namespace rubbish{
    
    namespace helper{
        template <class T> struct avl_tree_node{
            typedef avl_tree_node<T> self_type;
            
            T data;
            self_type *left,*right,*parent;
            int height;
            
            constexpr avl_tree_node():data(),left(nullptr),right(nullptr),parent(nullptr),height(1) {}
            explicit avl_tree_node(const T &elem):data(elem),left(nullptr),right(nullptr),parent(nullptr),height(1) {}
            explicit avl_tree_node(T &&elem):data(std::move(elem)),left(nullptr),right(nullptr),parent(nullptr),height(1) {}
            avl_tree_node(const self_type &o):data(o.data),left(nullptr),right(nullptr),parent(nullptr),height(o.height) {}
            avl_tree_node(self_type &&o):data(std::move(o.data)),left(nullptr),right(nullptr),parent(nullptr),height(o.height) {}
            
            // Assignment operators to avoid warning [-Weffc++]
            self_type& operator=(const self_type &o) {data=o.data; left=right=parent=nullptr; height=o.height;return *this;}
            self_type& operator=(self_type &&o) {data=std::move(o.data); left=right=parent=nullptr; height=o.height;return *this;}
        };
        
        // Some other helper functions
        template <class T> static inline T max(const T &lhs,const T &rhs) { return lhs>rhs?lhs:rhs; }
        
        template <class Node> static inline int avl_height(const Node *p) { return p==nullptr?0:p->height; }
        
        template <class Node> static inline int avl_balance(const Node *p) { return p==nullptr?0:avl_height<Node>(p->left)-avl_height<Node>(p->right); }
        
        // return the node with minimum value found in a tree
        template <class Node> static inline Node* min_node(Node *root){
            auto current = root;
            /* loop down to find the leftmost leaf */
            while (current->left != nullptr)
                current = current->left;
            return current;
        }
        
        // Functions used to rotate, defined in avl_tree.cc
        template <class Node> Node* avl_left_rotate(Node *root);
        template <class Node> Node* avl_right_rotate(Node *root);
        
    } // namespace helper
    
    // Minimum requirements of type `Node`:
    //   Satisfies requirements of `Node` used in `binary_tree_base`;
    //   Has a member of signed integral type named `height`;
    // Minimum requirements of `data`:
    //   Comparable using comparasion operator <, > and ==
    //   Assignable
    
    template <class T,class Node = rubbish::helper::avl_tree_node<T> > class avl_tree: public binary_tree_base<T,Node> {
        private:
            typedef binary_tree_base<T,Node> base_class;
        public:
            typedef typename base_class::node node;
            typedef typename base_class::inorder_iterator iterator;
            typedef typename base_class::reverse_inorder_iterator reverse_iterator;
            typedef typename base_class::const_inorder_iterator const_iterator;
            typedef typename base_class::const_reverse_inorder_iterator const_reverse_iterator;
            
            typedef avl_tree<T,Node> self_type;
            
        protected:
            // Insert node to a tree whose root is `root`, and return its new root
            // The inserted node is returned by the third parameter
            template <class U> node* insert(node* root,U&&,node*&);
            
            // Delete nodes in given tree
            template <class U> node* erase(node*,U&&);
            
        public:
            // Construct an empty tree
            constexpr avl_tree();
            
            // Construct from given list
            explicit avl_tree(std::initializer_list<T>&&);
            
            // Copy constructor
            avl_tree(const self_type&);
            
            // Move constructor
            avl_tree(self_type&&);
            
            // A destructor
            ~avl_tree() = default;
            
            // Insert a node to this tree, and return its location
            template <class U> iterator insert(U&&);
            
            // Find a node and return location, if not found return end iterator
            template <class U> const_iterator find(U&&) const;
            template <class U> iterator find(U&&);
            
            // Delete nodes with given value
            template <class U> void erase(U&&);
            
            // Iterator functions
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
        private:
            using base_class::m_root;
    };
    
} // namespace rubbish

#include "avl_tree.cc"

#endif // __RUBBISH_AVL_TREE__
