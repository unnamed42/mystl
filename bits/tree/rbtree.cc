template <class Node> void rubbish::helper::rbtree_left_rotate(Node *&root, Node *&ptr) {
    auto right = ptr->right;
    ptr->right = right->left;

    if (ptr->right != nullptr)
        ptr->right->parent = ptr;

    right->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = right;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = right;
    else
        ptr->parent->right = right;

    right->left = ptr;
    ptr->parent = right;
}

template <class Node> void rubbish::helper::rbtree_right_rotate(Node *&root, Node *&ptr) {
    auto left = ptr->left;
    ptr->left = left->right;

    if (ptr->left != nullptr)
        ptr->left->parent = ptr;

    left->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = left;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left;
    else
        ptr->parent->right = left;

    left->right = ptr;
    ptr->parent = left;
}

template <class Node> void rubbish::helper::rbtree_insertion_fix(Node *&root, Node *&ptr) {
    Node *parent = nullptr;
    Node *grandpa = nullptr;

    while ((ptr != root) && (ptr->color != _rb_black) &&
            (ptr->parent->color == _rb_red)) {
        parent = ptr->parent;
        grandpa = ptr->parent->parent;

        //  Case : A
        //  Parent of ptr is left child of Grand-parent of ptr
        if (parent == grandpa->left) {
            Node *uncle = grandpa->right;
            // Case : 1
            // The uncle of ptr is also red, only Recoloring required
            if (uncle != nullptr && uncle->color == _rb_red) {
                grandpa->color = _rb_red;
                parent->color = _rb_black;
                uncle->color = _rb_black;
                ptr = grandpa;
            } else {
                // Case : 2
                // ptr is right child of its parent, Left-rotation required
                if (ptr == parent->right) {
                    rbtree_left_rotate(root, parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                // Case : 3
                // ptr is left child of its parent, Right-rotation required
                rbtree_right_rotate(root, grandpa);
                auto tmp=parent->color;
                parent->color=grandpa->color;
                grandpa->color=tmp;
                ptr = parent;
            }
        } else {
            // Case : B
            // Parent of ptr is right child of Grand-parent of ptr
            Node *uncle = grandpa->left;

            //  Case : 1
            //  The uncle of ptr is also red, only Recoloring required
            if ((uncle != nullptr) && (uncle->color == _rb_red)) {
                grandpa->color = _rb_red;
                parent->color = _rb_black;
                uncle->color = _rb_black;
                ptr = grandpa;
            } else {
                // Case : 2
                // ptr is left child of its parent, Right-rotation required
                if (ptr == parent->left) {
                    rbtree_right_rotate(root, parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                // Case : 3
                // ptr is right child of its parent, Left-rotation required
                rbtree_left_rotate(root, grandpa);
                auto tmp=parent->color;
                parent->color=grandpa->color;
                grandpa->color=tmp;
                ptr = parent;
            }
        }
    }
    root->color = _rb_black;
}

template <class T,class Node> void rubbish::rbtree<T,Node>::rbtree_delete(Node *&root,Node *ptr){
    auto y=((ptr->left == nullptr) || (ptr->right == nullptr)) ? ptr : (++iterator(ptr)).get();
    auto x=(y->left == nullptr) ? y->right : y->left;
    if (root == (x->parent = y->parent)) /* assignment of y->p to x->p is intentional */
        root->left=x;
    else {
        if (y == y->parent->left) 
            y->parent->left=x;
        else
            y->parent->right=x;
    }
     /* y should not be nullptr in this case */
    if (y != ptr) {
        /* y is the node to splice out and x is its child */
        if (!(y->color)) // y is not color
            rbtree_deletion_fix(root,x);
        y->left=ptr->left;
        y->right=ptr->right;
        y->parent=ptr->parent;
        y->color=ptr->color;
        ptr->left->parent=ptr->right->parent=y;
        if (ptr == ptr->parent->left)
            ptr->parent->left=y;
        else
            ptr->parent->right=y;
        delete ptr;
    } else {
        if (!(y->color)) // y is not color
            rbtree_deletion_fix(root,x);
        delete y;
    }
}

template <class Node> void rubbish::helper::rbtree_deletion_fix(Node *&root,Node *ptr){
    Node *nroot=root->left,*w=nullptr;

    while( (!ptr->color) && (nroot != ptr)) {
        if (ptr == ptr->parent->left) {
            w=ptr->parent->right;
            if (w->color) {
                w->color=_rb_black;
                ptr->parent->color=_rb_red;
                rbtree_left_rotate(root,ptr->parent);
                w=ptr->parent->right;
            }
            if ( (!w->right->color) && (!w->left->color) ) { 
                w->color=_rb_red;
                ptr=ptr->parent;
            } else {
                if (!w->right->color) {
                    w->left->color=_rb_black;
                    w->color=_rb_red;
                    rbtree_right_rotate(root,w);
                    w=ptr->parent->right;
                }
                w->color=ptr->parent->color;
                ptr->parent->color=_rb_black;
                w->right->color=_rb_black;
                rbtree_left_rotate(root,ptr->parent);
                ptr=nroot; /* this is to exit while loop */
            }
        } else { /* the code below is has left and right switched from above */
            w=ptr->parent->left;
            if (w->color) {
                w->color=_rb_black;
                ptr->parent->color=_rb_red;
                rbtree_right_rotate(root,ptr->parent);
                w=ptr->parent->left;
            }
            if ( (!w->right->color) && (!w->left->color) ) { 
                w->color=_rb_red;
                ptr=ptr->parent;
            } else {
                if (!w->left->color) {
                    w->right->color=_rb_black;
                    w->color=_rb_red;
                    rbtree_left_rotate(root,w);
                    w=ptr->parent->left;
                }
                w->color=ptr->parent->color;
                ptr->parent->color=_rb_black;
                w->left->color=_rb_black;
                rbtree_right_rotate(root,ptr->parent);
                ptr=nroot; /* this is to exit while loop */
            }
        }
    }
    ptr->color=_rb_black;
}

template <class T,class Node> constexpr rubbish::rbtree<T, Node>::rbtree():base_class(){}

template <class T,class Node> rubbish::rbtree<T, Node>::rbtree(std::initializer_list<T> &&l):base_class(){
    for(auto &&i:l)
        insert(std::move(i));
}

template <class T,class Node> rubbish::rbtree<T, Node>::rbtree(const self_type &o):base_class(o){}

template <class T,class Node> rubbish::rbtree<T, Node>::rbtree(self_type &&o):base_class(std::move(o)){}

template <class T,class Node> template <class U> typename rubbish::rbtree<T,Node>::node* rubbish::rbtree<T,Node>::insert(node* &root,U &&data) {
    if(root==nullptr)
        return root=new node(std::forward<U>(data));
    if (root->data < data){
        auto ret=insert(root->right,std::forward<U>(data));
        root->right->parent = root;
        return ret;
    } else if (root->data == data) {
        return root;
    } else {
        auto ret = insert(root->left,std::forward<U>(data));
        root->left->parent = root;
        return ret;
    }
}

template <class T,class Node> template <class U> typename rubbish::rbtree<T,Node>::iterator rubbish::rbtree<T,Node>::insert(U &&data) {
    auto ptr = insert(m_root,std::forward<U>(data));
    helper::rbtree_insertion_fix(m_root, ptr);
    return iterator(ptr);
}

template <class T,class Node> template <class U> void rubbish::rbtree<T,Node>::erase(U &&value) { 
    auto it=find(value);
    if(it==cend())
        return;
    rbtree_delete(m_root,it.get());
}

template <class T,class Node> template <class U> typename rubbish::rbtree<T,Node>::iterator rubbish::rbtree<T,Node>::find(U &&data){
    auto ptr=m_root;
    while(ptr!=nullptr){
        if(ptr->data==data)
            break;
        if(ptr->data < data)
            ptr=ptr->right;
        else
            ptr=ptr->left;
    }
    return iterator(ptr);
}

template <class T,class Node> template <class U> typename rubbish::rbtree<T,Node>::const_iterator rubbish::rbtree<T,Node>::find(U &&data) const {return const_iterator(const_cast<self_type*>(this)->find(std::forward<U>(data)));}

template <class T,class Node> typename rubbish::rbtree<T,Node>::self_type& rubbish::rbtree<T,Node>::operator=(const self_type &o) {
    this->~rbtree();
    m_root=nullptr;
    base_class::copy_subtree(m_root,o.m_root);
    return *this;
}

template <class T,class Node> typename rubbish::rbtree<T,Node>::self_type& rubbish::rbtree<T,Node>::operator=(self_type &&o) {
    this->~rbtree();
    m_root=o.m_root;
    o.m_root=nullptr;
    return *this;
}

template <class T,class Node> typename rubbish::rbtree<T,Node>::iterator rubbish::rbtree<T,Node>::begin() { return base_class::inorder_begin();}

template <class T,class Node> typename rubbish::rbtree<T,Node>::iterator rubbish::rbtree<T,Node>::end() { return base_class::inorder_end();}

template <class T,class Node> typename rubbish::rbtree<T,Node>::const_iterator rubbish::rbtree<T,Node>::cbegin() const { return base_class::inorder_cbegin();}

template <class T,class Node> typename rubbish::rbtree<T,Node>::const_iterator rubbish::rbtree<T,Node>::cend() const { return base_class::inorder_cend();}
