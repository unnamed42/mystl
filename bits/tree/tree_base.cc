template <class T,class node> rubbish::tree_base<T,node>::tree_base(node *root):m_root(root) {}

template <class T,class node> rubbish::tree_base<T,node>::tree_base(const tree_base<T,node> &o) { copy_subtree(m_root,o.m_root); }

template <class T,class node> rubbish::tree_base<T,node>::tree_base(tree_base<T,node> &&o):m_root(o.m_root) { o.m_root=nullptr; }

template <class T,class node> rubbish::tree_base<T,node>::~tree_base() { delete_subtree(m_root); }

template <class T,class node> void rubbish::tree_base<T,node>::copy_subtree(node* &dest, const node *src) {
    if(src==nullptr){
        dest=nullptr;
        return;
    }
    if(dest!=nullptr)
        delete_subtree(dest);
    dest=new node(src->data);
    copy_subtree(dest->child,src->child);
    copy_subtree(dest->sibling,src->sibling);
}

template <class T,class node> void rubbish::tree_base<T,node>::delete_subtree(const node *root) {
    if(root==nullptr)
        return;
    delete_subtree(root->child);
    delete_subtree(root->sibling);
    delete root;
}

template <class T,class node> void rubbish::tree_base<T,node>::insert_child(const T &data) {
    if(m_root==nullptr){
        m_root=new node(data);
        return;
    }
    auto ptr=&m_root->child;
    while((*ptr)!=nullptr)
        ptr=&(*ptr)->sibling;
    *ptr=new node(data);
}

template <class T,class node> void rubbish::tree_base<T,node>::insert_parent(const T &data) {
    auto ptr=new node(data);
    ptr->child=m_root;
    m_root=ptr;
}


template <class T,class node> rubbish::tree_base<T,node>::iterator_base::iterator_base(node *root) {
    if(root==nullptr)
        return;
    m_cursor=std::make_shared<std::deque<node*> >(std::deque<node*>());
}

// Two iterators are equal iif they are both
// empty or their "next node"-s are equal
template <class T,class node> bool rubbish::tree_base<T,node>::iterator_base::operator==(const self_type &other) const {
    if(other.m_cursor==nullptr&&m_cursor==nullptr)
        return true;
    if(other.m_cursor==nullptr)
        return false;
    return true;
}

template <class T,class node> rubbish::tree_base<T,node>::preorder_iterator::preorder_iterator(node *root):base_class(root) {
    if(root!=nullptr)
        m_cursor->push_back(root);
}

template <class T,class node> typename rubbish::tree_base<T,node>::preorder_iterator::self_type& rubbish::tree_base<T,node>::preorder_iterator::operator++() {
    if(m_cursor==nullptr||m_cursor->empty()){
        m_cursor.reset();
        return *this;
    }
    auto ptr=m_cursor->back();
    m_cursor->pop_back();
    if(ptr->sibling!=nullptr)
        m_cursor->push_back(ptr->sibling);
    if(ptr->child!=nullptr)
        m_cursor->push_back(ptr->child);
    // Double check if the iteration comes to an end
    if(m_cursor->empty())
        m_cursor.reset();
    return *this;
}

template <class T,class node> rubbish::tree_base<T,node>::postorder_iterator::postorder_iterator(node *root):base_class(root) {
    if(root==nullptr)
        return;
    for(;;){
        m_cursor->push_back(root);
        if(root->child!=nullptr)
            root=root->child;
        else
            break;
    }
}

template <class T,class node> typename rubbish::tree_base<T,node>::postorder_iterator::self_type& rubbish::tree_base<T,node>::postorder_iterator::operator++() {
    if(m_cursor==nullptr||m_cursor->empty()){
        m_cursor.reset();
        return *this;
    }
    auto ptr=m_cursor->back();m_cursor->pop_back();
    if(m_cursor->empty()){
        m_cursor.reset();
        return *this;
    }
    auto stack_top = m_cursor->back(), tmp = stack_top->sibling;
    // TODO: find a better way to examine if `ptr` is `stack_top`'s child 
    if(ptr == stack_top->child && tmp != nullptr) {
        for(;;) {
            m_cursor->push_back(tmp);
            if(tmp->child != nullptr)
                tmp = tmp->child;
            else 
                break;
        }
    }
    // Double check if the iteration comes to an end
    if(m_cursor->empty())
        m_cursor.reset();
    return *this;
}

template <class T,class node> rubbish::tree_base<T,node>::level_iterator::level_iterator(node *root):base_class(root) {
    if(root!=nullptr)
        m_cursor->push_back(root);
}

template <class T,class node> typename rubbish::tree_base<T,node>::level_iterator::self_type& rubbish::tree_base<T,node>::level_iterator::operator++() {
    if(m_cursor==nullptr||m_cursor->empty()){
        m_cursor.reset();
        return *this;
    }
    auto ptr=m_cursor->front();
    m_cursor->pop_front();
    ptr=ptr->child;
    while(ptr!=nullptr){
        m_cursor->push_back(ptr);
        ptr=ptr->sibling;
    }
    // Double check if the iteration comes to an end
    if(m_cursor->empty())
        m_cursor.reset();
    return *this;
}
