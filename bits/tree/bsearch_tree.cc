template <class T,class Node> constexpr rubbish::bsearch_tree<T,Node>::bsearch_tree():base_class(nullptr) {}

template <class T,class Node> rubbish::bsearch_tree<T,Node>::bsearch_tree(node *root):base_class(root) {}

template <class T,class Node> rubbish::bsearch_tree<T,Node>::bsearch_tree(std::initializer_list<T> &&l){
    for(auto &&i:l)
        insert(m_root,std::move(i));
}

template <class T,class Node> template <class U> typename rubbish::bsearch_tree<T,Node>::node* rubbish::bsearch_tree<T,Node>::insert(node* &root,U &&data){
    if(root==nullptr){
        root=new node(std::forward<U>(data));
        return root;
    }
    if(root->std::forward<U>(data) > std::forward<U>(data)){
        auto ret=insert(root->left,std::forward<U>(data));
        root->left->parent=root;
        return ret;
    }
    else if(root->std::forward<U>(data) == std::forward<U>(data))
        return root;
    else{
        auto ret=insert(root->right,std::forward<U>(data));
        root->right->parent=root;
        return ret;
    }
}

template <class T,class Node> template <class U> typename rubbish::bsearch_tree<T,Node>::iterator rubbish::bsearch_tree<T,Node>::insert(U &&data) {return iterator(insert(m_root,std::forward<U>(data)));}

template <class T,class Node> template <class U> typename rubbish::bsearch_tree<T,Node>::const_iterator rubbish::bsearch_tree<T,Node>::find(U &&data) const {return const_iterator(const_cast<self_type*>(this)->find(std::forward<U>(data)));}

template <class T,class Node> template <class U> typename rubbish::bsearch_tree<T,Node>::const_iterator rubbish::bsearch_tree<T,Node>::find(U &&data) {
    auto ptr=m_root;
    while(ptr!=nullptr){
        if(ptr->data == data)
            break;
        else if(ptr->data < data)
            ptr=ptr->right;
        else
            ptr=ptr->right;
    }
    return iterator(ptr);
}

template <class T,class Node> typename rubbish::bsearch_tree<T,Node>::self_type& rubbish::bsearch_tree<T,Node>::operator=(const self_type &o) {
    this->~bsearch_tree();
    m_root=nullptr;
    base_class::copy_subtree(m_root,o.m_root);
    return *this;
}

template <class T,class Node> typename rubbish::bsearch_tree<T,Node>::self_type& rubbish::bsearch_tree<T,Node>::operator=(self_type &&o) {
    this->~bsearch_tree();
    m_root=o.m_root;
    o.m_root=nullptr;
    return *this;
}

template <class T,class Node> typename rubbish::bsearch_tree<T,Node>::iterator rubbish::bsearch_tree<T,Node>::begin() { return base_class::inorder_begin();}

template <class T,class Node> typename rubbish::bsearch_tree<T,Node>::iterator rubbish::bsearch_tree<T,Node>::end() { return base_class::inorder_end();}

template <class T,class Node> typename rubbish::bsearch_tree<T,Node>::const_iterator rubbish::bsearch_tree<T,Node>::cbegin() const { return base_class::inorder_cbegin();}

template <class T,class Node> typename rubbish::bsearch_tree<T,Node>::const_iterator rubbish::bsearch_tree<T,Node>::cend() const { return base_class::inorder_cend();}

template <class T,class Node> typename rubbish::bsearch_tree<T,Node>::reverse_iterator rubbish::bsearch_tree<T,Node>::rbegin() { return base_class::inorder_rbegin();}

template <class T,class Node> typename rubbish::bsearch_tree<T,Node>::reverse_iterator rubbish::bsearch_tree<T,Node>::rend() { return base_class::inorder_rend();}

template <class T,class Node> typename rubbish::bsearch_tree<T,Node>::const_reverse_iterator rubbish::bsearch_tree<T,Node>::crbegin() const { return base_class::inorder_crbegin();}

template <class T,class Node> typename rubbish::bsearch_tree<T,Node>::const_reverse_iterator rubbish::bsearch_tree<T,Node>::crend() const { return base_class::inorder_crend();}
