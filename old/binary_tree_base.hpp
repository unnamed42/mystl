#ifndef __RUBBISH_BINARY_TREE_BASE__
#define __RUBBISH_BINARY_TREE_BASE__

#include <deque> // stack, queue 
#include <memory> // std::shared_ptr
#include <initializer_list> // std::initializer_list
#include <bits/stl_iterator_base_types.h> // std::forward_iterator_tag

namespace rubbish{

    typedef enum {LEFT = 0, RIGHT} CHILD;

    namespace helper{
        template <class T> struct binary_tree_node{
            T data;
            binary_tree_node<T> *left,*right;
            
            binary_tree_node():data(T()),left(nullptr),right(nullptr) {}
            explicit binary_tree_node(const T &data_):data(data_),left(nullptr),right(nullptr) {}
            explicit binary_tree_node(T &&data_):data(std::move(data_)),left(nullptr),right(nullptr) {}
        };
    } // namespace helper
    
    // Minimum requirements of type `node`:
    //   A data member variable named `data`;
    //   Two pointer member variables named `left`, `right`, respectively;
    //   `node` can be default-initialized and value-initialized.
    
    template <class T,class Node = helper::binary_tree_node<T> > class binary_tree_base{
        public:
            typedef Node node;
            
            class tree_iterator_base {
                public:
                    typedef T                           value_type;
                    typedef T*                          pointer;
                    typedef T&                          reference;
                    typedef std::forward_iterator_tag   iterator_category;
                    typedef std::ptrdiff_t              difference_type;
                    
                    typedef tree_iterator_base                  self_type;
                    typedef std::shared_ptr<std::deque<node*> > data_type;
                    
                    explicit tree_iterator_base(node *root);
                    explicit tree_iterator_base(const data_type &cursor):m_cursor(cursor) {}
                    tree_iterator_base(const tree_iterator_base &other):m_cursor(other.m_cursor) {}
                    virtual ~tree_iterator_base() = default;
                    virtual reference operator*() const = 0;
                    pointer operator->() const { return &operator*(); }
                    data_type get() const {return m_cursor;}
                    virtual bool operator==(const self_type &other) const;
                    bool operator!=(const self_type &other) const {return !operator==(other);}
                    self_type& operator=(const self_type &other) {m_cursor=other.m_cursor; return *this;}
                protected:
                    data_type m_cursor; 
            };
            
            class preorder_iterator: public tree_iterator_base{
                private:
                    typedef tree_iterator_base base_class;
                public:
                    typedef preorder_iterator self_type;
                    typedef typename tree_iterator_base::reference reference;
                    
                    explicit preorder_iterator(node *root);
                    preorder_iterator(const self_type &other):base_class(other.m_cursor) {}
                    reference operator*() const {return m_cursor->back()->data;}
                    self_type& operator++();
                    self_type operator++(int) {auto i=*this; operator++(); return i;}
                    bool operator==(const self_type &other)  const {return base_class::operator==(other)&&other.m_cursor->back()==m_cursor->back();}
                private:
                    using base_class::m_cursor;
            };
            
            class inorder_iterator: public tree_iterator_base{
                private:
                    typedef tree_iterator_base base_class;
                public:
                    typedef inorder_iterator self_type;
                    typedef typename tree_iterator_base::reference reference;
                    explicit inorder_iterator(node *root);
                    inorder_iterator(const self_type &other):base_class(other.m_cursor) {}
                    reference operator*() const {return m_cursor->back()->data;}
                    self_type& operator++();
                    self_type operator++(int) {auto i=*this; operator++(); return i;}
                    bool operator==(const self_type &other) const {return base_class::operator==(other)&&other.m_cursor->back()==m_cursor->back();}
                private:
                    using base_class::m_cursor;
            };
            
            class postorder_iterator: public tree_iterator_base{
                private:
                    typedef tree_iterator_base base_class;
                public:
                    typedef postorder_iterator self_type;
                    typedef typename tree_iterator_base::reference reference;
                    explicit postorder_iterator(node *root);
                    postorder_iterator(const self_type &other):base_class(other.m_cursor) {}
                    reference operator*() const {return m_cursor->back()->data;}
                    self_type& operator++();
                    self_type operator++(int) {auto i=*this; operator++(); return i;}
                    bool operator==(const self_type &other) const {return base_class::operator==(other)&&other.m_cursor->back()==m_cursor->back();}
                private:
                    using base_class::m_cursor;
            };
            
            class level_iterator: public tree_iterator_base{
                private:
                    typedef tree_iterator_base base_class;
                public:
                    typedef level_iterator self_type;
                    typedef typename tree_iterator_base::reference reference;
                    explicit level_iterator(node *root);
                    level_iterator(const self_type &other):base_class(other.m_cursor) {}
                    reference operator*() const {return m_cursor->front()->data;}
                    self_type& operator++();
                    self_type operator++(int) {auto i=*this; operator++(); return i;}
                    bool operator==(const self_type &other) const {return base_class::operator==(other)&&other.m_cursor->front()==m_cursor->front();}
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
            
            // Data member, root of tree
            node *m_root;
        public:
            // Construct a binary tree with given root(a raw pointer, by default it is nullptr).
            explicit binary_tree_base(node * = nullptr);
            
            // Construct a binary tree with given level-order serialization, `null` means "this node is NULL"
            binary_tree_base(std::initializer_list<T> &&v, const T &null);
            
            // Construct from pre-order and in-order serialization
            binary_tree_base(std::initializer_list<T> &&pre,std::initializer_list<T> &&in);
            
            // Copy-construtor
            binary_tree_base(const binary_tree_base<T,Node>&);
            
            // Move-construtor
            binary_tree_base(binary_tree_base<T,Node>&&);
            
            // Destructor
            virtual ~binary_tree_base();
            
            // Return depth of this tree
            unsigned int depth() const noexcept;
            
            // Reset to an empty tree
            void clear();
            
            // Check emptiness
            bool empty() const noexcept;
            
            // Insert `root` to a new node as `LR` child
            void insert_parent(const T &_data, CHILD LR);
            
            // Insert a new node to `root` as `LR` child
            void insert_child(const T &_data, CHILD LR);
            
            
            // Iterator functions
            preorder_iterator preorder_begin() {return preorder_iterator(m_root);}
            
            preorder_iterator preorder_end() {return preorder_iterator(nullptr);}
            
            inorder_iterator inorder_begin() {return inorder_iterator(m_root);}
            
            inorder_iterator inorder_end() {return inorder_iterator(nullptr);}
            
            postorder_iterator postorder_begin() {return postorder_iterator(m_root);}
            
            postorder_iterator postorder_end() {return postorder_iterator(nullptr);}
            
            level_iterator level_begin() {return level_iterator(m_root);}
            
            level_iterator level_end() {return level_iterator(nullptr);}
            
            // Copy assignment operator
            binary_tree_base<T,Node>& operator=(const binary_tree_base<T,Node>&)=delete;
    };

} // namespace rubbish

// Binary tree base class function implementions
template <class T,class Node> rubbish::binary_tree_base<T,Node>::binary_tree_base(node *root): m_root(root) {}

template <class T,class Node> rubbish::binary_tree_base<T,Node>::binary_tree_base(const binary_tree_base<T,Node> &tree) {
    copy_subtree(m_root,tree.m_root);
}

template <class T,class Node> rubbish::binary_tree_base<T,Node>::binary_tree_base(binary_tree_base<T,Node> &&tree):m_root(tree.m_root) {tree.m_root = nullptr;}

template <class T,class Node> rubbish::binary_tree_base<T,Node>::binary_tree_base(std::initializer_list<T> &&pre,std::initializer_list<T> &&in):m_root(nullptr) {
    if(pre.size()!=in.size()||pre.size()==0||in.size()==0)
        return;
    std::deque<node*> stack;
    auto ipre=pre.begin();      // iterator of `pre`
    m_root = new node(*(ipre++));
    stack.push_back(m_root); 
    auto iin=in.begin();        // iterator of `in`
    for(;ipre!=pre.end();++ipre) {
        node *tmp= stack.back();
        if((tmp->data)!=*iin) {
            tmp->left = new node(*ipre);
            stack.push_back(tmp->left);
        } else {
            while(!stack.empty() && (stack.back()->data)==*iin) {
                tmp=stack.back(); stack.pop_back(); ++iin; 
            }
            // TODO: change the result of difference to some unsigned type
            if((iin-in.begin())< in.size()) {
                tmp->right = new node(*ipre);
                stack.push_back(tmp->right);
            } 
        }  
    }
}

template <class T,class Node> rubbish::binary_tree_base<T,Node>::binary_tree_base(std::initializer_list<T> &&v, const T &null): m_root(nullptr) {
    auto size = v.size();
    auto it = v.begin();
    if(size == 0 || *it == null)
        return;
    m_root = new node(*it);
    std::deque<node*> deque;
    deque.push_back(m_root);
    bool is_left = true;
    node *cur = nullptr;
    ++it;
    for(; it != v.end(); ++it) {
        node *ptr = nullptr;
        if(*it != null) {
            ptr = new node(*it);
            deque.push_back(ptr);
        }
        if(is_left) {
            cur = deque.front();
            deque.pop_front();
            cur->left = ptr;
            is_left = false;
        } else {
            cur->right = ptr;
            is_left = true;
        }
    }
}

template <class T,class Node> rubbish::binary_tree_base<T,Node>::~binary_tree_base() {
    delete_subtree(m_root);
}

template <class T,class Node> void rubbish::binary_tree_base<T,Node>::delete_subtree(const node *root) {
    if(root == nullptr)
        return;
    delete_subtree(root->left);
    delete_subtree(root->right);
    delete root;
}

template <class T,class Node> void rubbish::binary_tree_base<T,Node>::copy_subtree(node *&dest, const node *src) {
    if(src == nullptr){
        dest=nullptr;
        return;
    }
    if(dest != nullptr)
        delete_subtree(dest);
    dest = new node(*src);
    copy_subtree(dest->left, src->left);
    copy_subtree(dest->right, src->right);
}

template <class T,class Node> void rubbish::binary_tree_base<T,Node>::insert_parent(const T &_data, CHILD LR) {
    node *parent = new node(_data);
    if(LR == LEFT)
        parent->left = m_root;
    else
        parent->right = m_root;
    m_root = parent;
}

template <class T,class Node> void rubbish::binary_tree_base<T,Node>::insert_child(const T &_data, CHILD LR) {
    node *child = new node(_data);
    if(m_root == nullptr) {
        m_root = child;
        return;
    }
    if(LR == LEFT) {
        if(m_root->left != nullptr)
            delete_subtree(m_root->left);
        m_root->left = child;
    } else {
        if(m_root->right != nullptr)
            delete_subtree(m_root->right);
        m_root->right = child;
    }
}

template <class T,class Node> unsigned int rubbish::binary_tree_base<T,Node>::depth() const noexcept {
    return depth(m_root);
}

template <class T,class Node> unsigned int rubbish::binary_tree_base<T,Node>::depth(const node *root) const noexcept {
    if(root == nullptr)
        return 0;
    unsigned int left = depth(root->left), right = depth(root->right);
    return 1 + (left > right ? left : right);
}

template <class T,class Node> void rubbish::binary_tree_base<T,Node>::clear() {
    delete_subtree(m_root);
    m_root=nullptr;
}

template <class T,class Node> bool rubbish::binary_tree_base<T,Node>::empty() const noexcept {return m_root==nullptr;}


// Iterator function implementions


template <class T,class Node> rubbish::binary_tree_base<T,Node>::tree_iterator_base::tree_iterator_base(node *root):m_cursor(nullptr) {
    if(root==nullptr)
        return;
    m_cursor=std::make_shared<std::deque<node*> >(std::deque<node*>());
}

// Two iterators are equal iif they are both
// empty or their "next node"-s are equal
template <class T,class Node> bool rubbish::binary_tree_base<T,Node>::tree_iterator_base::operator==(const self_type &other) const {
    if(other.m_cursor==m_cursor)//==nullptr
        return true;
    return m_cursor!=nullptr&&other.m_cursor!=nullptr;
    // Further checks are made by derived classes' overloaded operators.
}

template <class T,class Node> rubbish::binary_tree_base<T,Node>::preorder_iterator::preorder_iterator(node *root):base_class(root) {
    if(m_cursor!=nullptr)
        m_cursor->push_back(root);
}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::preorder_iterator::self_type& rubbish::binary_tree_base<T,Node>::preorder_iterator::operator++(){
    if(m_cursor==nullptr||m_cursor->empty()){
        m_cursor.reset();
        return *this;
    }
    auto tmp=m_cursor->back();
    m_cursor->pop_back();
    if(tmp->right != nullptr)
        m_cursor->push_back(tmp->right);
    if(tmp->left != nullptr)
        m_cursor->push_back(tmp->left);
    // Double check if the iteration comes to an end
    if(m_cursor->empty())
        m_cursor.reset();
    return *this;
}

template <class T,class Node> rubbish::binary_tree_base<T,Node>::inorder_iterator::inorder_iterator(node *root):base_class(root) {
    if(m_cursor==nullptr)
        return;
    while(root!=nullptr){
        m_cursor->push_back(root);
        root=root->left;
    }
}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::inorder_iterator::self_type& rubbish::binary_tree_base<T,Node>::inorder_iterator::operator++(){
    if(m_cursor==nullptr||m_cursor->empty()){
        m_cursor.reset();
        return *this;
    }
    auto ptr = m_cursor->back()->right;
    m_cursor->pop_back();
    while(ptr != nullptr) {
        m_cursor->push_back(ptr);
        ptr = ptr->left;
    }
    // Double check if the iteration comes to an end
    if(m_cursor->empty())
        m_cursor.reset();
    return *this;
}

template <class T,class Node> rubbish::binary_tree_base<T,Node>::postorder_iterator::postorder_iterator(node *root):base_class(root) {
    if(m_cursor==nullptr)
        return;
    for(;;) {
        m_cursor->push_back(root);
        if(root->left != nullptr)
            root = root->left;
        else if(root->right != nullptr)
            root = root->right;
        else
            break;
    }
}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::postorder_iterator::self_type& rubbish::binary_tree_base<T,Node>::postorder_iterator::operator++(){
    if(m_cursor==nullptr||m_cursor->empty()){
        m_cursor.reset();
        return *this;
    }
    auto ptr=m_cursor->back();m_cursor->pop_back();
    if(m_cursor->empty()){
        m_cursor.reset();
        return *this;
    }
    auto stack_top = m_cursor->back(), tmp = stack_top->right;
    if(ptr == stack_top->left && tmp != nullptr) {
        for(;;) {
            m_cursor->push_back(tmp);
            if(tmp->left != nullptr)
                tmp = tmp->left;
            else if(tmp->right != nullptr)
                tmp = tmp->right;
            else 
                break;
        }
    }
    // Double check if the iteration comes to an end
    if(m_cursor->empty())
        m_cursor.reset();
    return *this;
}

template <class T,class Node> rubbish::binary_tree_base<T,Node>::level_iterator::level_iterator(node *root):base_class(root) {
    if(m_cursor!=nullptr)
        m_cursor->push_back(root);
}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::level_iterator::self_type& rubbish::binary_tree_base<T,Node>::level_iterator::operator++() {
    if(m_cursor==nullptr||m_cursor->empty()){
        m_cursor.reset();
        return *this;
    }
    auto ptr=m_cursor->front();m_cursor->pop_front();
    if(ptr->left != nullptr)
        m_cursor->push_back(ptr->left);
    if(ptr->right != nullptr)
        m_cursor->push_back(ptr->right);
    // Double check if the iteration comes to an end
    if(m_cursor->empty())
        m_cursor.reset();
    return *this;
}


using rubbish::CHILD::LEFT;
using rubbish::CHILD::RIGHT;

#endif // __RUBBISH_BINARY_TREE_BASE__
