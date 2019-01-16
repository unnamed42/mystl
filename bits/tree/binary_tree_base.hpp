#ifndef __RUBBISH_BINARY_TREE_BASE__
#define __RUBBISH_BINARY_TREE_BASE__

#include <deque> // used as queue in level order iterator
#include <initializer_list> // std::initializer_list
#include "../iterator.hpp" // base class of iterators

namespace rubbish{

    constexpr bool _left_child = true;
    constexpr bool _right_child = false;

    namespace helper{
        template <class T> struct binary_tree_node{
            typedef binary_tree_node<T> self_type;
            
            T data;
            self_type *left,*right;
            self_type *parent;
            
            constexpr binary_tree_node():data(),left(nullptr),right(nullptr),parent(nullptr) {}
            explicit binary_tree_node(const T &_data):data(_data),left(nullptr),right(nullptr),parent(nullptr) {}
            explicit binary_tree_node(T &&_data):data(std::move(_data)),left(nullptr),right(nullptr),parent(nullptr) {}
            binary_tree_node(const self_type &o):data(o.data),left(nullptr),right(nullptr),parent(nullptr) {}
            binary_tree_node(self_type &&o):data(std::move(o.data)),left(nullptr),right(nullptr),parent(nullptr) {}
            
            // Assignment operators to avoid warning [-Weffc++]
            self_type& operator=(const self_type &o) {data=o.data; left=right=parent=nullptr; return *this;}
            self_type& operator=(self_type &&o) {data=std::move(o.data); left=right=parent=nullptr; return *this;}
        };
        
        // template <class Node> inline Node* preorder_first(Node *root); // This is trival, just return root
        template <class Node> inline Node* inorder_first(Node*);
        template <class Node> inline Node* postorder_first(Node*);
        template <class Node> inline Node* preorder_final(Node*);
        template <class Node> inline Node* inorder_final(Node*);
        // template <class Node> inline Node* postorder_final(Node *root); // This is trival, just return root
    } // namespace helper
    
    // Minimum requirements of type `Node`:
    //   A data member variable named `data`;
    //   Three pointer member variables named `left`, `right`, `parent` respectively;
    //   `Node` can be default-initialized and value-initialized.
    
    template <class T,class Node = helper::binary_tree_node<T> > class binary_tree_base{
        public:
            typedef Node node;
            
            class tree_iterator_base:public rubbish::iterator<std::bidirectional_iterator_tag,T> {
                private:
                    typedef rubbish::iterator<std::bidirectional_iterator_tag,T> base_class;
                public:
                    typedef typename base_class::reference reference;
                    typedef typename base_class::pointer   pointer;
                    
                    typedef tree_iterator_base self_type;
                    typedef node*              data_type;
                    
                    explicit tree_iterator_base(const data_type &cursor):m_cursor(cursor) {}
                    tree_iterator_base(const tree_iterator_base &other):m_cursor(other.m_cursor) {}
                    virtual ~tree_iterator_base() {}
                    
                    reference operator*() const {return m_cursor->data;}
                    pointer operator->() const { return &operator*(); }
                    data_type get() const {return m_cursor;}
                    bool operator==(const self_type &other) const {return m_cursor==other.m_cursor;}
                    bool operator!=(const self_type &other) const {return !operator==(other);}
                    self_type& operator=(const tree_iterator_base &other) {m_cursor=other.m_cursor; return *this;}
                protected:
                    data_type m_cursor;
            };
            
            #define BTREE_ITERATOR_EXPANSION(kind) class kind##_iterator: public tree_iterator_base{\
                private:\
                    typedef tree_iterator_base base_class;\
                public:\
                    typedef kind##_iterator self_type;\
                    \
                    typedef typename base_class::reference reference;\
                    typedef typename base_class::data_type data_type;\
                    \
                    using base_class::base_class;\
                    \
                    self_type& operator++();\
                    self_type operator++(int) {auto i=*this; operator++(); return i;}\
                    self_type& operator--();\
                    self_type operator--(int) {auto i=*this;operator--();return i;}\
                private:\
                    using base_class::m_cursor;\
            }
            
            BTREE_ITERATOR_EXPANSION(preorder);
            BTREE_ITERATOR_EXPANSION(inorder);
            BTREE_ITERATOR_EXPANSION(postorder);
            
            #undef BTREE_ITERATOR_EXPANSION
            
            
            #define BTREE_RITERATOR_EXPANSION(kind) class reverse_##kind##_iterator:public rubbish::reverse_iterator<kind##_iterator>{\
                private:\
                    typedef rubbish::reverse_iterator<kind##_iterator> base_class;\
                public:\
                    typedef typename base_class::reference reference;\
                    typedef typename base_class::pointer   pointer;\
                    \
                    using base_class::base_class;\
                    \
                    reference operator*() const {return *m_iter;}\
                    pointer operator->() const {return &operator*();}\
                private:\
                    using base_class::m_iter;\
            }
            
            BTREE_RITERATOR_EXPANSION(preorder);
            BTREE_RITERATOR_EXPANSION(inorder);
            BTREE_RITERATOR_EXPANSION(postorder);
            
            #undef BTREE_RITERATOR_EXPANSION
            
            // This kind of iterator is totally different from the above three kinds,
            // so do not inherit from tree_iterator_base here
            class level_iterator:public rubbish::iterator<std::forward_iterator_tag,T> {
                private:
                    typedef rubbish::iterator<std::forward_iterator_tag,T> base_class;
                public:
                    typedef typename base_class::reference reference;
                    typedef typename base_class::pointer   pointer;
                    
                    typedef level_iterator self_type;
                    typedef node*          data_type;
                    
                    explicit level_iterator(const data_type &cursor):m_cursor() {
                        if(cursor!=nullptr)
                            m_cursor.push_back(cursor);
                    }
                    level_iterator(const level_iterator &other):m_cursor(other.m_cursor) {}
                    level_iterator(level_iterator &&other):m_cursor(std::move(other.m_cursor)) {}
                    
                    reference operator*() const {return const_cast<reference>(m_cursor.front()->data);}
                    pointer operator->() const { return &operator*(); }
                    const std::deque<data_type>& get() const {return m_cursor;}
                    self_type& operator++();
                    self_type operator++(int) {auto i=*this; operator++(); return i;}
                    
                    bool operator==(const level_iterator &other) const {return (m_cursor.empty()&&other.m_cursor.empty()) || (!m_cursor.empty()&&!other.m_cursor.empty() && m_cursor.front()==other.m_cursor.front());}
                    bool operator!=(const level_iterator &other) const {return !operator==(other);}
                    
                    self_type& operator=(const level_iterator &other) {m_cursor=const_cast<decltype(m_cursor)&>(other.get()); return *this;}
                    self_type& operator=(level_iterator &&other) {m_cursor=std::move(const_cast<decltype(m_cursor)&>(other.get())); return *this;}
                private:
                    std::deque<data_type> m_cursor;
            };
            
            typedef rubbish::const_iterator<preorder_iterator>  const_preorder_iterator;
            typedef rubbish::const_iterator<inorder_iterator>   const_inorder_iterator;
            typedef rubbish::const_iterator<postorder_iterator> const_postorder_iterator;
            typedef rubbish::const_iterator<reverse_preorder_iterator>  const_reverse_preorder_iterator;
            typedef rubbish::const_iterator<reverse_inorder_iterator>   const_reverse_inorder_iterator;
            typedef rubbish::const_iterator<reverse_postorder_iterator> const_reverse_postorder_iterator;
            
            typedef rubbish::const_iterator<level_iterator>     const_level_iterator;
            
            typedef binary_tree_base<T,Node> self_type;
            
        protected:
            // Deep-copy a tree from `src` to `dest`, recursively
            static void copy_subtree(node* &dest, const node *src);
            
            // Return the depth of a binary tree whose root is `root`, recursive solution
            static unsigned int depth(const node *root);
            
            // Destroy a tree whose root is `root`, recursively
            static void delete_subtree(const node *root);
            
            // Data member, root of tree
            node *m_root;
        public:
            // Default initialization
            constexpr binary_tree_base();
            
            // Construct a binary tree with given root(a raw pointer).
            explicit binary_tree_base(node*);
            
            // Construct a binary tree with given level-order serialization, `null` means "this node is NULL"
            binary_tree_base(std::initializer_list<T> &&v, const T &null);
            
            // Construct from pre-order and in-order serialization
            binary_tree_base(std::initializer_list<T> &&pre,std::initializer_list<T> &&in);
            
            // Copy-construtor
            binary_tree_base(const self_type&);
            
            // Move-construtor
            binary_tree_base(self_type&&);
            
            // Destructor
            virtual ~binary_tree_base();
            
            // Return depth of this tree
            unsigned int depth() const;
            
            // Reset to an empty tree
            void clear();
            
            // Check emptiness
            bool empty() const noexcept;
            
            // Insert `root` to a new node as `LR` child
            template <class U> void insert_parent(U &&, bool LR);
            
            // Insert a new node to `root` as `LR` child
            template <class U> void insert_child(U&&, bool LR);
            
            // Iterator functions
            preorder_iterator preorder_begin();
            preorder_iterator preorder_end();
            inorder_iterator inorder_begin();
            inorder_iterator inorder_end();
            postorder_iterator postorder_begin();
            postorder_iterator postorder_end();
            level_iterator level_begin();
            level_iterator level_end();
            reverse_preorder_iterator preorder_rbegin();
            reverse_preorder_iterator preorder_rend();
            reverse_inorder_iterator inorder_rbegin();
            reverse_inorder_iterator inorder_rend();
            reverse_postorder_iterator postorder_rbegin();
            reverse_postorder_iterator postorder_rend();
            const_preorder_iterator preorder_cbegin() const;
            const_preorder_iterator preorder_cend() const;
            const_inorder_iterator inorder_cbegin() const;
            const_inorder_iterator inorder_cend() const;
            const_postorder_iterator postorder_cbegin() const;
            const_postorder_iterator postorder_cend() const;
            const_reverse_preorder_iterator preorder_crbegin() const;
            const_reverse_preorder_iterator preorder_crend() const;
            const_reverse_inorder_iterator inorder_crbegin() const;
            const_reverse_inorder_iterator inorder_crend() const;
            const_reverse_postorder_iterator postorder_crbegin() const;
            const_reverse_postorder_iterator postorder_crend() const;
            const_level_iterator level_cbegin() const;
            const_level_iterator level_cend() const;
            
            // Assignment operator to avoid warning [-Weffc++]
            self_type& operator=(const self_type&);
            self_type& operator=(self_type&&);
    };
} // namespace rubbish

#include "binary_tree_base.cc"

#endif // __RUBBISH_BINARY_TREE_BASE__
