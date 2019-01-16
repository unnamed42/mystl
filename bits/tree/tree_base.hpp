#ifndef __RUBBISH_TREE_BASE__
#define __RUBBISH_TREE_BASE__

#include <deque>
#include <memory> // std::shared_ptr
#include <initializer_list>
#include <bits/stl_iterator_base_types.h> // std::forward_iterator_tag

namespace rubbish{
    
    template <class T> struct tree_node{
        T data;
        tree_node<T> *child,*sibling;
        
        tree_node():data(T()),child(nullptr),sibling(nullptr){}
        explicit tree_node(const T &e):data(e),child(nullptr),sibling(nullptr){}
        explicit tree_node(T &&e):data(e),child(nullptr),sibling(nullptr){}
    };
    
    // Minimum requirements of type `node`:
    //   A data member variable named `data`;
    //   Two pointer member variables named `child`, `sibling`, respectively;
    //   `node` can be default-initialized and value-initialized.
    
    template <class T,class node = rubbish::tree_node<T> > class tree_base{
        public:
            class iterator_base{
                public:
                    typedef T                           value_type;
                    typedef T*                          pointer;
                    typedef T&                          reference;
                    typedef std::forward_iterator_tag   iterator_category;
                    typedef std::ptrdiff_t              difference_type;
                    
                    typedef iterator_base                        self_type;
                    typedef std::shared_ptr< std::deque<node*> > data_type;
                    
                    explicit iterator_base(node *root);
                    explicit iterator_base(const data_type &cursor):m_cursor(cursor) {}
                    virtual ~iterator_base() =default;
                    
                    virtual reference operator*() const = 0;
                    pointer operator->() const { return &operator*(); }
                    data_type get() const {return m_cursor;}
                    virtual bool operator==(const self_type &other) const;
                    bool operator!=(const self_type &other) const {return !operator==(other);}
                    self_type& operator=(const self_type &other) {m_cursor=other.m_cursor; return *this;}
                protected:
                    data_type m_cursor;
            };
            
            class preorder_iterator: public iterator_base{
                private:
                    typedef iterator_base base_class;
                public:
                    typedef preorder_iterator self_type;
                    typedef typename base_class::pointer pointer;
                    typedef typename base_class::reference reference;
                    
                    explicit preorder_iterator(node*);
                    preorder_iterator(const self_type &o):base_class(o.m_cursor) {}
                    reference operator*() const override {return m_cursor->back()->data;}
                    self_type& operator++();
                    self_type operator++(int) {auto i=*this;operator++();return *this;}
                    bool operator==(const self_type &other) const override {return base_class::operator==(other)&&m_cursor->back()==other.m_cursor->back();}
                private:
                    using base_class::m_cursor;
            };
            
            class postorder_iterator: public iterator_base{
                private:
                    typedef iterator_base base_class;
                public:
                    typedef postorder_iterator self_type;
                    typedef typename base_class::reference reference;
                    
                    explicit postorder_iterator(node*);
                    postorder_iterator(const self_type &o):base_class(o.m_cursor) {}
                    reference operator*() const override {return m_cursor->back()->data;}
                    self_type& operator++();
                    self_type operator++(int) {auto i=*this;operator++();return *this;}
                    bool operator==(const self_type &other) const override {return base_class::operator==(other)&&m_cursor->back()==other.m_cursor->back();}
                private:
                    using base_class::m_cursor;
            };
            
            class level_iterator: public iterator_base{
                private:
                    typedef iterator_base base_class;
                public:
                    typedef level_iterator self_type;
                    typedef typename base_class::reference reference;
                    
                    explicit level_iterator(node*);
                    level_iterator(const self_type &o):base_class(o.m_cursor) {}
                    reference operator*() const override {return m_cursor->front()->data;}
                    self_type& operator++();
                    self_type operator++(int) {auto i=*this;operator++();return *this;}
                    bool operator==(const self_type &other) const override {return base_class::operator==(other)&&m_cursor->front()==other.m_cursor->front();}
                private:
                    using base_class::m_cursor;
            };
            
        protected:
            // Deep-copy a tree from `src` to `dest`, recursively
            void copy_subtree(node* &dest, const node *src);

            // Return the depth of a binary tree whose root is `root`, recursively
            unsigned int depth(const node *root) const noexcept;

            // Destroy a tree whose root is `root`, recursively
            void delete_subtree(const node *root);
        public:
            // Construct a binary tree with given root(a raw pointer, by default it is nullptr).
            explicit tree_base(node* =nullptr);
            
            // Copy-construtor
            tree_base(const tree_base<T,node> &);
            
            // Move-construtor
            tree_base(tree_base<T,node>&&);
            
            // Destructor
            virtual ~tree_base();
            
            // Insert root to a new node as a parent
            void insert_parent(const T &data);

            // Insert a new node to root as a child
            void insert_child(const T &data);
            
            // Iterator functions
            preorder_iterator preorder_begin() {return preorder_iterator(m_root);}
            
            preorder_iterator preorder_end() {return preorder_iterator(nullptr);}
            
            // There isn't a well-defined in-order traversal of a non-binary tree
            
            postorder_iterator postorder_begin() {return postorder_iterator(m_root);}
            
            postorder_iterator postorder_end() {return postorder_iterator(nullptr);}
            
            level_iterator level_begin() {return level_iterator(m_root);}
            
            level_iterator level_end() {return level_iterator(nullptr);}
            
        protected:
            node *m_root;
    };
    
} // namespace rubbish

#include "tree_base.cc"

#endif // __RUBBISH_TREE_BASE__
