// Iterator helper functions
template <class Node> inline Node* rubbish::helper::inorder_first(Node *root){
    if(root==nullptr)
        return nullptr;
    while(root->left!=nullptr)
        root=root->left;
    return root;
}

template <class Node> inline Node* rubbish::helper::postorder_first(Node *root){
    if(root==nullptr)
        return nullptr;
    for(;;) {
        if(root->left!=nullptr)
            root=root->left;
        else if(root->right!=nullptr)
            root=root->right;
        else
            return root;
    }
}

template <class Node> inline Node* rubbish::helper::preorder_final(Node *root){
    if(root==nullptr)
        return nullptr;
    for(;;){
        if(root->right!=nullptr)
            root=root->right;
        else if(root->left!=nullptr)
            root=root->left;
        else
            return root;
    }
}

template <class Node> inline Node* rubbish::helper::inorder_final(Node *root){
    if(root==nullptr)
        return nullptr;
    while(root->right!=nullptr)
        root=root->right;
    return root;
}

// Binary tree base class function implementions
template <class T,class Node> constexpr rubbish::binary_tree_base<T,Node>::binary_tree_base():m_root(nullptr) {}

template <class T,class Node> rubbish::binary_tree_base<T,Node>::binary_tree_base(node *root): m_root(root) {}

template <class T,class Node> rubbish::binary_tree_base<T,Node>::binary_tree_base(const self_type &tree) {copy_subtree(m_root,tree.m_root);}

template <class T,class Node> rubbish::binary_tree_base<T,Node>::binary_tree_base(self_type &&tree):m_root(tree.m_root) {tree.m_root = nullptr;}

template <class T,class Node> rubbish::binary_tree_base<T,Node>::binary_tree_base(std::initializer_list<T> &&pre,std::initializer_list<T> &&in):m_root(nullptr) {
    // Algorithm from https://leetcode.com/discuss/28271/my-o-n-19ms-solution-without-recusion-hope-help-you
    if(pre.size()==0||in.size()==0||pre.size()!=in.size())
        return;
    std::deque<node*> stack;
    auto ipre=pre.begin();      // iterator of `pre`
    m_root = new node(*(ipre++));
    stack.push_back(m_root); 
    auto iin=in.begin();        // iterator of `in`
    for(;ipre!=pre.end();++ipre) {
        // Keep pushing the nodes from the preorder into a stack,
        // and keep making the tree by adding nodes to the left of the previous node
        // until the top of the stack matches the inorder.
        node *tmp= stack.back();
        if((tmp->data)!=*iin) {
            tmp->left = new node(*ipre);
            tmp->left->parent=tmp;
            stack.push_back(tmp->left);
        } else {
            // At this point, pop the top of the stack until the top does not equal inorder 
            while(!stack.empty() && (stack.back()->data)==*iin) {
                tmp=stack.back(); stack.pop_back(); 
                ++iin; 
            }
            if((iin-in.begin())< long(in.size())) {
                tmp->right = new node(*ipre);
                tmp->right->parent=tmp;
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
    std::deque<node*> queue;
    m_root = new node(*(it++));
    queue.push_back(m_root);
    bool is_left = true;
    node *cur = nullptr;
    for(; it != v.end(); ++it) {
        node *ptr = nullptr;
        if(*it != null) {
            ptr = new node(*it);
            queue.push_back(ptr);
        }
        if(is_left) {
            cur = queue.front();
            queue.pop_front();
            cur->left = ptr;
            if(ptr!=nullptr)
                ptr->parent=cur;
            is_left = false;
        } else {
            cur->right = ptr;
            if(ptr!=nullptr)
                ptr->parent=cur;
            is_left = true;
        }
    }
}

template <class T,class Node> rubbish::binary_tree_base<T,Node>::~binary_tree_base() {delete_subtree(m_root);}

template <class T,class Node> void rubbish::binary_tree_base<T,Node>::delete_subtree(const node *root) {
    if(root == nullptr)
        return;
    delete_subtree(root->left);
    delete_subtree(root->right);
    delete root;
}

template <class T,class Node> void rubbish::binary_tree_base<T,Node>::copy_subtree(node* &dest, const node *src) {
    if(src == nullptr){
        dest=nullptr;
        return;
    }
    if(dest != nullptr)
        delete_subtree(dest);
    
    dest = new node(*src);
    // The pointers in newed node must all be nullptr, otherwise you should assign manually
    //dest->left = dest->right = dest->parent = nullptr;
    
    copy_subtree(dest->left, src->left);
    copy_subtree(dest->right, src->right);
    if(dest->left!=nullptr)
        dest->left->parent=dest;
    if(dest->right!=nullptr)
        dest->right->parent=dest;
}

template <class T,class Node> template <class U> void rubbish::binary_tree_base<T,Node>::insert_parent(U &&data, bool LR) {
    node *parent = new node(std::forward<U>(data));
    if(LR == _left_child)
        parent->left = m_root;
    else
        parent->right = m_root;
    m_root->parent=parent;
    m_root = parent;
}

template <class T,class Node> template <class U> void rubbish::binary_tree_base<T,Node>::insert_child(U &&data, bool LR) {
    node *child = new node(std::forward<U>(data));
    if(m_root == nullptr) {
        m_root = child;
        return;
    }
    child->parent=m_root;
    if(LR == _left_child) {
        if(m_root->left != nullptr)
            delete_subtree(m_root->left);
        m_root->left = child;
    } else {
        if(m_root->right != nullptr)
            delete_subtree(m_root->right);
        m_root->right = child;
    }
}

template <class T,class Node> unsigned int rubbish::binary_tree_base<T,Node>::depth() const {return depth(m_root);}

template <class T,class Node> unsigned int rubbish::binary_tree_base<T,Node>::depth(const node *root) {
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

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::self_type& rubbish::binary_tree_base<T,Node>::operator=(const self_type &o) {
    this->~binary_tree_base();
    m_root=nullptr;
    copy_subtree(m_root,o.m_root);
    return *this;
}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::self_type& rubbish::binary_tree_base<T,Node>::operator=(self_type &&o) {
    this->~binary_tree_base();
    m_root=o.m_root;
    o.m_root=nullptr;
    return *this;
}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::preorder_iterator rubbish::binary_tree_base<T,Node>::preorder_begin() {return preorder_iterator(m_root);}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::preorder_iterator rubbish::binary_tree_base<T,Node>::preorder_end() {return preorder_iterator(nullptr);}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::inorder_iterator rubbish::binary_tree_base<T,Node>::inorder_begin() {return inorder_iterator(helper::inorder_first(m_root));}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::inorder_iterator rubbish::binary_tree_base<T,Node>::inorder_end() {return inorder_iterator(nullptr);}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::postorder_iterator rubbish::binary_tree_base<T,Node>::postorder_begin() {return postorder_iterator(helper::postorder_first(m_root));}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::postorder_iterator rubbish::binary_tree_base<T,Node>::postorder_end() {return postorder_iterator(nullptr);}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::reverse_preorder_iterator rubbish::binary_tree_base<T,Node>::preorder_rbegin() {return reverse_preorder_iterator(preorder_iterator(helper::preorder_final(m_root)));}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::reverse_preorder_iterator rubbish::binary_tree_base<T,Node>::preorder_rend() {return reverse_preorder_iterator(preorder_end());}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::reverse_inorder_iterator rubbish::binary_tree_base<T,Node>::inorder_rbegin() {return reverse_inorder_iterator(inorder_iterator(helper::inorder_final(m_root)));}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::reverse_inorder_iterator rubbish::binary_tree_base<T,Node>::inorder_rend() {return reverse_inorder_iterator(inorder_end());}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::reverse_postorder_iterator rubbish::binary_tree_base<T,Node>::postorder_rbegin() {return reverse_postorder_iterator(postorder_iterator(m_root));}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::reverse_postorder_iterator rubbish::binary_tree_base<T,Node>::postorder_rend() {return reverse_postorder_iterator(postorder_end());}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::level_iterator rubbish::binary_tree_base<T,Node>::level_begin() {return level_iterator(m_root);}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::level_iterator rubbish::binary_tree_base<T,Node>::level_end() {return level_iterator(nullptr);}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::const_preorder_iterator rubbish::binary_tree_base<T,Node>::preorder_cbegin() const {return const_preorder_iterator(const_cast<self_type*>(this)->preorder_begin());}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::const_preorder_iterator rubbish::binary_tree_base<T,Node>::preorder_cend() const {return const_preorder_iterator(const_cast<self_type*>(this)->preorder_end());}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::const_inorder_iterator rubbish::binary_tree_base<T,Node>::inorder_cbegin() const {return const_inorder_iterator(const_cast<self_type*>(this)->inorder_begin());}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::const_inorder_iterator rubbish::binary_tree_base<T,Node>::inorder_cend() const {return const_inorder_iterator(const_cast<self_type*>(this)->inorder_end());}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::const_postorder_iterator rubbish::binary_tree_base<T,Node>::postorder_cbegin() const {return const_postorder_iterator(const_cast<self_type*>(this)->postorder_begin());}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::const_postorder_iterator rubbish::binary_tree_base<T,Node>::postorder_cend() const {return const_postorder_iterator(const_cast<self_type*>(this)->postorder_end());}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::const_level_iterator rubbish::binary_tree_base<T,Node>::level_cbegin() const {return const_level_iterator(const_cast<self_type*>(this)->level_begin());}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::const_level_iterator rubbish::binary_tree_base<T,Node>::level_cend() const {return const_level_iterator(const_cast<self_type*>(this)->level_end());}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::const_reverse_preorder_iterator rubbish::binary_tree_base<T,Node>::preorder_crbegin() const {return const_reverse_preorder_iterator(const_cast<self_type*>(this)->preorder_rbegin());}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::const_reverse_preorder_iterator rubbish::binary_tree_base<T,Node>::preorder_crend() const {return const_reverse_preorder_iterator(const_cast<self_type*>(this)->preorder_rend());}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::const_reverse_inorder_iterator rubbish::binary_tree_base<T,Node>::inorder_crbegin() const {return const_reverse_inorder_iterator(const_cast<self_type*>(this)->inorder_rbegin());}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::const_reverse_inorder_iterator rubbish::binary_tree_base<T,Node>::inorder_crend() const {return const_reverse_inorder_iterator(const_cast<self_type*>(this)->inorder_rend());}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::const_reverse_postorder_iterator rubbish::binary_tree_base<T,Node>::postorder_crbegin() const {return const_reverse_postorder_iterator(const_cast<self_type*>(this)->postorder_rbegin());}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::const_reverse_postorder_iterator rubbish::binary_tree_base<T,Node>::postorder_crend() const {return const_reverse_postorder_iterator(const_cast<self_type*>(this)->postorder_rend());}


// Iterator increment and decrement functions
template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::preorder_iterator::self_type& rubbish::binary_tree_base<T,Node>::preorder_iterator::operator++(){
    if(m_cursor==nullptr)
        return *this;
    if(m_cursor->left!=nullptr)
        m_cursor=m_cursor->left;
    else if(m_cursor->right!=nullptr)
        m_cursor=m_cursor->right;
    else {
        auto parent=m_cursor->parent;
        while(parent!=nullptr) {
            // If right-subtree is done or empty, then the whole tree is done, traceback.
            if(parent->right==nullptr || m_cursor==parent->right) {
                m_cursor=parent;
                parent=parent->parent;
                continue;
            }
            // If left-subtree is done, the next will be right-subtree.
            if(m_cursor==parent->left) {
                m_cursor=parent->right;
                return *this;
            }
        }
        // Whole tree is done.
        m_cursor=nullptr;
    }
    return *this;
}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::preorder_iterator::self_type& rubbish::binary_tree_base<T,Node>::preorder_iterator::operator--(){
    // When implementing this, just keep in mind that this serialization
    // should be the serialization of "right-left-self" traversal
    if(m_cursor==nullptr)
        return *this;
    auto parent=m_cursor->parent;
    if(parent!=nullptr){
        if(parent->right==m_cursor && parent->left!=nullptr)
            m_cursor=helper::preorder_final(parent->left);
        else
            m_cursor=parent;
    } else 
        m_cursor=nullptr;
    return *this;
}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::inorder_iterator::self_type& rubbish::binary_tree_base<T,Node>::inorder_iterator::operator++(){
    if(m_cursor==nullptr)
        return *this;
    // When we take a tree root, we can believe that its left-subtree is done.
    if(m_cursor->right!=nullptr)
        m_cursor=helper::inorder_first(m_cursor->right);
    else {
        // If one tree's right-subtree is also done,
        // then traceback until it's "come from left".
        auto parent=m_cursor->parent;
        while(parent!=nullptr) {
            if(m_cursor==parent->left) {
                m_cursor=parent;
                return *this;
            }
            m_cursor=parent;
            parent=parent->parent;
        }
        m_cursor=nullptr;
    }
    return *this;
}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::inorder_iterator::self_type& rubbish::binary_tree_base<T,Node>::inorder_iterator::operator--(){
    // When implementing this, just keep in mind that this serialization
    // should be serialization of "right-self-left" traversal.
    if(m_cursor==nullptr)
        return *this;
    if(m_cursor->left!=nullptr)
        m_cursor=helper::inorder_final(m_cursor->left);
    else {
        auto parent=m_cursor->parent;
        while(parent!=nullptr){
            if(m_cursor==parent->right) {
                m_cursor=parent;
                return *this;
            }
            m_cursor=parent;
            parent=parent->parent;
        }
        m_cursor=nullptr;
    }
    return *this;
}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::postorder_iterator::self_type& rubbish::binary_tree_base<T,Node>::postorder_iterator::operator++(){
    if(m_cursor==nullptr)
        return *this;
    // When we take a node, we can believe that all of its subtrees are done
    auto parent=m_cursor->parent;
    if(parent!=nullptr) {
        // If parent's left-subtree is done and right-subtree is undone, go to right
        if(m_cursor==parent->left && parent->right!=nullptr)
            m_cursor=helper::postorder_first(parent->right);
        else
            // Else, all done, traceback
            // In this branch, m_cursor==parent->right
            m_cursor=parent;
    } else
        // Whole tree is done
        m_cursor=nullptr;
    return *this;
}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::postorder_iterator::self_type& rubbish::binary_tree_base<T,Node>::postorder_iterator::operator--(){
    // When implementing this, just keep in mind that this serialization
    // should be the serialization of "self-right-left" traversal.
    if(m_cursor==nullptr)
        return *this;
    if(m_cursor->right!=nullptr)
        m_cursor=m_cursor->right;
    else if(m_cursor->left!=nullptr)
        m_cursor=m_cursor->left;
    else {
        auto parent=m_cursor->parent;
        while(parent!=nullptr) {
            if(parent->left==nullptr || m_cursor==parent->left) {
                m_cursor=parent;
                parent=parent->parent;
                continue;
            }
            if(m_cursor==parent->right) {
                m_cursor=parent->left;
                return *this;
            }
        }
        m_cursor=nullptr;
    }
    return *this;
}

template <class T,class Node> typename rubbish::binary_tree_base<T,Node>::level_iterator::self_type& rubbish::binary_tree_base<T,Node>::level_iterator::operator++() {
    if(m_cursor.empty())
        return *this;
    auto ptr=m_cursor.front();
    m_cursor.pop_front();
    if(ptr->left != nullptr)
        m_cursor.push_back(ptr->left);
    if(ptr->right != nullptr)
        m_cursor.push_back(ptr->right);
    return *this;
}
